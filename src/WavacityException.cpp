/*!********************************************************************

  Audacity: A Digital Audio Editor

  @file WavacityException.cpp
  @brief Implements WavacityException and related

  Paul Licameli

***********************************************************************/

#include "Wavacity.h"
#include "WavacityException.h"

#include <wx/atomic.h>

#include "widgets/WavacityMessageBox.h"
#include "widgets/ErrorDialog.h"

WavacityException::~WavacityException()
{
}

wxAtomicInt sOutstandingMessages {};

MessageBoxException::MessageBoxException( const TranslatableString &caption_ )
   : caption{ caption_ }
{
   if (!caption.empty())
      wxAtomicInc( sOutstandingMessages );
   else
      // invalidate me
      moved = true;
}

// The class needs a copy constructor to be throwable
// (or will need it, by C++14 rules).  But the copy
// needs to act like a move constructor.  There must be unique responsibility
// for each exception thrown to decrease the global count when it is handled.
MessageBoxException::MessageBoxException( const MessageBoxException& that )
{
   caption = that.caption;
   moved = that.moved;
   helpUrl = that.helpUrl;
   that.moved = true;
}

MessageBoxException::~MessageBoxException()
{
   if (!moved)
      // If exceptions are used properly, you should never reach this,
      // because moved should become true earlier in the object's lifetime.
      wxAtomicDec( sOutstandingMessages );
}

SimpleMessageBoxException::~SimpleMessageBoxException()
{
}

TranslatableString SimpleMessageBoxException::ErrorMessage() const
{
   return message;
}

// This is meant to be invoked via wxEvtHandler::CallAfter
void MessageBoxException::DelayedHandlerAction()
{
   if (!moved) {
      // This test prevents accumulation of multiple messages between idle
      // times of the main even loop.  Only the last queued exception
      // displays its message.  We assume that multiple messages have a
      // common cause such as exhaustion of disk space so that the others
      // give the user no useful added information.
      
      if ( wxAtomicDec( sOutstandingMessages ) == 0 ) {
         if (ErrorHelpUrl().IsEmpty())
         {
            ::WavacityMessageBox(
               ErrorMessage(),
               (caption.empty() ? WavacityMessageBoxCaptionStr() : caption),
               wxICON_ERROR 
            );
         }
         else
         {
            ShowErrorDialog(
               nullptr,
               (caption.empty() ? WavacityMessageBoxCaptionStr() : caption),
               ErrorMessage(),
               ErrorHelpUrl());
         }
      }

      moved = true;
   }
}
