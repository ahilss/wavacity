/**********************************************************************

  Audacity: A Digital Audio Editor

  Demo.h

  James Crook

**********************************************************************/

#ifndef __WAVVY_DEMO_COMMAND__
#define __WAVVY_DEMO_COMMAND__

#include "WavvyCommand.h"
#include "../SampleFormat.h"

class ShuttleGui;

class DemoCommand final : public WavvyCommand
{
public:
   static const ComponentInterfaceSymbol Symbol;

   // ComponentInterface overrides
   ComponentInterfaceSymbol GetSymbol() override {return Symbol;};
   TranslatableString GetDescription() override {return XO("Does the demo action.");};
   bool DefineParams( ShuttleParams & S ) override;
   void PopulateOrExchange(ShuttleGui & S) override;
   bool Apply(const CommandContext & context) override;

   // WavvyCommand overrides
   wxString ManualPage() override {return wxT("Extra_Menu:_Scriptables_I");};

private:
   double delay;
   double decay;
};

#endif // __WAVVY_DEMO_COMMAND__
