/**********************************************************************

  Audacity: A Digital Audio Editor

  Languages.h

  Dominic Mazzoni

**********************************************************************/

#ifndef __WAVACITY_LANGUAGES__
#define __WAVACITY_LANGUAGES__

class wxArrayString;
class wxString;

#include "wavacity/Types.h"

void GetLanguages(
   wxArrayString &langCodes, TranslatableStrings &langNames);

wxString GetSystemLanguageCode();

#endif // __WAVACITY_LANGUAGES__
