/**********************************************************************

Audacity: A Digital Audio Editor

NoteTrackVRulerControls.h

Paul Licameli split from TrackPanel.cpp

**********************************************************************/

#ifndef __WAVVY_NOTE_TRACK_VRULER_CONTROLS__
#define __WAVVY_NOTE_TRACK_VRULER_CONTROLS__

#include "../../../ui/TrackVRulerControls.h"

class NoteTrackVZoomHandle;

class NoteTrackVRulerControls final : public TrackVRulerControls
{
   NoteTrackVRulerControls(const NoteTrackVRulerControls&) = delete;
   NoteTrackVRulerControls &operator=(const NoteTrackVRulerControls&) = delete;

public:
   explicit
   NoteTrackVRulerControls( const std::shared_ptr<TrackView> &pTrackView )
      : TrackVRulerControls( pTrackView ) {}
   ~NoteTrackVRulerControls();

   std::vector<UIHandlePtr> HitTest
      (const TrackPanelMouseState &state,
       const WavvyProject *pProject) override;

   unsigned HandleWheelRotation
      (const TrackPanelMouseEvent &event,
       WavvyProject *pProject) override;

private:
   // TrackPanelDrawable implementation
   void Draw(
      TrackPanelDrawingContext &context,
      const wxRect &rect, unsigned iPass ) override;

   // TrackVRulerControls implementation
   void UpdateRuler( const wxRect &rect ) override;

   std::weak_ptr<NoteTrackVZoomHandle> mVZoomHandle;
};

#endif
