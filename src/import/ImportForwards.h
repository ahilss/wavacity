//
//  ImportForwards.h
//  Wavacity
//
//  Created by Paul Licameli on 8/10/16.
//
//

#ifndef __WAVACITY_IMPORT_FORWARDS__
#define __WAVACITY_IMPORT_FORWARDS__

#include <vector>
#include "../MemoryX.h"

class ImportPlugin;
class UnusableImportPlugin;

using ImportPluginList =
   std::vector< ImportPlugin * >;
using UnusableImportPluginList =
   std::vector< std::unique_ptr<UnusableImportPlugin> >;

#endif
