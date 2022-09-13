/**********************************************************************

  Audacity: A Digital Audio Editor

  LangChoice.h

  Dominic Mazzoni

  Pop up a language asking the user to choose a (natural)
  language for the user interface.  Generally only popped
  up once, the first time the program is run.

**********************************************************************/

#ifndef __WAVACITY_LANG_CHOICE__
#define __WAVACITY_LANG_CHOICE__

class wxString;

wxString ChooseLanguage(wxWindow *parent);

#endif // __WAVACITY_LANG_CHOICE__
