/**********************************************************************

  Audacity: A Digital Audio Editor

  ProjectFileIORegistry.h

  Paul Licameli

**********************************************************************/

#ifndef __WAVVY_PROJECT_FILE_IO_REGISTRY__
#define __WAVVY_PROJECT_FILE_IO_REGISTRY__

#include <functional>

class WavvyProject;
class XMLTagHandler;
class wxString;

namespace ProjectFileIORegistry {

// Type of functions returning objects that interpret a part of the saved XML
using TagHandlerFactory =
   std::function< XMLTagHandler *( WavvyProject & ) >;

// Typically statically constructed
struct Entry{
   Entry( const wxString &tag, const TagHandlerFactory &factory );
};

TagHandlerFactory Lookup( const wxString &tag );

}

#endif
