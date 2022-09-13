/**********************************************************************
 
 Audacity: A Digital Audio Editor
 
 CrashReport.h
 
 Paul Licameli
 split from WavacityApp.h
 
 **********************************************************************/

#ifndef __WAVACITY_CRASH_REPORT__
#define __WAVACITY_CRASH_REPORT__

#include "Wavacity.h"
#include "Experimental.h"

#if defined(EXPERIMENTAL_CRASH_REPORT)

#include <wx/debugrpt.h>

namespace CrashReport
{
   void Generate(wxDebugReport::Context ctx);
}

#endif

#endif
