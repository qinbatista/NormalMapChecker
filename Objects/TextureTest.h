
#include <math.h>
#include <OpenGL/GL.h>

GLuint LoadTexture(char *path)
{
    GLuint TextureGluint;
    unsigned char *Texture;
    int Width, Height;
    Texture = BmpToTexture(path, &Width, &Height);
    int level = 0, ncomps = 3, border = 0;
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &TextureGluint);
    glBindTexture(GL_TEXTURE_2D, TextureGluint);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, Texture);
    return TextureGluint;
}
void BindTexture(GLuint _panel2D, GLuint _texture)
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    SetMaterial(1, 1., 1, 0.1);
    glBindTexture(GL_TEXTURE_2D, _texture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glCallList(_panel2D);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
GLuint Panel2D()
{
    // create the object:
    GLuint Panel2dGluint = glGenLists(1);
    glNewList(Panel2dGluint, GL_COMPILE);
    glPushMatrix();
    SetMaterial(1, 1, 1, 1);

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);

    glTexCoord2f( 0., 0. );
    glVertex3f( -1., -1., 0. );

    glTexCoord2f( 1., 0. );
    glVertex3f( 1., -1., 0. );

    glTexCoord2f( 1., 1. );
    glVertex3f( 1., 1., 0. );

    glTexCoord2f( 0., 1. );
    glVertex3f( -1., 1., 0. );

    glEnd();
    glPopMatrix();
    glEndList();
    return Panel2dGluint;
}
