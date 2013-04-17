TEMPLATE = app
CONFIG += console
CONFIG -= qt

LIBS += -lglut -lGLU -lGL -lrt `pkg-config bullet --libs`

INCLUDEPATH += /opt/BulletPhysicsEngine/src

SOURCES += main.cpp \
    Tronera.cpp \
    Esfera.cpp \
    Tablero.cpp \
    Tiempo.cpp

HEADERS += \
    Globals.h \
    Tablero.h \
    Esfera.h \
    Tronera.h \
    Tiempo.h

