#include "Patch.h"
#include <stdlib.h> 

Patch::Patch(int order, int partsU, int partsV, Compute compute, Point3d * controlpoints) :
	order(order), partsU(partsU), partsV(partsV),compute(compute)
{
	
}

void Patch::draw() const
{


}

Patch::~Patch(void)
{
}
	