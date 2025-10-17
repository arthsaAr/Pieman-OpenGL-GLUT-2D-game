/******************************************************************************
*  File Name:    main.cpp
*  Author:       Raashtra KC
*  Date:         2025-10-5
*  Language:     C++
*  Notes:        Compile and run(Make sure the required libraries are installed on your system)
******************************************************************************/

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#ifdef _WIN32
#include <windows.h>
#define M_PI 3.14159265358979323846 // Window doesn't seem to define this
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif
#include <cmath>
#include <iostream>


//I am starting with the values for rotation as minimum from 140 to max of 180 for openinig and closing the mouth. THe reason for this value was when starting from 0 it was doing weird movements.

float windowX = 800;
float windowY = 800;
float rotAng = 0.0f;

void cubeMaker() {
    glColor3f(1.0f, 0.0f, 0.0f);        //red

    glBegin(GL_TRIANGLES);

    // possible faces +-x, +-y, +-z

    // FRONT face (z = +1)
    glNormal3f(0.0f, 0.0f, 1.0f);           //normal for lighting calculations  Z direction
    
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);

    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    // BACK face (z = -1)
    glNormal3f(0.0f, 0.0f, -1.0f);          //-Z
    
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);


    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);

    // RIGHT face (x = +1)
    glNormal3f(1.0f, 0.0f, 0.0f);

    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);


    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);


    // LEFT face (x = -1)
    glNormal3f(-1.0f, 0.0f, 0.0f);

    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);


    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);

    // TOP face (y = +1)
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);


    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);


    // BOTTOM face (y = -1)
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);


    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);

    glEnd();


}

// The function to call when the screen needs to be redrawn
void display(void)
{
    //glClearColor(0.3f, 0.3f, 0.3f, 0.3f); // background colour of black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the background
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);   //setting up camera view, 0,0,5 for eye position, 0,0,0 for center point, 0,1,0 for up direction

    glRotatef(rotAng, 0.0f, 1.0f, 0.0f);
    cubeMaker();

    glutSwapBuffers();

}

void refreshShape(int w, int h) {
    if (h == 0) {
        h = 1;
    }
    float view = (float)w / (float)h;

    glViewport(0, 0, w, h);         //viewport in this case is all window
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80, view, 0.1, 100.0);         //sets the perspective projection to degrees: we can say when angle is reduced the cube becomes closer to the camera and when angle is increased the cube goes away
    glMatrixMode(GL_MODELVIEW);     //switch back to modelview
}

void timerF(int val) {
    rotAng = rotAng + 1.0f;     //increasing angle by 1 degrees each time
    if (rotAng > 360.0f) {      //if angle goes beyong 360.0f resetting it back to 0 and starting over again
        rotAng = rotAng - 360.0f;
    }
    glutPostRedisplay();        //everyrun of timer, says to redraw window now(timer->glurpostredisplay->display->glrotate
    glutTimerFunc(40, timerF, 0);       //calls the function every 15ms
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // two buffers to prevent flicker, and red, green blue

    // Make the window
    int windowHandle = glutCreateWindow("Demonstration Two");
    glutSetWindow(windowHandle);

    glutPositionWindow(100, 100);
    glutReshapeWindow(windowX, windowY);
    glEnable(GL_DEPTH_TEST);            //enables depthtesting, lighting and lightsource(just 1 light)
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);


    //default eye direction, because if we call gllightfv before setting up camera then light will be relative to world. if called after glulookat, light is transformed into camera space
    //calling before camera setup(before glulookat)
    float lightPosition[] = { 1.0f, 1.0f, 1.0f, 0.0f };         //this means light coming from direction 1,1,1 from far(at certain angle)
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);       //setting the position of light 

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);       //bg clear


    glutDisplayFunc(display);       
    glutReshapeFunc(refreshShape);
    glutTimerFunc(0, timerF, 0);        //starting timer for rotation


    glutMainLoop();
    return 0; // required since main returns an int, but this line will never be reached
}
