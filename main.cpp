#include <GL/glut.h>

#include <iostream>
#include <math.h>

#include "Tronera.h"
#include "Esfera.h"
#include "Tablero.h"

#include "Globals.h"

using namespace std;

// Objetos
static int contEsferas = 0;
static Esfera esfera[MAX_BOLAS];
static Table tablero;
static Tronera tronera;

// Angulos de vision
static float camera_angle_x = 0;
static float camera_angle_y = 0.5;

//Perspectiva
static float angulo=100, aspecto=0;

//Camara
static float cenX=0,cenY=0,cenZ=0,vpX=0,vpY=1,vpZ=0;

static char texto[30];

static int fX,fY,fZ;

void crearEsferas(){

    esfera[0]= Esfera(30, RADIO, 0, BLANCO, CUE); // Bola blanca
    contEsferas++;

    int tipos[][2] = {
        {AZUL  , RAYAS},
        {AMARILLO,  SOLIDO},
        {VERDE , RAYAS},
        {PURPURA,  SOLIDO},
        {NEGRO ,  SOLIDO}, // 8 ball
        {NARANJA,  SOLIDO},
        {VERDE ,  SOLIDO},
        {NARANJA, RAYAS},
        {MARRON ,  SOLIDO},
        {AMARILLO, RAYAS},
        {AZUL  ,  SOLIDO},
        {ROJO   , RAYAS},
        {PURPURA, RAYAS},
        {ROJO   ,  SOLIDO},
        {MARRON , RAYAS}
    };

    //Posiciones en triangulo

    float fudge = RADIO + .08;
    float paso = pow(3 * fudge, 0.5);
    int i = 0;
    float x, z;

    for (int row = 0; row < 5; row++){
        x = -paso * row;
        z = 0 - fudge * row;

        for (int nEsfera = 0; nEsfera < row + 1; nEsfera++){
            esfera[contEsferas] = Esfera(x - 10, RADIO, z, tipos[i][0],tipos[i][1]);

            i++;
            z += 2 * fudge;

            esfera[contEsferas].agregarCuerpo(dynamicsWorld);
            contEsferas++;
        }
    }
}

void myTickCallback(btDynamicsWorld *world, btScalar timeStep) {

    for (int i = 0; i < contEsferas; i++){
        btVector3 vel = esfera[i].getBody()->getLinearVelocity();

        if (vel.getY() > 0)
            vel.setY(0);

        esfera[i].getBody()->setLinearVelocity(vel);
    }
}

void inicializar(){

    glClearColor(0.0, 0.0, 0.0, 1.0);

    broadphase = new btDbvtBroadphase();
    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);

    solver = new btSequentialImpulseConstraintSolver;

    //Configuracion de mundo
    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0,-10,0));
    //dynamicsWorld->setInternalTickCallback(myTickCallback);

    //Agregar cuerpos al mundo
    //tronera.add(dynamicsWorld);
    //tablero.add(dynamicsWorld);

    //Crear y agregar Esferas al mundo
    crearEsferas();

    sprintf(texto, "Fuerza = %d", fX);

    timer.start_clock();
}

void mostrarTexto(char *cadena){
    glPushMatrix();
        glRasterPos3f(0,25,0);
        // Mostrar cada caracter
        while(*cadena)
             glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*cadena++);
    glPopMatrix();
}

void drawScene(){

    timer.end_clock();
    elapsed = timer.seconds();
    timer.start_clock();

    //Dibujar cuerpos

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_POLYGON_SMOOTH);
    glEnable(GL_LINE_SMOOTH);

    tablero.draw();

    tronera.draw();

    for (int i = 0; i < contEsferas;  i++)
        esfera[i].draw();

    //Texto
    glColor3f(1.0f,1.0f,1.0f);
    mostrarTexto(texto);

    glutSwapBuffers();
}


void parametrosVisualizacion(){

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(angulo, aspecto,0.1, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(45 * cos(camera_angle_x) * sin(camera_angle_y),
              45 * cos(camera_angle_y),
              45 * sin(camera_angle_x) * sin(camera_angle_y),
              cenX, cenY, cenZ, vpX, vpY, vpZ);
}

void resize(GLsizei w, GLsizei h){

    if ( h == 0 ) h = 1;

    glViewport(0, 0, w, h);

    aspecto = (GLfloat)w/(GLfloat)h;

    parametrosVisualizacion();
}

void specialKeyInput(int key, int x, int y){

    switch(key){

        case GLUT_KEY_UP:
            camera_angle_y += .05;
            break;
        case GLUT_KEY_DOWN:
            camera_angle_y -= .05;
            break;
        case GLUT_KEY_LEFT:
            camera_angle_x += 20 / PI;
            break;
        case GLUT_KEY_RIGHT:
            camera_angle_x -= 20 / PI;
            break;
        default:
            break;
    }

    parametrosVisualizacion();

    glutPostRedisplay();

}

void aplicarFuerzaTaco(){

    if (esfera[0].getBody()->getLinearVelocity().length() < 0.01 &&
        esfera[0].getBody()->getLinearVelocity().length() > -0.01){

        esfera[0].getBody()->activate(true);
        esfera[0].getBody()->applyCentralForce(btVector3(-20 * 10, 0, -20 * 10));
    }
}

void keyInput(unsigned char key, int x, int y){

    int tx=0,ty=0,tz=0;

    switch(key){
        case 27:
            exit(0);
            break;
        case 'c':
            aplicarFuerzaTaco();
            break;
        case '1':
            angulo -= 5;
            break;
        case '2':
            angulo += 5;
            break;

        case 'q':
            tx=1;
            break;
        case 'w':
            ty=1;
            break;
        case 'e':
            tz=1;
            break;
        case 'a':
            tx=-1;
            break;
        case 's':
            ty=-1;
            break;
        case 'd':
            tz=-1;
            break;

        case 'u':
            cenX++;
            break;
        case 'i':
            cenY++;
            break;
        case 'o':
            cenZ++;
            break;

        case 'j':
            cenX--;
            break;
        case 'k':
            cenY--;
            break;
        case 'l':
            cenZ--;
            break;

        default:
            break;
    }

    esfera[0].setPosicion(tx,ty,tz);

    parametrosVisualizacion();

    glutPostRedisplay();
}

void botonesMouse(int button, int state, int x, int y){

    /*
    if (button == GLUT_LEFT_BUTTON)
        if (state == GLUT_DOWN) // Zoom-in
            angulo -= 5;
    if (button == GLUT_RIGHT_BUTTON)
        if (state == GLUT_DOWN) // Zoom-out
            angulo += 5;

    parametrosVisualizacion();

    glutPostRedisplay();
    */
}

void mouseWheel(int button, int state, int x, int y){

    if ((button == 3) || (button == 4)){

        if (state == GLUT_UP) return;

        (button == 3) ? fX++ : fX--;
    }

    sprintf(texto, "Fuerza = %d", fX);

    glutPostRedisplay();
}

//Animar mundo segun tiempo
/*
void animate(int value){

    dynamicsWorld->stepSimulation(elapsed,0);

    //Actualizar Esferas
    for (int i = 0; i < contEsferas; i++)
        esfera[i].update();

    glutTimerFunc(animationPeriod, animate, 1);
    glutPostRedisplay();
}
*/

int main(int argc, char **argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(600,600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Billar-3D");

    inicializar();


    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);

    glutMouseFunc(botonesMouse);
    glutMouseFunc(mouseWheel);

    glutKeyboardFunc(keyInput);
    glutSpecialFunc(specialKeyInput);

    //Animacion
    //glutTimerFunc(5, animate, 1);

    glutMainLoop();

    return 0;
}

