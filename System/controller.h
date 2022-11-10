bool Light0On, Light1On, Light2On;
bool bothVF, VOpen, FOpen;
// the keyboard callback:
void Keyboard(unsigned char c, int x, int y)
{
    if (DebugOn != 0)
        fprintf(stderr, "Keyboard: '%c' (0x%0x)\n", c, c);

    switch (c)
    {
    case 'o':
    case 'O':
        WhichProjection = ORTHO;
        break;

    case 'p':
    case 'P':
        WhichProjection = PERSP;
        break;

    case 'q':
    case 'Q':
    case ESCAPE:
        DoMainMenu(QUIT); // will not return here
        break;            // happy compiler

    case 'f':
        Frozen = !Frozen;
        if (Frozen)
            glutIdleFunc(NULL);
        else
            glutIdleFunc(Animate);
        break;

    case 'F':
        FOpen = !FOpen;
        bothVF =false;
        VOpen = false;
        break;

    case '0':
        Light0On = !Light0On;
        printf("Light0On");
        break;

    case '1':
        Light1On = !Light1On;
        break;
    case '2':
        Light2On = !Light2On;
        break;

    case 'b':
        bothVF = !bothVF;
        printf("b");
        break;

    case 'V':
        VOpen = !VOpen;
        bothVF =false;
        FOpen = false;
        printf("v");
        break;

    default:
        fprintf(stderr, "Don't know what to do with keyboard hit: '%c' (0x%0x)\n", c, c);
    }

    // force a call to Display( ):

    glutSetWindow(MainWindow);
    glutPostRedisplay();
}

// called when the mouse button transitions down or up:

void MouseButton(int button, int state, int x, int y)
{
    int b = 0; // LEFT, MIDDLE, or RIGHT

    if (DebugOn != 0)
        fprintf(stderr, "MouseButton: %d, %d, %d, %d\n", button, state, x, y);

    // get the proper button bit mask:

    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        b = LEFT;
        break;

    case GLUT_MIDDLE_BUTTON:
        b = MIDDLE;
        break;

    case GLUT_RIGHT_BUTTON:
        b = RIGHT;
        break;

    case SCROLL_WHEEL_UP:
        Scale += SCLFACT * SCROLL_WHEEL_CLICK_FACTOR;
        // keep object from turning inside-out or disappearing:
        if (Scale < MINSCALE)
            Scale = MINSCALE;
        break;

    case SCROLL_WHEEL_DOWN:
        Scale -= SCLFACT * SCROLL_WHEEL_CLICK_FACTOR;
        // keep object from turning inside-out or disappearing:
        if (Scale < MINSCALE)
            Scale = MINSCALE;
        break;

    default:
        b = 0;
        fprintf(stderr, "Unknown mouse button: %d\n", button);
    }

    // button down sets the bit, up clears the bit:

    if (state == GLUT_DOWN)
    {
        Xmouse = x;
        Ymouse = y;
        ActiveButton |= b; // set the proper bit
    }
    else
    {
        ActiveButton &= ~b; // clear the proper bit
    }

    glutSetWindow(MainWindow);
    glutPostRedisplay();
}

// called when the mouse moves while a button is down:

void MouseMotion(int x, int y)
{
    int dx = x - Xmouse; // change in mouse coords
    int dy = y - Ymouse;

    if ((ActiveButton & LEFT) != 0)
    {
        Xrot += (ANGFACT * dy);
        Yrot += (ANGFACT * dx);
    }

    if ((ActiveButton & MIDDLE) != 0)
    {
        Scale += SCLFACT * (float)(dx - dy);

        // keep object from turning inside-out or disappearing:

        if (Scale < MINSCALE)
            Scale = MINSCALE;
    }

    Xmouse = x; // new current position
    Ymouse = y;

    glutSetWindow(MainWindow);
    glutPostRedisplay();
}

// reset the transformations and the colors:
// this only sets the global variables --
// the glut main loop is responsible for redrawing the scene