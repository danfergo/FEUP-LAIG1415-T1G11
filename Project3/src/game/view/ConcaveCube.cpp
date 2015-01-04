#include "ConcaveCube.h"
#include "../../scenegraph/primitives/Primitive.h"

#include <math.h>
#include <iostream>

using namespace std;

ConcaveCube::ConcaveCube(void)
{
	float pi = acos(-1.0);
float deg2rad = pi/180.0;

	double alpha = 135.0*deg2rad;
	for(int i=0; i<19; i++){
		
		xis[i] = cos(alpha)*sqrt(8.0)+4+2;
		zes[i] = sin(alpha)*sqrt(8.0)+2;

	/**	cout<<i<<": "<<xis[i]<<" " <<zes[i]<< endl; **/

		alpha+=5.0*deg2rad;
	}

}

void ConcaveCube::draw(Texture * texture){
	glPushMatrix();
		glScaled(0.05,0.05,0.05);
		glScaled(0.25,0.25,0.25);
		glTranslatef(-2,0,-2);
	glPushMatrix();
		glBegin(GL_TRIANGLE_STRIP);
			for(int i=0; i<19; i++){
				glVertex3d(xis[i],1,zes[i]);
				glVertex3d(xis[i],0,zes[i]);
			}
		glEnd();
	glPopMatrix();

	glBegin(GL_TRIANGLE_FAN);
		glVertex3d(0,0,2);

		glVertex3d(0,0,0);
		glVertex3d(4,0,0);
		
		for(int i=19; i>0; i--){
			glVertex3d(xis[i],0,zes[i]);
		}
		glVertex3d(4,0,4);
		glVertex3d(0,0,4);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
		glVertex3d(0,1,2);

		glVertex3d(0,1,4);
		glVertex3d(4,1,4);
		for(int i=0; i<19; i++){
			glVertex3d(xis[i],1,zes[i]);
		}
		glVertex3d(4,1,0);
		glVertex3d(0,1,0);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0,0,0);
		glVertex3d(0,1,0);
		glVertex3d(4,1,0);
		glVertex3d(4,0,0);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0,0,4);
		glVertex3d(4,0,4);
		glVertex3d(4,1,4);
		glVertex3d(0,1,4);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3d(0,0,0);
		glVertex3d(0,0,4);
		glVertex3d(0,1,4);
		glVertex3d(0,1,0);
	glEnd();

	glPopMatrix();
}

