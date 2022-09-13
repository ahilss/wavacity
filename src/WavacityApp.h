/**********************************************************************

  Audacity: A Digital Audio Editor

  WavacityApp.h

  Dominic Mazzoni

  This is the main source file for Wavacity which handles
  initialization and termination by subclassing wxApp.

**********************************************************************/

#ifndef __WAVACITY_APP__
#define __WAVACITY_APP__

#include "Wavacity.h"
#include "wavacity/Types.h"

#include "Experimental.h"

#include <wx/app.h> // to inherit
#include <wx/timer.h> // member variable

#if defined(EXPERIMENTAL_CRASH_REPORT)
#include <wx/debugrpt.h> // for wxDebugReport::Context
#endif

#include "MemoryX.h"

class wxSingleInstanceChecker;
class wxSocketEvent;
class wxSocketServer;

class IPCServ;
class Importer;
class CommandHandler;
class AppCommandEvent;
class WavacityProject;

class WavacityApp final : public wxApp {
 public:
   WavacityApp();
   ~WavacityApp();
   bool OnInit(void) override;
   bool InitPart2();
   int OnExit(void) override;
   void OnFatalException() override;
   bool OnExceptionInMainLoop() override;

   // These are currently only used on Mac OS, where it's
   // possible to have a menu bar but no windows open.  It doesn't
   // hurt any other platforms, though.
   void OnMenuAbout(wxCommandEvent & event);
   void OnMenuNew(wxCommandEvent & event);
   void OnMenuOpen(wxCommandEvent & event);
   void OnMenuPreferences(wxCommandEvent & event);
   void OnMenuExit(wxCommandEvent & event);

   void OnQueryEndSession(wxCloseEvent & event);
   void OnEndSession(wxCloseEvent & event);

   // Most Recently Used File support (for all platforms).
   void OnMRUClear(wxCommandEvent &event);
   void OnMRUFile(wxCommandEvent &event);
   // Backend for above - returns true for success, false for failure
   bool MRUOpen(const FilePath &fileName);
   // A wrapper of the above that does not throw
   bool SafeMRUOpen(const wxString &fileName);

   void OnReceiveCommand(AppCommandEvent &event);

   void OnKeyDown(wxKeyEvent &event);

   void OnTimer(wxTimerEvent & event);

   // IPC communication
   void OnServerEvent(wxSocketEvent & evt);
   void OnSocketEvent(wxSocketEvent & evt);

   #ifdef __WXMAC__
    // In response to Apple Events
    void MacOpenFile(const wxString &fileName)  override;
    void MacPrintFile(const wxString &fileName)  override;
    void MacNewFile()  override;
   #endif

   #if defined(__WXMSW__) && !defined(__WXUNIVERSAL__) && !defined(__CYGWIN__)
    void AssociateFileTypes();
   #endif

#ifdef __WXMAC__

   void MacActivateApp();
   void MacFinishLaunching();

#endif


 private:
   std::unique_ptr<CommandHandler> mCmdHandler;

   std::unique_ptr<wxSingleInstanceChecker> mChecker;

   wxTimer mTimer;

   void InitCommandHandler();

   bool InitTempDir();
   bool CreateSingleInstanceChecker(const wxString &dir);

   std::unique_ptr<wxCmdLineParser> ParseCommandLine();

#if defined(__WXMSW__)
   std::unique_ptr<IPCServ> mIPCServ;
#elif !defined(__WXWASM__)
   std::unique_ptr<wxSocketServer> mIPCServ;
#endif

 public:
    DECLARE_EVENT_TABLE()
};

extern WavacityApp & wxGetApp();

void RegisterAll();

void RegisterSampleBlock();
void RegisterSelectionState();

void RegisterClipMenu();
void RegisterEditMenu();
void RegisterExtraMenu();
void RegisterFileMenu();
void RegisterHelpMenu();
void RegisterLabelMenu();
void RegisterNavigationMenu();
void RegisterPluginMenu();
void RegisterSelectMenu();
void RegisterToolbarMenu();
void RegisterTrackMenu();
void RegisterTransportMenu();
void RegisterViewMenu();
void RegisterHistoryMenuItem();
void RegisterLyricsMenuItem();
void RegisterMixerBoardMenuItem();
void RegisterMenus();

void RegisterLabelTrackControls();
void RegisterDeviceToolBar();
void RegisterEditToolBar();
void RegisterMeterToolBar();
void RegisterMixerToolBar();
void RegisterScrubbingToolBar();
void RegisterSelectionToolBar();
void RegisterSpectralSelectionToolBar();
void RegisterTimeToolBar();
void RegisterToolsToolBar();
void RegisterTransportToolBar();
void RegisterTranscriptionToolBar();
void RegisterToolBars();

void RegisterAUPImportPlugin();
void RegisterFFmpegImportPlugin();
void RegisterFLACImportPlugin();
void RegisterLOFImportPlugin();
void RegisterMP3ImportPlugin();
void RegisterOGGImportPlugin();
void RegisterPCMImportPlugin();
void RegisterImportPlugins();

void RegisterFFmpegExportPlugin();
void RegisterFLACExportPlugin();
void RegisterMP3ExportPlugin();
void RegisterOGGExportPlugin();
void RegisterPCMExportPlugin();
void RegisterExportPlugins();

void RegisterAmplifyEffect();
void RegisterAutoDuckEffect();
void RegisterBassTrebleEffect();
void RegisterClassicFiltersEffect();
void RegisterChangePitchEffect();
void RegisterChangeSpeedEffect();
void RegisterChangeTempoEffect();
void RegisterClickRemovalEffect();
void RegisterCompressorEffect();
void RegisterContrastEffect();
void RegisterDistortionEffect();
void RegisterDtmfEffect();
void RegisterEchoEffect();
void RegisterEqualizationEffect();
void RegisterFadeEffect();
void RegisterFindClippingEffect();
void RegisterInvertEffect();
void RegisterLoudnessEffect();
void RegisterNoiseEffect();
void RegisterNoiseReductionEffect();
void RegisterNormalizeEffect();
void RegisterPaulstretchEffect();
void RegisterPhaserEffect();
void RegisterPlotSpectrumEffect();
void RegisterRepairEffect();
void RegisterRepeatEffect();
void RegisterReverbEffect();
void RegisterReverseEffect();
void RegisterSilenceEffect();
void RegisterToneGenEffect();
void RegisterTruncSilenceEffect();
void RegisterWahwahEffect();
void RegisterNyquistEffects();
void RegisterEffects();

void RegisterLabelTrackShifter();
void RegisterLabelTrackView();
void RegisterNoteTrackControls();
void RegisterNoteTrackView();
void RegisterNoteTrackShifter();
void RegisterTimeTrackControls();
void RegisterTimeTrackView();
void RegisterWaveTrackView();
void RegisterWaveformView();
void RegisterSpectrumView();
void RegisterWaveTrackControls();
void RegisterWaveTrackShifter();

void RegisterBackgroundCell();
void RegisterEditCursorOverlay();
void RegisterScrubber();
void RegisterScrubbingOverlay();
void RegisterPlayIndicatorOverlay();
void RegisterTrackControls();
void RegisterTrackShifter();
void RegisterTrackView();
void RegisterViews();

void RegisterDevicePrefs();
void RegisterMousePrefs();
void RegisterRecorderPrefs();
void RegisterWarningPrefs();
void RegisterExtImportPrefs();
void RegisterPrefs();

void InjectSampleBlockFactoryFactory();

#endif
