float White[] = {1., 1., 1., 1.};
float Green[] = {0., 1., 0., 1.};

void SetLight();
float *Array3(float a, float b, float c)
{
    static float array[4];
    array[0] = a;
    array[1] = b;
    array[2] = c;
    array[3] = 1.;
    return array;
}
float *MulArray3(float factor, float array0[3])
{
    static float array[4];
    array[0] = factor * array0[0];
    array[1] = factor * array0[1];
    array[2] = factor * array0[2];
    array[3] = 1.;
    return array;
}
void SetLight()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // possibly draw the axes:
    glEnable(GL_LIGHTING);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, MulArray3(.2, White));
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

}
void SetPointLight_GL_SMOOTH(int ilight, float x, float y, float z, float r, float g, float b)
{
    glLightfv(ilight, GL_POSITION, Array3(x, y, z));

    glLightfv(ilight, GL_AMBIENT, Array3(0., 0., 0.));
    glLightfv(ilight, GL_DIFFUSE, Array3(r, g, b));
    glLightfv(ilight, GL_SPECULAR, Array3(r, g, b));

    glLightf(ilight, GL_CONSTANT_ATTENUATION, 1.);
    glLightf(ilight, GL_LINEAR_ATTENUATION, 0.);
    glLightf(ilight, GL_QUADRATIC_ATTENUATION, 0.);

    glEnable(ilight);
}
void SetPointLight(int ilight, float x, float y, float z, float r, float g, float b)
{
    glShadeModel(GL_SMOOTH);
    glLightfv(ilight, GL_POSITION, Array3(x, y, z));

    glLightfv(ilight, GL_AMBIENT, Array3(0., 0., 0.));
    glLightfv(ilight, GL_DIFFUSE, Array3(r, g, b));
    glLightfv(ilight, GL_SPECULAR, Array3(r, g, b));

    glLightf(ilight, GL_CONSTANT_ATTENUATION, 1.);
    glLightf(ilight, GL_LINEAR_ATTENUATION, 0.);
    glLightf(ilight, GL_QUADRATIC_ATTENUATION, 0.);

    glEnable(ilight);
}

void SetSpotLight(int ilight, float x, float y, float z, float xdir, float ydir, float zdir, float r, float g, float b)
{
    glShadeModel(GL_FLAT);
    glLightfv(ilight, GL_POSITION, Array3(x, y, z));

    glLightfv(ilight, GL_SPOT_DIRECTION, Array3(xdir, ydir, zdir));
    glLightf(ilight, GL_SPOT_EXPONENT, 1.);
    glLightf(ilight, GL_SPOT_CUTOFF, 45.);

    glLightfv(ilight, GL_AMBIENT, Array3(0., 0., 0.));
    glLightfv(ilight, GL_DIFFUSE, Array3(r, g, b));
    glLightfv(ilight, GL_SPECULAR, Array3(r, g, b));

    glLightf(ilight, GL_CONSTANT_ATTENUATION, 1.);
    glLightf(ilight, GL_LINEAR_ATTENUATION, 0.);
    glLightf(ilight, GL_QUADRATIC_ATTENUATION, 0.);

    glEnable(ilight);
}