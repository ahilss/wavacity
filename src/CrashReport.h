/**********************************************************************
 
 Audacity: A Digital Audio Editor
 
 CrashReport.h
 
 Paul Licameli
 split from WavvyApp.h
 
 **********************************************************************/

#ifndef __WAVVY_CRASH_REPORT__
#define __WAVVY_CRASH_REPORT__

#include "Wavvy.h"
#include "Experimental.h"

#if defined(EXPERIMENTAL_CRASH_REPORT)

#include <wx/debugrpt.h>

namespace CrashReport
{
   void Generate(wxDebugReport::Context ctx);
}

#endif

#endif
