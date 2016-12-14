
/* Copyright (c) Mark J. Kilgard, 1997. */

/* This program is freely distributable without licensing fees
   and is provided without guarantee or warrantee expressed or
   implied. This program is -not- in the public domain. */

/* This program was requested by Patrick Earl; hopefully someone else
   will write the equivalent Direct3D immediate mode program. */

#include <GL/glut.h>


float xRotated = 90.0, yRotated = 0.0, zRotated = 0.0;

//------------------------------  reshapeFunc  ---------------------------------


void init(void)
{
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}

void reshapeFunc (int w, int h)
{
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho (-1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w,
                 1.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
    else
        glOrtho (-1.5*(GLfloat)w/(GLfloat)h,
                 1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);

   // gluPerspective (0.0, (GLdouble)w / (GLdouble)h, 0.5, 10.0);
    glMatrixMode   (GL_MODELVIEW);
    glViewport     (0, 0, w, h);
}
GLdouble eq[4];
//------------------------------  Draw_Spheres   -------------------------------

void Draw_Spheres (void)
{
    glMatrixMode   (GL_MODELVIEW);
    glClear        (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity ();
    eq[0] = 0.0f;
    eq[1] = 1.0f;
    eq[2] = 0.0f;
    eq[3] = 0.0f;
    glColorMaterial (GL_FRONT,GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(1,1,0);
    glPushMatrix ();
    glClipPlane(GL_CLIP_PLANE0,eq);
    glEnable(GL_CLIP_PLANE0);
    glTranslated(0.5,0,0);
    glRotatef(zRotated,0,1,0);
    glTranslated(-0.5,0,0);
    glutSolidTorus(0.05,0.1, 50, 50);
    glDisable(GL_CLIP_PLANE0);

    glTranslated(0.5,0.0,0.5);
    glRotatef(180,1,1,0);
    glutSolidTorus(0.05,0.1, 50, 50);
    glTranslated(-0.5,0.0,-0.5);


    glPopMatrix ();
    glTranslated(0.5,0,0);
    glRotatef(zRotated,0,1,0);
    glutSolidSphere(0.5,50,50);

    glutSwapBuffers();
}

//--------------------------------  idleFunc  ----------------------------------

void idleFunc (void)
{
    zRotated += 0.3;
    glutPostRedisplay();
}

//----------------------------------  main  ------------------------------------

int main (int argc, char **argv)
{
    glutInit               (&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize     (800, 700);
    glutInitWindowPosition (700, 200);
    glutCreateWindow       ("Sphere Rotating Animation");
    init();
    glPolygonMode          (GL_FRONT_AND_BACK, GL_QUADS);

    glClearColor (0.0, 0.0, 0.0, 0.0);

    glutDisplayFunc (Draw_Spheres);
    glutReshapeFunc (reshapeFunc);
    glutIdleFunc    (idleFunc);

    glutMainLoop();
    return 1;
}