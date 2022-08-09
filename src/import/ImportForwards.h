//
//  ImportForwards.h
//  Wavvy
//
//  Created by Paul Licameli on 8/10/16.
//
//

#ifndef __WAVVY_IMPORT_FORWARDS__
#define __WAVVY_IMPORT_FORWARDS__

#include <vector>
#include "../MemoryX.h"

class ImportPlugin;
class UnusableImportPlugin;

using ImportPluginList =
   std::vector< ImportPlugin * >;
using UnusableImportPluginList =
   std::vector< std::unique_ptr<UnusableImportPlugin> >;

#endif
