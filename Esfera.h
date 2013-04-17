
#if !defined(BALL_H)
#define BALL_H

#include <GL/glut.h>

#include <iostream>
#include <math.h>

#include "Globals.h"

// Tipos de bolas
enum {SOLIDO = 0, RAYAS, CUE, BOLA8};

//Colores bolas
enum {BLANCO = 0,AMARILLO,AZUL,ROJO,PURPURA,NARANJA,VERDE,MARRON,NEGRO};

#define MASA 1
#define RADIO 2

#define MAX_BOLAS 100

using namespace std;

class Esfera
{
    private:
        int color;
        int tipo;
        float x, y, z; // posicion de la bola

        btCollisionShape *shape;
        btMotionState *motionState;
        btRigidBody *rigidBody;
        btScalar ballMatrix[16];
	
	public:
        Esfera();
        ~Esfera();

        Esfera(float x, float y, float z, int color, int tipo);

        void draw(); //Dibujar esfera

        void agregarCuerpo(btDiscreteDynamicsWorld *dynamicsWorld); // Agrega esfera al mundo

        void update(); //Actualizar propiedades fisicas de esfera
        void reset();  //Estado inicial de la esfera

        btRigidBody* getBody();
        btTransform  getTrans();

        void setPosicion(float x,float y,float z);
};

#endif

