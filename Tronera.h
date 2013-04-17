
#if !defined(CUP_H)
#define CUP_H

#include <GL/glut.h>

#include <iostream>
#include <math.h>

#define sideBottom_length 8
#define sideWall_length 8
#define cornerBottom_length 8
#define cornerWall_length 8

using namespace std;

class Tronera
{
    private:

		// vertex arrays for drawing the 6 cups. sideBottom and cornerBottom are not used, cups are just shutes, balls can fall out
		static const float sideBottomVertex[sideBottom_length][3];
		static const float sideWallVertex[sideWall_length][3];
		static const float cornerBottomVertex[cornerBottom_length][3];
        static const float cornerWallVertex[cornerWall_length][3];

	public:
        Tronera();
        ~Tronera();
		void draw();
};

#endif

