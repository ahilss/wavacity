/**********************************************************************

  Audacity: A Digital Audio Editor

  ActiveProjects.h

**********************************************************************/

#ifndef __WAVACITY_ACTIVE_PROJECTS__
#define __WAVACITY_ACTIVE_PROJECTS__

#include "Wavacity.h"
#include "wavacity/Types.h"

#include <wx/string.h>

namespace ActiveProjects
{
   FilePaths GetAll();
   void Add(const FilePath &path);
   void Remove(const FilePath &path);
   wxString Find(const FilePath &path);
};

#endif
