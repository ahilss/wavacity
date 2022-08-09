/**********************************************************************

  Audacity: A Digital Audio Editor

  WavvyMessageBox.h

  Paul Licameli split this out of ErrorDialog.h

**********************************************************************/

#ifndef __WAVVY_MESSAGE_BOX__
#define __WAVVY_MESSAGE_BOX__

#include <wx/msgdlg.h>
#include "../Internat.h"

extern TranslatableString WavvyMessageBoxCaptionStr();

// Do not use wxMessageBox!!  Its default window title does not translate!
inline int WavvyMessageBox(const TranslatableString& message,
   const TranslatableString& caption = WavvyMessageBoxCaptionStr(),
   long style = wxOK | wxCENTRE,
   wxWindow *parent = NULL,
   int x = wxDefaultCoord, int y = wxDefaultCoord)
{
   ::wxMessageBox(message.Translation(), caption.Translation(),
      style, parent, x, y);
   return wxID_CANCEL;
}

#endif
