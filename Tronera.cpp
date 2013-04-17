#if !defined(CUP_CPP)
#define CUP_CPP

#include "Tronera.h"

const float Tronera::sideWallVertex[sideWall_length][3] = {
	{  1.5,-2,  15},
	{  1.5, 2,  15},
	{  1.5,-2,19},
	{  1.5, 2,19},
	{ -1.5,-2,19},
	{ -1.5, 2,19},
	{ -1.5,-2,  15},
	{ -1.5, 2,  15}
	};

const float Tronera::cornerWallVertex[cornerWall_length][3] = {
	{27.878, -2, 15},
	{27.878,  2, 15},
	{30,     -2, 17.121},
	{30,      2, 17.121},
	{32.121, -2, 15},
	{32.121,  2, 15},
	{30    , -2, 12.878},
	{30    ,  2, 12.878},
	};

Tronera::Tronera()
{
}

Tronera::~Tronera(){
}

void Tronera::draw()
{
	glPushMatrix();
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glColor3f(0.5, 0.2, 1);

    //Troneras laterales
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < sideWall_length; i++)
		glVertex3f( sideWallVertex[i][0], sideWallVertex[i][1], sideWallVertex[i][2]);	
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < sideWall_length; i++)
		glVertex3f( sideWallVertex[i][0], sideWallVertex[i][1], -sideWallVertex[i][2]);	
	glEnd();

    //Troneras esquinas
	glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i < cornerWall_length; i++)
		glVertex3f( cornerWallVertex[i][0], cornerWallVertex[i][1], cornerWallVertex[i][2]);	
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < cornerWall_length; i++)
		glVertex3f( cornerWallVertex[i][0], cornerWallVertex[i][1], -cornerWallVertex[i][2]);	
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < cornerWall_length; i++)
		glVertex3f( -cornerWallVertex[i][0], cornerWallVertex[i][1], cornerWallVertex[i][2]);	
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < cornerWall_length; i++)
		glVertex3f( -cornerWallVertex[i][0], cornerWallVertex[i][1], -cornerWallVertex[i][2]);	
	glEnd();

	glPopMatrix();
}

#endif

