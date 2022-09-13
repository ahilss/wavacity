/**********************************************************************

  Audacity: A Digital Audio Editor

  CommandManagerWindowClasses.h

  Paul Licameli

**********************************************************************/

#ifndef __WAVACITY_COMMAND_MANAGER_WINDOW_CLASSES__
#define __WAVACITY_COMMAND_MANAGER_WINDOW_CLASSES__

/*
 \brief By default, windows when focused override the association of the digits
 and certain navigation keys with commands, but certain windows do not, and
 those inherit this class.
 */
struct WAVACITY_DLL_API NonKeystrokeInterceptingWindow
{
   virtual ~NonKeystrokeInterceptingWindow();
};

/*
 \brief Top-level windows that do redirect keystrokes to the associated
 project's CommandManager inherit this class.
*/
struct TopLevelKeystrokeHandlingWindow
{
   virtual ~TopLevelKeystrokeHandlingWindow();
};

#endif
