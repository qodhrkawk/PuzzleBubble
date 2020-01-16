#pragma once

#include "Material.h"
#include "VectorN.h"



class SolidShape3D
{
public:
	SolidShape3D();
	SolidShape3D(const SolidShape3D& sh3d);

	void setCenter(float x, float y, float z);
	void setCenter(const VectorN<float, 3>& c);
	VectorN<float, 3> getCenter() const;
	void setVelocity(float x, float y, float z);
	void setVelocity(const VectorN<float, 3>& v);
	VectorN<float, 3> getVelocity() const;
	void move();
	void setMTL();
	void setMTL(const float* color);
	virtual void draw() const = 0;
	


protected:
	VectorN<float, 3> center;
	VectorN<float, 3> velocity;
	Material mtl;


};

