
void DoMainMenu(int);
void Visibility(int);
void Reset();
void Resize(int, int);
void InitMenus();
void MetaInitial(int argc, char *argv[]);
void WorldInitial();
void MetaInitial(int argc, char *argv[])
{
    // turn on the glut package:
    // (do this before checking argc and argv since it might
    // pull some command line arguments out)
    glutInit(&argc, argv);
    // setup all the graphics stuff:
    InitGraphics();
    // create the display structures that will not change:
    WorldInitial();
    // init all the global variables used by Display( ):
    // this will also post a redisplay
    Reset();
    // setup all the user interface stuff:
    InitMenus();
    // draw the scene once and wait for some interaction:
    // (this will never return)
    glutSetWindow(MainWindow);
    glutMainLoop();
    // glutMainLoop( ) never actually returns
    // the following line is here to make the compiler happy:
}
void InitGraphics()
{
    // request the display modes:
    // ask for red-green-blue-alpha color, double-buffering, and z-buffering:
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    // set the initial window configuration:
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(INIT_WINDOW_SIZE, INIT_WINDOW_SIZE);

    // open the window and set its title:
    MainWindow = glutCreateWindow(WINDOWTITLE);
    glutSetWindowTitle(WINDOWTITLE);
    // set the framebuffer clear values:
    glClearColor(BACKCOLOR[0], BACKCOLOR[1], BACKCOLOR[2], BACKCOLOR[3]);
    // setup the callback functions:
    // DisplayFunc -- redraw the window
    // ReshapeFunc -- handle the user resizing the window
    // KeyboardFunc -- handle a keyboard input
    // MouseFunc -- handle the mouse button going down or up
    // MotionFunc -- handle the mouse moving with a button down
    // PassiveMotionFunc -- handle the mouse moving with a button up
    // VisibilityFunc -- handle a change in window visibility
    // EntryFunc	-- handle the cursor entering or leaving the window
    // SpecialFunc -- handle special keys on the keyboard
    // SpaceballMotionFunc -- handle spaceball translation
    // SpaceballRotateFunc -- handle spaceball rotation
    // SpaceballButtonFunc -- handle spaceball button hits
    // ButtonBoxFunc -- handle button box hits
    // DialsFunc -- handle dial rotations
    // TabletMotionFunc -- handle digitizing tablet motion
    // TabletButtonFunc -- handle digitizing tablet button hits
    // MenuStateFunc -- declare when a pop-up menu is in use
    // TimerFunc -- trigger something to happen a certain time from now
    // IdleFunc -- what to do when nothing else is going on

    glutSetWindow(MainWindow);
    glutDisplayFunc(Display);
    glutReshapeFunc(Resize);
    glutKeyboardFunc(Keyboard);
    glutMouseFunc(MouseButton);
    glutMotionFunc(MouseMotion);
    glutPassiveMotionFunc(MouseMotion);
    // glutPassiveMotionFunc( NULL );
    glutVisibilityFunc(Visibility);
    glutEntryFunc(NULL);
    glutSpecialFunc(NULL);
    glutSpaceballMotionFunc(NULL);
    glutSpaceballRotateFunc(NULL);
    glutSpaceballButtonFunc(NULL);
    glutButtonBoxFunc(NULL);
    glutDialsFunc(NULL);
    glutTabletMotionFunc(NULL);
    glutTabletButtonFunc(NULL);
    glutMenuStateFunc(NULL);
    glutTimerFunc(-1, NULL, 0);

    // setup glut to call Animate( ) every time it has
    // 	nothing it needs to respond to (which is most of the time)
    // we don't need to do this for this program, and really should set the argument to NULL
    // but, this sets us up nicely for doing animation
    glutIdleFunc(Animate);

    // init the glew package (a window must be open to do this):

#ifdef WIN32
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        fprintf(stderr, "glewInit Error\n");
    }
    else
        fprintf(stderr, "GLEW initialized OK\n");
    fprintf(stderr, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
#endif
}
