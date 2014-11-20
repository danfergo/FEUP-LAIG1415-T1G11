#include "Patch.h"
#include <stdlib.h> 
#include "CGFobject.h"
#include "../utils/Normals.h"


float texturePts[2][2][2] =  {{{0.0, 0.0}, {0.0, 1.0}}, 
			{{1.0, 0.0}, {1.0, 1.0}}};

Patch::Patch(int o, int partsU, int partsV, Compute compute, Point3d * controlpoints) :
	partsU(partsU), partsV(partsV),order(order)
{
	this->order = o+1;
	this->controlPoints = new float[order*order*3];
	this->compute = compute == POINT ? GL_POINT : (compute == LINE ? GL_LINE : GL_FILL);

	if(controlpoints != NULL) setControlPoints(controlpoints);

	
}  

void Patch::setControlPoints(Point3d * controlpoints){
	for(unsigned i = 0, k = 0; i < (unsigned)order*order; i++, k+=3){
		this->controlPoints[k] = controlpoints[i].x;
		this->controlPoints[k+1] = controlpoints[i].y;
		this->controlPoints[k+2] = controlpoints[i].z;
	}
}


void Patch::draw(Texture * texture)
{
	
	glFrontFace(GL_CW);
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, order, 0.0, 1.0, 3*order, order, &controlPoints[0]);
    glMap2f(GL_MAP2_TEXTURE_COORD_2, 0, 1, 2, 2, 0, 1, 4, 2, &texturePts[0][0][0]);

	//glMap2f(GL_MAP1_TEXTURE_COORD_1, 0.0, 1.0, 3, 2, 0.0, 1.0, 6, 2, &controlPoints[0]);
	//glMap2f(GL_MAP2_COLOR_4, 0.0, 1.0, 4, 2, 0.0, 1.0, 8, 2, colorpoints[0][0]);

	glMapGrid2f(partsU,0.0,1.0,partsV,0.0,1.0);
	glEvalMesh2(compute,0,partsU,0,partsV);

	/** REMOVE THIS THING - make it dynamic*/
	glFrontFace(GL_CCW);
}

Patch::~Patch(void)
{
	delete[] this->controlPoints;
}
	