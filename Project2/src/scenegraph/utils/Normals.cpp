#include "Normals.h"
#include <math.h>

void normals::calculateSurfaceNormalTriangle(const Point3d tri[3], Vector3d & normal){

	//Set Vector U to (Triangle.p2 minus Triangle.p1)
	Vector3d u = {tri[1].x-tri[0].x,tri[1].y-tri[0].y,tri[1].z-tri[0].z};
	//Set Vector V to (Triangle.p3 minus Triangle.p1)
	Vector3d v = {tri[2].x-tri[1].x,tri[2].y-tri[1].y,tri[2].z-tri[1].z};


	//Set Normal.x to (multiply U.y by V.z) minus (multiply U.z by V.y)
	normal.x = (u.y*v.z) - (u.z*v.y);

	//Set Normal.y to (multiply U.z by V.x) minus (multiply U.x by V.z)
	normal.y = (u.z*v.x) - (u.x*v.z);	
	
	//Set Normal.z to (multiply U.x by V.y) minus (multiply U.y by V.x)
	normal.z = (u.x*v.y) - (u.y*v.x);

	//Returning Normalize(Normal)
	normalizeVector(normal);
}

void normals::calculateSurfaceNormal(const Point3d * poly,unsigned n, Vector3d & normal){
	Point3d current,next;

	//Set Vertex Normal to (0, 0, 0)
	normal.x = 0; normal.y=0; normal.z = 0;

	//Begin Cycle for Index in [0, Polygon.vertexNumber)
	for(unsigned i = 0 ; i < n; i++) {

    //Set Vertex Current to Polygon.verts[Index]
    current.x = poly[i].x;current.y = poly[i].y;current.z = poly[i].z;

	//Set Vertex Next    to Polygon.verts[(Index plus 1) mod Polygon.vertexNumber]
    next.x = poly[(i+1)%n].x;next.y = poly[(i+1)%n].y;next.z = poly[(i+1)%n].z; 

    //Set Normal.x to Sum of Normal.x and (multiply (Current.y minus Next.y) by (Current.z plus Next.z))
	normal.x += (current.y - next.y) * (current.z + next.z); 

    //Set Normal.y to Sum of Normal.y and (multiply (Current.z minus Next.z) by (Current.x plus Next.x))
    normal.y += (current.z - next.z) * (current.x + next.x);
		
	//Set Normal.z to Sum of Normal.z and (multiply (Current.x minus Next.x) by (Current.y plus Next.y))
	normal.z += (current.x - next.x) * (current.y + next.y);

	}  //End Cycle
	
   //Returning Normalize(Normal)
	normalizeVector(normal);
}


void normals::normalizeVector(Vector3d & vector){
	float norm = sqrt(pow(vector.x,2) + pow(vector.y,2) + pow(vector.z,2));
	if(norm == 0) return; // just in case O.o
	vector.x /= norm;
	vector.y /= norm;
	vector.z /= norm;
}


double normals::norm(const Vector3d & vector){
	return sqrt(pow(vector.x,2) + pow(vector.y,2) + pow(vector.z,2));
}