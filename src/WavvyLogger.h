/**********************************************************************

  Audacity: A Digital Audio Editor

  WavvyLogger.h

  Dominic Mazzoni

  This is the main source file for Wavvy which handles
  initialization and termination by subclassing wxApp.

**********************************************************************/

#ifndef __WAVVY_LOGGER__
#define __WAVVY_LOGGER__

#include "Wavvy.h"

#include "Experimental.h"

#include "MemoryX.h"
#include "Prefs.h"
#include <wx/log.h> // to inherit
#include <wx/event.h> // to inherit wxEvtHandler

class wxFrame;
class wxTextCtrl;

class WavvyLogger final : public wxEvtHandler,
                             public wxLog,
                             public PrefsListener
{
 public:
 
   // Get the singleton instance or null
   static WavvyLogger *Get();

   void Show(bool show = true);

   bool SaveLog(const wxString &fileName) const;
   bool ClearLog();

   wxString GetLog(int count = 0);

 protected:
   void Flush()  override;
   void DoLogText(const wxString & msg) override;

 private:
   WavvyLogger();

   void OnCloseWindow(wxCloseEvent & e);
   void OnClose(wxCommandEvent & e);
   void OnClear(wxCommandEvent & e);
   void OnSave(wxCommandEvent & e);

   // PrefsListener implementation
   void UpdatePrefs() override;

   Destroy_ptr<wxFrame> mFrame;
   wxTextCtrl *mText;
   wxString mBuffer;
   bool mUpdated;
};

#endif
