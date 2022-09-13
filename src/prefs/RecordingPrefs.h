/**********************************************************************

  Audacity: A Digital Audio Editor

  RecordingPrefs.h

  Joshua Haberman
  James Crook

**********************************************************************/

#ifndef __WAVACITY_RECORDING_PREFS__
#define __WAVACITY_RECORDING_PREFS__

#include "../Wavacity.h"
#include "../Experimental.h"

#include <wx/defs.h>

#include "PrefsPanel.h"

class wxTextCtrl;
class ShuttleGui;

#ifdef EXPERIMENTAL_AUTOMATED_INPUT_LEVEL_ADJUSTMENT
   #define AILA_DEF_TARGET_PEAK 92
   #define AILA_DEF_DELTA_PEAK 2
   #define AILA_DEF_ANALYSIS_TIME 1000
   #define AILA_DEF_NUMBER_ANALYSIS 5
#endif

#define RECORDING_PREFS_PLUGIN_SYMBOL ComponentInterfaceSymbol{ XO("Recording") }

#define DEFAULT_LATENCY_DURATION 100.0
#define DEFAULT_LATENCY_CORRECTION -130.0

#define AUDIO_PRE_ROLL_KEY (wxT("/AudioIO/PreRoll"))
#define DEFAULT_PRE_ROLL_SECONDS 5.0

#define AUDIO_ROLL_CROSSFADE_KEY (wxT("/AudioIO/Crossfade"))
#define DEFAULT_ROLL_CROSSFADE_MS 10.0

class RecordingPrefs final : public PrefsPanel
{
 public:
   RecordingPrefs(wxWindow * parent, wxWindowID winid);
   virtual ~RecordingPrefs();
   ComponentInterfaceSymbol GetSymbol() override;
   TranslatableString GetDescription() override;

   bool Commit() override;
   wxString HelpPageName() override;
   void PopulateOrExchange(ShuttleGui & S) override;

 private:
   void Populate();
   void OnToggleCustomName(wxCommandEvent & /* Evt */);

   wxTextCtrl *mToggleCustomName;
   bool mUseCustomTrackName;
   bool mOldNameChoice;

   DECLARE_EVENT_TABLE()
};

#endif
