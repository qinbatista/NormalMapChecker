//	Author:			Yupeng Qin

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define _USE_MATH_DEFINES
#include <math.h>
#ifdef WIN32
#include <windows.h>
#pragma warning(disable : 4996)
#endif
#include <GL/glew.h>
#include <OpenGL/GL.h>
#include <OpenGL/glu.h>
#include <list>
#include <iostream>
#include "MyLibrary/glut.h"
#include "sample.h"
#include "System/enum.h"
#include "System/initialize.h"
#include "System/controller.h"
#include "System/menu.h"
#include "System/display.h"
#include "System/loadobjfile.h"
#include "System/curve.h"
#include "Objects/cessna.550"
#include "Objects/plane.h"
#include "Objects/bmptotexture.h"
#include "Objects/Axes.h"
#include "Objects/osusphere.h"
#include "Objects/TextureTest.h"
#include "Shader/glslprogram.h"
using namespace std;
list<GLuint> modelList;
GLSLProgram *Pattern;
GLSLProgram *Lighting;
GLuint patternObj;
GLuint lightObj;
Curve Curves[10]; // if you are creating a pattern of curves
Curve Stem;       // if you are not

GLuint texture;
GLuint panel2D;
int main(int argc, char *argv[])
{
    MetaInitial(argc, argv);
    return 0;
}
void WorldInitial()
{
    CreateAxis();
    // Textures
    texture = LoadTexture("Texture/worldtex.bmp");
    //Objects
    panel2D = Panel2D();
    // Lights
    SetLight();
    SetPointLight_GL_SMOOTH(GL_LIGHT1, 0, 0, 100,    1, 1, 1);

}

void WorldDisplay()
{

    BindTexture(panel2D,texture);
    OSUSphereDisplayTextureOn(OSUSphere(1.0, 20, 20, 0, 1, 0),texture);
}

void WorldUpdate()
{
    int ms = glutGet(GLUT_ELAPSED_TIME); // milliseconds
    TimeCycle = sin((float)ms / (float)MS_IN_THE_ANIMATION_CYCLE);
    OSUSphereAnimation(TimeCycle);
}