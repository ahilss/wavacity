/**********************************************************************

  Audacity: A Digital Audio Editor

  Clipboard.h

  Paul Licameli

**********************************************************************/

#ifndef __WAVACITY_CLIPBOARD__
#define __WAVACITY_CLIPBOARD__

#include "Wavacity.h"

#include <memory>
#include <wx/event.h> // to inherit wxEvtHandler

class WavacityProject;
class TrackList;

// An event emitted by the clipboard whenever its contents change.
wxDECLARE_EXPORTED_EVENT( WAVACITY_DLL_API,
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

   const std::weak_ptr<WavacityProject> &Project() const { return mProject; }

   void Clear();
   
   void Assign(
     TrackList && newContents, double t0, double t1,
     const std::weak_ptr<WavacityProject> &pProject );

   Clipboard();
   ~Clipboard();

   void Swap( Clipboard &other );

private:

   std::shared_ptr<TrackList> mTracks;
   std::weak_ptr<WavacityProject> mProject{};
   double mT0{ 0 };
   double mT1{ 0 };
};

#endif
