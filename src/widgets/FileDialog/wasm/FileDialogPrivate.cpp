#include "Internat.h"
#include "widgets/WavacityMessageBox.h"
#include "../FileDialog.h"

#include "emscripten.h"

#include <wx/filename.h> // wxFilename
#include <wx/sizer.h>

//-----------------------------------------------------------------------------
// FileDialog
//-----------------------------------------------------------------------------

static FileDialog* g_file_dialog = NULL;

IMPLEMENT_DYNAMIC_CLASS(FileDialog,FileDialogBase)

BEGIN_EVENT_TABLE(FileDialog,FileDialogBase)
    EVT_SIZE(FileDialog::OnSize)
END_EVENT_TABLE()

FileDialog::FileDialog(wxWindow *parent, const wxString& message,
                           const wxString& defaultDir,
                           const wxString& defaultFileName,
                           const wxString& wildCard,
                           long style, const wxPoint& pos,
                           const wxSize& sz,
                           const wxString& name)
    : FileDialogBase(),
      m_filterIndex(0),
      m_callback(nullptr)
{
    Create(parent, message, defaultDir, defaultFileName, wildCard, style, pos, sz, name);
}

bool FileDialog::Create(wxWindow *parent, const wxString& message,
                           const wxString& defaultDir,
                           const wxString& defaultFileName,
                           const wxString& wildCard,
                           long style, const wxPoint& pos,
                           const wxSize& sz,
                           const wxString& name)
{
/*
    parent = GetParentForModalDialog(parent, style);

    if (!FileDialogBase::Create(parent, message, defaultDir, defaultFileName,
                                  wildCard, style, pos, sz, name))
    {
        return false;
    }
*/
    SetWildcard(wildCard);
    SetWindowStyle(style);

    return true;
}

FileDialog::~FileDialog()
{
}

int FileDialog::ShowModal()
{
   return 0;
}

void FileDialog::ShowModal(std::function<void (int)> callback)
{
   g_file_dialog = this;
   m_callback = callback;

   bool multiple = HasFdFlag(wxFD_MULTIPLE);
   // TODO(ahilss): pass accept file types

   EM_ASM({
      showFileDialog($0);
   }, multiple);
}

// Change the currently displayed extension
void FileDialog::SetFileExtension(const wxString& extension)
{
}

void FileDialog::DoSetSize(int WXUNUSED(x), int WXUNUSED(y),
                             int WXUNUSED(width), int WXUNUSED(height),
                             int WXUNUSED(sizeFlags))
{
}

void FileDialog::OnSize(wxSizeEvent&)
{
}

wxString FileDialog::GetPath() const
{
    return FileDialogBase::GetPath();
}

void FileDialog::GetFilenames(wxArrayString& files) const
{
    GetPaths(files);
}

void FileDialog::GetPaths(wxArrayString& paths) const
{
    paths.clear();
    paths.push_back(m_path);
}

void FileDialog::SetMessage(const wxString& message)
{
    m_message = message;
    SetTitle(message);
}

void FileDialog::SetPath(const wxString& path)
{
    FileDialogBase::SetPath(path);
}

void FileDialog::SetDirectory(const wxString& dir)
{
    FileDialogBase::SetDirectory(dir);
}

void FileDialog::SetFilename(const wxString& name)
{
    FileDialogBase::SetFilename(name);
}

wxString FileDialog::GetFilename() const
{
    return FileDialogBase::GetFilename();
}

void FileDialog::SetWildcard(const wxString& wildCard)
{
    FileDialogBase::SetWildcard(wildCard);
}

void FileDialog::SetFilterIndex(int filterIndex)
{
    m_filterIndex = filterIndex;
}

int FileDialog::GetFilterIndex() const
{
    return m_filterIndex;
}

void FileDialog::OnOpenFile(const wxString& fileName)
{
   if (m_callback)
   {
      m_path = fileName;
      m_callback(wxID_OK);
   }
}

void FileDialog::OnOpenFileFailed(const wxString& fileName)
{
    WavacityMessageBox(
    XO("Could not open file: %s").Format( fileName ),
    XO("Error Opening File"),
    wxOK | wxCENTRE,
    m_parent);
}

extern "C" {

void EMSCRIPTEN_KEEPALIVE OpenFileCallback(const char *fileName, int retCode) {
   if (g_file_dialog)
   {
      if (retCode == 0) {
         g_file_dialog->OnOpenFile(fileName);
      } else {
         g_file_dialog->OnOpenFileFailed(fileName);
      }

      g_file_dialog = NULL;
   }
}

}
