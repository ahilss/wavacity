/**********************************************************************

   Audacity - A Digital Audio Editor
   Copyright 1999-2009 Audacity Team
   File License: wxWidgets

   Dan Horgan

******************************************************************//**

\file CommandBuilder.h
\brief Contains declaration of CommandBuilder class.

*//*******************************************************************/

#ifndef __COMMANDBUILDER__
#define __COMMANDBUILDER__

#include "../MemoryX.h"

class WavvyProject;
class ResponseTarget;
using ResponseTargetPointer = std::shared_ptr<ResponseTarget>;
class OldStyleCommand;
using OldStyleCommandPointer = std::shared_ptr<OldStyleCommand>;
class wxString;

// CommandBuilder has the task of validating and interpreting a command string.
// If the string represents a valid command, it builds the command object.

class CommandBuilder
{
   private:
      bool mValid;
      ResponseTargetPointer mResponse;
      OldStyleCommandPointer mCommand;
      wxString mError;

      void Failure(const wxString &msg = {});
      void Success(const OldStyleCommandPointer &cmd);
      void BuildCommand( WavvyProject *project,
         const wxString &cmdName, const wxString &cmdParams);
      void BuildCommand( WavvyProject *project, const wxString &cmdString);
   public:
      CommandBuilder(WavvyProject *project, const wxString &cmdString);
      CommandBuilder(WavvyProject *project, const wxString &cmdName,
                     const wxString &cmdParams);
      ~CommandBuilder();
      bool WasValid();
      OldStyleCommandPointer GetCommand();
      wxString GetResponse();
};
#endif /* End of include guard: __COMMANDBUILDER__ */
