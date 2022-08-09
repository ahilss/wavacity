/**********************************************************************
 
 Audacity: A Digital Audio Editor
 
 TempDirectory.h
 
 Paul Licameli split from FileNames.h
 
 **********************************************************************/

#ifndef __WAVVY_TEMP_DIRECTORY__
#define __WAVVY_TEMP_DIRECTORY__

#include "Wavvy.h"
#include "wavvy/Types.h"

namespace TempDirectory
{
   wxString TempDir();
   void ResetTempDir();

   const FilePath &DefaultTempDir();
   void SetDefaultTempDir( const FilePath &tempDir );
   bool IsTempDirectoryNameOK( const FilePath & Name );

   // Create a filename for an unsaved/temporary project file
   wxString UnsavedProjectFileName();

   bool FATFilesystemDenied(const FilePath &path,
                            const TranslatableString &msg,
                            wxWindow *window = nullptr);

};

#endif
