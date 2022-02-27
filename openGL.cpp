#include <GL\glut.h>
#include <windows.h>

GLfloat xRotated, yRotated, zRotated; /// global float variables for the rotation of the sphere
GLdouble radius=1; /// global variable for the initialization of radius

/// static  global variables for the initialization of the number of slices and stacks
static int slices = 16;
static int stacks = 16;

/// This is the function displayed by the "glutDisplayFunc()", which draws the body and its movement.
void displayFunction (void)
{
    glMatrixMode(GL_MODELVIEW); /// sets the view point
    glClear(GL_COLOR_BUFFER_BIT); /// clears the drawing buffer and deletes everything on the screen

    glLoadIdentity(); /// initializes the matrix before rotating or translating it (before you multiply further matrices with the matrix)
    glTranslatef(0.0, 0.0, -5.0); /// translates the draw by z=-5.0, how close or far you see the object
    glColor3f(1.0, 0.0, 0.0); /// sets the red color for the segments

    /// Changing in the transformation matrix
    /// Rotation about:
    glRotatef(xRotated, 1.0, 0.0, 0.0); /// x axis
    glRotatef(yRotated, 0.0, 1.0, 0.0); /// y axis
    glRotatef(zRotated, 0.0, 0.0, 1.0); /// z axis
    glutSolidSphere(radius, slices, stacks); /// draws a sphere with 16 slices, 16 stacks and radius=1, built in glut library function
    glFlush(); /// makes sure that all the commands are executed and are not preserved in buffer waiting for the OpenGL commands
}

/// This function controls the rotation speed, on the x axis and z axis, incrementing the global variables xRotated and zRotated
void idleFunction (void)
{
    xRotated+=0.01;
    zRotated+=0.01;

    displayFunction(); ///displays again the body and its movement, after the speed is modified
}

void mouseCommand (int button, int state, int x, int y)
{
    /// Using the switch command and the predefined logic variables for mouse, you can stop and restart the animation and also changing the background
    switch(button)
    {
     case GLUT_RIGHT_BUTTON:
        if(state==GLUT_DOWN)
        {
          glutIdleFunc(NULL);
          glClearColor(0.5, 0.9, 0.3, 1.0);
        }
     break;

     case GLUT_LEFT_BUTTON:
        if(state==GLUT_DOWN)
        {
        glutIdleFunc(idleFunction);
        glClearColor(1.0, 0.8, 0.5, 1.0);
        }
     break;

     default:
     break;
    }
}
static void keyboardCommand (unsigned char key, int x, int y)
{
    /// Using the switch command, you can increase or decrease the number of slices and stacks
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;

        case '+':
            slices++;
            stacks++;
            break;

        case '-':
            if (slices>6 && stacks>6)
            {
                slices--;
                stacks--;
            }
            break;
    }

    /// Using the switch command and ASCII codes, you can change the background color depending on the key you presses the buttons from 0 to 9
    switch (key) {
    case 27:
        exit(0);
    case 48:
        glClearColor(0.52, 0.5, 0.26, 1.0);
        break;
    case 49:
        glClearColor(0.23 ,0.5 ,0.34, 1.0);
        break;
    case 50:
        glClearColor(0.7, 0.6, 0.93, 1.0);
        break;
    case 51:
        glClearColor(0.55, 0.8, 0.88, 1.0);
        break;
    case 52:
        glClearColor(0.5, 1.0, 0.5, 1.0);
        break;
    case 53:
        glClearColor(1.0, 1.0, 0.5, 0.0);
        break;
    case 54 :
        glClearColor(1.0, 0.8, 0.1, 1.0);
        break;
    case 55 :
        glClearColor(1.0, 0.5, 0.68, 1.0);
        break;
    case 56:
        glClearColor(1.0, 0.5, 0.3, 1.0);
        break;
    case 57:
        glClearColor(0.55, 0.09, 0.15, 1.0);
        break;
    }
}
/// This function is called when the window is reshaped,it scales the object and set up the perspectives depending on the window form and dimentions
void reshapeFunction(int x, int y)
{
    if(y==0 || x==0) return; /// the window becomes so thin nothing being visible
    glMatrixMode(GL_PROJECTION); /// sets and initializes new projection matrix
    glLoadIdentity();

    /// set up a perspective using: Angle of view: 30 degrees, Near clipping plane distance:0.5, Far clipping plane distance:20.0.
    gluPerspective(30.0, (GLdouble)x/(GLdouble)y, 0.5, 20.0);
    glMatrixMode(GL_MODELVIEW); /// sets the viewpoint
    glViewport(0,0,x,y); /// specifies the viewport rectangle by setting the coordinates of lower left corner and its dimensions
}
int main (int argc, char **argv)
{
    /// Initializing Glut: accesses the specific functions of operating system which are the foundation of any OpenGL program
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); /// specifies if the color format is RGBA or another color index, here it sets a unique buffer
    glutInitWindowSize(600, 600); /// sets the window size in pixels
    glutInitWindowPosition(80, 80); /// sets the position of the window
    glutCreateWindow("OpenGL Project"); /// creates a new window and sets its title
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); /// sets a polygon rasterization mode, draws lines from the front and back facing polygon's edges
    xRotated=yRotated=zRotated=30.0; /// sets the global variables declared previously
    glClearColor(1.0, 1.0, 1.0, 1.0); /// sets the background color
    glutDisplayFunc(displayFunction); /// register callback handler for window redraw event
    glutReshapeFunc(reshapeFunction); /// register callback handler for window resize event
    glutIdleFunc(idleFunction); /// callback perform background processing tasks or continuous animation when the window events are not being received

    /// Functions which realize the human-program interaction
    glutMouseFunc(mouseCommand);
    glutKeyboardFunc(keyboardCommand);
    glutMainLoop(); /// enter the infinite event-processing loop
    return 0;
}
