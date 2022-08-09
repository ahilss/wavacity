#ifndef _WASM_FILEDIALOGPRIVATE_H_
#define _WASM_FILEDIALOGPRIVATE_H_

#include <wx/generic/filectrlg.h>
#include <wx/panel.h>

//-------------------------------------------------------------------------
// FileDialog
//-------------------------------------------------------------------------

class WXDLLIMPEXP_CORE FileDialog: public FileDialogBase
{
public:
    FileDialog() { }

    FileDialog(wxWindow *parent,
               const wxString& message = wxFileSelectorPromptStr,
               const wxString& defaultDir = wxEmptyString,
               const wxString& defaultFile = wxEmptyString,
               const wxString& wildCard = wxFileSelectorDefaultWildcardStr,
               long style = wxFD_DEFAULT_STYLE,
               const wxPoint& pos = wxDefaultPosition,
               const wxSize& sz = wxDefaultSize,
               const wxString& name = wxFileDialogNameStr);
    bool Create(wxWindow *parent,
                const wxString& message = wxFileSelectorPromptStr,
                const wxString& defaultDir = wxEmptyString,
                const wxString& defaultFile = wxEmptyString,
                const wxString& wildCard = wxFileSelectorDefaultWildcardStr,
                long style = wxFD_DEFAULT_STYLE,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& sz = wxDefaultSize,
                const wxString& name = wxFileDialogNameStr);
    virtual ~FileDialog();

    virtual wxString GetPath() const;
    virtual void GetPaths(wxArrayString& paths) const;
    virtual wxString GetFilename() const;
    virtual void GetFilenames(wxArrayString& files) const;
    virtual int GetFilterIndex() const;

    virtual void SetMessage(const wxString& message);
    virtual void SetPath(const wxString& path);
    virtual void SetDirectory(const wxString& dir);
    virtual void SetFilename(const wxString& name);
    virtual void SetWildcard(const wxString& wildCard);
    virtual void SetFilterIndex(int filterIndex);

    virtual int ShowModal();
    virtual void ShowModal(std::function<void (int)> callback);

    virtual bool SupportsExtraControl() const { return true; }

    virtual void SetFileExtension(const wxString& extension);

    void OnOpenFile(const wxString& filename);
    void OnOpenFileFailed(const wxString& filename);

protected:
    // override this from wxTLW since the native
    // form doesn't have any m_wxwindow
    virtual void DoSetSize(int x, int y,
                           int width, int height,
                           int sizeFlags = wxSIZE_AUTO);


private:
    void OnSize(wxSizeEvent&);

    wxArrayString m_filterNames;
    int m_filterIndex;
    std::function<void (int)> m_callback;

    DECLARE_DYNAMIC_CLASS(FileDialog)
    DECLARE_EVENT_TABLE()
};

#endif
