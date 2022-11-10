void MyFirstObject()
{
    float dx = BOXSIZE / 2.f;
    float dy = BOXSIZE / 2.f;
    float dz = BOXSIZE / 2.f;
    // create the object:
    BoxList = glGenLists(1);
    glNewList(BoxList, GL_COMPILE);
    glBegin(GL_QUADS);
    float gradient = 0.01f;
    for (int i = 0; i < 101; i++)
    {
        glColor3f(gradient * i * 0.3, gradient * i * 0.5, 0.65);
        glNormal3f(1., 0., 0.);
        glVertex3f(dx, -dy, dz);
        glVertex3f(dx, -dy * i * gradient * 2, -dz * i * gradient);
        glVertex3f(dx, dy * i * gradient * 2, -dz * i * gradient);
        glVertex3f(dx, dy, dz);
        glColor3f(gradient * i * 0.1, 0.3, gradient * i * 0.7);
        glNormal3f(-1., 0., 0.);
        glVertex3f(-dx, -dy, dz);
        glVertex3f(-dx, dy, dz);
        glVertex3f(-dx, dy * i * gradient * 2, -dz * i * gradient);
        glVertex3f(-dx, -dy * i * gradient * 2, -dz * i * gradient);
    }
    for (int i = 0; i < 101; i++)
    {
        glColor3f(0.1, 0.6, gradient * i);
        glNormal3f(0., 1., 0.);
        glVertex3f(-dx, dy, dz);
        glVertex3f(dx, dy, dz);
        glVertex3f(dx, dy * i * gradient * 2, -dz);
        glVertex3f(-dx, dy * i * gradient * 2, -dz);

        glColor3f(0.6, 0.1, gradient * i);
        glNormal3f(0., -1., 0.);
        glVertex3f(-dx, -dy, dz);
        glVertex3f(-dx, -dy * i * gradient * 2, -dz);
        glVertex3f(dx, -dy * i * gradient * 2, -dz);
        glVertex3f(dx, -dy, dz);
    }
    glEnd();
    glEndList();
}
void CreateAxis()
{
    // create the axes:
    AxesList = glGenLists(1);
    glNewList(AxesList, GL_COMPILE);
    glLineWidth(AXES_WIDTH);
    Axes(10);
    glLineWidth(10.);
    glEndList();
}
void WireFrame()
{
    // create wireframe helicopter
    PlaneList = glGenLists(1);
    glNewList(PlaneList, GL_COMPILE);
    int i;
    struct edge *ep;
    struct point *p0, *p1, *p2;
    glPushMatrix();
    // glTranslatef(0., -1., 0.);
    glRotatef(90., 0., 1., 0.);
    // glRotatef(-15., 0., 0., 1.);
    glBegin(GL_LINES);
    for (i = 0, ep = CESSNAedges; i < CESSNAnedges; i++, ep++)
    {
        glColor3f(0.3, 0.001*i, 0.2);
        p0 = &CESSNApoints[ep->p0];
        p1 = &CESSNApoints[ep->p1];
        glVertex3f(p0->x, p0->y, p0->z);
        glVertex3f(p1->x, p1->y, p1->z);
    }
    glEnd();
    glPopMatrix();
    glEndList();
}
void PolygonFrame()
{
    PolygonList = glGenLists(1);
    glNewList(PolygonList, GL_COMPILE);
    int i;
    struct point *p0, *p1, *p2;
    struct tri *tp;
    float p01[3], p02[3], n[3];

    glPushMatrix();
    // glRotatef(-7., 0., 1., 0.);
    // glTranslatef(0., -1., 0.);
    glRotatef(90., 0., 1., 0.);
    // glRotatef(-15., 0., 0., 1.);
    glBegin(GL_TRIANGLES);
    for (i = 0, tp = CESSNAtris; i < CESSNAntris; i++, tp++)
    {
        p0 = &CESSNApoints[tp->p0];
        p1 = &CESSNApoints[tp->p1];
        p2 = &CESSNApoints[tp->p2];

        // fake "lighting" from above:

        p01[0] = p1->x - p0->x;
        p01[1] = p1->y - p0->y;
        p01[2] = p1->z - p0->z;
        p02[0] = p2->x - p0->x;
        p02[1] = p2->y - p0->y;
        p02[2] = p2->z - p0->z;
        Cross(p01, p02, n);
        Unit(n, n);
        n[1] = fabs(n[1]);
        glColor3f(n[1], .5f * n[1], 0.);

        glVertex3f(p0->x, p0->y, p0->z);
        glVertex3f(p1->x, p1->y, p1->z);
        glVertex3f(p2->x, p2->y, p2->z);
    }
    glEnd();
    glPopMatrix();
    glEndList();
}
void Propeller()
{
    PropellerList = glGenLists(1);
    glNewList(PropellerList, GL_COMPILE);
    // glRotatef(90., 1, 0, 0.);
    // glTranslatef(5, 0., -2.2);
    glBegin(GL_TRIANGLES);
    glColor3f(1, 1, 1);
    glVertex3f(PROPELLER_RADIUS, PROPELLER_WIDTH / 2, 0.);
    glVertex3f(0, 0, 0);
    glVertex3f(PROPELLER_RADIUS, -PROPELLER_WIDTH / 2., 0);
    glVertex3f(-PROPELLER_RADIUS, -PROPELLER_WIDTH / 2., 0.);
    glVertex3f(0, 0, 0);
    glVertex3f(-PROPELLER_RADIUS, PROPELLER_WIDTH / 2., 0.);
    glEnd();
    glEndList();
    glRotatef(0., 0, 0, 0.);
    glTranslatef(0, 0., 0);
}