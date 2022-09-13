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

#ifndef __WAVACITY_SCREENSHOT__
#define __WAVACITY_SCREENSHOT__

#include "Wavacity.h"

#include <wx/defs.h>

class WavacityProject;

void OpenScreenshotTools( WavacityProject &project );
void CloseScreenshotTools();

#endif // __WAVACITY_SCREENSHOT__
