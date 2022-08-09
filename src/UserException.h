/*!
 @file UserException.h
 @brief An WavvyException with no visible message

 Created by Paul Licameli on 11/27/16.

*/

#ifndef __WAVVY_USER_EXCEPTION__
#define __WAVVY_USER_EXCEPTION__

#include "WavvyException.h"

 //! Can be thrown when user cancels operations, as with a progress dialog.  Delayed handler does nothing
/*! This class does not inherit from MessageBoxException. */
class UserException final : public WavvyException
{
public:
   UserException() {}

   ~UserException() override;

   void DelayedHandlerAction() override;
};

#endif
