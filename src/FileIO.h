/**********************************************************************

  Audacity: A Digital Audio Editor

  FileIO.h

  Leland Lucius

**********************************************************************/

#ifndef __WAVVY_FILEIO__
#define __WAVVY_FILEIO__

#include "MemoryX.h"

class wxInputStream;
class wxOutputStream;
class wxFFileOutputStream;
class wxFileNameWrapper;

class FileIO
{
 public:
   typedef enum FileIOMode
   {
      Input,
      Output
   } FileIOMode;

 public:
   FileIO(const wxFileNameWrapper & name, FileIOMode mode);

   // Calls Close()
   ~FileIO();

   bool IsOpened();

   bool Close();

   wxInputStream & Read(void *buffer, size_t size);
   wxOutputStream & Write(const void *buffer, size_t size);

 private:
   FileIOMode mMode;
   std::unique_ptr<wxInputStream> mInputStream;
   std::unique_ptr<wxFFileOutputStream> mOutputStream;
   bool mOpen;
};

#endif
