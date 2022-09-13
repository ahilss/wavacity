/**********************************************************************
 
 Audacity: A Digital Audio Editor
 
 SelectUtilities.h
 
 Paul Licameli split from SelectMenus.h
 
 **********************************************************************/

#ifndef __WAVACITY_SELECT_UTILITIES__
#define __WAVACITY_SELECT_UTILITIES__

class WavacityProject;
class Track;

/// Namespace for functions for Select menu
namespace SelectUtilities {

void DoSelectTimeAndTracks(
   WavacityProject &project, bool bAllTime, bool bAllTracks);
void SelectAllIfNone( WavacityProject &project );
bool SelectAllIfNoneAndAllowed( WavacityProject &project );
void SelectNone( WavacityProject &project );
void DoListSelection(
   WavacityProject &project, Track *t,
   bool shift, bool ctrl, bool modifyState );
void DoSelectAll( WavacityProject &project );
void DoSelectAllAudio( WavacityProject &project );
void DoSelectSomething( WavacityProject &project );

}

#endif
