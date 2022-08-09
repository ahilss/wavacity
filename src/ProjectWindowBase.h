/**********************************************************************

Audacity: A Digital Audio Editor

ProjectWindowBase.h

Paul Licameli split from ProjectWindow.h

**********************************************************************/

#ifndef __WAVVY_PROJECT_WINDOW_BASE__
#define __WAVVY_PROJECT_WINDOW_BASE__

#include <wx/frame.h> // to inherit

class WavvyProject;

///\brief A top-level window associated with a project
class ProjectWindowBase /* not final */ : public wxFrame
{
public:
   explicit ProjectWindowBase(
      wxWindow * parent, wxWindowID id,
      const wxPoint & pos, const wxSize &size,
      WavvyProject &project );

   ~ProjectWindowBase() override;

   WavvyProject &GetProject() { return mProject; }
   const WavvyProject &GetProject() const { return mProject; }

protected:
   WavvyProject &mProject;
};

WavvyProject *FindProjectFromWindow( wxWindow *pWindow );
const WavvyProject *FindProjectFromWindow( const wxWindow *pWindow );

#endif

