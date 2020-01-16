#include <vector>

#include "CollisionHandling.h"
#include "Light.h"

#include <time.h>
#include "ETCShapes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

#define WIDTH 450
#define HEIGHT 600
#define PI 3.141592

#define boundaryX WIDTH/2
#define boundaryY HEIGHT/2
clock_t start_clock = clock();
clock_t end_clock;

const int radius = 22.5;
int timelimit = 100;




bool colhandle = false;
int score = 0;
int angle = 90;


clock_t limited_start_time = clock() / CLOCKS_PER_SEC;
clock_t limited_end_time;
int printingtime = 0;

bool dropping = 0;

int phase = 0;

VectorN<int, 2> mouse;
VectorN<int, 2> mouse1;
vector<Line> lines;
vector<SolidSphere> spheres;
Light* light;
vector<Arrow> arrows;

SolidSphere* tmp;


float fps = 1000;


bool doing = 0;
bool gameover = 0;
void collided();

float* oddFloor = new float[10];
float* evenFloor = new float[9];


void setDrops(SolidSphere& s);

void doDrops();





bool thereisE(SolidSphere s) {
	if (s.getXY()[0] == 9)
		return false;
	int x = s.getXY()[0] + 1;
	int y = s.getXY()[1];

	float tmpx = 0;
	float tmpy = 0;
	bool result = false;
	if (y % 2 == 1) {
		tmpy = 15 * boundaryY / 20 - (radius + sqrt(3) * radius * (y - 1));
		tmpx = oddFloor[x];
	}
	else {
		tmpy = 15 * boundaryY / 20 - (radius + sqrt(3) * radius * (y - 1));
		tmpx = evenFloor[x];
	}

	for (auto& sph : spheres) {
		if (tmpx == sph.getCenter()[0] && tmpy == sph.getCenter()[1]) {
			result = true;

		}

	}

	return result;
}

bool thereisW(SolidSphere s) {
	if (s.getXY()[0] == 0)
		return false;
	int x = s.getXY()[0] - 1;
	int y = s.getXY()[1];

	float tmpx = 0;
	float tmpy = 0;
	bool result = false;
	if (y % 2 == 1) {
		tmpy = 15 * boundaryY / 20 - (radius + sqrt(3) * radius * (y - 1));
		tmpx = oddFloor[x];
	}
	else {
		tmpy = 15 * boundaryY / 20 - (radius + sqrt(3) * radius * (y - 1));
		tmpx = evenFloor[x];
	}

	for (auto& sph : spheres) {
		if (tmpx == sph.getCenter()[0] && tmpy == sph.getCenter()[1]) {
			result = true;
		}

	}

	return result;
}

bool thereisSE(SolidSphere s) {
	if (s.getXY()[0] == 9)
		return false;



	float tmpx = 0;
	float tmpy = 0;
	bool result = false;
	if (s.getFloor() % 2 == 1) {
		int x = s.getXY()[0];
		int y = s.getXY()[1] + 1;
		tmpy = 15 * boundaryY / 20 - (radius + sqrt(3) * radius * (y - 1));
		tmpx = evenFloor[x];
	}
	else {
		int x = s.getXY()[0] + 1;
		int y = s.getXY()[1] + 1;
		tmpy = 15 * boundaryY / 20 - (radius + sqrt(3) * radius * (y - 1));
		tmpx = oddFloor[x];
	}

	for (auto& sph : spheres) {
		if (tmpx == sph.getCenter()[0] && tmpy == sph.getCenter()[1]) {
			result = true;

		}

	}

	return result;
}

bool thereisSW(SolidSphere s) {
	if (s.getXY()[0] == 0 && s.getXY()[1] % 2 == 1)
		return false;



	float tmpx = 0;
	float tmpy = 0;
	bool result = false;
	if (s.getFloor() % 2 == 1) {
		int x = s.getXY()[0] - 1;
		int y = s.getXY()[1] + 1;
		tmpy = 15 * boundaryY / 20 - (radius + sqrt(3) * radius * (y - 1));
		tmpx = evenFloor[x];
	}
	else {
		int x = s.getXY()[0];
		int y = s.getXY()[1] + 1;
		tmpy = 15 * boundaryY / 20 - (radius + sqrt(3) * radius * (y - 1));
		tmpx = oddFloor[x];
	}

	for (auto& sph : spheres) {
		if (tmpx == sph.getCenter()[0] && tmpy == sph.getCenter()[1]) {
			result = true;

		}

	}

	return result;
}


bool thereisNE(SolidSphere s) {
	if (s.getXY()[0] == 9)
		return false;



	float tmpx = 0;
	float tmpy = 0;
	bool result = false;
	if (s.getFloor() % 2 == 1) {
		int x = s.getXY()[0];
		int y = s.getXY()[1] - 1;
		tmpy = 15 * boundaryY / 20 - (radius + sqrt(3) * radius * (y - 1));
		tmpx = evenFloor[x];
	}
	else {

		int x = s.getXY()[0] + 1;
		int y = s.getXY()[1] - 1;

		tmpy = 15 * boundaryY / 20 - (radius + sqrt(3) * radius * (y - 1));
		tmpx = oddFloor[x];
	}

	for (auto& sph : spheres) {
		if (tmpx == sph.getCenter()[0] && tmpy == sph.getCenter()[1]) {
			result = true;

		}

	}

	return result;
}

bool thereisNW(SolidSphere s) {
	if (s.getXY()[0] == 0 && s.getXY()[1] % 2 == 1)
		return false;



	float tmpx = 0;
	float tmpy = 0;
	bool result = false;
	if (s.getFloor() % 2 == 1) {
		int x = s.getXY()[0] - 1;
		int y = s.getXY()[1] - 1;
		tmpy = 15 * boundaryY / 20 - (radius + sqrt(3) * radius * (y - 1));
		tmpx = evenFloor[x];
	}
	else {
		int x = s.getXY()[0];
		int y = s.getXY()[1] - 1;
		tmpy = 15 * boundaryY / 20 - (radius + sqrt(3) * radius * (y - 1));
		tmpx = oddFloor[x];
	}

	for (auto& sph : spheres) {
		if (tmpx == sph.getCenter()[0] && tmpy == sph.getCenter()[1]) {
			result = true;

		}

	}

	return result;
}

void settingPosition(SolidSphere& s) {
	if (spheres.size() > 2) {
		float result = 1000;

		int itmp = 0;
		if (s.getFloor() % 2 == 1) {
			for (int i = 0; i < 10; i++) {
				float tmp = abs(s.getCenter()[0] - oddFloor[i]);
				if (tmp < result) {
					result = tmp;
					itmp = i;
				}

			}
			s.setCenter(oddFloor[itmp], 15 * boundaryY / 20 - (radius + sqrt(3) * radius * (s.getFloor() - 1)), 0);

			s.setXY(itmp, s.getFloor());

		}

		else {
			for (int i = 0; i < 9; i++) {
				float tmp = abs(s.getCenter()[0] - evenFloor[i]);
				if (tmp < result) {
					result = tmp;
					itmp = i;
				}

			}
			s.setCenter(evenFloor[itmp], 15 * boundaryY / 20 - (radius + sqrt(3) * radius * (s.getFloor() - 1)), 0);
			s.setXY(itmp, s.getFloor());
		}

	}
}




int removeCount(SolidSphere& s, int color) {

	int result = 1;
	bool* direction = new bool[6];
	//west, nw, ne, east , se, sw
	s.setRemove(true);
	s.setremovevisited(true);

	direction[0] = thereisW(s);
	direction[1] = thereisNW(s);
	direction[2] = thereisNE(s);
	direction[3] = thereisE(s);
	direction[4] = thereisSE(s);
	direction[5] = thereisSW(s);


	if (s.getFloor() % 2 == 1) {
		if (direction[0]) {

			int x = s.getXY()[0] - 1;
			int y = s.getXY()[1];
			float tmpy = 15 * boundaryY / 20 - (radius + sqrt(3) * radius * (y - 1));
			float tmpx = oddFloor[x];


			for (auto& sph : spheres) {
				if (sph.getCenter()[0] == tmpx && sph.getCenter()[1] == tmpy && !sph.getremovevisited()) {
					if (sph.getBallColor() == color) {
						result += removeCount(sph, color);
						sph.setRemove(true);

					}
				}

			}

		}
		if (direction[1]) {
			int x = s.getXY()[0] - 1;
			int y = s.getXY()[1] - 1;
			float tmpy = 15 * boundaryY / 20 - (radius + sqrt(3) * radius * (y - 1));
			float tmpx = evenFloor[x];

			for (auto& sph : spheres) {
				if (sph.getCenter()[0] == tmpx && sph.getCenter()[1] == tmpy && !sph.getremovevisited()) {
					if (sph.getBallColor() == color) {
						result += removeCount(sph, color);
						sph.setRemove(true);
					}
				}

			}

		}
		if (direction[2]) {

			int x = s.getXY()[0];
			int y = s.getXY()[1] - 1;
			float tmpy = 15 * boundaryY / 20 - (radius + sqrt(3) * radius * (y - 1));
			float tmpx = evenFloor[x];

			for (auto& sph : spheres) {
				if (sph.getCenter()[0] == tmpx && sph.getCenter()[1] == tmpy && !sph.getremovevisited()) {
					if (sph.getBallColor() == color) {

						result += removeCount(sph, color);
						sph.setRemove(true);

					}
				}

			}

		}

		if (direction[3]) {
			int x = s.getXY()[0] + 1;
			int y = s.getXY()[1];
			float tmpy = 15 * boundaryY / 20 - (radius + sqrt(3) * radius * (y - 1));
			float tmpx = oddFloor[x];

			for (auto& sph : spheres) {
				if (sph.getCenter()[0] == tmpx && sph.getCenter()[1] == tmpy && !sph.getremovevisited()) {
					if (sph.getBallColor() == color) {
						result += removeCount(sph, color);
						sph.setRemove(true);
					}
				}

			}

		}
		if (direction[4]) {
			int x = s.getXY()[0];
			int y = s.getXY()[1] + 1;
			float tmpy = 15 * boundaryY / 20 - (radius + sqrt(3) * radius * (y - 1));
			float tmpx = evenFloor[x];

			for (auto& sph : spheres) {
				if (sph.getCenter()[0] == tmpx && sph.getCenter()[1] == tmpy && !sph.getremovevisited()) {
					if (sph.getBallColor() == color) {
						result += removeCount(sph, color);
						sph.setRemove(true);
					}
				}

			}

		}

		if (direction[5]) {
			int x = s.getXY()[0] - 1;
			int y = s.getXY()[1] + 1;
			float tmpy = 15 * boundaryY / 20 - (radius + sqrt(3) * radius * (y - 1));
			float tmpx = evenFloor[x];

			for (auto& sph : spheres) {
				if (sph.getCenter()[0] == tmpx && sph.getCenter()[1] == tmpy && !sph.getremovevisited()) {
					if (sph.getBallColor() == color) {
						result += removeCount(sph, color);
						sph.setRemove(true);
					}
				}

			}

		}
	}

	else {
		//west, nw, ne, east , se, sw
		if (direction[0]) {
			int x = s.getXY()[0] - 1;
			int y = s.getXY()[1];
			float tmpy = 15 * boundaryY / 20 - (radius + sqrt(3) * radius * (y - 1));
			float tmpx = evenFloor[x];

			for (auto& sph : spheres) {
				if (sph.getCenter()[0] == tmpx && sph.getCenter()[1] == tmpy && !sph.getremovevisited()) {
					if (sph.getBallColor() == color) {
						result += removeCount(sph, color);
						sph.setRemove(true);
					}
				}

			}

		}
		if (direction[1]) {
			int x = s.getXY()[0];
			int y = s.getXY()[1] - 1;
			float tmpy = 15 * boundaryY / 20 - (radius + sqrt(3) * radius * (y - 1));
			float tmpx = oddFloor[x];

			for (auto& sph : spheres) {
				if (sph.getCenter()[0] == tmpx && sph.getCenter()[1] == tmpy && !sph.getremovevisited()) {
					if (sph.getBallColor() == color) {
						result += removeCount(sph, color);
						sph.setRemove(true);
					}
				}

			}

		}
		//west, nw, ne, east , se, sw
		if (direction[2]) {
			int x = s.getXY()[0] + 1;
			int y = s.getXY()[1] - 1;
			float tmpy = 15 * boundaryY / 20 - (radius + sqrt(3) * radius * (y - 1));
			float tmpx = oddFloor[x];


			for (auto& sph : spheres) {
				if (sph.getCenter()[0] == tmpx && sph.getCenter()[1] == tmpy && !sph.getremovevisited()) {

					if (sph.getBallColor() == color) {
						result += removeCount(sph, color);
						sph.setRemove(true);
					}
				}

			}

		}

		if (direction[3]) {
			int x = s.getXY()[0] + 1;
			int y = s.getXY()[1];
			float tmpy = 15 * boundaryY / 20 - (radius + sqrt(3) * radius * (y - 1));
			float tmpx = evenFloor[x];

			for (auto& sph : spheres) {
				if (sph.getCenter()[0] == tmpx && sph.getCenter()[1] == tmpy && !sph.getremovevisited()) {
					if (sph.getBallColor() == color) {
						result += removeCount(sph, color);
						sph.setRemove(true);
					}
				}

			}

		}
		if (direction[4]) {
			int x = s.getXY()[0] + 1;
			int y = s.getXY()[1] + 1;
			float tmpy = 15 * boundaryY / 20 - (radius + sqrt(3) * radius * (y - 1));
			float tmpx = oddFloor[x];

			for (auto& sph : spheres) {
				if (sph.getCenter()[0] == tmpx && sph.getCenter()[1] == tmpy && !sph.getremovevisited()) {
					if (sph.getBallColor() == color) {
						result += removeCount(sph, color);
						sph.setRemove(true);
					}
				}

			}

		}

		if (direction[5]) {
			int x = s.getXY()[0];
			int y = s.getXY()[1] + 1;
			float tmpy = 15 * boundaryY / 20 - (radius + sqrt(3) * radius * (y - 1));
			float tmpx = oddFloor[x];

			for (auto& sph : spheres) {
				if (sph.getCenter()[0] == tmpx && sph.getCenter()[1] == tmpy && !sph.getremovevisited()) {
					if (sph.getBallColor() == color) {
						result += removeCount(sph, color);
						sph.setRemove(true);
					}
				}

			}

		}


	}

	return result;




}



void removeAlgorithm(SolidSphere& s) {



	int color = s.getBallColor();

	int a = removeCount(s, color);


	if (a < 3) {

		for (auto& sph : spheres) {
			sph.setRemove(false);
			sph.setremovevisited(false);
		}
	}

	else {
		score += a * 10;

		/*	for (it = spheres.begin(); it != spheres.end(); ++it) {
				if (it->getRemove() == true) {
					cout << "here" << endl;
					spheres.erase(it);

				}
			}*/

		vector<SolidSphere>::iterator it;
		Isvisited_Remove a;
		while ((it = find_if(spheres.begin(), spheres.end(), a)) != spheres.end()) {
			spheres.erase(it);
		}

		doDrops();



	}





}


void setDrops(SolidSphere& s) {

	bool* direction = new bool[6];
	//west, nw, ne, east , se, sw
	s.setdropvisited(true);
	s.setdrop(false);

	direction[0] = thereisW(s);
	direction[1] = thereisNW(s);
	direction[2] = thereisNE(s);
	direction[3] = thereisE(s);
	direction[4] = thereisSE(s);
	direction[5] = thereisSW(s);


	if (s.getFloor() % 2 == 1) {
		if (direction[0]) {

			int x = s.getXY()[0] - 1;
			int y = s.getXY()[1];
			float tmpy = 15 * boundaryY / 20 - (radius + sqrt(3) * radius * (y - 1));
			float tmpx = oddFloor[x];


			for (auto& sph : spheres) {
				if (sph.getCenter()[0] == tmpx && sph.getCenter()[1] == tmpy && !sph.getdropvisited()) {
					sph.setdrop(false);
					setDrops(sph);
				}
			}

		}
		if (direction[1]) {
			int x = s.getXY()[0] - 1;
			int y = s.getXY()[1] - 1;
			float tmpy = 15 * boundaryY / 20 - (radius + sqrt(3) * radius * (y - 1));
			float tmpx = evenFloor[x];

			for (auto& sph : spheres) {
				if (sph.getCenter()[0] == tmpx && sph.getCenter()[1] == tmpy && !sph.getdropvisited()) {
					sph.setdrop(false);
					setDrops(sph);
				}
			}

		}
		if (direction[2]) {

			int x = s.getXY()[0];
			int y = s.getXY()[1] - 1;
			float tmpy = 15 * boundaryY / 20 - (radius + sqrt(3) * radius * (y - 1));
			float tmpx = evenFloor[x];

			for (auto& sph : spheres) {
				if (sph.getCenter()[0] == tmpx && sph.getCenter()[1] == tmpy && !sph.getdropvisited()) {
					sph.setdrop(false);
					setDrops(sph);
				}
			}

		}

		if (direction[3]) {
			int x = s.getXY()[0] + 1;
			int y = s.getXY()[1];
			float tmpy = 15 * boundaryY / 20 - (radius + sqrt(3) * radius * (y - 1));
			float tmpx = oddFloor[x];

			for (auto& sph : spheres) {
				if (sph.getCenter()[0] == tmpx && sph.getCenter()[1] == tmpy && !sph.getdropvisited()) {
					sph.setdrop(false);
					setDrops(sph);
				}
			}

		}
		if (direction[4]) {
			int x = s.getXY()[0];
			int y = s.getXY()[1] + 1;
			float tmpy = 15 * boundaryY / 20 - (radius + sqrt(3) * radius * (y - 1));
			float tmpx = evenFloor[x];

			for (auto& sph : spheres) {
				if (sph.getCenter()[0] == tmpx && sph.getCenter()[1] == tmpy && !sph.getdropvisited()) {
					sph.setdrop(false);
					setDrops(sph);
				}
			}

		}

		if (direction[5]) {
			int x = s.getXY()[0] - 1;
			int y = s.getXY()[1] + 1;
			float tmpy = 15 * boundaryY / 20 - (radius + sqrt(3) * radius * (y - 1));
			float tmpx = evenFloor[x];

			for (auto& sph : spheres) {
				if (sph.getCenter()[0] == tmpx && sph.getCenter()[1] == tmpy && !sph.getdropvisited()) {
					sph.setdrop(false);
					setDrops(sph);
				}
			}

		}
	}

	else {
		//west, nw, ne, east , se, sw
		if (direction[0]) {
			int x = s.getXY()[0] - 1;
			int y = s.getXY()[1];
			float tmpy = 15 * boundaryY / 20 - (radius + sqrt(3) * radius * (y - 1));
			float tmpx = evenFloor[x];

			for (auto& sph : spheres) {
				if (sph.getCenter()[0] == tmpx && sph.getCenter()[1] == tmpy && !sph.getdropvisited()) {
					sph.setdrop(false);
					setDrops(sph);
				}
			}

		}
		if (direction[1]) {
			int x = s.getXY()[0];
			int y = s.getXY()[1] - 1;
			float tmpy = 15 * boundaryY / 20 - (radius + sqrt(3) * radius * (y - 1));
			float tmpx = oddFloor[x];

			for (auto& sph : spheres) {
				if (sph.getCenter()[0] == tmpx && sph.getCenter()[1] == tmpy && !sph.getdropvisited()) {
					sph.setdrop(false);
					setDrops(sph);
				}
			}

		}
		//west, nw, ne, east , se, sw
		if (direction[2]) {
			int x = s.getXY()[0] + 1;
			int y = s.getXY()[1] - 1;
			float tmpy = 15 * boundaryY / 20 - (radius + sqrt(3) * radius * (y - 1));
			float tmpx = oddFloor[x];


			for (auto& sph : spheres) {
				if (sph.getCenter()[0] == tmpx && sph.getCenter()[1] == tmpy && !sph.getdropvisited()) {
					sph.setdrop(false);
					setDrops(sph);
				}
			}

		}

		if (direction[3]) {
			int x = s.getXY()[0] + 1;
			int y = s.getXY()[1];
			float tmpy = 15 * boundaryY / 20 - (radius + sqrt(3) * radius * (y - 1));
			float tmpx = evenFloor[x];

			for (auto& sph : spheres) {
				if (sph.getCenter()[0] == tmpx && sph.getCenter()[1] == tmpy && !sph.getdropvisited()) {
					sph.setdrop(false);
					setDrops(sph);
				}
			}

		}
		if (direction[4]) {
			int x = s.getXY()[0] + 1;
			int y = s.getXY()[1] + 1;
			float tmpy = 15 * boundaryY / 20 - (radius + sqrt(3) * radius * (y - 1));
			float tmpx = oddFloor[x];

			for (auto& sph : spheres) {
				if (sph.getCenter()[0] == tmpx && sph.getCenter()[1] == tmpy && !sph.getdropvisited()) {
					sph.setdrop(false);
					setDrops(sph);
				}
			}

		}

		if (direction[5]) {
			int x = s.getXY()[0];
			int y = s.getXY()[1] + 1;
			float tmpy = 15 * boundaryY / 20 - (radius + sqrt(3) * radius * (y - 1));
			float tmpx = oddFloor[x];

			for (auto& sph : spheres) {
				if (sph.getCenter()[0] == tmpx && sph.getCenter()[1] == tmpy && !sph.getdropvisited()) {
					sph.setdrop(false);
					setDrops(sph);
				}
			}

		}


	}

}

void doDrops() {
	for (auto& sph : spheres) {
		if (!sph.notShooted) {
			sph.setdrop(true);
			sph.setdropvisited(false);

		}
	}

	for (auto& sph : spheres) {
		if (sph.getXY()[1] == 1) {
			setDrops(sph);
		}
	}




	vector<SolidSphere>::iterator it;
	Isvisited_Drop a;

	//for (it = spheres.begin(); it != spheres.end(); it++) {
	//	if (it->getdrop() == true) {
	//		it->setVelocity(0, -5.0, 0);
	//		dropping = true;
	//	
	//	}
	//}

	for (auto& sph : spheres) {
		if (sph.getdrop()) {
			sph.setVelocity(0.0, -5.0, 0.0);

			dropping = true;

		}

	}









}





class CollisionHandling
{
public:
	void operator()(SolidSphere& sph1, SolidSphere& sph2);
};

void CollisionHandling::operator()(SolidSphere& sph1, SolidSphere& sph2) {
	/* Implement */
	CollisionDetection check;

	if (check(sph1, sph2)) {

		sph1.setVelocity(0, 0, 0);
		sph2.setVelocity(0, 0, 0);
		collided();
		if (sph1.getCenter()[1] - sph2.getCenter()[1] >= 0.5 * radius) {
			sph1.setFloor(sph2.getFloor() - 1);



		}
		else if (sph1.getCenter()[1] - sph2.getCenter()[1] > -0.5 * radius) {
			sph1.setFloor(sph2.getFloor());

		}
		else if (sph1.getCenter()[1] - sph2.getCenter()[1] <= -0.5 * radius) {

			sph1.setFloor(sph2.getFloor() + 1);

		}


		settingPosition(sph1);




		if (sph1.getCenter()[1] - radius < -14 * boundaryY / 20)
			gameover = 1;

		removeAlgorithm(sph1);



	}



}

CollisionHandling colHandler;

float red[3] = { 1.0,0.0,0.0 };
float green[3] = { 0.0,1.0,0.0 };
float blue[3] = { 0.0,0.0,1.0 };
float yellow[3] = { 1.0,1.0,0.0 };
float pink[3] = { 1.0,0.0,1.0 };
float silver[3] = { 0.19225,0.19225,0.19225 };




using namespace std;


void drawCharacters(void* font, const string c, float x, float y) {
	glColor3f(0.0, 1.0, 0.0);
	glRasterPos2f(x, y);
	for (int i = 0; i < c.length(); i++)
		glutBitmapCharacter(font, c[i]);


}





void makeBubble() {
	SolidSphere tmp(radius, 100, 100);
	tmp.setCenter(-17 * boundaryX / 20, -18 * boundaryY / 20, 0);


	tmp.setVelocity(0, 0, 0);

	srand((unsigned int)time(0));

	int cRand = rand() % 5;

	if (cRand == 0) { //RED

		tmp.setMTL(red);
		tmp.setBallColor(0);

	}
	else if (cRand == 1) {//GREEN

		tmp.setMTL(green);
		tmp.setBallColor(1);

	}

	else if (cRand == 2) {	//BLUE

		tmp.setMTL(blue);
		tmp.setBallColor(2);

	}
	else if (cRand == 3) { //YELLOW

		tmp.setMTL(yellow);
		tmp.setBallColor(3);

	}
	else { //PINK

		tmp.setMTL(pink);
		tmp.setBallColor(4);

	}


	spheres.push_back(tmp);



}




void collided() {

	doing = 0;
	limited_start_time = limited_end_time;

}

void keyboards(unsigned char key, int x, int y) {
	switch (key) {
	case ' ':
		if (doing == 0) {
			doing = 1;
			spheres[spheres.size() - 2].setVelocity(10 * cos(angle * (PI / 180)), 10 * sin(angle * (PI / 180)), 0);
			spheres[spheres.size() - 2].notShooted = false;
			spheres.back().setCenter(0, -17 * boundaryY / 20, 0);
			makeBubble();
			limited_start_time = limited_end_time;
			printingtime = 0;
			angle = 90;
			arrows.begin()->setAngle(angle);
		}
		break;


	}


}

void keyboard(int key, int x, int y) {

	switch (key)
	{
		/*case GLUT_KEY_UP:
			if (doing == 0) {
				doing = 1;
				spheres[spheres.size() - 2].setVelocity(10*cos(angle*(PI/180)), 10*sin(angle * (PI / 180)), 0);
				spheres.back().setCenter(0, -17 * boundaryY / 20, 0);
				makeBubble();
				limited_start_time = limited_end_time;
				printingtime = 0;
				angle = 90;
				arrows.begin()->setAngle(angle);
			}
			break;*/

	case GLUT_KEY_RIGHT: // GLUT_KEY_RIGHT ('' 없이 하는거임.)
		if (doing == 0) {
			if (angle >= 20) {
				angle -= 10;
				arrows.begin()->setAngle(angle);

			}
		}
		break;
	case GLUT_KEY_LEFT: //GLUT_ KEY_LEFT
		if (doing == 0) {
			if (angle <= 160) {
				angle += 10;
				arrows.begin()->setAngle(angle);
			}
		}
		break;
	default:
		break;
	}



}





void init() {
	light = new Light(boundaryX, boundaryY, boundaryX / 2, GL_LIGHT0);
	light->setAmbient(0.5, 0.5, 0.5, 1.0);
	light->setDiffuse(0.7, 0.7, 0.7, 1.0);
	light->setSpecular(1.0, 1.0, 1.0, 1.0);


	//위와 아래 경계선 설정

	VectorN<float, 2> under1;
	under1[0] = -boundaryX;
	under1[1] = -14 * boundaryY / 20;
	VectorN<float, 2> under2;
	under2[0] = boundaryX;
	under2[1] = -14 * boundaryY / 20;
	Line underLine(under1, under2);


	VectorN<float, 2> upper1;
	upper1[0] = -boundaryX;
	upper1[1] = 15 * boundaryY / 20;

	VectorN<float, 2> upper2;
	upper2[0] = boundaryX;
	upper2[1] = 15 * boundaryY / 20;
	Line upperLine(upper1, upper2);

	lines.push_back(underLine);
	lines.push_back(upperLine);

	SolidSphere startBubble(radius, 100, 100);
	startBubble.setCenter(0, -17 * boundaryY / 20, 0);
	startBubble.setVelocity(0, 0, 0);
	startBubble.setMTL(red);
	startBubble.setBallColor(0);
	spheres.push_back(startBubble);



	SolidSphere nextBubble(radius, 100, 100);
	nextBubble.setCenter(-17 * boundaryX / 20, -18 * boundaryY / 20, 0);
	nextBubble.setVelocity(0, 0, 0);
	nextBubble.setMTL(yellow);
	nextBubble.setBallColor(3);
	spheres.push_back(nextBubble);

	VectorN<float, 3> a;
	a[0] = 0;
	a[1] = -boundaryY;
	a[2] = 0;

	Arrow arrow(a);
	arrow.setAngle(angle);
	arrow.setMTL(silver);
	arrow.setVelocity(0, 0, 0);

	arrows.push_back(arrow);




}


bool alldropped(SolidSphere& s) {
	if (s.getCenter()[1] < -14 * boundaryY / 20 && s.getdrop() == true)
		return true;
	return false;

}


void idle() {
	if (phase != 0 && phase != 1) {
		arrows.begin()->draw();

		if (!gameover) {
			limited_end_time = clock() / CLOCKS_PER_SEC;
			if (doing != 1 && !dropping) {




				if (limited_end_time - limited_start_time >= timelimit) {
					//자동발사 부분

					doing = 1;
					spheres[spheres.size() - 2].setVelocity(10 * cos(angle * (PI / 180)), 10 * sin(angle * (PI / 180)), 0);
					spheres[spheres.size() - 2].notShooted = false;


					spheres.back().setCenter(0, -17 * boundaryY / 20, 0);
					//다음 공 추가

					makeBubble();


					limited_start_time = limited_end_time;
					printingtime = 0;
					angle = 90;
					arrows.begin()->setAngle(angle);

				}
				if (limited_end_time - limited_start_time - printingtime >= 1) {
					printingtime++;
				}
			}
			else {
				end_clock = clock();

				if (end_clock - start_clock >= fps) {

					int before = spheres.size();
					int after = spheres.size();
					if (spheres.size() >= 3) {
						if (dropping == false) {
							for (int i = 0; i < spheres.size() - 3; i++) {

								after = spheres.size();
								if (before - after != 0)
									break;
								colHandler(spheres[spheres.size() - 3], spheres[i]);

							}



						}
						if (before == after) {

							if (spheres[spheres.size() - 3].getCenter()[0] + spheres[spheres.size() - 3].getRadius() >= boundaryX ||
								spheres[spheres.size() - 3].getCenter()[0] - spheres[spheres.size() - 3].getRadius() <= -boundaryX)
								spheres[spheres.size() - 3].setVelocity(-spheres[spheres.size() - 3].getVelocity()[0], spheres[spheres.size() - 3].getVelocity()[1], spheres[spheres.size() - 3].getVelocity()[2]);
							if (spheres[spheres.size() - 3].getCenter()[1] + spheres[spheres.size() - 3].getRadius() >= 15 * boundaryY / 20) {
								spheres[spheres.size() - 3].setVelocity(0, 0, 0);

								spheres[spheres.size() - 3].setFloor(1);

								settingPosition(spheres[spheres.size() - 3]);

								collided();
								removeAlgorithm(spheres[spheres.size() - 3]);
							}

						}
					}

					for (auto& sph : spheres) {
						sph.move();

					}

					if (dropping == true) {

						vector<SolidSphere>::iterator it;

						while ((it = find_if(spheres.begin(), spheres.end(), alldropped)) != spheres.end()) {
							score += 30;
							spheres.erase(it);
						}




						int count = 0;
						for (auto& sph : spheres) {
							if (sph.getdrop() == true) {
								count++;
								sph.setVelocity(0.0, -5.0, 0.0);

							}
						}






						if (count == 0) {
							dropping = false;
							for (auto& sph : spheres) {
								sph.setdrop(false);
								sph.setdropvisited(false);
							}

							limited_start_time = limited_end_time;

						}


					}



					start_clock = end_clock;
				}
			}
		}
	}
	glutPostRedisplay();
}

bool pressed = false;

void processMouse(int button, int state, int x, int y) {
	if (button == 0 && state == 1) {
		mouse[0] = x;
		mouse[1] = y;
		pressed = true;

	}

}


void processMouse1(int button, int state, int x, int y) {
	if (button == 0 && state == 1) {
		mouse1[0] = x;
		mouse1[1] = y;
		pressed = true;

	}

}

void renderScene() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (phase == 0) {


		drawCharacters(GLUT_BITMAP_TIMES_ROMAN_24, "CHOOSE BALL SPEED", -120, 200);


		glColor3f(1, 1, 1);
		glBegin(GL_QUADS);
		glVertex2f(-200, 150);
		glVertex2f(200, 150);
		glVertex2f(200, 50);
		glVertex2f(-200, 50);
		glEnd();


		glColor3f(1, 1, 1);
		glBegin(GL_QUADS);
		glVertex2f(-200, 25);
		glVertex2f(200, 25);
		glVertex2f(200, -75);
		glVertex2f(-200, -75);
		glEnd();

		glColor3f(1, 1, 1);
		glBegin(GL_QUADS);
		glVertex2f(-200, -100);
		glVertex2f(200, -100);
		glVertex2f(200, -200);
		glVertex2f(-200, -200);
		glEnd();
		drawCharacters(GLUT_BITMAP_TIMES_ROMAN_24, "SLOW", -30, 90);
		drawCharacters(GLUT_BITMAP_TIMES_ROMAN_24, "NORMAL", -50, -35);
		drawCharacters(GLUT_BITMAP_TIMES_ROMAN_24, "FAST", -30, -160);

		glutMouseFunc(processMouse);



		if (mouse[0] >= 25 && mouse[0] <= 425) {

			if (mouse[1] <= 250 && mouse[1] >= 150) {

				fps /= 30;
				phase = 1;
			}
			else if (mouse[1] <= 375 && mouse[1] >= 275) {
				fps /= 60;

				phase = 1;
			}
			else if (mouse[1] <= 500 && mouse[1] >= 400) {
				fps /= 120;
				phase = 1;
			}
		}

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-boundaryX, boundaryX, -boundaryY, boundaryY, -100.0, 100.0);


		if (phase == 1) {
			mouse[0] = 0; mouse[1] = 0;
		}



		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

	}

	else if (phase == 1) {
		drawCharacters(GLUT_BITMAP_TIMES_ROMAN_24, "CHOOSE TIME LIMIT", -120, 200);


		glColor3f(1, 1, 1);
		glBegin(GL_QUADS);
		glVertex2f(-200, 150);
		glVertex2f(200, 150);
		glVertex2f(200, 50);
		glVertex2f(-200, 50);
		glEnd();


		glColor3f(1, 1, 1);
		glBegin(GL_QUADS);
		glVertex2f(-200, 25);
		glVertex2f(200, 25);
		glVertex2f(200, -75);
		glVertex2f(-200, -75);
		glEnd();

		glColor3f(1, 1, 1);
		glBegin(GL_QUADS);
		glVertex2f(-200, -100);
		glVertex2f(200, -100);
		glVertex2f(200, -200);
		glVertex2f(-200, -200);
		glEnd();
		drawCharacters(GLUT_BITMAP_TIMES_ROMAN_24, "3 SECONDS", -70, 90);
		drawCharacters(GLUT_BITMAP_TIMES_ROMAN_24, "5 SECONDS", -70, -35);
		drawCharacters(GLUT_BITMAP_TIMES_ROMAN_24, "8 SECONDS", -70, -160);

		glutMouseFunc(processMouse1);



		if (mouse1[0] >= 25 && mouse1[0] <= 425) {


			if (mouse1[1] <= 250 && mouse1[1] >= 150) {

				timelimit = 3;
				phase = 2;
				limited_start_time = clock() / CLOCKS_PER_SEC;

			}
			else if (mouse1[1] <= 375 && mouse1[1] >= 275) {
				timelimit = 5;
				phase = 2;
				limited_start_time = clock() / CLOCKS_PER_SEC;

			}
			else if (mouse1[1] <= 500 && mouse1[1] >= 400) {
				timelimit = 8;
				phase = 2;
				limited_start_time = clock() / CLOCKS_PER_SEC;
			}
		}

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-boundaryX, boundaryX, -boundaryY, boundaryY, -100.0, 100.0);


		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();



	}



	else {
		if (!gameover) {

			drawCharacters(GLUT_BITMAP_9_BY_15, "SCORE: ", -19 * boundaryX / 20, 17 * boundaryY / 20);


			string scorestr = to_string(score);

			drawCharacters(GLUT_BITMAP_9_BY_15, scorestr + " points", -11 * boundaryX / 20, 17 * boundaryY / 20);

			drawCharacters(GLUT_BITMAP_9_BY_15, "TIME: ", 0, 17 * boundaryY / 20);

			int timetmp = timelimit - printingtime;

			string timestr = to_string(timetmp);
			drawCharacters(GLUT_BITMAP_9_BY_15, timestr, 5 * boundaryX / 20, 17 * boundaryY / 20);
			drawCharacters(GLUT_BITMAP_HELVETICA_10, "NEXT", -28 * boundaryX / 30, -23 * boundaryY / 30);


			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(-boundaryX, boundaryX, -boundaryY, boundaryY, -100.0, 100.0);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			for (auto ln : lines)
				ln.draw();

			arrows.begin()->draw();





			glEnable(GL_DEPTH_TEST);
			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
			light->draw();

			for (auto ar : arrows)
				ar.draw();

			for (auto sp : spheres)
				sp.draw();



			glDisable(GL_DEPTH_TEST);
			glDisable(GL_LIGHTING);
			glDisable(GL_LIGHT0);

		}

		else {

			drawCharacters(GLUT_BITMAP_TIMES_ROMAN_24, "GAME OVER ", -100, 0);

		}
	}
	glutSwapBuffers();
}

int main(int argc, char** argv) {

	for (int i = 0; i < 10; i++)
		oddFloor[i] = WIDTH / 20 + i * WIDTH / 10 - boundaryX;

	for (int i = 0; i < 9; i++)
		evenFloor[i] = WIDTH / 10 + i * WIDTH / 10 - boundaryX;
	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(300, 0);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Move spheres and handle collisions");
	init();

	// register callbacks
	glutDisplayFunc(renderScene);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboards);
	glutSpecialFunc(keyboard);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 0;
}
