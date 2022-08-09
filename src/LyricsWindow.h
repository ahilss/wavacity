/**********************************************************************

  Audacity: A Digital Audio Editor

  LyricsWindow.h

  Vaughan Johnson
  Dominic Mazzoni

**********************************************************************/

#ifndef __WAVVY_LYRICS_WINDOW__
#define __WAVVY_LYRICS_WINDOW__

#include <wx/frame.h> // to inherit

#include "Prefs.h"

class WavvyProject;
class LyricsPanel;

class LyricsWindow final : public wxFrame,
                           public PrefsListener
{

 public:
   LyricsWindow(WavvyProject* parent);

   LyricsPanel *GetLyricsPanel() { return mLyricsPanel; };

 private:
   void OnCloseWindow(wxCloseEvent & WXUNUSED(event));

   void OnStyle_BouncingBall(wxCommandEvent &evt);
   void OnStyle_Highlight(wxCommandEvent &evt);
   void OnTimer(wxCommandEvent &event);

   void SetWindowTitle();

   // PrefsListener implementation
   void UpdatePrefs() override;

   WavvyProject *mProject;
   LyricsPanel *mLyricsPanel;

 public:
   DECLARE_EVENT_TABLE()
};

#endif
