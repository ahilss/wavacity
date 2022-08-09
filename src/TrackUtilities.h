/**********************************************************************
 
 Audacity: A Digital Audio Editor
 
 TrackUtilities.h
 
 Paul Licameli split from TrackMenus.h
 
 **********************************************************************/

#ifndef __WAVVY_TRACK_UTILITIES__
#define __WAVVY_TRACK_UTILITIES__

class WavvyProject;
class Track;

namespace TrackUtilities {

   enum MoveChoice {
      OnMoveUpID, OnMoveDownID, OnMoveTopID, OnMoveBottomID
   };
   /// Move a track up, down, to top or to bottom.
   void DoMoveTrack( WavvyProject &project, Track* target, MoveChoice choice );
   // "exclusive" mute means mute the chosen track and unmute all others.
   void DoTrackMute( WavvyProject &project, Track *pTrack, bool exclusive );
   // Type of solo (standard or simple) follows the set preference, unless
   // exclusive == true, which causes the opposite behavior.
   void DoTrackSolo( WavvyProject &project, Track *pTrack, bool exclusive );
   void DoRemoveTrack( WavvyProject &project, Track * toRemove );
   void DoRemoveTracks( WavvyProject & );

}

#endif
