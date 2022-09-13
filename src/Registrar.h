/**********************************************************************

  Audacity: A Digital Audio Editor

  Registrar.h

  James Crook

*******************************************************************//**

\class Registrar
\brief Base class for registration callback.
Wavacity will call providers RegisterNameOfThing() functions with
an &Registrar as the argument.  RegisterNameOfThing() is then 
responsible for calling the appropriate callback functions.

**********************************************************************/


#ifndef __WAVACITY_REGISTRAR__
#define __WAVACITY_REGISTRAR__

#include "Wavacity.h"

#include "MemoryX.h"

class WavacityCommand;
class LoadableModule;
class ComponentInterface;
class Effect;

class WAVACITY_DLL_API Registrar 
{
public:
   Registrar(){
      bWantsModules = false;
      bWantsCommands= false;
      bWantsCommandTypes= false;
      bWantsEffects= false;
   }
   bool bWantsModules;
   bool bWantsCommands;
   bool bWantsCommandTypes;
   bool bWantsEffects;
   virtual void AddCommandType(std::unique_ptr<ComponentInterface> && WXUNUSED(comDef) ){;};
   virtual void AddCommand(std::unique_ptr<WavacityCommand> && WXUNUSED(command) ){;};
   virtual void AddModule(std::unique_ptr<LoadableModule> && WXUNUSED(module) ){;};
   virtual void AddEffect(std::unique_ptr<Effect> && WXUNUSED(effect) ){;};
};

#endif
