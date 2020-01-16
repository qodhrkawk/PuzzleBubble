#include "SolidSphere.h"

SolidSphere::SolidSphere(float r, int sl, int st) : SolidShape3D() {
	radius = r;
	segmentation[0] = sl;
	segmentation[1] = st;
	
}

SolidSphere::SolidSphere(const SolidSphere& sph) : SolidShape3D(sph) {
	radius = sph.radius;
	segmentation[0] = sph.segmentation[0];
	segmentation[1] = sph.segmentation[1];
	floor = sph.floor;
	ballColor = sph.ballColor;
	remove = sph.remove;
	removevisited = sph.removevisited;
	xy = sph.xy;
	drop = sph.drop;
	dropvisited = sph.dropvisited;
	notShooted = sph.notShooted;

}

float SolidSphere::getRadius() const {
	return radius;
}

void SolidSphere::draw() const {
	glPushMatrix();

	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_EMISSION, mtl.getEmission());
	glMaterialfv(GL_FRONT, GL_AMBIENT, mtl.getAmbient());
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mtl.getDiffuse());
	glMaterialfv(GL_FRONT, GL_SPECULAR, mtl.getSpecular());
	glMaterialfv(GL_FRONT, GL_SHININESS, mtl.getShininess());

	glTranslatef(center[0], center[1], center[2]);
	glutSolidSphere(radius, segmentation[0], segmentation[1]);
	glPopMatrix();
}

void SolidSphere::setFloor(const int f) {
	floor = f;

}
int SolidSphere::getFloor() {

	return floor;
}

void SolidSphere::setBallColor(int c) {
	ballColor = c;

}
int SolidSphere::getBallColor() {
	return ballColor;
}

void SolidSphere::setXY(int x, int y) {
	xy[0] = x;
	xy[1] = y;
}
VectorN<int, 2> SolidSphere::getXY() {
	return xy;
}

void SolidSphere::setRemove(bool r) {

	remove = r;

}
bool SolidSphere::getRemove() {
	return remove;
}

void SolidSphere::setremovevisited(bool v) {
	removevisited = v;
}
bool SolidSphere::getremovevisited() {

	return removevisited;
}


void SolidSphere::setdrop(bool d) {

	drop = d;
}
bool SolidSphere::getdrop() {
	return drop;


}
void SolidSphere::setdropvisited(bool d) {
	dropvisited = d;

}
bool SolidSphere::getdropvisited() {
	return dropvisited;

}