/**********************************************************************

   Audacity: A Digital Audio Editor
   Audacity(R) is copyright (c) 1999-2018 Audacity Team.
   File License: wxwidgets

   OpenSaveCommands.h
   Stephen Parry
   James Crook

******************************************************************//**

\class OpenProjectCommand
\brief Command for opening an Wavacity project

\class SaveProjectCommand
\brief Command for saving an Wavacity project

\class SaveCopyCommand
\brief Command for saving a copy of currently project

\class SaveLogCommand
\brief Command for saving the log contents

*//*******************************************************************/

#include "Command.h"
#include "CommandType.h"

class OpenProjectCommand : public WavacityCommand
{
public:
   static const ComponentInterfaceSymbol Symbol;

   // ComponentInterface overrides
   ComponentInterfaceSymbol GetSymbol() override {return Symbol;};
   TranslatableString GetDescription() override {return XO("Opens a project.");};
   bool DefineParams( ShuttleParams & S ) override;
   void PopulateOrExchange(ShuttleGui & S) override;
   bool Apply(const CommandContext & context) override;

   // WavacityCommand overrides
   wxString ManualPage() override {return wxT("Extra_Menu:_Scriptables_II#open_project");};
public:
   wxString mFileName;
   bool mbAddToHistory;
   bool bHasAddToHistory;
};

class SaveProjectCommand : public WavacityCommand
{
public:
   static const ComponentInterfaceSymbol Symbol;

   // ComponentInterface overrides
   ComponentInterfaceSymbol GetSymbol() override {return Symbol;};
   TranslatableString GetDescription() override {return XO("Saves a project.");};
   bool DefineParams( ShuttleParams & S ) override;
   void PopulateOrExchange(ShuttleGui & S) override;
   bool Apply(const CommandContext & context) override;

   // WavacityCommand overrides
   wxString ManualPage() override {return wxT("Extra_Menu:_Scriptables_II#save_project");};
public:
   wxString mFileName;
   bool mbAddToHistory;
   bool bHasAddToHistory;
};

class SaveCopyCommand : public WavacityCommand
{
public:
   static const ComponentInterfaceSymbol Symbol;

   // ComponentInterface overrides
   ComponentInterfaceSymbol GetSymbol() override {return Symbol;};
   TranslatableString GetDescription() override {return XO("Saves a copy of current project.");};
   bool DefineParams( ShuttleParams & S ) override;
   void PopulateOrExchange(ShuttleGui & S) override;
   bool Apply(const CommandContext & context) override;

   // WavacityCommand overrides
   wxString ManualPage() override {return wxT("Extra_Menu:_Scriptables_II#save_copy");};
public:
   wxString mFileName;
};

class SaveLogCommand : public WavacityCommand
{
public:
   static const ComponentInterfaceSymbol Symbol;

   // ComponentInterface overrides
   ComponentInterfaceSymbol GetSymbol() override {return Symbol;};
   TranslatableString GetDescription() override {return XO("Saves the log contents.");};
   bool DefineParams( ShuttleParams & S ) override;
   void PopulateOrExchange(ShuttleGui & S) override;
   bool Apply(const CommandContext & context) override;

   // WavacityCommand overrides
   wxString ManualPage() override {return wxT("Extra_Menu:_Scriptables_II#save_log");};
public:
   wxString mFileName;
};

class ClearLogCommand : public WavacityCommand
{
public:
   static const ComponentInterfaceSymbol Symbol;

   // ComponentInterface overrides
   ComponentInterfaceSymbol GetSymbol() override {return Symbol;};
   TranslatableString GetDescription() override {return XO("Clears the log contents.");};
   bool DefineParams( ShuttleParams & S ) override;
   bool PromptUser(wxWindow *parent, std::function<void (bool)> callback = nullptr) override;
   bool Apply(const CommandContext & context) override;

   // WavacityCommand overrides
   wxString ManualPage() override {return wxT("Extra_Menu:_Scriptables_II#Clear_log");};
public:
   wxString mFileName;
};
