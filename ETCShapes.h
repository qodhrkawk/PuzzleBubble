#pragma once

#include "Material.h"
#include "VectorN.h"
#include <GL/glut.h>
#include "SolidShape3D.h"
#include "SolidSphere.h"

class Line {
public:
	Line() { point1[0] = 0; point1[1] = 0; point2[0] = 0; point2[1] = 0; }
	Line(const VectorN<float, 2> p1, const VectorN<float,2> p2);

	void setPoints(float* p1, float* p2);
	void draw();

	
protected:
	VectorN<float, 2> point1;
	VectorN<float, 2> point2;
	//Material mtl;
};


class Arrow :public SolidShape3D {

public:
	Arrow();
	Arrow(VectorN<float, 3> c);


	VectorN<float, 3> getCenter();
	void setAngle(int a);
	int getAngle();

	void draw() const;





protected:

	VectorN<float, 3> center;
	int angle;



};


class Isvisited_Remove {
public:
	Isvisited_Remove();
	Isvisited_Remove(bool r);
	void setvisited(bool r);
	bool operator()(SolidSphere sph);
private:
	bool isvisited_r;


};

class Isvisited_Drop{
public:
	Isvisited_Drop();
	Isvisited_Drop(bool r);
	void setvisited(bool r);
	bool operator()(SolidSphere sph);
private:
	bool isvisited_d;


};