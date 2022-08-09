/**********************************************************************

  Audacity: A Digital Audio Editor

  Screenshot.h

  Dominic Mazzoni

*******************************************************************//**

\file Screenshot.h

  Opens a modeless dialog that aids in rearranging the project window
  to a canonical size and state and then capturing full and partial
  screenshots to disk.

*//*******************************************************************/

#ifndef __WAVVY_SCREENSHOT__
#define __WAVVY_SCREENSHOT__

#include "Wavvy.h"

#include <wx/defs.h>

class WavvyProject;

void OpenScreenshotTools( WavvyProject &project );
void CloseScreenshotTools();

#endif // __WAVVY_SCREENSHOT__
