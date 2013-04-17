#ifndef GLOBALS_H
#define GLOBALS_H

#include <btBulletDynamicsCommon.h>
#include "Tiempo.h"

#define PI 3.14

//Variables - Mundo dinamico
static btBroadphaseInterface *broadphase;
static btDefaultCollisionConfiguration *collisionConfiguration;
static btSequentialImpulseConstraintSolver *solver;
static btCollisionDispatcher *dispatcher;
static btDiscreteDynamicsWorld *dynamicsWorld;

//Tiempo
static Tiempo timer;
static double elapsed = 0.0;
static int animationPeriod = 10;



#endif // GLOBALS_H
