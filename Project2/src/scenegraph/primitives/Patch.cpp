#include "Patch.h"
#include <stdlib.h> 
#include "CGFobject.h"
#include "../utils/Normals.h"


Patch::Patch(int o, int partsU, int partsV, Compute compute, Point3d * controlpoints) :
	partsU(partsU), partsV(partsV),order(order)
{
	this->order = o+1;
	unsigned nrOfPoints = order*order;
	this->controlPoints = new float[order*order*3];




	for(unsigned i = 0, k = 0; i < nrOfPoints; i++, k+=3){
		this->controlPoints[k] = controlpoints[i].x;
		this->controlPoints[k+1] = controlpoints[i].y;
		this->controlPoints[k+2] = controlpoints[i].z;
	}



	this->compute = compute == POINT ? GL_POINT : (compute == LINE ? GL_LINE : GL_FILL);

}  

void Patch::draw(Texture * texture) const
{
	
	glFrontFace(GL_CW);
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, order, 0.0, 1.0, 3*order, order, &controlPoints[0]);
	glMapGrid2f(partsU,0.0,1.0,partsV,0.0,1.0);
	glEvalMesh2(compute,0,partsU,0,partsV);

	/** REMOVE THIS THING - make it dynamic*/
	glFrontFace(GL_CW);
}

Patch::~Patch(void)
{
	delete[] this->controlPoints;
}
	