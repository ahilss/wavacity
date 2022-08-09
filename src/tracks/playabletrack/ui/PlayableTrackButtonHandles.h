/**********************************************************************

Audacity: A Digital Audio Editor

PlayableTrackButtonHandles.h

Paul Licameli split from TrackPanel.cpp

**********************************************************************/

#ifndef __WAVVY_PLAYABLE_TRACK_BUTTON_HANDLES__
#define __WAVVY_PLAYABLE_TRACK_BUTTON_HANDLES__

#include "../../ui/ButtonHandle.h"
class wxMouseState;

class MuteButtonHandle final : public ButtonHandle
{
   MuteButtonHandle(const MuteButtonHandle&) = delete;

public:
   explicit MuteButtonHandle
      ( const std::shared_ptr<Track> &pTrack, const wxRect &rect );

   MuteButtonHandle &operator=(const MuteButtonHandle&) = default;

   virtual ~MuteButtonHandle();

protected:
   Result CommitChanges
      (const wxMouseEvent &event, WavvyProject *pProject, wxWindow *pParent)
      override;

   TranslatableString Tip(
      const wxMouseState &state, WavvyProject &) const override;

   bool StopsOnKeystroke () override { return true; }

public:
   static UIHandlePtr HitTest
      (std::weak_ptr<MuteButtonHandle> &holder,
       const wxMouseState &state, const wxRect &rect,
       const WavvyProject *pProject, const std::shared_ptr<Track> &pTrack);
};

////////////////////////////////////////////////////////////////////////////////

class SoloButtonHandle final : public ButtonHandle
{
   SoloButtonHandle(const SoloButtonHandle&) = delete;

public:
   explicit SoloButtonHandle
      ( const std::shared_ptr<Track> &pTrack, const wxRect &rect );

   SoloButtonHandle &operator=(const SoloButtonHandle&) = default;

   virtual ~SoloButtonHandle();

protected:
   Result CommitChanges
      (const wxMouseEvent &event, WavvyProject *pProject, wxWindow *pParent)
      override;

   TranslatableString Tip(
      const wxMouseState &state, WavvyProject &) const override;

   bool StopsOnKeystroke () override { return true; }

public:
   static UIHandlePtr HitTest
      (std::weak_ptr<SoloButtonHandle> &holder,
       const wxMouseState &state, const wxRect &rect,
       const WavvyProject *pProject, const std::shared_ptr<Track> &pTrack);
};

#endif
