#if !defined(TABLE_CPP)
#define TABLE_CPP

#include "Tablero.h"

Table::Table()
{
}

Table::~Table()
{
}

const float Table::puntosTablero[numPuntosTablero][3] = {
    {-40, 0, -20},
    {-40, 0, -20},
    { 40, 0, -20},
    { 40, 0, -20},
    { 40, 0,  20},
    { 40, 0,  20},
    {-40, 0,  20},
    {-40, 0,  20}
};

const float Table::puntosParedCorta[numPuntosParedCorta][3] = {
    {30, 0, -12.878},
    {30, 0,  12.878},
    {30, 2, -12.878},
    {30, 2,  12.878},
    {32.121, 2, -15},
    {32.121, 2,  15}
};

const float Table::puntosParedLarga[numPuntosParedLarga][3] = {
    {27.878, 0, 15},
    {   1.5, 0, 15},
    {27.878, 2, 15},
    {   1.5, 2, 15},
    {30, 2, 17.121},
    {   1.5, 2, 19}
};

void Table::draw()
{
	glPushMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    /////////////////////////// TABLERO //////////////////////////
    glColor3f(0.0, 0.5, 0.2); //VERDE

    glBegin(GL_POLYGON);
    for (int i = 0, length = numPuntosTablero; i < length; i++)
        glVertex3f( puntosTablero[i][0], puntosTablero[i][1], puntosTablero[i][2]);
	glEnd();

    /*
    ////////////////////// CONTORNO TABLERO - ANCHO //////////////////////
    glColor3f(0.5, 0.2, 0.0); //MARRON
    for (int j = 0; j < 2; j++){
		int n = 1;

		if (j == 0) n = -1;

        glBegin(GL_POLYGON);
        for (int i = 0, length = numPuntosParedCorta; i < length; i++)
            glVertex3f( n * puntosParedCorta[i][0], puntosParedCorta[i][1], puntosParedCorta[i][2]);
		glEnd();
	}

    ////////////////////// CONTORNO TABLERO - LARGO //////////////////////

    for (int j = 0; j < 2; j++){
		int n = 1;

		if (j == 0) n = -1;

		for (int m = 0; m < 2; m++){

			int k = 1;
			if (m == 0) k = -1;

            glBegin(GL_POLYGON);
            for (int i = 0, length = numPuntosParedLarga; i < length; i++)
                glVertex3f( n * puntosParedLarga[i][0], puntosParedLarga[i][1], k * puntosParedLarga[i][2]);
			glEnd();
		}
	}
    */

	glPopMatrix();
}

#endif

