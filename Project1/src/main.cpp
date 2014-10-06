/* 
 * G0_Base: projeto inicial de Laig* 
 * O Nelson mexeu aqui!
 */
	
#include <iostream>
#include <exception>
 
#include "CGFapplication.h"
#include "Scene.h"
#include "parser/ANFparser.h"
#include "Interface.h"


int main(int argc, char* argv[]) {
	CGFapplication app = CGFapplication();

	try {
		app.init(&argc, argv);

		Scene * scene = new Scene();


		std::string filename;
		std::cout << "Insert the ANF filename: \n>";
		std::cin >> filename;

		std::cout << "---------------------------------------------------" << std::endl;
		ANFparser parser = ANFparser(ANFparser::PERMISSIVE);


		if(!parser.parse(scene,filename.c_str())){
			std::cout << "Build scene FAILED." << std::endl;
			std::cout << "---------------------------------------------------" << std::endl;
		}else{

			std::cout << "Build scene DONE." << std::endl;
			std::cout << "Running..." << std::endl;
			std::cout << "---------------------------------------------------" << std::endl;	
			app.setScene(scene);
			app.setInterface(new Interface());
			app.run();
		}

		std::cout << "Press any key to continue..." << std::endl;
		std::cin >> filename;

		
		// Running CGF scene 
		
	}
	catch(GLexception& ex) {
		cout << "Erro: " << ex.what();
		return -1;
	}
	catch(exception& ex) {
		cout << "Erro inesperado: " << ex.what();
		return -1;
	}
	
	return 0;
}