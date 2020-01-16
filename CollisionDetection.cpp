#include "CollisionDetection.h"

bool CollisionDetection::operator()(const SolidSphere& sph1, const SolidSphere& sph2) {
	/* Implement */
	VectorN<float, 3> temp;
	temp = sph2.getCenter() - sph1.getCenter();

	float x = dotProduct(temp, temp);

	float y = sph1.getRadius() + sph2.getRadius();
	if (y * y >= x) {
		return true;
	}
	else {
		return false;
	}



}