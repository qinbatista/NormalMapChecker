
const char *WINDOWTITLE = "OpenGL / GLUT Sample -- Qin's Graphics";
const char *GLUITITLE = "User Interface Window";
// what the glui package defines as true and false:
const int GLUITRUE = true;
const int GLUIFALSE = false;
// the escape key:
const int ESCAPE = 0x1b;
// initial window size:
const int INIT_WINDOW_SIZE = 600;
// size of the 3d box to be drawn:
const float BOXSIZE = 2.f;
// multiplication factors for input interaction:
//  (these are known from previous experience)
const float ANGFACT = 1.f;
const float SCLFACT = 0.005f;
// minimum allowable scale factor:
const float MINSCALE = 0.05f;
// scroll wheel button values:
const int SCROLL_WHEEL_UP = 3;
const int SCROLL_WHEEL_DOWN = 4;
// equivalent mouse movement when we click the scroll wheel:
const float SCROLL_WHEEL_CLICK_FACTOR = 5.f;
// active mouse buttons (or them together):
const int LEFT = 4;
const int MIDDLE = 2;
const int RIGHT = 1;

//plane
#define PROPELLER_RADIUS 1.0
#define PROPELLER_WIDTH 0.4
float   TimeCycle;
float BladeAngle;
bool Frozen;
#define MS_IN_THE_ANIMATION_CYCLE	10000



// window background color (rgba):
const GLfloat BACKCOLOR[] = {0., 0., 0., 1.};
// line width for the axes:
const GLfloat AXES_WIDTH = 3.;
// the color numbers:
// this order must match the radio button order, which must match the order of the color names,
// 	which must match the order of the color RGB values
// fog parameters:
const GLfloat FOGCOLOR[4] = {.0f, .0f, .0f, 1.f};
const GLenum FOGMODE = GL_LINEAR;
const GLfloat FOGDENSITY = 0.30f;
const GLfloat FOGSTART = 1.5f;
const GLfloat FOGEND = 4.f;
// what options should we compile-in?
// in general, you don't need to worry about these
// i compile these in to show class examples of things going wrong
//#define DEMO_Z_FIGHTING
//#define DEMO_DEPTH_BUFFER
// non-constant global variables:
int ActiveButton;    // current button that is down
GLuint AxesList;     // list to hold the axes
int AxesOn;          // != 0 means to draw the axes
int DebugOn;         // != 0 means to print debugging info
int DepthCueOn;      // != 0 means to use intensity depth cueing
int DepthBufferOn;   // != 0 means to use the z-buffer
int DepthFightingOn; // != 0 means to force the creation of z-fighting
GLuint BoxList;      // object display list
GLuint PlaneList;    // object display list
GLuint PolygonList;  // object display list
GLuint PropellerList;
int MainWindow;      // window id for main graphics window
float Scale;         // scaling factor
int ShadowsOn;       // != 0 means to turn shadows on
int WhichColor;      // index into Colors[ ]
int WhichProjection; // ORTHO or PERSP
int WhichViewMode;  // OUTSIDE or INSIDE
int Xmouse, Ymouse;  // mouse values
float Xrot, Yrot;    // rotation angles in degrees




// function prototypes:
void Animate();
void Display();
void DoAxesMenu(int);
void DoColorMenu(int);
void DoDepthBufferMenu(int);
void DoDepthFightingMenu(int);
void DoDepthMenu(int);
void DoDebugMenu(int);
void DoMainMenu(int);
void DoProjectMenu(int);
void DoRasterString(float, float, float, char *);
void DoStrokeString(float, float, float, float, char *);
float ElapsedSeconds();
void InitGraphics();
void InitMenus();
void Keyboard(unsigned char, int, int);
void MouseButton(int, int, int, int);
void MouseMotion(int, int);
void Reset();
void Resize(int, int);
void Visibility(int);

void Axes(float);
void MyFirstObject();
void CreateAxis();
void WireFrame();
void PolygonFrame();
void Propeller();
void DoViewModeMenu(int);

unsigned char *BmpToTexture(char *, int *, int *);
int ReadInt(FILE *);
short ReadShort(FILE *);
void HsvRgb(float[3], float[3]);
// void Cross(float[3], float[3], float[3]);
float Dot(float[3], float[3]);
// float Unit(float[3], float[3]);