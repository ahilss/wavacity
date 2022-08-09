/**********************************************************************

Audacity: A Digital Audio Editor

CutlineHandle.h

Paul Licameli

**********************************************************************/

#ifndef __WAVVY_CUTLINE_HANDLE__
#define __WAVVY_CUTLINE_HANDLE__

#include "../../../../UIHandle.h"
#include "../../../../WaveTrackLocation.h"

class wxMouseEvent;
class wxMouseState;
class WaveTrack;

class CutlineHandle final : public UIHandle
{
   CutlineHandle(const CutlineHandle&) = delete;
   static HitTestPreview HitPreview(bool cutline, bool unsafe);

public:
   explicit CutlineHandle
      ( const std::shared_ptr<WaveTrack> &pTrack,
        WaveTrackLocation location );

   CutlineHandle &operator=(const CutlineHandle&) = default;

   static UIHandlePtr HitAnywhere
      (const WavvyProject *pProject, bool cutline, UIHandlePtr ptr);
   static UIHandlePtr HitTest
      (std::weak_ptr<CutlineHandle> &holder,
       const wxMouseState &state, const wxRect &rect,
       const WavvyProject *pProject,
       const std::shared_ptr<WaveTrack> &pTrack);

   virtual ~CutlineHandle();

   const WaveTrackLocation &GetLocation() { return mLocation; }
   std::shared_ptr<WaveTrack> GetTrack() { return mpTrack; }

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

   bool StopsOnKeystroke() override { return true; }

private:
   std::shared_ptr<WaveTrack> mpTrack{};
   enum Operation { Merge, Expand, Remove };
   Operation mOperation{ Merge };
   double mStartTime{}, mEndTime{};
   WaveTrackLocation mLocation {};
};

#endif
