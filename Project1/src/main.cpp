/* 
 * G0_Base: projeto inicial de Laig* 
 * O Nelson mexeu aqui!
 */

#include <iostream>
#include <exception>
 
#include "CGFapplication.h"
#include "Scene.h"
#include "parser/ANFparser.h"

using std::cout; 
using std::exception;



int main(int argc, char* argv[]) {
	
	CGFapplication app = CGFapplication();

	try {
		app.init(&argc, argv);

		Scene * scene = new Scene();

		std::string filename;
		std::cout << "Insert the ANF filename: \n>";
		std::cin >> filename;

		if(!ParseANFscene::parse(scene,filename.c_str())){
			printf("Press Any Key to Continue\n");  
			std::cin >> filename;
			return 0;
		}

		/* Running CGF scene */
		

		app.setScene(scene);
		app.setInterface(new CGFinterface());

		
		app.run();
		
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