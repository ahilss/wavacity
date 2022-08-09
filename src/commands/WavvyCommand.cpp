/**********************************************************************

  Audacity: A Digital Audio Editor

  WavvyCommand.cpp

  James Crook

*******************************************************************//**

\class WavvyCommand
\brief Base class for command in Wavvy.

*//****************************************************************//**

\class WavvyCommandDialog
\brief Default dialog used for commands.  Is populated using 
ShuttleGui.

*//*******************************************************************/

#include "../Wavvy.h"
#include "WavvyCommand.h"

#include "CommandContext.h"

#include <algorithm>

#include <wx/defs.h>
#include <wx/sizer.h>
#include <wx/stockitem.h>
#include <wx/string.h>
#include <wx/tglbtn.h>
#include <wx/timer.h>
#include <wx/utils.h>
#include <wx/log.h>

#include "wavvy/ConfigInterface.h"

#include "../Shuttle.h"
#include "../ShuttleGui.h"
#include "../widgets/ProgressDialog.h"
#include "../widgets/HelpSystem.h"
#include "../widgets/WavvyMessageBox.h"

#include <unordered_map>

namespace {

WavvyCommand::VetoDialogHook &GetVetoDialogHook()
{
   static WavvyCommand::VetoDialogHook sHook = nullptr;
   return sHook;
}

}

auto WavvyCommand::SetVetoDialogHook( VetoDialogHook hook )
   -> VetoDialogHook
{
   auto &theHook = GetVetoDialogHook();
   auto result = theHook;
   theHook = hook;
   return result;
}

WavvyCommand::WavvyCommand()
{
   mProgress = NULL;
   mUIParent = NULL;
   mUIDialog = NULL;
   mUIDebug = false;
   mIsBatch = false;
   mNeedsInit = true;
}

WavvyCommand::~WavvyCommand()
{
   if (mUIDialog)
      mUIDialog->Close();
}


PluginPath WavvyCommand::GetPath(){        return BUILTIN_GENERIC_COMMAND_PREFIX + GetSymbol().Internal(); }
VendorSymbol WavvyCommand::GetVendor(){      return XO("Wavvy");}
wxString WavvyCommand::GetVersion(){     return WAVVY_VERSION_STRING;}


bool WavvyCommand::Init(){
   if( !mNeedsInit )
      return true;
   mNeedsInit = false;
   ShuttleDefaults DefaultSettingShuttle;
   return DefineParams( DefaultSettingShuttle );
}

bool WavvyCommand::ShowInterface(wxWindow *parent, bool WXUNUSED(forceModal), std::function<void (bool)> callback)
{
   if (mUIDialog)
   {
      if ( mUIDialog->Close(true) )
         mUIDialog = nullptr;
      return false;
   }

   // mUIDialog is null
   auto cleanup = valueRestorer( mUIDialog );
   
   mUIDialog = CreateUI(parent, this);
   if (!mUIDialog)
      return false;

   mUIDialog->Layout();
   mUIDialog->Fit();
   mUIDialog->SetMinSize(mUIDialog->GetSize());

   // The Screenshot command might be popping this dialog up, just to capture it.
   auto hook = GetVetoDialogHook();
   if( hook && hook( mUIDialog ) )
      return false;

   mUIDialog->ShowModal([callback](int retCode) {
      if (callback) {
        callback(retCode != 0);
      }
   });
   return true;
}

wxDialog *WavvyCommand::CreateUI(wxWindow *parent, WavvyCommand * WXUNUSED(client))
{
   Destroy_ptr<WavvyCommandDialog> dlg { safenew WavvyCommandDialog{
      parent, GetName(), this}};

   if (dlg->Init())
   {
      // release() is safe because parent will own it
      return dlg.release();
   }
   return NULL;
}

bool WavvyCommand::GetAutomationParameters(wxString & parms)
{
   CommandParameters eap;

   if (mUIDialog && !TransferDataFromWindow())
   {
      return false;
   }

   ShuttleGetAutomation S;
   S.mpEap = &eap;
   bool bResult = DefineParams( S );
   wxASSERT_MSG( bResult, "You did not define DefineParameters() for this command" );
   static_cast<void>(bResult); // fix unused variable warning in release mode

   return eap.GetParameters(parms);
}

bool WavvyCommand::SetAutomationParameters(const wxString & parms)
{
   wxString preset = parms;

   CommandParameters eap(parms);
   ShuttleSetAutomation S;

   S.SetForWriting( &eap );
   bool bResult = DefineParams( S );
   wxASSERT_MSG( bResult, "You did not define DefineParameters() for this command" );
   static_cast<void>(bResult); // fix unused variable warning in release mode
   if (!S.bOK)
   {
      WavvyCommand::MessageBox(
         XO(
"%s: Could not load settings below. Default settings will be used.\n\n%s")
            .Format( GetName(), preset ) );

      // fror now always succeed, so that we can prompt the user.
      return true;
   }

   return TransferDataToWindow();
}

bool WavvyCommand::DoWavvyCommand(wxWindow *parent,
                      const CommandContext & context,
                      bool shouldPrompt /* = true */)
{
   // Note: Init may read parameters from preferences
   if (!Init())
   {
      return false;
   }

   // Prompting will be bypassed when applying a command that has already 
   // been configured, e.g. repeating the last effect on a different selection.
   // Prompting may call WavvyCommand::Preview
   if (shouldPrompt && /*IsInteractive() && */!PromptUser(parent))
   {
      return false;
   }

   auto cleanup = finally( [&] {
      End();
   } );

   bool returnVal = true;
   bool skipFlag = CheckWhetherSkipWavvyCommand();
   if (skipFlag == false)
   {
      auto name = GetName();
      ProgressDialog progress{
         name,
         XO("Applying %s...").Format( name ),
         pdlgHideStopButton
      };
      auto vr = valueRestorer( mProgress, &progress );

      returnVal = Apply(context);
   }
   return returnVal;
}

// This is used from Macros.
bool WavvyCommand::PromptUser(wxWindow *parent, std::function<void (bool)> callback)
{
   return ShowInterface(parent, IsBatchProcessing(), callback);
}

bool WavvyCommand::TransferDataToWindow()
{
   if (mUIParent && !mUIParent->TransferDataToWindow())
      return false;
   return true;
}

bool WavvyCommand::TransferDataFromWindow()
{
   if (mUIParent && (!mUIParent->Validate() || !mUIParent->TransferDataFromWindow()))
      return false;
   return true;
}

int WavvyCommand::MessageBox(
   const TranslatableString& message, long style,
   const TranslatableString &titleStr)
{
   auto title = titleStr.empty()
      ? GetName()
      : XO("%s: %s").Format( GetName(), titleStr );
   return WavvyMessageBox(message, title, style, mUIParent);
}

BEGIN_EVENT_TABLE(WavvyCommandDialog, wxDialogWrapper)
   EVT_BUTTON(wxID_OK, WavvyCommandDialog::OnOk)
   EVT_BUTTON(wxID_HELP, WavvyCommandDialog::OnHelp)
   EVT_BUTTON(wxID_CANCEL, WavvyCommandDialog::OnCancel)
END_EVENT_TABLE()

WavvyCommandDialog::WavvyCommandDialog(wxWindow * parent,
                           const TranslatableString & title,
                           WavvyCommand * pCommand,
                           int type,
                           int flags,
                           int additionalButtons)
: wxDialogWrapper(parent, wxID_ANY, title, wxDefaultPosition, wxDefaultSize, flags)
{
   mType = type;
   wxASSERT( pCommand );
   mpCommand = pCommand;
   mAdditionalButtons = additionalButtons |eCancelButton;
   if( !pCommand->ManualPage().empty() )
      mAdditionalButtons |= eHelpButton;
}

bool WavvyCommandDialog::Init()
{
   ShuttleGui S(this, eIsCreating);

   S.SetBorder(5);
   S.StartVerticalLay(true);
   {
      PopulateOrExchange(S);

      long buttons = eOkButton;
      S.AddStandardButtons(buttons|mAdditionalButtons);
   }
   S.EndVerticalLay();

   Layout();
   Fit();
   SetMinSize(GetSize());
   Center();
   return true;
}

/// This is a virtual function which will be overridden to
/// provide the actual parameters that we want for each
/// kind of dialog.
void WavvyCommandDialog::PopulateOrExchange(ShuttleGui & S)
{
   wxASSERT( mpCommand );
   mpCommand->PopulateOrExchange( S );
}

bool WavvyCommandDialog::TransferDataToWindow()
{
   ShuttleGui S(this, eIsSettingToDialog);
   PopulateOrExchange(S);
   return true;
}

bool WavvyCommandDialog::TransferDataFromWindow()
{
   ShuttleGui S(this, eIsGettingFromDialog);
   PopulateOrExchange(S);
   return true;
}

bool WavvyCommandDialog::Validate()
{
   return true;
}

void WavvyCommandDialog::OnOk(wxCommandEvent & WXUNUSED(evt))
{
   // On wxGTK (wx2.8.12), the default action is still executed even if
   // the button is disabled.  This appears to affect all wxDialogs, not
   // just our WavvyCommands dialogs.  So, this is a only temporary workaround
   // for legacy effects that disable the OK button.  Hopefully this has
   // been corrected in wx3.
   if (FindWindow(wxID_OK)->IsEnabled() && Validate() && TransferDataFromWindow())
   {
      EndModal(true);
   }
}


void WavvyCommandDialog::OnCancel(wxCommandEvent & WXUNUSED(evt))
{
   EndModal(false);
}

void WavvyCommandDialog::OnHelp(wxCommandEvent & WXUNUSED(event))
{
   if( mpCommand )
   {
      // otherwise use ShowHelp
      HelpSystem::ShowHelp(FindWindow(wxID_HELP), mpCommand->ManualPage(), true);
   }
}


