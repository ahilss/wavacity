/**********************************************************************

Audacity: A Digital Audio Editor

WaveTrackVZoomHandle.h

Paul Licameli split from TrackPanel.cpp

**********************************************************************/

#ifndef __WAVACITY_WAVE_TRACK_VZOOM_HANDLE__
#define __WAVACITY_WAVE_TRACK_VZOOM_HANDLE__

class wxMouseState;
class PopupMenuTable;
class WaveTrack;
#include "WaveTrackViewConstants.h"
#include "../../../../UIHandle.h"
#include "../../../../Prefs.h"

namespace WaveTrackVZoomHandle
{
   // See RefreshCode.h for bit flags:
   using Result = unsigned;

   HitTestPreview HitPreview(const wxMouseState &state);

   bool IsDragZooming(int zoomStart, int zoomEnd);

   using DoZoomFunction = void (*)( WavacityProject *pProject,
       WaveTrack *pTrack,
       WaveTrackViewConstants::ZoomActions ZoomKind,
       const wxRect &rect, int zoomStart, int zoomEnd,
       bool fixedMousePoint);

   Result DoDrag(
      const TrackPanelMouseEvent &event, WavacityProject *pProject,
      int zoomStart, int &zoomEnd );

   Result DoRelease(
      const TrackPanelMouseEvent &event, WavacityProject *pProject,
      wxWindow *pParent, WaveTrack *pTrack, const wxRect &mRect,
      DoZoomFunction doZoom, PopupMenuTable &table,
      int zoomStart, int zoomEnd );

   void DoDraw(
      TrackPanelDrawingContext &context,
      const wxRect &rect, unsigned iPass, int zoomStart, int zoomEnd );

   wxRect DoDrawingArea(
      const wxRect &rect, const wxRect &panelRect, unsigned iPass );
};

#include "../../../../widgets/PopupMenuTable.h" // to inherit

class WaveTrackVRulerMenuTable
   : public PopupMenuTable
   , private PrefsListener
{
public:
   struct InitMenuData
   {
   public:
      WavacityProject &project;
      WaveTrack *pTrack;
      wxRect rect;
      unsigned result;
      int yy;
      WaveTrackVZoomHandle::DoZoomFunction doZoom;
   };

protected:
   WaveTrackVRulerMenuTable( const Identifier &id )
      : PopupMenuTable{ id }
   {}

   void InitUserData(void *pUserData) override;

private:
   void DestroyMenu() override
   {
      mpData = nullptr;
   }

protected:
   InitMenuData *mpData {};

   void OnZoom( WaveTrackViewConstants::ZoomActions iZoomCode );
   void OnZoomFitVertical(wxCommandEvent&)
      { OnZoom( WaveTrackViewConstants::kZoom1to1 );};
   void OnZoomReset(wxCommandEvent&)
      { OnZoom( WaveTrackViewConstants::kZoomReset );};
   void OnZoomDiv2Vertical(wxCommandEvent&)
      { OnZoom( WaveTrackViewConstants::kZoomDiv2 );};
   void OnZoomTimes2Vertical(wxCommandEvent&)
      { OnZoom( WaveTrackViewConstants::kZoomTimes2 );};
   void OnZoomHalfWave(wxCommandEvent&)
      { OnZoom( WaveTrackViewConstants::kZoomHalfWave );};
   void OnZoomInVertical(wxCommandEvent&)
      { OnZoom( WaveTrackViewConstants::kZoomIn );};
   void OnZoomOutVertical(wxCommandEvent&)
      { OnZoom( WaveTrackViewConstants::kZoomOut );};

   void UpdatePrefs() override;
};

enum {
   OnZoomFitVerticalID = 20000,
   OnZoomResetID,
   OnZoomDiv2ID,
   OnZoomTimes2ID,
   OnZoomHalfWaveID,
   OnZoomInVerticalID,
   OnZoomOutVerticalID,

   // Reserve an ample block of ids for waveform scale types
   OnFirstWaveformScaleID,
   OnLastWaveformScaleID = OnFirstWaveformScaleID + 9,

   // Reserve an ample block of ids for spectrum scale types
   OnFirstSpectrumScaleID,
   OnLastSpectrumScaleID = OnFirstSpectrumScaleID + 19,
};

#endif
