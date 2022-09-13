/**********************************************************************

  Audacity: A Digital Audio Editor

  WavacityMessageBox.h

  Paul Licameli split this out of ErrorDialog.h

**********************************************************************/

#ifndef __WAVACITY_MESSAGE_BOX__
#define __WAVACITY_MESSAGE_BOX__

#include <wx/msgdlg.h>
#include "../Internat.h"

extern TranslatableString WavacityMessageBoxCaptionStr();

// Do not use wxMessageBox!!  Its default window title does not translate!
inline int WavacityMessageBox(const TranslatableString& message,
   const TranslatableString& caption = WavacityMessageBoxCaptionStr(),
   long style = wxOK | wxCENTRE,
   wxWindow *parent = NULL,
   int x = wxDefaultCoord, int y = wxDefaultCoord)
{
   ::wxMessageBox(message.Translation(), caption.Translation(),
      style, parent, x, y);
   return wxID_CANCEL;
}

#endif
