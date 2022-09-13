/**********************************************************************

Audacity: A Digital Audio Editor

EnvelopeHandle.h

Paul Licameli split from TrackPanel.cpp

**********************************************************************/

#ifndef __WAVACITY_ENVELOPE_HANDLE__
#define __WAVACITY_ENVELOPE_HANDLE__

#include "../../UIHandle.h"

#include <vector>

class wxMouseEvent;
class wxMouseState;

class Envelope;
class EnvelopeEditor;
class ViewInfo;
class TimeTrack;
class WaveTrack;

class EnvelopeHandle final : public UIHandle
{
   EnvelopeHandle(const EnvelopeHandle&) = delete;
   EnvelopeHandle &operator=(const EnvelopeHandle&) = delete;

   static UIHandlePtr HitEnvelope
      (std::weak_ptr<EnvelopeHandle> &holder,
       const wxMouseState &state, const wxRect &rect,
       const WavacityProject *pProject,
       Envelope *envelope, float zoomMin, float zoomMax,
       bool dB, float dBRange, bool timeTrack);

public:
   explicit EnvelopeHandle( Envelope *pEnvelope );

   virtual ~EnvelopeHandle();

   static UIHandlePtr HitAnywhere
      (std::weak_ptr<EnvelopeHandle> &holder, Envelope *envelope,
       bool timeTrack);
   static UIHandlePtr TimeTrackHitTest
      (std::weak_ptr<EnvelopeHandle> &holder,
       const wxMouseState &state, const wxRect &rect,
       const WavacityProject *pProject, const std::shared_ptr<TimeTrack> &tt);
   static UIHandlePtr WaveTrackHitTest
      (std::weak_ptr<EnvelopeHandle> &holder,
       const wxMouseState &state, const wxRect &rect,
       const WavacityProject *pProject, const std::shared_ptr<WaveTrack> &wt);

   Envelope *GetEnvelope() const { return mEnvelope; }

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

   bool StopsOnKeystroke() override { return true; }

private:
   bool ForwardEventToEnvelopes
      (const wxMouseEvent &event, const ViewInfo &viewInfo);

   wxRect mRect{};
   bool mLog{};
   float mLower{}, mUpper{};
   double mdBRange{};

   Envelope *mEnvelope{};
   std::vector< std::unique_ptr<EnvelopeEditor> > mEnvelopeEditors;

   bool mTimeTrack{};
};

#endif
