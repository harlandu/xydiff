
#include "Tools.hpp"
#include "xydiff/XyDelta_FileInterface.hpp"
#include "xydiff/XyLatinStr.hpp"

#include "xercesc/util/PlatformUtils.hpp"
#include "xercesc/dom/DOMException.hpp"

XERCES_CPP_NAMESPACE_USE

int main(int argc, char **argv) {
 
	char  *versionFile, *deltaFile;
	
	bool help=false;
	for (int i=1; i<argc; i++) if (strcmp(argv[i], "--help")==0) help=true;
    if (argc!=3) help=true;
	
	if (help) {
		std::cerr << "============" << std::endl;
		std::cerr << "usage       : exec new_version.xml delta_file.xml " << std::endl ;
		std::cerr << std::endl;
		std::cerr << "description : " << std::endl ;
		std::cerr << "              XyLoad loads a new version of an XML document into the \"repository\" " << std::endl 
			 << "              The name of the last version of XML document is kept into the delta file" << std::endl;
		std::cerr << "              new_version.xml : file with the new version of the XML document " << std::endl 
			 << "                                or the XML document if it's loaded for the first time" << std::endl;
		std::cerr << "              delta_file.xml  : file to store the delta in " << std::endl 
		     << "                                for the first time when a document is loaded it should not exist" << std::endl 
			 << "                                if it exists, it's considered to be an update" << std::endl;
		exit(-1);
	}
	
    try {
		XMLPlatformUtils::Initialize();
    }
	catch(const XMLException& toCatch) {
		std::cerr << "Error during Xerces-c Initialization" << std::endl << "  Exception message:" << toCatch.getMessage() << std::endl;
    }

	
	// XyLoad action

	versionFile = argv[1];
	deltaFile = argv[2];

	
	try {

        XyDelta::XyLoadAndDiff(versionFile, deltaFile );
  	}

	catch( const VersionManagerException &e ) {
		std::cerr << e << std::endl ;
		exit(-1);
	}
		
	catch( const DOMException &e ) {
		std::cerr << "DOMException, code=" << e.code << std::endl ;
		std::cerr << "DOMException, message=" << e.msg << std::endl ;
		exit(-1);
	}	

	return(0);
}
	
