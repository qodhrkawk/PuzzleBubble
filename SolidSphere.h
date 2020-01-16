#pragma once

#include "SolidShape3D.h"
#include <math.h>

class SolidSphere : public SolidShape3D
{
public:
	SolidSphere(float r, int sl, int st);
	SolidSphere(const SolidSphere& sph);
	float getRadius() const;
	void draw() const;
	void setFloor(const int f);
	int getFloor();

	void setBallColor(int c);
	int getBallColor();

	void setXY(int x, int y);
	VectorN<int, 2> getXY();
	void setRemove(bool r);
	bool getRemove();
	void setremovevisited(bool v);
	bool getremovevisited();

	void setdrop(bool d);
	bool getdrop();
	void setdropvisited(bool d);
	bool getdropvisited();

	bool notShooted = true;


private:
	float radius;
	VectorN<int, 2> segmentation;	// slices, stacks
	int floor;
	VectorN<int, 2> xy;
	int ballColor;
	bool remove = false;
	bool removevisited = false;
	bool drop = false;
	bool dropvisited = false;

};

