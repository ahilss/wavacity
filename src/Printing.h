/**********************************************************************

  Audacity: A Digital Audio Editor

  Printing.h

  Dominic Mazzoni

**********************************************************************/

#ifndef __WAVVY_PRINTING__
#define __WAVVY_PRINTING__

#include <wx/defs.h>

class wxString;
class wxWindow;
class TrackList;
class TrackPanel;

void HandlePageSetup(wxWindow *parent);
void HandlePrint(
   wxWindow *parent, const wxString &name, TrackList *tracks,
   TrackPanel &panel);

#endif // __WAVVY_PRINTING__

