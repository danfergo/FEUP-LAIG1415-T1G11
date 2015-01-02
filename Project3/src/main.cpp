#include <iostream>
#include <exception>
 
#include "CGFapplication.h"
#include "scenegraph/Scene.h"
#include "scenegraph/parser/ANFparser.h"
#include "scenegraph/Interface.h"
#include "game/view/Board.h"
#include "game/controller/TixelController.h"


int main(int argc, char* argv[]) {
		
	try {
		TixelController tixel = TixelController();
		tixel.init(argc, argv);
		tixel.run();


			/** while(true){
			Scene * scene;
			scene = new Scene();

			scene->setRoot(new Board());
						tixel.setScene(scene);
			tixel.setInterface(new Interface());
				
			

			std::cout << "---------------------------------------------------" << std::endl;
		ANFparser parser = ANFparser(ANFparser::STRICT);


			if(!parser.parse(scene,"resources/scene.anf")){
				std::cout << "Build scene FAILED." << std::endl;
				std::cout << "---------------------------------------------------" << std::endl;					
				std::cout << "Press any key to continue..." << std::endl;
				std::cin;

			}else{

				std::cout << "Build scene DONE." << std::endl;
				std::cout << "Running..." << std::endl;
				std::cout << "---------------------------------------------------" << std::endl;	
				tixel.setScene(scene);
				tixel.setInterface(new Interface());
				
				tixel.run();
			}


			
		}**/

		
	} catch(ServerNotFound & e){
		std::cout << "Server Offline " << std::endl;
		return -1;
	} catch(GLexception& ex) {
		cout << "Erro: " << ex.what();
		return -1;
	} catch(exception& ex) {
		cout << "Erro inesperado: " << ex.what();
		return -1;
	}

	return 0;
}