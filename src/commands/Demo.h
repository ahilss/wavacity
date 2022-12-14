/**********************************************************************

  Audacity: A Digital Audio Editor

  Demo.h

  James Crook

**********************************************************************/

#ifndef __WAVACITY_DEMO_COMMAND__
#define __WAVACITY_DEMO_COMMAND__

#include "WavacityCommand.h"
#include "../SampleFormat.h"

class ShuttleGui;

class DemoCommand final : public WavacityCommand
{
public:
   static const ComponentInterfaceSymbol Symbol;

   // ComponentInterface overrides
   ComponentInterfaceSymbol GetSymbol() override {return Symbol;};
   TranslatableString GetDescription() override {return XO("Does the demo action.");};
   bool DefineParams( ShuttleParams & S ) override;
   void PopulateOrExchange(ShuttleGui & S) override;
   bool Apply(const CommandContext & context) override;

   // WavacityCommand overrides
   wxString ManualPage() override {return wxT("Extra_Menu:_Scriptables_I");};

private:
   double delay;
   double decay;
};

#endif // __WAVACITY_DEMO_COMMAND__
