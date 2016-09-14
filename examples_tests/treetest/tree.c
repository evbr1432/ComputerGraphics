// Program to draw a fractal tree
// Written by Mark Semkew and Michael Knothe
// Written using OpenGL
// Tuesday Oct 08 16:34:20 EST 2002
// fractal tree

//////////////////////////////////////////////////////////////////////////////////////////////////
// INCLUDES //////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////
// GLOBAL VARIABLES //////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

//Handles user pressing escape key
const unsigned char ESCAPE_KEY = 27;

GLUquadricObj *rootquad;

int windowHandle;									// Handle on the created window
const double pi = 3.141592654;
const double lean = 0.0;                      


float treeArray[13] = { 
0.75, 0.08, 
0.05, 0.025, 0.6,
-60.0, 0.3, 0.0,  0.5, 
70.0, -0.7, 0.0, 1.0 };


void display();
//////////////////////////////////////////////////////////////////////////////////////////////////
// CALLBACK FUNCTIONS ////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

// This function is called by GLUT every time the window is resized, including when the window is
// given its initial size when the program is first run, eliminating the need for a glInit 
// function.



void myReshape(int w, int h)
{
    glViewport(0, 0, w, h); /* lower left x,y coordinates, width and height */

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();


    if (w <= h)
        glOrtho(-2.0, 2.0, -2.0 * (GLfloat) h / (GLfloat) w,
            2.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-2.0 * (GLfloat) w / (GLfloat) h,
            2.0 * (GLfloat) w / (GLfloat) h, -2.0, 2.0, -10.0, 10.0);

    glMatrixMode(GL_MODELVIEW);
}



//////////////////////////////////////////////////////////////////////////////////////////////////

// HandleKeyboard() is called each it a key is pressed and will cause the program to end it the 
// escape key is pressed.

void HandleKeyboard(unsigned char key, int x, int y) {
	if (key == ESCAPE_KEY)								// Has escape been pressed
	{
		glutDestroyWindow(windowHandle);				// Destroy the window being used
														
		exit(1);										// Exit the program
	}



}



//redraws tree when mouse button is clicked
void mouse(int button, int state, int x, int y) 
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		glutPostRedisplay();
}


//draw leaf

void makeleaf()
{
	//ability to resize leaves
	int div = 9;

	//set vertices
	GLfloat vertices[][3] = {{0.0,-0.6/div,0.0},{-0.5/div,-0.3/div,0.1/div},
	{-0.3/div,-0.3/div,0.0},{-0.5/div,0.2/div,-0.1/div}, {-0.2/div,0.0,0.0}, 
	{0.0,0.6/div,0.0}, {0.2/div,0.0,0.0}, {0.5/div,0.2/div,-0.1/div}, {0.3/div,-0.3/div,0.0}, 
	{0.5/div,-0.3/div,0.1/div}};

	//set normals
	GLfloat normals[][3] = {{0.0,-0.6/div,0.0},{-0.5/div,-0.3/div,0.1/div},
	{-0.3/div,-0.3/div,0.0},{-0.5/div,0.2/div,-0.1/div}, {-0.2/div,0.0,0.0}, 
	{0.0,0.6/div,0.0}, {0.2/div,0.0,0.0}, {0.5/div,0.2/div,-0.1/div}, {0.3/div,-0.3/div,0.0}, 
	{0.5/div,-0.3/div,0.1/div}};

	//set colors
	GLfloat colors[][3] = {{0.0,0.3,0.1},{0.6,0.3,0.1}};
	
	//Draw veins in leaf
	glBegin(GL_LINES);
		glColor3fv(colors[1]);
		glVertex2fv(vertices[0]);
		glColor3fv(colors[1]);
		glVertex2fv(vertices[2]);
		glColor3fv(colors[1]);
		glVertex2fv(vertices[0]);
		glColor3fv(colors[1]);
		glVertex2fv(vertices[4]);
		glColor3fv(colors[1]);
		glVertex2fv(vertices[0]);
		glColor3fv(colors[1]);
		glVertex2fv(vertices[5]);
		glColor3fv(colors[1]);
		glVertex2fv(vertices[0]);
		glColor3fv(colors[1]);
		glVertex2fv(vertices[6]);
		glColor3fv(colors[1]);
		glVertex2fv(vertices[0]);
		glColor3fv(colors[1]);
		glVertex2fv(vertices[8]);
	glEnd();

	//Draw leaf
	glBegin(GL_POLYGON);
		glColor3fv(colors[0]);
		glNormal3fv(normals[0]);
		glVertex3fv(vertices[0]);
		glColor3fv(colors[0]);
		glNormal3fv(normals[0]);
		glVertex3fv(vertices[1]);
		glColor3fv(colors[0]);
		glNormal3fv(normals[2]);
		glVertex3fv(vertices[2]);
		glColor3fv(colors[0]);
		glNormal3fv(normals[3]);
		glVertex3fv(vertices[3]);
		glColor3fv(colors[0]);
		glNormal3fv(normals[4]);
		glVertex3fv(vertices[4]);
		glColor3fv(colors[0]);
		glNormal3fv(normals[5]);
		glVertex3fv(vertices[5]);
		glColor3fv(colors[0]);
		glNormal3fv(normals[6]);
		glVertex3fv(vertices[6]);
		glColor3fv(colors[0]);
		glNormal3fv(normals[7]);
		glVertex3fv(vertices[7]);
		glColor3fv(colors[0]);
		glNormal3fv(normals[8]);
		glVertex3fv(vertices[8]);
		glColor3fv(colors[0]);
		glNormal3fv(normals[9]);
		glVertex3fv(vertices[9]);
	glEnd();
}

// Recursive tree drawing function
void drawTreeRecurse( int depth, float *p, double diam, double length){

   if (depth > 0)
  {
	
   glPushMatrix();
     
     rootquad = gluNewQuadric();

	 //set light properties	 
	GLfloat light_diffuse[] = {0.7, 0.7, 0.7, 0.7};  
	GLfloat light_ambient[] = {0.4, 0.4, 0.4, 0.4};
	GLfloat light_specular[] = {0.4, 0.4, 0.4, 0.4};
	GLfloat light_location[] = { -1.5, 1.5, 0.0, 0.0 };
	GLfloat light_position[] = {10.0, 10.0, 10.0, 0.0};
	 
	GLfloat leaf_color[][4] = { { 0.0, 0.0, 0.0, 1.0},   // ambient
				 { 0.0, 0.4, 0.01, 1.0},  // diffuse
				 {0.0, 0.0, 0.01, 1.0},    // spec
				 {0.0, 0.4, 0.01, 0.01},    // emit
				 
	};

	GLfloat tree_color[][4] = { { 0.0, 0.0, 0.0, 1.0},   // ambient
				 { 0.6, 0.3, 0.04, 1.0},  // diffuse
				 {0.0, 0.0, 0.0, 1.0},    // spec
				 {0.3, 0.15, 0.0, 0.01},    // emit
				 
	};
	 
			
	float light_buf[4] = {1.0, 1.0, 1.0, 1.0 };

//Set light buffer		
	 light_buf[0] = 1; 
     light_buf[1] = 1;
     light_buf[2] = 1; 
     light_buf[3] = 1; 

	
    //Set and enable lights
     glLightfv(GL_LIGHT1, GL_DIFFUSE, light_buf);
     glLightfv(GL_LIGHT1, GL_AMBIENT, light_buf);
     glLightfv(GL_LIGHT1, GL_SPECULAR, light_buf);
     glLightfv(GL_LIGHT1, GL_POSITION, light_location );
     glEnable(GL_LIGHT1);
     glEnable(GL_LIGHTING);


	 //Set tree material
	glMaterialfv( GL_FRONT, GL_AMBIENT, tree_color[0] );
    glMaterialfv( GL_FRONT, GL_DIFFUSE,  tree_color[1] );
    glMaterialfv( GL_FRONT, GL_SPECULAR,  tree_color[2] );
	glMaterialfv( GL_FRONT, GL_EMISSION,  tree_color[3] );


		//Set color and draw branch then translate to the end of last branch
		glColor3f(.6,.3,0);
		gluCylinder( rootquad, diam,diam/1.5 , length, 40, 40 );
		glTranslatef( 0.0, 0.0, length );
	
	//Check for last branch
	 if(depth == 1)
	{
		//Set materials for the leaves	 
		glMaterialfv( GL_FRONT, GL_AMBIENT, leaf_color[0] );
		glMaterialfv( GL_FRONT, GL_DIFFUSE,  leaf_color[1] );
		glMaterialfv( GL_FRONT, GL_SPECULAR,  leaf_color[2] );
		glMaterialfv( GL_FRONT, GL_EMISSION,  leaf_color[3] );

		//Set leaf color
		glColor3f(0.0,.4,.01);
		
		//Rotate leaf1 along y axis and call make leaf
		glRotatef( 45, 0.0, 1.0, 0.0 );
		 makeleaf();
		
		 //Rotate leaf2 along y axis and call make leaf
		 glRotatef( 45, 1.0, 0.0, 0.0 );
		 makeleaf();

		//traslate leaf to the end of last branch
		glTranslatef( 0.0, 0.0, length );
		

	 }
	
	//decrease lenght and diam.
	length = length/1.25;
    diam = diam/1.5;

	//generate random numbers
	int num = rand() % 70;
	int num2 = rand() % 1;
	
	// set random angle1
	//if num2 == 0 then set angle negative
	if(num2 < 1)
		num = num * -1;

     glPushMatrix();
		//rotate and call function again
        glRotatef( (float)num, p[6], p[7], p[8] );
        drawTreeRecurse(depth - 1, p, diam, length);
     glPopMatrix();
	
	 //generate random numbers
	num = rand() % 70;
	num2 = rand() % 1;
	
	// set random angle2
	//if num2 == 0 then set angle negative
	if(num2 < 1)
		num = num * -1;
     glPushMatrix();
		//rotate and call function again
        glRotatef( num, p[10], p[11], p[12] );
        drawTreeRecurse(depth - 1, p, diam, length);
     glPopMatrix();
  glPopMatrix();
   }
}


// Draws a tree
//////////////////////////////////////////
void drawTree( int height, float *p ) {
  
	
	glPushMatrix();
		//rotate so the tree is vertical
		glRotatef( 90.0, 1.0, 0.0, 0.0 );
		//set quadric object
		rootquad = gluNewQuadric();
     
		//Scale 
		glScalef( 1.0, 1.0, -1.0 );

		//translate tree to bottom of window
		glTranslatef( 0.0, 0.0, -1.94 );
		//call draw tree
		drawTreeRecurse(height, p, p[1], p[0]);
	glPopMatrix();
  return;
}



void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	//draw tree that is 9 levels
	drawTree( 10, treeArray);
	glFlush();
	glutSwapBuffers();
}


//////////////////////////////////////////////////////////////////////////////////////////////////
// APPLICATION ENTRY POINT ///////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc,char* argv[])
{
				// however this information is trivial for 
														// our application, so this will do for
														// now.

	glutInit(&argc,argv);								// Initialize the GLUT engine

	/* need both double buffering and z buffer */
	//set up window
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
	glutInitWindowPosition(80, 80);
	glutInitWindowSize(1100, 900);
	glutCreateWindow("fractal tree");
	
	//keyboard function
	glutKeyboardFunc(HandleKeyboard);
	
	//reshape function
	glutReshapeFunc(myReshape);
	
	//display tree
	glutDisplayFunc(display);
  
	//handle mouse click
	glutMouseFunc(mouse);

    glEnable(GL_DEPTH_TEST); /* Enable hidden--surface--removal */
    glutMainLoop();



	return 0;
}