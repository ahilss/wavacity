/**********************************************************************

  Audacity: A Digital Audio Editor

  BatchPrefs.h

  Dominic Mazzoni
  James Crook

**********************************************************************/

#ifndef __WAVVY_BATCH_PREFS__
#define __WAVVY_BATCH_PREFS__

#include <wx/defs.h>

#include "PrefsPanel.h"

class ShuttleGui;

#define BATCH_PREFS_PLUGIN_SYMBOL ComponentInterfaceSymbol{ XO("Batch") }

class BatchPrefs final : public PrefsPanel
{
public:
   BatchPrefs(wxWindow * parent, wxWindowID winid);
   ~BatchPrefs();
   ComponentInterfaceSymbol GetSymbol() override;
   TranslatableString GetDescription() override;
   wxString HelpPageName() override;

   bool Commit() override;
   void PopulateOrExchange(ShuttleGui & S) override;

private:
   void Populate();

   DECLARE_EVENT_TABLE()
};

#endif
