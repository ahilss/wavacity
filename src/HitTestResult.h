/**********************************************************************

Audacity: A Digital Audio Editor

HitTestResult.h

Paul Licameli

**********************************************************************/

#ifndef __WAVVY_HIT_TEST_RESULT__
#define __WAVVY_HIT_TEST_RESULT__

#include "MemoryX.h"
#include "Internat.h" // for TranslatableString

class wxCursor;

struct HitTestPreview
{
   HitTestPreview()
   {}

   HitTestPreview(const TranslatableString &message_, wxCursor *cursor_,
      const TranslatableString &tooltip_ = {})
      : message{ message_ }, cursor{ cursor_ }, tooltip{ tooltip_ }
   {}

   TranslatableString message {};
   wxCursor *cursor {};
   TranslatableString tooltip{};
};

#endif
