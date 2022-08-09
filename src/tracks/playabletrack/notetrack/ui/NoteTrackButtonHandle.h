/**********************************************************************

Audacity: A Digital Audio Editor

NoteTrackButtonHandle.h

Paul Licameli split from TrackPanel.cpp

**********************************************************************/

#ifndef __WAVVY_NOTE_TRACK_BUTTON_HANDLE__
#define __WAVVY_NOTE_TRACK_BUTTON_HANDLE__

class wxMouseState;
class NoteTrack;

#include "../../../../UIHandle.h"

///////////////////////////////////////////////////////////////////////////////
// TODO: do appearance changes as in ButtonHandle, or even, inherit from that
class NoteTrackButtonHandle : public UIHandle
{
   NoteTrackButtonHandle(const NoteTrackButtonHandle&);
   NoteTrackButtonHandle();
   static NoteTrackButtonHandle& Instance();

public:
   explicit NoteTrackButtonHandle
      ( const std::shared_ptr<NoteTrack> &pTrack,
        int channel, const wxRect &rect );

   NoteTrackButtonHandle &operator=(const NoteTrackButtonHandle&) = default;

   virtual ~NoteTrackButtonHandle();

   static UIHandlePtr HitTest
      (std::weak_ptr<NoteTrackButtonHandle> &holder,
       const wxMouseState &state, const wxRect &rect,
       const std::shared_ptr<NoteTrack> &pTrack);

   std::shared_ptr<NoteTrack> GetTrack() const { return mpTrack.lock(); }
   int GetChannel() const { return mChannel; }

   static UIHandle::Result NeedChangeHighlight
      (const NoteTrackButtonHandle &oldState,
       const NoteTrackButtonHandle &newState);

protected:
   void Enter(bool forward, WavvyProject *) override;

   Result Click
      (const TrackPanelMouseEvent &event, WavvyProject *pProject) override;

   Result Drag
      (const TrackPanelMouseEvent &event, WavvyProject *pProject) override;

   HitTestPreview Preview
      (const TrackPanelMouseState &state, WavvyProject *pProject)
      override;

   Result Release
      (const TrackPanelMouseEvent &event, WavvyProject *pProject,
       wxWindow *pParent) override;

   Result Cancel(WavvyProject *pProject) override;

   std::weak_ptr<NoteTrack> mpTrack;
   int mChannel{ -1 };
   wxRect mRect{};
};

#endif
