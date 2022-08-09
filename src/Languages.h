/**********************************************************************

  Audacity: A Digital Audio Editor

  Languages.h

  Dominic Mazzoni

**********************************************************************/

#ifndef __WAVVY_LANGUAGES__
#define __WAVVY_LANGUAGES__

class wxArrayString;
class wxString;

#include "wavvy/Types.h"

void GetLanguages(
   wxArrayString &langCodes, TranslatableStrings &langNames);

wxString GetSystemLanguageCode();

#endif // __WAVVY_LANGUAGES__
