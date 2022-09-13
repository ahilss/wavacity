/**********************************************************************

Audacity: A Digital Audio Editor

NoteTrackButtonHandle.h

Paul Licameli split from TrackPanel.cpp

**********************************************************************/

#ifndef __WAVACITY_NOTE_TRACK_BUTTON_HANDLE__
#define __WAVACITY_NOTE_TRACK_BUTTON_HANDLE__

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
   void Enter(bool forward, WavacityProject *) override;

   Result Click
      (const TrackPanelMouseEvent &event, WavacityProject *pProject) override;

   Result Drag
      (const TrackPanelMouseEvent &event, WavacityProject *pProject) override;

   HitTestPreview Preview
      (const TrackPanelMouseState &state, WavacityProject *pProject)
      override;

   Result Release
      (const TrackPanelMouseEvent &event, WavacityProject *pProject,
       wxWindow *pParent) override;

   Result Cancel(WavacityProject *pProject) override;

   std::weak_ptr<NoteTrack> mpTrack;
   int mChannel{ -1 };
   wxRect mRect{};
};

#endif
