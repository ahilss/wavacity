/**********************************************************************

Audacity: A Digital Audio Editor

SliderHandle.h

Paul Licameli

**********************************************************************/

#ifndef __WAVACITY_SLIDER_HANDLE__
#define __WAVACITY_SLIDER_HANDLE__

#include "../../UIHandle.h"

class wxMouseEvent;
class LWSlider;
class Track;
class TranslatableString;

class SliderHandle /* not final */ : public UIHandle
{
   SliderHandle(const SliderHandle&) = delete;

public:
   using SliderFn = LWSlider *(*)( WavacityProject*, const wxRect&, Track* );

   explicit SliderHandle
      ( SliderFn sliderFn, const wxRect &rect,
        const std::shared_ptr<Track> &pTrack );

   SliderHandle &operator=(const SliderHandle&) = default;

   std::shared_ptr<Track> GetTrack() const { return mpTrack.lock(); }
   bool IsClicked() const { return mIsClicked; }

protected:
   virtual ~SliderHandle();

   // These NEW abstract virtuals simplify the duties of further subclasses.
   // This class will decide whether to refresh the clicked cell for slider state
   // change.
   // Subclass can decide to refresh other things and the results will be ORed.
   virtual float GetValue() = 0;
   virtual Result SetValue(WavacityProject *pProject, float newValue) = 0;
   virtual Result CommitChanges
      (const wxMouseEvent &event, WavacityProject *pProject) = 0;

   // Define a message for the status bar and tooltip.
   virtual TranslatableString Tip(
      const wxMouseState &state, WavacityProject &project) const = 0;
 
   void Enter(bool forward, WavacityProject *) override;

   Result Click
      (const TrackPanelMouseEvent &event, WavacityProject *pProject)
      final override;

   Result Drag
      (const TrackPanelMouseEvent &event, WavacityProject *pProject)
      final override;

   HitTestPreview Preview
      (const TrackPanelMouseState &state, WavacityProject *pProject)
      final override;

   Result Release
      (const TrackPanelMouseEvent &event, WavacityProject *pProject,
       wxWindow *pParent) final override;

   Result Cancel(WavacityProject *pProject) final override;

   // Derived class is expected to set these two before Click():
   std::weak_ptr<Track> mpTrack;
   wxRect mRect{};
   SliderFn mSliderFn;
   LWSlider *GetSlider( WavacityProject *pProject );

   float mStartingValue {};

   bool mIsClicked{};
};

#endif
