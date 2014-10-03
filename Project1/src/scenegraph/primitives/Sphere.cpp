#include "Sphere.h"
#include <math.h>

static float const PI = acos(-1.0);
static float ambientNull[4]={0,0,0,1};


Sphere::Sphere(unsigned st, unsigned sl): slices(sl< 3 ? 3 : sl),stacks(st < 1  ? 1 : st){
	dots = new Point3d* [stacks+1];
	for (unsigned i = 0; i <= stacks; ++i)
		dots[i] = new Point3d[slices+1];
	
	angle_a = 2*PI/(float)slices;
	angle_b = (PI/(float)2)/stacks;
	
	
	for(unsigned i = 0 ; i <= stacks; i++){
		for(unsigned j = 0; j <= slices ; j++){
			dots[i][j].x = (float)cos((i)*angle_b)*sin(j*angle_a);
			dots[i][j].y = sin(angle_b*i);
			dots[i][j].z = cos((i)*angle_b)*cos(j*angle_a);
		}
	}

}

Sphere::~Sphere(){
	for (unsigned i = 0; i < stacks; ++i)
		    delete [] dots[i];
	delete [] dots;
}


void Sphere::draw(){
	glPushMatrix();
		
	for(unsigned i = 0 ; i < stacks; i++){
			glPushMatrix();	
				glBegin(GL_TRIANGLE_STRIP);
					for(unsigned j = 0; j <= slices ; j++){
						
						glNormal3d(-dots[i][j].x,-dots[i][j].y,-dots[i][j].z);
						glVertex3f(dots[i][j].x,dots[i][j].y,dots[i][j].z);
						
						glNormal3d(-dots[i+1][j].x,-dots[i+1][j].y,-dots[i+1][j].z);
						glVertex3f(dots[i+1][j].x,dots[i+1][j].y,dots[i+1][j].z);
						
					}
				glEnd();
			glPopMatrix();
		}

		//glRotated(180,1,0,0);
		for(unsigned i = 0 ; i < stacks; i++){
			glPushMatrix();	
				glBegin(GL_TRIANGLE_STRIP);
					for(unsigned j = 0; j <= slices ; j++){
						glNormal3d(-dots[i+1][j].x,dots[i+1][j].y,-dots[i+1][j].z);
						glVertex3f(dots[i+1][j].x,-dots[i+1][j].y,dots[i+1][j].z);

						glNormal3d(-dots[i][j].x,dots[i][j].y,-dots[i][j].z);
						glVertex3f(dots[i][j].x,-dots[i][j].y,dots[i][j].z);				
					}
				glEnd();
			glPopMatrix();
		}

	glPopMatrix();
} 

