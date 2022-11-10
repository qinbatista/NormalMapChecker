
int TextureMode;
void DoTextureMenu(int);

void InitMenus()
{
    glutSetWindow(MainWindow);

    int numColors = sizeof(Colors) / (3 * sizeof(int));
    int colormenu = glutCreateMenu(DoColorMenu);
    for (int i = 0; i < numColors; i++)
    {
        glutAddMenuEntry(ColorNames[i], i);
    }

    int axesmenu = glutCreateMenu(DoAxesMenu);
    glutAddMenuEntry("Off", 0);
    glutAddMenuEntry("On", 1);

    int depthcuemenu = glutCreateMenu(DoDepthMenu);
    glutAddMenuEntry("Off", 0);
    glutAddMenuEntry("On", 1);

    int depthbuffermenu = glutCreateMenu(DoDepthBufferMenu);
    glutAddMenuEntry("Off", 0);
    glutAddMenuEntry("On", 1);

    int depthfightingmenu = glutCreateMenu(DoDepthFightingMenu);
    glutAddMenuEntry("Off", 0);
    glutAddMenuEntry("On", 1);

    int debugmenu = glutCreateMenu(DoDebugMenu);
    glutAddMenuEntry("Off", 0);
    glutAddMenuEntry("On", 1);

    int projmenu = glutCreateMenu(DoProjectMenu);
    glutAddMenuEntry("Orthographic", ORTHO);
    glutAddMenuEntry("Perspective", PERSP);

    int viewModeMenu = glutCreateMenu(DoViewModeMenu);
    glutAddMenuEntry("Outside", OUTSIDE);
    glutAddMenuEntry("Inside", INSIDE);

    int TextureMenu = glutCreateMenu(DoTextureMenu);
    glutAddMenuEntry("Off Texture", OFF);
    glutAddMenuEntry("On Texture", ON);
    glutAddMenuEntry("Distort Texture", DISTORT);

    int mainmenu = glutCreateMenu(DoMainMenu);
    glutAddSubMenu("Axes", axesmenu);
    glutAddSubMenu("Axis Colors", colormenu);

#ifdef DEMO_DEPTH_BUFFER
    glutAddSubMenu("Depth Buffer", depthbuffermenu);
#endif

#ifdef DEMO_Z_FIGHTING
    glutAddSubMenu("Depth Fighting", depthfightingmenu);
#endif

    glutAddSubMenu("Depth Cue", depthcuemenu);
    glutAddSubMenu("Projection", projmenu);
    glutAddMenuEntry("Reset", RESET);
    glutAddSubMenu("ViewMode", viewModeMenu);
    glutAddSubMenu("TextureMode", TextureMenu);
    glutAddSubMenu("Debug", debugmenu);
    glutAddMenuEntry("Quit", QUIT);

    // attach the pop-up menu to the right mouse button:

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
void Reset()
{
    Light0On = Light1On = Light2On = false;
    bothVF = VOpen = FOpen = true;


    ActiveButton = 0;
    AxesOn = 1;
    DebugOn = 0;
    DepthBufferOn = 1;
    DepthFightingOn = 0;
    DepthCueOn = 0;
    Scale = 1.0;
    ShadowsOn = 0;
    WhichColor = WHITE;
    WhichProjection = PERSP;
    Xrot = Yrot = 0.;
}
void DoViewModeMenu(int id)
{
    Reset();
    WhichViewMode = id;
    glutSetWindow(MainWindow);
    glutPostRedisplay();
}

void DoTextureMenu(int id)
{
    Reset();
    TextureMode = id;
    glutSetWindow(MainWindow);
    glutPostRedisplay();
}
void DoAxesMenu(int id)
{
    AxesOn = id;
    glutSetWindow(MainWindow);
    glutPostRedisplay();
}

void DoColorMenu(int id)
{
    WhichColor = id - RED;

    glutSetWindow(MainWindow);
    glutPostRedisplay();
}

void DoDebugMenu(int id)
{
    DebugOn = id;

    glutSetWindow(MainWindow);
    glutPostRedisplay();
}

void DoDepthBufferMenu(int id)
{
    DepthBufferOn = id;

    glutSetWindow(MainWindow);
    glutPostRedisplay();
}

void DoDepthFightingMenu(int id)
{
    DepthFightingOn = id;

    glutSetWindow(MainWindow);
    glutPostRedisplay();
}

void DoDepthMenu(int id)
{
    DepthCueOn = id;

    glutSetWindow(MainWindow);
    glutPostRedisplay();
}

// main menu callback:

void DoMainMenu(int id)
{
    switch (id)
    {
    case RESET:
        Reset();
        break;

    case QUIT:
        // gracefully close out the graphics:
        // gracefully close the graphics window:
        // gracefully exit the program:
        glutSetWindow(MainWindow);
        glFinish();
        glutDestroyWindow(MainWindow);
        exit(0);
        break;

    default:
        fprintf(stderr, "Don't know what to do with Main Menu ID %d\n", id);
    }

    glutSetWindow(MainWindow);
    glutPostRedisplay();
}

void DoProjectMenu(int id)
{
    WhichProjection = id;

    glutSetWindow(MainWindow);
    glutPostRedisplay();
}

// use glut to display a string of characters using a raster font:

void DoRasterString(float x, float y, float z, char *s)
{
    glRasterPos3f((GLfloat)x, (GLfloat)y, (GLfloat)z);

    char c; // one character to print
    for (; (c = *s) != '\0'; s++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }
}

// use glut to display a string of characters using a stroke font:

void DoStrokeString(float x, float y, float z, float ht, char *s)
{
    glPushMatrix();
    glTranslatef((GLfloat)x, (GLfloat)y, (GLfloat)z);
    float sf = ht / (119.05f + 33.33f);
    glScalef((GLfloat)sf, (GLfloat)sf, (GLfloat)sf);
    char c; // one character to print
    for (; (c = *s) != '\0'; s++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
    }
    glPopMatrix();
}

// return the number of seconds since the start of the program:

float ElapsedSeconds()
{
    // get # of milliseconds since the start of the program:

    int ms = glutGet(GLUT_ELAPSED_TIME);

    // convert it to seconds:

    return (float)ms / 1000.f;
}
// called when user resizes the window:

void Resize(int width, int height)
{
    // don't really need to do anything since window size is
    // checked each time in Display( ):

    glutSetWindow(MainWindow);
    glutPostRedisplay();
}

// handle a change to the window's visibility:

void Visibility(int state)
{
    if (DebugOn != 0)
        fprintf(stderr, "Visibility: %d\n", state);

    if (state == GLUT_VISIBLE)
    {
        glutSetWindow(MainWindow);
        glutPostRedisplay();
    }
    else
    {
        // could optimize by keeping track of the fact
        // that the window is not visible and avoid
        // animating or redrawing it ...
    }
}
