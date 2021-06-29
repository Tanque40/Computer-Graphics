#include <GL/freeglut.h>

void myinit()
{

    //** attributes
    glClearColor(1.0, 1.0, 1.0, 1.0); //*? White baclground
    glColor3f(1.0, 0.0, 0.0);         //*? Draw in red

    //** setup viewing
    //** 50.0 x 50.0 camera coordinate window with origin lower left
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 50.0, 0.0, 50.0);
    glMatrixMode(GL_MODELVIEW);
}

void display()
{
    //** An arbitrary triangle in the plane z
    GLfloat vertices[3][2] = {{0.0, 0.0}, {25.0, 50.0}, {50.0, 0.0}};

    int i, j, k;
    //int rand(); //*? Standard random number generator

    //** Set to any desired point inside the triangle
    GLfloat p[2] = {7.5, 5.0};

    glClear(GL_COLOR_BUFFER_BIT); //** Clear the window
    glBegin(GL_POINTS);

    //** Compute and plot 5000 new points
    for (k = 0; k < 50000000; k++)
    {
        //** Pick a random vertex from 0,1,2
        j = rand() % 3;

        //** Compute new location
        p[0] = (p[0] + vertices[j][0]) / 2;
        p[1] = (p[1] + vertices[j][1]) / 2;

        //** Display new point
        glVertex2fv(p);
    }

    glEnd();

    glFlush();
}

int main(int argc, char **argv)
{

    //Todo Standar GLUT initialization
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //*? Default, not needed

    glutInitWindowSize(500, 500);          //*? 500 x 500 pixel window
    glutInitWindowPosition(0, 0);          //*? place window top left on display
    glutCreateWindow("Sierpinski Gasket"); //*? Window title
    glutDisplayFunc(display);              //*? display callback invoked when window opened

    myinit(); //*? set attributes

    glutMainLoop(); //*? enter event loop

    return 0;
}