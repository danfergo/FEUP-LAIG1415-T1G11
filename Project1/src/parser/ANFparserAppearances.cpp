#include "ANFparser.h"

bool ParseANFscene::parseAppearances(TiXmlElement * anfAppearances, std::map<std::string, CGFappearance *> & appearances){
	TiXmlElement * anfAppearance = anfAppearances->FirstChildElement("appearance");
	CGFappearance  * appearance;
	while(anfAppearance){
		if(!(appearance=parseAppearance(anfAppearance))){
			return false;
		}else{
			//anfAppearance.insert(std::pair<std::string,CGFappearance>(,appearance));
		}
		anfAppearance = anfAppearance->NextSiblingElement("appearance"); 
	}

	return true;
}



CGFappearance * ParseANFscene::parseAppearance(TiXmlElement * anfAppearance){
	return NULL;
}