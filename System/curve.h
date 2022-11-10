#define NUMPOINTS 500
#define NUMCURVES 5

Point p0 = {0, 0, 0, 0, 0, 0};
Point p1 = {4, 2, 6, 1, 2, 2};
Point p2 = {-6, -2, -1, 2, 5, 1};
Point p3 = {1, 1, 3, 6, 2, 8};
float rgb[5][3] = {
    1.0,
    0.0,
    0.0,
    1.0,
    1.0,
    0.0,
    1.0,
    1.0,
    1.0,
    0.0,
    1.0,
    1.0,
    0.0,
    0.0,
    1.0,
};
Point p0s = {0, 0, 0, 0, 0, 0};
Point p1s = {4, 2, 6, 1, 2, 2};
Point p2s = {-6, -2, -1, 2, 5, 1};
Point p3s = {1, 1, 3, 6, 2, 8};

float r = 1.;
float g = 1.;
float b = 1.;

Curve curve = {r, g, b, p0, p1, p2, p3};
Curve curveStatic = {r, g, b, p0s, p1s, p2s, p3s};
void RotateX(Point *p, float deg, float xc, float yc, float zc)
{
    float rad = deg * (M_PI / 180.f); // radians
    float x = p->x0 - xc;
    float y = p->y0 - yc;
    float z = p->z0 - zc;

    float xp = x;
    float zp = y * sin(rad) + z * cos(rad);
    float yp = y * cos(rad) - z * sin(rad);

    p->x = xp + xc;
    p->y = yp + yc;
    p->z = zp + zc;
}
void RotateY(Point *p, float deg, float xc, float yc, float zc)
{
    float rad = deg * (M_PI / 180.f); // radians
    float x = p->x0 - xc;
    float y = p->y0 - yc;
    float z = p->z0 - zc;

    float xp = x * cos(rad) + z * sin(rad);
    float yp = y;
    float zp = -x * sin(rad) + z * cos(rad);

    p->x = xp + xc;
    p->y = yp + yc;
    p->z = zp + zc;
}
void RotateZ(Point *p, float deg, float xc, float yc, float zc)
{
    float rad = deg * (M_PI / 180.f); // radians
    float x = p->x0 - xc;
    float y = p->y0 - yc;
    float z = p->z0 - zc;

    float xp = x * cos(rad) - y * sin(rad);
    float yp = x * sin(rad) + y * cos(rad);
    float zp = z;

    p->x = xp + xc;
    p->y = yp + yc;
    p->z = zp + zc;
}

void DrawCatmullRomCurve()
{
    float r, g, b;
    Point p0, p1, p2, p3;

    p0 = curve.p0;
    p1 = curve.p1;
    p2 = curve.p2;
    p3 = curve.p3;

    r = curve.r;
    g = curve.g;
    b = curve.b;

    glLineWidth(3.);
    glBegin(GL_LINE_STRIP);
    for (int it = 0; it <= NUMPOINTS; it++)
    {
        float t = (float)it / (float)NUMPOINTS;
        float breakpoint = 1.f - t;
        glColor3f(r * breakpoint, g * breakpoint, b * breakpoint);
        float x = breakpoint * breakpoint * breakpoint * p0.x + 3.f * t * breakpoint * breakpoint * p1.x + 3.f * t * t * breakpoint * p2.x + t * t * t * p3.x;
        float y = breakpoint * breakpoint * breakpoint * p0.y + 3.f * t * breakpoint * breakpoint * p1.y + 3.f * t * t * breakpoint * p2.y + t * t * t * p3.y;
        float z = breakpoint * breakpoint * breakpoint * p0.z + 3.f * t * breakpoint * breakpoint * p1.z + 3.f * t * t * breakpoint * p2.z + t * t * t * p3.z;
        glVertex3f(x, y, z);
    }
    glEnd();
    glLineWidth(1.);
}
void DrawCatmullRomCurveStatic()
{
    float r, g, b;
    Point p0, p1, p2, p3;

    p0 = curveStatic.p0;
    p1 = curveStatic.p1;
    p2 = curveStatic.p2;
    p3 = curveStatic.p3;

    r = curveStatic.r;
    g = curveStatic.g;
    b = curveStatic.b;

    glLineWidth(3.);
    glBegin(GL_LINE_STRIP);
    for (int it = 0; it <= NUMPOINTS; it++)
    {
        float t = (float)it / (float)NUMPOINTS;
        float breakpoint = 1.f - t;
        glColor3f(r * breakpoint, g * breakpoint, b * breakpoint);
        float x = breakpoint * breakpoint * breakpoint * p0.x + 3.f * t * breakpoint * breakpoint * p1.x + 3.f * t * t * breakpoint * p2.x + t * t * t * p3.x;
        float y = breakpoint * breakpoint * breakpoint * p0.y + 3.f * t * breakpoint * breakpoint * p1.y + 3.f * t * t * breakpoint * p2.y + t * t * t * p3.y;
        float z = breakpoint * breakpoint * breakpoint * p0.z + 3.f * t * breakpoint * breakpoint * p1.z + 3.f * t * t * breakpoint * p2.z + t * t * t * p3.z;
        glVertex3f(x, y, z);
    }
    glEnd();
    glLineWidth(1.);
}


void DrawDynamicGraph1()
{
    for (int i = 0; i <= NUMCURVES; i++)
    {
        curve.r = 0.7- rgb[i][0] * sin(TimeCycle);
        curve.g = 0.7+ rgb[i][1] * sin(TimeCycle);
        curve.b = 0.3+ rgb[i][2] * sin(TimeCycle);
        RotateX(&curve.p1, 200 * sin(TimeCycle*5), 5, 6, 7);
        RotateY(&curve.p2, 312 * sin(TimeCycle*5), 5, 6, 1);
        RotateZ(&curve.p3, 170 * sin(TimeCycle*5), 1, 2, 7);
        glPushMatrix();
        glRotatef(360. / NUMCURVES * i, 0, 1, 0);
        DrawCatmullRomCurve();
        glPopMatrix();
    }
}
void DrawStaticGraph()
{
    for (int i = 0; i <= NUMCURVES; i++)
    {
        curveStatic.r = 0.7- rgb[i][0] * sin(TimeCycle);
        curveStatic.g = 0.7+ rgb[i][1] * sin(TimeCycle);
        curveStatic.b = 0.3+ rgb[i][2] * sin(TimeCycle);
        glPushMatrix();
        glRotatef(360. / NUMCURVES * i, 1, 0, 0);
        DrawCatmullRomCurveStatic();
        glPopMatrix();
    }
}
void DrawDynamicGraph2()
{
    for (int i = 0; i <= NUMCURVES; i++)
    {
        curve.r = 0.7- rgb[i][0] * sin(TimeCycle);
        curve.g = 0.1+ rgb[i][1] * sin(TimeCycle);
        curve.b = 0.9+ rgb[i][2] * sin(TimeCycle);
        RotateX(&curve.p1, 360 * sin(TimeCycle*5), 56, 6, 7);
        RotateY(&curve.p2, 170 * sin(TimeCycle*5), 25, 66, 51);
        RotateZ(&curve.p3, 66 * sin(TimeCycle*5), 86, 22, 71);
        glPushMatrix();
        glRotatef(360. / NUMCURVES * i, 0, 1, 0);
        DrawCatmullRomCurve();
        glPopMatrix();
    }
}