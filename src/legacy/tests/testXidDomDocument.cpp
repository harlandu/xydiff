#include "xercesc/util/PlatformUtils.hpp"
//#include <../src/dom/RefCountedImpl.hpp>
#include "xercesc/dom/DOMException.hpp"

#include "xydiff/XID_DOMDocument.hpp"
#include "xydiff/XID_map.hpp"
#include "xydiff/XyLatinStr.hpp"
#include "Tools.hpp"
#include <stdio.h>
#include <fstream>

XERCES_CPP_NAMESPACE_USE

int main(int argc, char **argv) {
  
	if (argc<2) {
	  std::cerr << "usage: exec filename" << std::endl ;
		std::cerr << "example: exec example1.xml" << std::endl ;
		std::cerr << "result: example1.xml.debugXID" << std::endl;
		return(0);
		}

  try {
    XMLPlatformUtils::Initialize();
    }
  catch(const XMLException& toCatch) {
    std::cerr << "Error during Xerces-c Initialization.\n"
	       << "  Exception message:" << XyLatinStr(toCatch.getMessage()).localForm() << std::endl;
    }
	
	try {
		printf("Opening file <%s>\n", argv[1]);
		XID_DOMDocument d(argv[1]);
	
	  std::string fileWithXID = argv[1] ;
	  fileWithXID += ".debugXID" ;

		printf("Saving with XID as file <%s>\n", fileWithXID.c_str());
		globalPrintContext.SetModeDebugXID(d.getXidMap());
	  d.SaveAs(fileWithXID.c_str(), false);
		globalPrintContext.ReleaseContext();

#if 0
		printf("Testing 'Clone XID_DOMDocument'\n");
	  XID_DOMDocument e(d);
	
	  std::string saveAsName = std::string(argv[1]) + ".Version0.xml" ;
		printf("Saving as <%s>\n", saveAsName.c_str());
	  e.SaveAs( saveAsName.c_str() );
		printf("All done.\n");
#endif
	  }
	catch( const VersionManagerException &e ) {
	  std::cerr << e << std::endl ;
		}
	catch( const DOMException &e ) {
	  std::cerr << "DOMException, code=" << e.code << std::endl ;
		std::cerr << "DOMException, message=" << e.msg << std::endl ;
		}	
	std::cout << "Terminated." << std::endl ;
	}
	
