/**********************************************************************

  Audacity: A Digital Audio Editor

  Clipboard.h

  Paul Licameli

**********************************************************************/

#ifndef __WAVVY_CLIPBOARD__
#define __WAVVY_CLIPBOARD__

#include "Wavvy.h"

#include <memory>
#include <wx/event.h> // to inherit wxEvtHandler

class WavvyProject;
class TrackList;

// An event emitted by the clipboard whenever its contents change.
wxDECLARE_EXPORTED_EVENT( WAVVY_DLL_API,
                          EVT_CLIPBOARD_CHANGE, wxCommandEvent );

class Clipboard final
   : public wxEvtHandler
{
public:
   static Clipboard &Get();

   const TrackList &GetTracks() const;

   double T0() const { return mT0; }
   double T1() const { return mT1; }
   double Duration() const { return mT1 - mT0; }

   const std::weak_ptr<WavvyProject> &Project() const { return mProject; }

   void Clear();
   
   void Assign(
     TrackList && newContents, double t0, double t1,
     const std::weak_ptr<WavvyProject> &pProject );

   Clipboard();
   ~Clipboard();

   void Swap( Clipboard &other );

private:

   std::shared_ptr<TrackList> mTracks;
   std::weak_ptr<WavvyProject> mProject{};
   double mT0{ 0 };
   double mT1{ 0 };
};

#endif
