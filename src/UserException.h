/*!
 @file UserException.h
 @brief An WavacityException with no visible message

 Created by Paul Licameli on 11/27/16.

*/

#ifndef __WAVACITY_USER_EXCEPTION__
#define __WAVACITY_USER_EXCEPTION__

#include "WavacityException.h"

 //! Can be thrown when user cancels operations, as with a progress dialog.  Delayed handler does nothing
/*! This class does not inherit from MessageBoxException. */
class UserException final : public WavacityException
{
public:
   UserException() {}

   ~UserException() override;

   void DelayedHandlerAction() override;
};

#endif
