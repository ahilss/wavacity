/**********************************************************************

   Audacity - A Digital Audio Editor
   Copyright 1999-2018 Audacity Team
   File License: wxWidgets

   Stephen Parry
   James Crook

******************************************************************//**

\file OpenSaveCommands.cpp
\brief Contains definitions for the OpenProjectCommand and SaveProjectCommand classes

*//*******************************************************************/

#include "../Wavvy.h"
#include "OpenSaveCommands.h"

#include "LoadCommands.h"
#include "../WavvyLogger.h"
#include "../Project.h"
#include "../ProjectFileIO.h"
#include "../ProjectFileManager.h"
#include "../ProjectManager.h"
#include "../export/Export.h"
#include "../Shuttle.h"
#include "../ShuttleGui.h"
#include "CommandContext.h"


const ComponentInterfaceSymbol OpenProjectCommand::Symbol
{ XO("Open Project2") };

namespace{ BuiltinCommandsModule::Registration< OpenProjectCommand > reg; }

bool OpenProjectCommand::DefineParams( ShuttleParams & S ){
   S.Define( mFileName, wxT("Filename"),  "test.aup3" );
   S.OptionalN(bHasAddToHistory).Define( mbAddToHistory, wxT("AddToHistory"),  false );
   return true;
}

void OpenProjectCommand::PopulateOrExchange(ShuttleGui & S)
{
   S.AddSpace(0, 5);

   S.StartMultiColumn(2, wxALIGN_CENTER);
   {
      S.TieTextBox(XXO("File Name:"),mFileName);
      S.TieCheckBox(XXO("Add to History"), mbAddToHistory );
   }
   S.EndMultiColumn();
}

bool OpenProjectCommand::Apply(const CommandContext & context){

   auto &projectFileIO = ProjectFileIO::Get(context.project);

   auto oldFileName = projectFileIO.GetFileName();
   if(mFileName.empty())
   {
      auto project = &context.project;
      ProjectManager::OpenFiles(project);
   }
   else
   {
      ProjectFileManager::Get( context.project )
         .OpenFile(mFileName, mbAddToHistory);
   }
   const auto &newFileName = projectFileIO.GetFileName();

   // Because Open does not return a success or failure, we have to guess
   // at this point, based on whether the project file name has
   // changed and what to...
   return !newFileName.empty() && newFileName != oldFileName;
}

const ComponentInterfaceSymbol SaveProjectCommand::Symbol
{ XO("Save Project2") };

namespace{ BuiltinCommandsModule::Registration< SaveProjectCommand > reg2; }

bool SaveProjectCommand::DefineParams( ShuttleParams & S ){
   S.Define( mFileName, wxT("Filename"),  "name.aup3" );
   S.Define( mbAddToHistory, wxT("AddToHistory"),  false );
   return true;
}

void SaveProjectCommand::PopulateOrExchange(ShuttleGui & S)
{
   S.AddSpace(0, 5);

   S.StartMultiColumn(2, wxALIGN_CENTER);
   {
      S.TieTextBox(XXO("File Name:"),mFileName);
      S.TieCheckBox(XXO("Add to History"), mbAddToHistory );
   }
   S.EndMultiColumn();
}

bool SaveProjectCommand::Apply(const CommandContext &context)
{
   auto &projectFileManager = ProjectFileManager::Get( context.project );
   if ( mFileName.empty() )
      return projectFileManager.SaveAs();
   else
      return projectFileManager.SaveAs(mFileName, mbAddToHistory);
}

const ComponentInterfaceSymbol SaveCopyCommand::Symbol
{ XO("Save Copy") };

namespace{ BuiltinCommandsModule::Registration< SaveCopyCommand > reg3; }

bool SaveCopyCommand::DefineParams( ShuttleParams & S ){
   S.Define( mFileName, wxT("Filename"),  "name.aup3" );
   return true;
}

void SaveCopyCommand::PopulateOrExchange(ShuttleGui & S)
{
   S.AddSpace(0, 5);

   S.StartMultiColumn(2, wxALIGN_CENTER);
   {
      S.TieTextBox(XXO("File Name:"),mFileName);
   }
   S.EndMultiColumn();
}

bool SaveCopyCommand::Apply(const CommandContext &context)
{
   auto &projectFileManager = ProjectFileManager::Get( context.project );
   return projectFileManager.SaveCopy(mFileName);
}

const ComponentInterfaceSymbol SaveLogCommand::Symbol
{ XO("Save Log") };

namespace{ BuiltinCommandsModule::Registration< SaveLogCommand > reg4; }

bool SaveLogCommand::DefineParams(ShuttleParams & S)
{
   S.Define( mFileName, wxT("Filename"),  "log.txt" );
   return true;
}

void SaveLogCommand::PopulateOrExchange(ShuttleGui & S)
{
   S.AddSpace(0, 5);

   S.StartMultiColumn(2, wxALIGN_CENTER);
   {
      S.TieTextBox(XXO("File Name:"),mFileName);
   }
   S.EndMultiColumn();
}

bool SaveLogCommand::Apply(const CommandContext &context)
{
   auto logger = WavvyLogger::Get();
   return logger->SaveLog(mFileName);
}

const ComponentInterfaceSymbol ClearLogCommand::Symbol
{ XO("Clear Log") };

namespace{ BuiltinCommandsModule::Registration< ClearLogCommand > reg5; }

bool ClearLogCommand::DefineParams(ShuttleParams & S)
{
   return true;
}

bool ClearLogCommand::PromptUser(wxWindow *parent, std::function<void (bool)> callback)
{
   return true;
}

bool ClearLogCommand::Apply(const CommandContext &context)
{
   auto logger = WavvyLogger::Get();
   return logger->ClearLog();
}
