struct point
{
	float x, y, z;		// coordinates
	float nx, ny, nz;	// surface normal
	float s, t;		// texture coords
};
struct Point
{
        float x0, y0, z0;       // initial coordinates
        float x,  y,  z;        // animated coordinates
};
struct Curve
{
        float r, g, b;
        Point p0, p1, p2, p3;
};
enum Projections
{
    ORTHO,
    PERSP
};

enum ViewPerspective {
    OUTSIDE,
    INSIDE
};
enum TextureMode {
    OFF,
    ON,
    DISTORT,
};

// which button:

enum ButtonVals
{
    RESET,
    QUIT
};
enum Colors
{
    RED,
    YELLOW,
    GREEN,
    CYAN,
    BLUE,
    MAGENTA,
    WHITE,
    BLACK
};

char *ColorNames[] =
    {
        (char *)"Red",
        (char *)"Yellow",
        (char *)"Green",
        (char *)"Cyan",
        (char *)"Blue",
        (char *)"Magenta",
        (char *)"White",
        (char *)"Black"};

// the color definitions:
// this order must match the menu order

const GLfloat Colors[][3] =
    {
        {1., 0., 0.}, // red
        {1., 1., 0.}, // yellow
        {0., 1., 0.}, // green
        {0., 1., 1.}, // cyan
        {0., 0., 1.}, // blue
        {1., 0., 1.}, // magenta
        {1., 1., 1.}, // white
        {0., 0., 0.}, // black
};
