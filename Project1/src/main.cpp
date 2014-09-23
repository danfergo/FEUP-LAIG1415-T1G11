/* 
 * G0_Base: projeto inicial de Laig* 
 * O Nelson mexeu aqui!
 */

#include <iostream>
#include <exception>
 
#include "CGFapplication.h"
#include "Scene.h"

#include "XMLScene.h"

using std::cout; 
using std::exception;



int main(int argc, char* argv[]) {

	XMLScene teste = XMLScene("demograph.xml");






	/* Starting CGF application*/


	CGFapplication app = CGFapplication();

	try {
		app.init(&argc, argv);

		app.setScene(new Scene());
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