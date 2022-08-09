/**********************************************************************

Audacity: A Digital Audio Editor

WavvyFileConfig.cpp

Paul Licameli split from Prefs.cpp

**********************************************************************/

#include "Wavvy.h"
#include "WavvyFileConfig.h"

#include "widgets/HelpSystem.h"
#include "widgets/wxPanelWrapper.h"
#include "ShuttleGui.h"
#include "../images/Help.xpm"

#include <wx/app.h>
#include <wx/bmpbuttn.h>
#include <wx/sizer.h>

WavvyFileConfig::WavvyFileConfig(
   const wxString& appName,
   const wxString& vendorName,
   const wxString& localFilename,
   const wxString& globalFilename,
   long style,
   const wxMBConv& conv
)
: FileConfig{ appName, vendorName, localFilename, globalFilename, style, conv }
{}

WavvyFileConfig::~WavvyFileConfig() = default;

std::unique_ptr<WavvyFileConfig> WavvyFileConfig::Create(
   const wxString& appName,
   const wxString& vendorName,
   const wxString& localFilename,
   const wxString& globalFilename,
   long style,
   const wxMBConv& conv
)
{
   // Private ctor means make_unique can't compile, so this verbosity:
   auto result = std::unique_ptr<WavvyFileConfig>{
      safenew WavvyFileConfig{
         appName, vendorName, localFilename, globalFilename, style, conv } };
   result->Init();
   return result;
}

void WavvyFileConfig::Warn()
{
   wxDialogWrapper dlg(nullptr, wxID_ANY, XO("Wavvy Configuration Error"));

   ShuttleGui S(&dlg, eIsCreating);

   wxButton *retryButton;
   wxButton *quitButton;

   S.SetBorder(5);
   S.StartVerticalLay(wxEXPAND, 1);
   {
      S.SetBorder(15);
      S.StartHorizontalLay(wxALIGN_RIGHT, 0);
      {
         S.AddFixedText(
            XO("The following configuration file could not be accessed:\n\n"
               "\t%s\n\n"
               "This could be caused by many reasons, but the most likely are that "
               "the disk is full or you do not have write permissions to the file. "
               "More information can be obtained by clicking the help button below.\n\n"
               "You can attempt to correct the issue and then click \"Retry\" to continue.\n\n"
               "If you choose to \"Quit Wavvy\", your project may be left in an unsaved "
               "state which will be recovered the next time you open it.")
            .Format(GetFilePath()),
            false,
            500);
      }
      S.EndHorizontalLay();

      S.SetBorder(5);
      S.StartHorizontalLay(wxALIGN_RIGHT, 0);
      {
         // Can't use themed bitmap since the theme manager might not be
         // initialized yet and it requires a configuration file.
         wxButton *b = S.Id(wxID_HELP).AddBitmapButton(wxBitmap(Help_xpm));
         b->SetToolTip( XO("Help").Translation() );
         b->SetLabel(XO("Help").Translation());       // for screen readers

         b = S.Id(wxID_CANCEL).AddButton(XXO("&Quit Wavvy"));
         b = S.Id(wxID_OK).AddButton(XXO("&Retry"));
         dlg.SetAffirmativeId(wxID_OK);

         b->SetDefault();
         b->SetFocus();
      }
      S.EndHorizontalLay();
   }
   S.EndVerticalLay();

   dlg.Layout();
   dlg.GetSizer()->Fit(&dlg);
   dlg.SetMinSize(dlg.GetSize());
   dlg.Center();

   auto onButton = [&](wxCommandEvent &e)
   {
      dlg.EndModal(e.GetId());
   };

   dlg.Bind(wxEVT_BUTTON, onButton);

   switch (dlg.ShowModal())
   {
      case wxID_HELP:
         // Can't use the HelpSystem since the theme manager may not
         // yet be initialized and it requires a configuration file.
         OpenInDefaultBrowser("https://" +
                              HelpSystem::HelpHostname +
                              HelpSystem::HelpServerHomeDir +
                              "Error:_Wavvy_settings_file_unwritable");
      break;

      case wxID_CANCEL:
         _exit(-1);
      break;
   }

   dlg.Unbind(wxEVT_BUTTON, onButton);
}
