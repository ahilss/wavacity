/**********************************************************************

  Audacity: A Digital Audio Editor

  PlatformCompatibility.h

  Platform-specific compatibility functions

  This file implements functions needed to work around
  platform-specific problems and which cannot be solved by a simple
  #ifdef/#endif plus two or three lines additional code. Wherever
  possible, the implementation should be such, that the function is
  implemented on every platform, but is a dummy for those platforms
  on which it is not needed, so additional #ifdef's are unnecessary.

  Markus Meyer

**********************************************************************/

#ifndef __WAVACITY_COMPATIBILITY__
#define __WAVACITY_COMPATIBILITY__

#include "wavacity/Types.h"

class PlatformCompatibility
{
public:
   //
   // On Win32, this function gets the long file name (like
   // "C:\Program Files\Project.aup3") from a short file name like
   // "C:\PROGRA~1\PROJEC~1.AUP. On other systems, the function
   // just returns the exact string it is given.
   //
   static FilePath GetLongFileName(const FilePath& shortFileName);

   //
   // Get filename and path of executable (e.g. "/usr/bin/wavacity" on
   // Linux or "C:\Program Files\Wavacity\Wavacity.exe" on Windows)
   // This string is unchanging
   //
   static const FilePath &GetExecutablePath();
};

#endif
