/**********************************************************************

  Audacity: A Digital Audio Editor

  LoadNyquist.cpp

  Dominic Mazzoni

**********************************************************************/

#include "../../Wavacity.h"

#include "LoadNyquist.h"

#include <wx/log.h>

#include "Nyquist.h"

#include "../../FileNames.h"

// ============================================================================
// List of effects that ship with Wavacity.  These will be autoregistered.
// ============================================================================
const static wxChar *kShippedEffects[] =
{
   wxT("adjustable-fade.ny"),
   wxT("beat.ny"),
   wxT("clipfix.ny"),
   wxT("crossfadeclips.ny"),
   wxT("crossfadetracks.ny"),
   wxT("delay.ny"),
   wxT("equalabel.ny"),
   wxT("highpass.ny"),
   wxT("label-sounds.ny"),
   wxT("limiter.ny"),
   wxT("lowpass.ny"),
   wxT("noisegate.ny"),
   wxT("notch.ny"),
   wxT("nyquist-plug-in-installer.ny"),
   wxT("pluck.ny"),
   wxT("rhythmtrack.ny"),
   wxT("rissetdrum.ny"),
#ifdef __WXWASM__
   wxT("rms.ny"),
#endif
   wxT("sample-data-export.ny"),
   wxT("sample-data-import.ny"),
   wxT("spectral-delete.ny"),
   wxT("SpectralEditMulti.ny"),
   wxT("SpectralEditParametricEQ.ny"),
   wxT("SpectralEditShelves.ny"),
   wxT("StudioFadeOut.ny"),
   wxT("tremolo.ny"),
   wxT("vocalrediso.ny"),
   wxT("vocoder.ny"),
};

// ============================================================================
// Module registration entry point
//
// This is the symbol that Wavacity looks for when the module is built as a
// dynamic library.
//
// When the module is builtin to Wavacity, we use the same function, but it is
// declared static so as not to clash with other builtin modules.
// ============================================================================
DECLARE_MODULE_ENTRY(WavacityModule)
{
   // Create and register the importer
   // Trust the module manager not to leak this
   return safenew NyquistEffectsModule(path);
}

// ============================================================================
// Register this as a builtin module
// ============================================================================
DECLARE_BUILTIN_MODULE(NyquistsEffectBuiltin);

///////////////////////////////////////////////////////////////////////////////
//
// NyquistEffectsModule
//
///////////////////////////////////////////////////////////////////////////////

NyquistEffectsModule::NyquistEffectsModule(const wxString *path)
{
   if (path)
   {
      mPath = *path;
   }
}

NyquistEffectsModule::~NyquistEffectsModule()
{
   mPath.clear();
}

// ============================================================================
// ComponentInterface implementation
// ============================================================================

PluginPath NyquistEffectsModule::GetPath()
{
   return mPath;
}

ComponentInterfaceSymbol NyquistEffectsModule::GetSymbol()
{
   return XO("Nyquist Effects");
}

VendorSymbol NyquistEffectsModule::GetVendor()
{
   return XO("The Audacity Team");
}

wxString NyquistEffectsModule::GetVersion()
{
   // This "may" be different if this were to be maintained as a separate DLL
   return NYQUISTEFFECTS_VERSION;
}

TranslatableString NyquistEffectsModule::GetDescription()
{
   return XO("Provides Nyquist Effects support to Wavacity");
}

// ============================================================================
// ModuleInterface implementation
// ============================================================================

bool NyquistEffectsModule::Initialize()
{
   const auto &wavacityPathList = FileNames::WavacityPathList();

   for (size_t i = 0, cnt = wavacityPathList.size(); i < cnt; i++)
   {
      wxFileName name(wavacityPathList[i], wxT(""));
      name.AppendDir(wxT("nyquist"));
      name.SetFullName(wxT("nyquist.lsp"));
      if (name.FileExists())
      {
         // set_xlisp_path doesn't handle fn_Str() in Unicode build. May or may not actually work.
         nyx_set_xlisp_path(name.GetPath().ToUTF8());
         return true;
      }
   }

   wxLogWarning(wxT("Critical Nyquist files could not be found. Nyquist effects will not work."));

   return false;
}

void NyquistEffectsModule::Terminate()
{
   nyx_set_xlisp_path(NULL);

   return;
}

EffectFamilySymbol NyquistEffectsModule::GetOptionalFamilySymbol()
{
#if USE_NYQUIST
   return NYQUISTEFFECTS_FAMILY;
#else
   return {};
#endif
}

const FileExtensions &NyquistEffectsModule::GetFileExtensions()
{
   static FileExtensions result{{ _T("ny") }};
   return result;
}

FilePath NyquistEffectsModule::InstallPath()
{
   return FileNames::PlugInDir();
}

bool NyquistEffectsModule::AutoRegisterPlugins(PluginManagerInterface & pm)
{
   // Autoregister effects that we "think" are ones that have been shipped with
   // Wavacity.  A little simplistic, but it should suffice for now.
   auto pathList = NyquistEffect::GetNyquistSearchPath();
   FilePaths files;
   TranslatableString ignoredErrMsg;

   if (!pm.IsPluginRegistered(NYQUIST_PROMPT_ID))
   {
      // No checking of error ?
      DiscoverPluginsAtPath(NYQUIST_PROMPT_ID, ignoredErrMsg,
         PluginManagerInterface::DefaultRegistrationCallback);
   }

   for (size_t i = 0; i < WXSIZEOF(kShippedEffects); i++)
   {
      files.clear();
      pm.FindFilesInPathList(kShippedEffects[i], pathList, files);
      for (size_t j = 0, cnt = files.size(); j < cnt; j++)
      {
         if (!pm.IsPluginRegistered(files[j]))
         {
            // No checking of error ?
            DiscoverPluginsAtPath(files[j], ignoredErrMsg,
               PluginManagerInterface::DefaultRegistrationCallback);
         }
      }
   }

   // We still want to be called during the normal registration process
   return false;
}

PluginPaths NyquistEffectsModule::FindPluginPaths(PluginManagerInterface & pm)
{
   auto pathList = NyquistEffect::GetNyquistSearchPath();
   FilePaths files;

   // Add the Nyquist prompt
   files.push_back(NYQUIST_PROMPT_ID);

   // Load .ny plug-ins
   pm.FindFilesInPathList(wxT("*.ny"), pathList, files);
   // LLL:  Works for all platform with NEW plugin support (dups are removed)
   pm.FindFilesInPathList(wxT("*.NY"), pathList, files); // Ed's fix for bug 179

   return { files.begin(), files.end() };
}

unsigned NyquistEffectsModule::DiscoverPluginsAtPath(
   const PluginPath & path, TranslatableString &errMsg,
   const RegistrationCallback &callback)
{
   errMsg = {};
   NyquistEffect effect(path);
   if (effect.IsOk())
   {
      if (callback)
         callback(this, &effect);
      return 1;
   }

   errMsg = effect.InitializationError();
   return 0;
}

bool NyquistEffectsModule::IsPluginValid(const PluginPath & path, bool bFast)
{
   // Ignores bFast parameter, since checking file exists is fast enough for
   // the small number of Nyquist plug-ins that we have.
   static_cast<void>(bFast);
   if(path == NYQUIST_PROMPT_ID)
      return true;

   return wxFileName::FileExists(path);
}

ComponentInterface *NyquistEffectsModule::CreateInstance(const PluginPath & path)
{
   // Acquires a resource for the application.
   auto effect = std::make_unique<NyquistEffect>(path);
   if (effect->IsOk())
   {
      // Safety of this depends on complementary calls to DeleteInstance on the module manager side.
      return effect.release();
   }

   return NULL;
}

void NyquistEffectsModule::DeleteInstance(ComponentInterface *instance)
{
   std::unique_ptr < NyquistEffect > {
      dynamic_cast<NyquistEffect *>(instance)
   };
}

// ============================================================================
// NyquistEffectsModule implementation
// ============================================================================

void RegisterNyquistEffects() {}
