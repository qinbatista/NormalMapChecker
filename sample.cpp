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
GLuint texture_Normal;
GLuint panel2D;
int main(int argc, char *argv[])
{
    MetaInitial(argc, argv);
    return 0;
}
void WorldInitial()
{
    CreateAxis();// create the axis
    SetLight();// Lights


    texture = LoadTexture("Texture/dragon.bmp");//earth texture
    texture_Normal = LoadTexture("Texture/dragon.png");//earth texture
    // texture = LoadTexture("Texture/worldtex.bmp"); // my texture
    panel2D = Panel2D();// create panel objects

    //Initial shader
    Pattern = new GLSLProgram();
    Pattern->Create("Shader/normal.vert", "Shader/normal.frag");
    Pattern->SetVerbose(false);

}

void WorldDisplay()
{
    SetPointLight_GL_SMOOTH(GL_LIGHT1, 0, 0, 1,    1, 1, 1);
    glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, texture);
	// glActiveTexture(GL_TEXTURE6);
	// glBindTexture(GL_TEXTURE_2D, texture_Normal);

    //Display Shader
    Pattern->Use();
    Pattern->SetUniformVariable("uKa", 1);
    Pattern->SetUniformVariable("uKd", 1);
    Pattern->SetUniformVariable("uKs", 1);
    Pattern->SetUniformVariable("uShininess", 1);
    Pattern->SetUniformVariable("uFreq", 1);
    // Pattern->SetUniformVariable("Color_Map", 5);
    // Pattern->SetUniformVariable("Normal_Map", 6);
    // Pattern->SetUniformVariable("Normal_Map", GL_TEXTURE5);
    BindTexture(panel2D, texture);
    Pattern->UnUse();
}

void WorldUpdate()
{
    int ms = glutGet(GLUT_ELAPSED_TIME); // milliseconds
    TimeCycle = sin((float)ms / (float)MS_IN_THE_ANIMATION_CYCLE);
}