/**********************************************************************

Audacity: A Digital Audio Editor

ProjectWindowBase.h

Paul Licameli split from ProjectWindow.h

**********************************************************************/

#ifndef __WAVACITY_PROJECT_WINDOW_BASE__
#define __WAVACITY_PROJECT_WINDOW_BASE__

#include <wx/frame.h> // to inherit

class WavacityProject;

///\brief A top-level window associated with a project
class ProjectWindowBase /* not final */ : public wxFrame
{
public:
   explicit ProjectWindowBase(
      wxWindow * parent, wxWindowID id,
      const wxPoint & pos, const wxSize &size,
      WavacityProject &project );

   ~ProjectWindowBase() override;

   WavacityProject &GetProject() { return mProject; }
   const WavacityProject &GetProject() const { return mProject; }

protected:
   WavacityProject &mProject;
};

WavacityProject *FindProjectFromWindow( wxWindow *pWindow );
const WavacityProject *FindProjectFromWindow( const wxWindow *pWindow );

#endif

