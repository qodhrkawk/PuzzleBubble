#include "ETCShapes.h"
#include <math.h>
//#include <iostream>



Line::Line(const VectorN<float,2> p1, const VectorN<float,2> p2) {
	point1[0] = p1[0];
	point1[1] = p1[1];

	point2[0] = p2[0];
	point2[1] = p2[1];

}

void Line::setPoints(float* p1, float* p2) {
	point1[0] = p1[0];
	point1[1] = p1[1];

	point2[0] = p2[0];
	point2[1] = p2[1];


}
void Line::draw() {
	glColor3f(1, 1, 1);
	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glVertex2f(point1[0], point1[1]);
	glVertex2f(point2[0], point2[1]);
	glEnd();
}


Arrow::Arrow() {


}
Arrow::Arrow(VectorN<float, 3> c) {
	center[0] = c[0];
	center[1] = c[1];
	center[2] = c[2];

}

VectorN<float, 3> Arrow::getCenter() {

	return center;

}


void  Arrow::setAngle(int a) {
	angle = a;


}
int  Arrow::getAngle() {

	return angle;
}

void Arrow::draw() const {
	
	GLUquadricObj* pObj;
	glPushMatrix();
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_EMISSION, mtl.getEmission());
	glMaterialfv(GL_FRONT, GL_AMBIENT, mtl.getAmbient());
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mtl.getDiffuse());
	glMaterialfv(GL_FRONT, GL_SPECULAR, mtl.getSpecular());
	glMaterialfv(GL_FRONT, GL_SHININESS, mtl.getShininess());

	


	glTranslatef(center[0],center[1],center[2]);
	//glRotatef(angle,1.0,0.0,0.0);
	
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);

	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(90-angle, 0.0f, 1.0f, 0.0f);
	
	gluCylinder(pObj, 5, 5, 70, 26, 13);

	
	glTranslatef(0,0, 70);
	glutSolidCone(20, 40, 100, 100);

	

	glPopMatrix();


}


Isvisited_Remove::Isvisited_Remove() {

}
Isvisited_Remove::Isvisited_Remove(bool r) {
	isvisited_r = r;
}
void Isvisited_Remove::setvisited(bool r) {
	isvisited_r = r;
}
bool Isvisited_Remove::operator()(SolidSphere sph) {
	isvisited_r = sph.getRemove();
	return isvisited_r;

}


Isvisited_Drop::Isvisited_Drop() {


}
Isvisited_Drop::Isvisited_Drop(bool r) {

	isvisited_d = r;
}
void Isvisited_Drop::setvisited(bool r) {
	isvisited_d = r;

}
bool Isvisited_Drop::operator()(SolidSphere sph) {
	isvisited_d = sph.getdrop();
	return isvisited_d;

}