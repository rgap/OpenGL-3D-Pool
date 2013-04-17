#if !defined(TABLE_H)
#define TABLE_H

#include <GL/glut.h>

#include <iostream>
#include <math.h>

#define numPuntosTablero 8
#define numPuntosParedCorta 6
#define numPuntosParedLarga 6

using namespace std;

class Table
{
	private:

        static const float puntosTablero[numPuntosTablero][3];
        static const float puntosParedCorta[numPuntosParedCorta][3];
        static const float puntosParedLarga[numPuntosParedLarga][3];

    public:
		Table();
        ~Table();

		void draw();
};

#endif

