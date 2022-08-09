/**********************************************************************

  Audacity: A Digital Audio Editor

  ActiveProjects.h

**********************************************************************/

#ifndef __WAVVY_ACTIVE_PROJECTS__
#define __WAVVY_ACTIVE_PROJECTS__

#include "Wavvy.h"
#include "wavvy/Types.h"

#include <wx/string.h>

namespace ActiveProjects
{
   FilePaths GetAll();
   void Add(const FilePath &path);
   void Remove(const FilePath &path);
   wxString Find(const FilePath &path);
};

#endif
