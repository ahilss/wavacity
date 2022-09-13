/**********************************************************************

Audacity: A Digital Audio Editor

ButtonHandle.h

Paul Licameli

**********************************************************************/

#ifndef __WAVACITY_BUTTON_HANDLE__
#define __WAVACITY_BUTTON_HANDLE__

#include "../../UIHandle.h"

class wxMouseEvent;
class wxMouseState;

class Track;
class TranslatableString;


/// \brief A UIHandle for a TrackPanel button, such as the Mute and Solo 
/// buttons.
class ButtonHandle /* not final */ : public UIHandle
{
   ButtonHandle(const ButtonHandle&) = delete;

public:
   std::shared_ptr<Track> GetTrack() const { return mpTrack.lock(); }
   bool IsClicked() const { return mIsClicked; }

protected:
   explicit ButtonHandle
      ( const std::shared_ptr<Track> &pTrack, const wxRect &rect );

   ButtonHandle &operator=(const ButtonHandle&) = default;

   virtual ~ButtonHandle();

   // This NEW abstract virtual simplifies the duties of further subclasses.
   // This class will decide whether to refresh the clicked cell for button state
   // change.
   // Subclass can decide to refresh other things and the results will be ORed.
   virtual Result CommitChanges
      (const wxMouseEvent &event, WavacityProject *pProject, wxWindow *pParent) = 0;

   // Define a message for the status bar and tooltip.
   virtual TranslatableString Tip(
      const wxMouseState &state, WavacityProject &project) const = 0;

   void Enter(bool forward, WavacityProject *) final override;

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

   std::weak_ptr<Track> mpTrack;
   wxRect mRect;
   bool mWasIn{ true };
   bool mIsClicked{};
};

#endif
