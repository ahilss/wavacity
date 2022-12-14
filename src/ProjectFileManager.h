/**********************************************************************

Audacity: A Digital Audio Editor

ProjectFileManager.h

Paul Licameli split from WavacityProject.h

**********************************************************************/

#ifndef __WAVACITY_PROJECT_FILE_MANAGER__
#define __WAVACITY_PROJECT_FILE_MANAGER__

#include <memory>
#include <vector>

#include "ClientData.h" // to inherit
#include "FileNames.h" // for FileType

class wxString;
class wxFileName;
class WavacityProject;
class Track;
class TrackList;
class WaveTrack;
class XMLTagHandler;

using WaveTrackArray = std::vector < std::shared_ptr < WaveTrack > >;
using TrackHolders = std::vector< WaveTrackArray >;

class ProjectFileManager final
   : public ClientData::Base
{
public:
   static ProjectFileManager &Get( WavacityProject &project );
   static const ProjectFileManager &Get( const WavacityProject &project );

   // Open and close a file, invisibly, removing its Autosave blob
   static void DiscardAutosave(const FilePath &filename);

   explicit ProjectFileManager( WavacityProject &project );
   ProjectFileManager( const ProjectFileManager & ) PROHIBITED;
   ProjectFileManager &operator=( const ProjectFileManager & ) PROHIBITED;
   ~ProjectFileManager();

   struct ReadProjectResults
   {
      bool parseSuccess;
      bool trackError;
      const TranslatableString errorString;
      wxString helpUrl;
   };
   ReadProjectResults ReadProjectFile(
      const FilePath &fileName, bool discardAutosave = false );

   bool OpenProject();
   void CloseProject();
   bool OpenNewProject();

   void CompactProjectOnClose();

   bool Save();
   bool SaveAs(bool allowOverwrite = false);
   bool SaveAs(const FilePath &newFileName, bool addToHistory = true);
   // strProjectPathName is full path for aup except extension
   bool SaveFromTimerRecording( wxFileName fnFile );
   bool SaveCopy(const FilePath &fileName = wxT(""));

   /** @brief Show an open dialogue for opening audio files, and possibly other
    * sorts of files.
    *
    * The file type filter will automatically contain:
    * - "All files" with any extension or none,
    * - "All supported files" based on the file formats supported in this
    *   build of Wavacity,
    * - All of the individual formats specified by the importer plug-ins which
    *   are built into this build of Wavacity, each with the relevant file
    *   extensions for that format.
    * The dialogue will start in the DefaultOpenPath directory read from the
    * preferences, failing that the working directory. The file format filter
    * will be set to the DefaultOpenType from the preferences, failing that
    * the first format specified in the dialogue. These two parameters will
    * be saved to the preferences once the user has chosen a file to open.
    * @param extraType Specify an additional format to allow opening in this
    * dialogue.
    * @return Array of file paths which the user selected to open (multiple
    * selections allowed).
    */
   static void ShowOpenDialog(FileNames::Operation op,
      const FileNames::FileType &extraType = {},
      std::function<void (const wxArrayString&)> callback = nullptr);

   static bool IsAlreadyOpen(const FilePath &projPathName);

   void OpenFile(const FilePath &fileName, bool addtohistory = true);

   bool Import(const FilePath &fileName,
               bool addToHistory = true);

   void Compact();

   void AddImportedTracks(const FilePath &fileName,
                     TrackHolders &&newTracks);

   bool GetMenuClose() const { return mMenuClose; }
   void SetMenuClose(bool value) { mMenuClose = value; }

private:
   bool DoSave(const FilePath & fileName, bool fromSaveAs);

   WavacityProject &mProject;

   std::shared_ptr<TrackList> mLastSavedTracks;
   
   // Are we currently closing as the result of a menu command?
   bool mMenuClose{ false };
};

#endif
