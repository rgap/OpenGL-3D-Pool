#if !defined(BALL_CPP)
#define BALL_CPP

#include "Esfera.h"

Esfera::Esfera(){
    Esfera(0,RADIO,0, BLANCO, SOLIDO);
}

Esfera::Esfera(float x, float y, float z, int color, int tipo){
    this->x = x;
    this->y = y;
    this->z = z;

    this->color = color;
    this->tipo = tipo;

}

Esfera::~Esfera(){
}

void Esfera::setPosicion(float tx,float ty,float tz){
    this->x += tx;
    this->y += ty;
    this->z += tz;
}

void Esfera::draw(){

    float colores[3] = {0, 0, 0};

    // Definir color
    switch(this->color)
	{
        case BLANCO:
            colores[0] = 1.0; colores[1] = 1.0; colores[2] = 1.0;
			break;
        case AMARILLO:
            colores[0] = 1.0; colores[1] = 1.0; colores[2] = 0.0;
			break;
        case AZUL:
            colores[0] = 0.0; colores[1] = 0.0; colores[2] = 1.0;
			break;
        case ROJO:
            colores[0] = 1.0; colores[1] = 0.0; colores[2] = 0.0;
			break;
        case PURPURA:
            colores[0] = 0.5; colores[1] = 0.0; colores[2] = 0.5;
			break;
        case NARANJA:
            colores[0] = 1.0; colores[1] = 0.5; colores[2] = 0.0;
			break;
        case VERDE:
            colores[0] = 0.0; colores[1] = 1.0; colores[2] = 0.0;
			break;
        case MARRON:
            colores[0] = 0.4; colores[1] = 0.2; colores[2] = 0.0;
			break;
        case NEGRO:
            colores[0] = 0.0; colores[1] = 0.0; colores[2] = 0.0;
			break;
		default:
			break;
    }

    //Dibujar esfera
    GLUquadricObj *quadratic = gluNewQuadric();

    glPushMatrix();

    //Posicion
    glTranslatef(this->x, this->y, this->z);

    glColor3f(colores[0],colores[1],colores[2]);

    gluSphere(quadratic,RADIO,30,30);

    glPopMatrix();
}

//Agregar cuerpo al mundo
void Esfera::agregarCuerpo(btDiscreteDynamicsWorld *world){

    shape = new btSphereShape(RADIO);
    motionState = new btDefaultMotionState(
                  btTransform(btQuaternion(rand(),rand(),rand(),1), btVector3(this->x,this->y,this->z))
                  );

    btScalar mass = MASA;
    btVector3 inertia(0,0,0);
    shape->calculateLocalInertia(mass,inertia);

    btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass,motionState,shape,inertia);
    rigidBody = new btRigidBody(rigidBodyCI);
    rigidBody->setRestitution(0.9);
    rigidBody->setDamping(0,0.8);

    world->addRigidBody(rigidBody);
}

void Esfera::update(){

    btTransform trans;
    rigidBody->getMotionState()->getWorldTransform(trans);
    trans.getOpenGLMatrix(ballMatrix); // set ballMatrix to the matrix from opengl
}

void Esfera::reset(){

    rigidBody->setLinearVelocity(btVector3(0, 0, 0));
    rigidBody->setAngularVelocity(btVector3(0, 0, 0));
    delete rigidBody->getMotionState();
    motionState =
        new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), btVector3(x, y, z)));
    rigidBody->setMotionState(motionState);
}

btRigidBody* Esfera::getBody(){
    return rigidBody;
}

btTransform Esfera::getTrans(){

    btTransform trans;
    rigidBody->getMotionState()->getWorldTransform(trans);
    return trans;
}

#endif

