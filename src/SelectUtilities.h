/**********************************************************************
 
 Audacity: A Digital Audio Editor
 
 SelectUtilities.h
 
 Paul Licameli split from SelectMenus.h
 
 **********************************************************************/

#ifndef __WAVVY_SELECT_UTILITIES__
#define __WAVVY_SELECT_UTILITIES__

class WavvyProject;
class Track;

/// Namespace for functions for Select menu
namespace SelectUtilities {

void DoSelectTimeAndTracks(
   WavvyProject &project, bool bAllTime, bool bAllTracks);
void SelectAllIfNone( WavvyProject &project );
bool SelectAllIfNoneAndAllowed( WavvyProject &project );
void SelectNone( WavvyProject &project );
void DoListSelection(
   WavvyProject &project, Track *t,
   bool shift, bool ctrl, bool modifyState );
void DoSelectAll( WavvyProject &project );
void DoSelectAllAudio( WavvyProject &project );
void DoSelectSomething( WavvyProject &project );

}

#endif
