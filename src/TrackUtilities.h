/**********************************************************************
 
 Audacity: A Digital Audio Editor
 
 TrackUtilities.h
 
 Paul Licameli split from TrackMenus.h
 
 **********************************************************************/

#ifndef __WAVACITY_TRACK_UTILITIES__
#define __WAVACITY_TRACK_UTILITIES__

class WavacityProject;
class Track;

namespace TrackUtilities {

   enum MoveChoice {
      OnMoveUpID, OnMoveDownID, OnMoveTopID, OnMoveBottomID
   };
   /// Move a track up, down, to top or to bottom.
   void DoMoveTrack( WavacityProject &project, Track* target, MoveChoice choice );
   // "exclusive" mute means mute the chosen track and unmute all others.
   void DoTrackMute( WavacityProject &project, Track *pTrack, bool exclusive );
   // Type of solo (standard or simple) follows the set preference, unless
   // exclusive == true, which causes the opposite behavior.
   void DoTrackSolo( WavacityProject &project, Track *pTrack, bool exclusive );
   void DoRemoveTrack( WavacityProject &project, Track * toRemove );
   void DoRemoveTracks( WavacityProject & );

}

#endif
