/*  Connor Davis
 *  Homework 3 : Adding Lighting and textures
 *
 *  See README for key bindings
 *
 *  Consulted for 1st person:
      http://www.lighthouse3d.com/tutorials/glut-tutorial/keyboard-example-moving-around-the-world/
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

#include "CSCIx229.h"

//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

int th=0;         //  Azimuth of view angle
int ph=0;         //  Elevation of view angle
//double zh=0;      //  Rotation of teapot
int axes=1;       //  Display axes

int perspec=1;	  //  Projection or Orthographic
int fov=50;       //  Field of view (for perspective)
double asp=1;     //  Aspect ratio
double dim=5.0;   //  Size of world

//--------------------

//1st person/camera variables
// is it in 1stperson?
int first_person = 0;

// angle of rotation for the camera direction
float angle = 0.0f;

// vector representing the camera's direction
float lx=0.0f,lz=-1.0f,ly=0.0f;

// position of the camera
float x=0.0f, z=5.0f, y=0.0f;
//hese variables will be zero
//when no key is being pressed
float CameraAngle = 0.0f;
float CameraPos = 0;
int xOrigin = -2;

//--------------------

// Light values
int move=1;       //  Move light
int light=1;      //  Lighting

int one       =   1;  // Unit value
int distance  =   5;  // Light distance
int inc       =  10;  // Ball increment
int smooth    =   1;  // Smooth/Flat shading
int local     =   0;  // Local Viewer Model
int emission  =   0;  // Emission intensity (%)
int ambient   =  30;  // Ambient intensity (%)
int diffuse   = 100;  // Diffuse intensity (%)
int specular  =   10;  // Specular intensity (%)
int shininess =   0;  // Shininess (power of two)
float shinyvec[1];    // Shininess (value)
int zh        =  90;  // Light azimuth
float ylight  =   0;  // Elevation of light

//--------------------

// USE ME FOR TEXTURE NAMES
unsigned int texture[4];

// TEXTURE MODE
int texturemode = 1; 

int num = 26;
int k;
double rep=1;  //  Repetition
double X=1;    //  Top Right X
double Y=1;    //  Top Right Y
//--------------------

#define LEN 8192  //  Maximum length of text string
void Print(const char* format , ...)
{
   char    buf[LEN];
   char*   ch=buf;
   va_list args;
   //  Turn the parameters into a character string
   va_start(args,format);
   vsnprintf(buf,LEN,format,args);
   va_end(args);
   //  Display the characters one at a time at the current raster position
   while (*ch)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}



void calc_position(float CameraPos) {

   x += CameraPos * lx * 0.1f;
   z += CameraPos * lz * 0.1f;
   y += CameraPos * ly * 0.1f;

}

/*
 *  Draw a cube
 *     at (x,y,z)
 *     dimentions (dx,dy,dz)
 *     rotated th about the y axis
 */

 //---------------------SHAPES-----------------------------------


static void cube(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{
   //New Lighting Variables
   //  Set specular color to white
   float white[] = {1,1,1,1};
   float black[] = {0,0,0,1};
   //float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
   //float Emission[] ?

   //  Save transformation
   glPushMatrix();
   //  Offset
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);

   
   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   glColor3f(1,1,1);
   
   //ENABLE THE TEXTUREFOR THA ROBOTS
   //glBindTexture(GL_TEXTURE_2D,texture[1]);
  
    

   //  Cube
   
   //  Front
   glColor3f(.1,.7,.7);
   glBindTexture(GL_TEXTURE_2D,texture[3]);
   glBegin(GL_QUADS);
   glNormal3f( 0, 0, 1);
   glTexCoord2f(0,0); glVertex3f(-1,-1, 1);
   glTexCoord2f(1,0); glVertex3f(+1,-1, 1);
   glTexCoord2f(1,1); glVertex3f(+1,+1, 1);
   glTexCoord2f(0,1); glVertex3f(-1,+1, 1);
   glEnd();
   //  Back
   glColor3f(.1,.1,.1);
   glBindTexture(GL_TEXTURE_2D,texture[3]);
   glBegin(GL_QUADS);
   glNormal3f( 0, 0,-1);
   glTexCoord2f(0,0); glVertex3f(+1,-1,-1);
   glTexCoord2f(1,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(1,1); glVertex3f(-1,+1,-1);
   glTexCoord2f(0,1); glVertex3f(+1,+1,-1);
   glEnd();
   //  Right
   glColor3f(.1,.7,.7);
   glBindTexture(GL_TEXTURE_2D,texture[3]);
   glBegin(GL_QUADS);
   glNormal3f(+1, 0, 0);
   glTexCoord2f(0,0); glVertex3f(+1,-1,+1);
   glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
   glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
   glTexCoord2f(0,1); glVertex3f(+1,+1,+1);
   glEnd();
   //  Left
   glColor3f(.1,.7,.7);
   glBindTexture(GL_TEXTURE_2D,texture[3]);
   glBegin(GL_QUADS);
   glNormal3f(-1, 0, 0);
   glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(1,0); glVertex3f(-1,-1,+1);
   glTexCoord2f(1,1); glVertex3f(-1,+1,+1);
   glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
   glEnd();
   //  Top
   glColor3f(0,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[3]);
   glBegin(GL_QUADS);
   glNormal3f( 0,+1, 0);
   glTexCoord2f(0,0); glVertex3f(-1,+1,+1);
   glTexCoord2f(1,0); glVertex3f(+1,+1,+1);
   glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
   glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
   glEnd();
   //  Bottom
   glColor3f(.1,.1,.1);
   glBindTexture(GL_TEXTURE_2D,texture[3]);
   glBegin(GL_QUADS);
   glNormal3f( 0,-one, 0);
   glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
   glTexCoord2f(1,1); glVertex3f(+1,-1,+1);
   glTexCoord2f(0,1); glVertex3f(-1,-1,+1);
   glEnd();
   //  Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

/*
static void test_gridcube()
{
   int i,j;
   double mul = 2.0/num;
   //New Lighting Variables
   //Set specular color to white
   float white[] = {1,1,1,1};
   float black[] = {0,0,0,1};
   glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
   //float Emission[] ?

   //  Save transformation
   glPushMatrix();
   //  Offset
   //glTranslated(x,y,z);
   //glRotated(th,0,1,0);
   //glScaled(dx,dy,dz);

   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   

   
   for (j=0;j<num;j++)
      for (i=0;i<num;i++)
      {
         //X Y Z    
         
         //glTexCoord2d(mul*(i+0),mul*(j+0)); glVertex2d(5*mul*(i+0)-5,5*mul*(i+0)-5);
         //glTexCoord2d(mul*(i+1),mul*(j+0)); glVertex2d(5*mul*(i+1)-5,5*mul*(j+0)-5);
         //glTexCoord2d(mul*(i+1),mul*(j+1)); glVertex2d(5*mul*(i+1)-5,5*mul*(j+1)-5);
         //glTexCoord2d(mul*(i+0),mul*(j+1)); glVertex2d(5*mul*(i+0)-5,5*mul*(j+1)-5);

         glTexCoord2d(mul*(i+0),mul*(j+0)); glVertex3f(5*mul*(i+0)-5,5*mul*(i+0)-5,1);
         glTexCoord2d(mul*(i+1),mul*(j+0)); glVertex3f(5*mul*(i+1)-5,5*mul*(j+0)-5,1);
         glTexCoord2d(mul*(i+1),mul*(j+1)); glVertex3f(5*mul*(i+1)-5,5*mul*(j+1)-5,1);
         glTexCoord2d(mul*(i+0),mul*(j+1)); glVertex3f(5*mul*(i+0)-5,5*mul*(j+1)-5,1);
      }
   glEnd();
 

   glBegin(GL_QUADS);

   for (i=0;i<num;i++)
    for (j=0;j<num;j++)
    {
      //  Draw the wall
      glColor3f(1.0,1.0,1.0);
      glNormal3f(0,0,1); 
      
      glVertex3f(i+1,j+1,1);
    }

   glEnd();
   glDisable(GL_TEXTURE_2D);
   //  Undo transformations
   glPopMatrix();
}
*/

static void connorObject(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{
	glPushMatrix();

	glTranslated(x,y,z);
	glRotated(th,0,1,0);
	glScaled(dx,dy,dz);

	glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

	// Front
	
	glColor3f(1,1,1);
	glBindTexture(GL_TEXTURE_2D,texture[3]);
    glBegin(GL_QUADS);
    glNormal3f( 0, 0, 1);
	glTexCoord2f(0,0); glVertex3f(-1,0,1);
	glTexCoord2f(1,0); glVertex3f(1,0,1);
	glTexCoord2f(1,1); glVertex3f(1,3,1);
	glTexCoord2f(0,1); glVertex3f(-1,3,1);
   	glEnd();


	//Slant
	glColor3f(.1,.1,.1);
	glBindTexture(GL_TEXTURE_2D,texture[1]);
    glBegin(GL_QUADS);
    glNormal3f(0,1,-1);
	glTexCoord2f(0,0); glVertex3f(1,3,1);
	glTexCoord2f(1,0); glVertex3f(-1,3,1);
	glTexCoord2f(1,1); glVertex3f(-1,0,-2);
	glTexCoord2f(0,1); glVertex3f(1,0,-2);
	glEnd();
	
	//Bottom
	glColor3f(.1,.1,.1);
	glBindTexture(GL_TEXTURE_2D,texture[1]);
    glBegin(GL_QUADS);
    glNormal3f( 0,-one, 0);
	glTexCoord2f(0,0); glVertex3f(1,0,1);
    glTexCoord2f(1,0); glVertex3f(-1,0,1);
    glTexCoord2f(1,1); glVertex3f(-1,0,-2);
	glTexCoord2f(0,1); glVertex3f(1,0,-2);

    glTexCoord2f(0,0); glVertex3f(-1,0,1);
	glTexCoord2f(1,0); glVertex3f(1,0,1);
	glTexCoord2f(1,1); glVertex3f(1,3,1);
	glTexCoord2f(0,1); glVertex3f(-1,3,1);
	glEnd();

  //Left Ear
	glBindTexture(GL_TEXTURE_2D,texture[1]);
    glBegin(GL_TRIANGLES);
	glColor3f(.1,.7,.7);
    glNormal3f(-1, 0, 0); 
	glTexCoord2f(0,0); glVertex3f(-1,3,1);
	glTexCoord2f(.5,0); glVertex3f(-1,0,-2);
	glTexCoord2f(.5,1); glVertex3f(-1,0,1);
	glEnd();

  //Right Ear
	glBindTexture(GL_TEXTURE_2D,texture[1]);
    glBegin(GL_TRIANGLES);
    glNormal3f(+1, 0, 0);
	glTexCoord2f(0,0); glVertex3f(1,3,1);
	glTexCoord2f(.5,0); glVertex3f(1,0,-2);
	glTexCoord2f(.5,1); glVertex3f(1,0,1);
    glEnd();  	


 	glPopMatrix();
 	glDisable(GL_TEXTURE_2D);
}


/*
 *  Draw vertex in polar coordinates
 */
static void Vertex(double th,double ph)
{
   /*
   glColor3f(0.0,.99,.5);
   glVertex3d(Sin(th)*Cos(ph) , Sin(ph) , Cos(th)*Cos(ph));
  */
   
   //New Vertex Function 
   double x = Sin(th)*Cos(ph);
   double y = Cos(th)*Cos(ph);
   double z =         Sin(ph);
   //  For a sphere at the origin, the position
   //  and normal vectors are the same
   glNormal3d(x,y,z);
   glTexCoord2d(th/360.0,ph/180.0+0.5);
   glVertex3d(x,y,z);
   
}

/*
 *  Draw a sphere (version 2)
 *     at (x,y,z)
 *     radius (r)
 */
static void sphere2(double x,double y,double z,double r)
{
   const int d=5;
   int th,ph;

   //  Save transformation
   glPushMatrix();
   //  Offset and scale
   glTranslated(x,y,z);
   glScaled(r,r,r);

   glEnable(GL_TEXTURE_2D);
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   //  Latitude bands
   for (ph=-90;ph<90;ph+=d)
   {
      glBegin(GL_QUAD_STRIP);
      for (th=0;th<=360;th+=d)
      {
         Vertex(th,ph);
         Vertex(th,ph+d);
      }
      glEnd();
      glDisable(GL_BLEND);
   }

   //  Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

static void portal_step(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{
   //  Save transformation
   glPushMatrix();
   //  Offsetm
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);

//  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   


   // Rectangles 
   glBindTexture(GL_TEXTURE_2D,texture[1]);
   glBegin(GL_QUADS);
   
   //  Front
   glColor3f(1, 1, 1);
   glNormal3f( 0, 0, 1);
   glTexCoord2f(0,0); glVertex3f(-1,-1, 1);
   glTexCoord2f(1,0); glVertex3f(+1,-1, 1);
   glTexCoord2f(1,1); glVertex3f(+1,+1, 1);
   glTexCoord2f(0,1); glVertex3f(-1,+1, 1);
   //glEnd();
   
   //  Back
   glNormal3f( 0, 0, -1);
   glTexCoord2f(0,0); glVertex3f(+1,-1,-1);
   glTexCoord2f(1,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(1,1); glVertex3f(-1,+1,-1);
   glTexCoord2f(0,1); glVertex3f(+1,+1,-1);
   
   //  Right
   glNormal3f(1, 0, 0);
   glTexCoord2f(0,0); glVertex3f(+1,-1,+1);
   glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
   glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
   glTexCoord2f(0,1); glVertex3f(+1,+1,+1);
   
   //  Left
   glNormal3f(-1, 0, 0);
   glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(1,0); glVertex3f(-1,-1,+1);
   glTexCoord2f(1,1); glVertex3f(-1,+1,+1);
   glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
   
   //  Top
   glNormal3f( 0,+1, 0);
   glTexCoord2f(0,0); glVertex3f(-1,+1,+1);
   glTexCoord2f(1,0); glVertex3f(+1,+1,+1);
   glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
   glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
   
   //  Bottom
   glNormal3f( 0,-one, 0);
   glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
   glTexCoord2f(1,1); glVertex3f(+1,-1,+1);
   glTexCoord2f(0,1); glVertex3f(-1,-1,+1);
   
   //  End
   glEnd();

   //  Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

static void building(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{
   //  Save transformation
   glPushMatrix();
   //  Offsetm
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);

//  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   


   // Rectangles 
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   
   //  Front
   glColor3f(1, 1, 1);
   glNormal3f( 0, 0, 1);
   glTexCoord2f(0,0); glVertex3f(-1,-1, 1);
   glTexCoord2f(1,0); glVertex3f(+1,-1, 1);
   glTexCoord2f(1,1); glVertex3f(+1,+1, 1);
   glTexCoord2f(0,1); glVertex3f(-1,+1, 1);
   //glEnd();
   
   //  Back
   glNormal3f( 0, 0, -1);
   glTexCoord2f(0,0); glVertex3f(+1,-1,-1);
   glTexCoord2f(1,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(1,1); glVertex3f(-1,+1,-1);
   glTexCoord2f(0,1); glVertex3f(+1,+1,-1);
   
   //  Right
   glNormal3f(1, 0, 0);
   glTexCoord2f(0,0); glVertex3f(+1,-1,+1);
   glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
   glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
   glTexCoord2f(0,1); glVertex3f(+1,+1,+1);
   
   //  Left
   glNormal3f(-1, 0, 0);
   glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(1,0); glVertex3f(-1,-1,+1);
   glTexCoord2f(1,1); glVertex3f(-1,+1,+1);
   glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
   
   //  Top
   glNormal3f(0,1, 0);
   glTexCoord2f(0,0); glVertex3f(-1,+1,+1);
   glTexCoord2f(1,0); glVertex3f(+1,+1,+1);
   glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
   glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
   
   //  Bottom
   glNormal3f( 0,-one, 0);
   glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
   glTexCoord2f(1,1); glVertex3f(+1,-1,+1);
   glTexCoord2f(0,1); glVertex3f(-1,-1,+1);
   
   //  End
   glEnd();

   //  Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}



/*
 *  Draw a ball
 *     at (x,y,z)
 *     radius (r)
 */
static void ball(double x,double y,double z,double r)
{
   int th,ph;
   float yellow[] = {1.0,1.0,0.0,1.0};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(r,r,r);
   //  White ball
   glColor3f(1,1,1);
   glMaterialfv(GL_FRONT,GL_SHININESS,shinyvec);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission);
   //  Bands of latitude
   for (ph=-90;ph<90;ph+=inc)
   {
      glBegin(GL_QUAD_STRIP);
      for (th=0;th<=360;th+=2*inc)
      {
         Vertex(th,ph);
         Vertex(th,ph+inc);
      }
      glEnd();
   }
   //  Undo transofrmations
   glPopMatrix();
}

/*
 *  GLUT calls this toutine when there is nothing else to do
 */
void idle()
{
   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   zh = fmod(90*t,360);
   glutPostRedisplay();
}


//-----------------------DISPLAY------------------------

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   if (CameraPos)
      calc_position(CameraPos);

   const double len=1.5;  //  Length of axes
   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);
   //  Undo previous transformations
   glLoadIdentity();

   //Variables for gluLookAt
   double Ex = -2*dim*Sin(th)*Cos(ph);
   double Ey = +2*dim        *Sin(ph);
   double Ez = +2*dim*Cos(th)*Cos(ph);

   if (first_person)
   {
    gluLookAt(x, 1.05f, z,
       x+lx, 1.0f,  z+lz,
       0.0f, 1.0f,  0.0f);
   }

	//Projection Mode
	else
   {
      if (perspec)
         {
            gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,1,0);
         }
         
      //  Orthogonal - set world orientation
      else
      {
         glRotatef(ph,1,0,0);
         glRotatef(th,0,1,0);
      }

         
   }
   
   //---------LIGHTS---------


   //  Flat or smooth shading
   glShadeModel(smooth ? GL_SMOOTH : GL_FLAT);

   //  Light switch
   if (light)
   {
        //  Translate intensity to color vectors
        float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
        float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
        float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
        //  Light position
        float Position[]  = {distance*Cos(zh),ylight,distance*Sin(zh),1.0};
        //  Draw light position as ball (still no lighting here)
        glColor3f(1,1,1);
        ball(Position[0],Position[1],Position[2] , 0.1);
        //  OpenGL should normalize normal vectors
        glEnable(GL_NORMALIZE);
        //  Enable lighting
        glEnable(GL_LIGHTING);
        //  Location of viewer for specular calculations
        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,local);
        //  glColor sets ambient and diffuse color materials
        glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
        glEnable(GL_COLOR_MATERIAL);
        //  Enable light 0
        glEnable(GL_LIGHT0);
        //  Set ambient, diffuse, specular components and position of light 0
        glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
        glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
        glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
        glLightfv(GL_LIGHT0,GL_POSITION,Position);
   }
   else
     glDisable(GL_LIGHTING);

 	//-----------------


   // BIG ROBOT
   // LEGS
   cube(0,0,0 , 0.05, 0.15, 0.05, 0);
   cube(0.25,0,0 , 0.05,0.15,0.05, 0);

   // BODY
   cube(0.125,0.3,0 , 0.2,0.25,0.15, 0);

   // ARMS
   cube(-.125,0.35,0.35 , 0.05, 0.05, 0.25, 0);
   cube(.375,0.35,0.35 , 0.05, 0.05, 0.25, 0);

   // HEAD
	connorObject(0.125,0.55,0 , .1,.1,.1, 0);

	//Tiny Robot (Half Scale)
		
   // LEGS
   cube(.05,-.075,2 , 0.025, 0.075, 0.025, 180);
   cube(0.2,-.075,2 , 0.025,0.075,0.025, 180);

   // BODY
   cube(0.125,0.125,2 , 0.1,0.125,0.075, 180);

   // ARMS
   cube(0,0.15,1.85 , 0.025, 0.025, 0.125, 180);
   cube(0.25,0.15,1.85 , 0.025, 0.025, 0.125, 180);
   // HEAD
   connorObject(0.125,0.25,2 , .05,.05,.05, 180);

   //GREEN PORTAL
   sphere2(1,.5,-1.5,.5);
   //sphere2();
   
   //PORTAL MACHINERY
   portal_step(1,1.05,-1.5 , .5,.1,.5, 1);
   portal_step(1,-.05,-1.5 , .5,.1,.5, 1);

   
   //Create the floor/building
   building(0,-5.15,0 , 2,-5,2, 1);

   //test_gridcube();



   //  White for axes
   glColor3f(1,1,1);
   //  Draw axes
   if (axes)
   {
      glBegin(GL_LINES);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(len,0.0,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,len,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,0.0,len);
      glEnd();
      //  Label axes
      glRasterPos3d(len,0.0,0.0);
      Print("X");
      glRasterPos3d(0.0,len,0.0);
      Print("Y");
      glRasterPos3d(0.0,0.0,len);
      Print("Z");
   }
   //  Five pixels from the lower left corner of the window
   glWindowPos2i(5,5);
   //  Print the text string - UPDATED
   Print("Angle=%d,%d  Dim=%.1f FOV=%d Projection=%s Light=%s",
     th,ph,dim,fov,perspec?"Perpective":"Orthogonal",light?"On":"Off");
   if (light)
   {
      glWindowPos2i(5,45);
      Print("Model=%s LocalViewer=%s Distance=%d Elevation=%.1f",smooth?"Smooth":"Flat",local?"On":"Off",distance,ylight);
      glWindowPos2i(5,25);
      Print("Ambient=%d  Diffuse=%d Specular=%d Emission=%d Shininess=%.0f",ambient,diffuse,specular,emission,shinyvec[0]);
   }
   //  Error Checking
   ErrCheck("display");
   //  Render the scene
   glFlush();
   //  Make the rendered scene visible
   glutSwapBuffers();

   
}


/*
*  GLUT calls this routine when an arrow key is released
*/
void releaseKey(int key, int x, int y) {    
   switch (key) {
      case GLUT_KEY_UP :
      case GLUT_KEY_DOWN : CameraPos = 0; break;
      case GLUT_KEY_LEFT : CameraPos = 0; break;
   }
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{

   if(first_person == 1){

      switch (key) {
             case GLUT_KEY_UP : CameraPos = 0.5f; break;
             case GLUT_KEY_DOWN : CameraPos = -0.5f; break;
             case GLUT_KEY_LEFT :
                  angle -= 0.05f;
                  lx = sin(angle);
                  lz = -cos(angle);
                  break;
            case GLUT_KEY_RIGHT :
                  angle += 0.05f;
                  lx = sin(angle);
                  lz = -cos(angle);
                  break;
               }
   }

   else{
   
      //  Right arrow key - increase angle by 5 degrees
      if (key == GLUT_KEY_RIGHT)
         th += 5;
      //  Left arrow key - decrease angle by 5 degrees
      else if (key == GLUT_KEY_LEFT)
         th -= 5;
      //  Up arrow key - increase elevation by 5 degrees
      else if (key == GLUT_KEY_UP)
         ph += 5;
      //  Down arrow key - decrease elevation by 5 degrees
      else if (key == GLUT_KEY_DOWN)
         ph -= 5;
      // NEW STUFF

      //  PageUp key - increase dim
      else if (key == GLUT_KEY_PAGE_DOWN)
         dim += 0.1;
      //  PageDown key - decrease dim
      else if (key == GLUT_KEY_PAGE_UP && dim>1)
         dim -= 0.1;
      //  Smooth color model
      else if (key == GLUT_KEY_F1)
         smooth = 1-smooth;
       //  Local Viewer
      else if (key == GLUT_KEY_F2)
         local = 1-local;
      else if (key == GLUT_KEY_F3)
         distance = (distance==1) ? 5 : 1;
      //  Toggle ball increment
      else if (key == GLUT_KEY_F8)
         inc = (inc==10)?3:10;
      //  Flip sign
      else if (key == GLUT_KEY_F9)
         one = -one;



      //  Keep angles to +/-360 degrees
      th %= 360;
      ph %= 360;
      //  Tell GLUT it is necessary to redisplay the scene


      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      if (perspec)
         gluPerspective(fov,asp,dim/4,4*dim);
      else
         glOrtho(-asp*dim,+asp*dim, -dim,+dim, -dim,+dim);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      glutPostRedisplay();
   }
}


/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0);
   //  Reset view angle
   else if (ch == '0')
      th = ph = 0;
   //  Toggle axes
   else if (ch == 'x' || ch == 'X')
      axes = 1-axes;
   else if (ch == '-' && ch>1)
      fov--;
   else if (ch == '+' && ch<179)
      fov++;
   else if (ch == '1' && perspec == 1)
      first_person = 1-first_person;
   //  Toggle lighting
   else if (ch == 'l' || ch == 'L')
      light = 1-light;
   //  Toggle light movement
   else if (ch == 'm' || ch == 'M')
      move = 1-move;
   //  Move light
   else if (ch == '<')
      zh += 1;
   else if (ch == '>')
      zh -= 1;
   //  Light elevation
   else if (ch=='[')
      ylight -= 0.1;
   else if (ch==']')
      ylight += 0.1;
   //  Ambient level
   else if (ch=='a' && ambient>0)
      ambient -= 5;
   else if (ch=='A' && ambient<100)
      ambient += 5;
   //  Diffuse level
   else if (ch=='d' && diffuse>0)
      diffuse -= 5;
   else if (ch=='D' && diffuse<100)
      diffuse += 5;
   //  Specular level
   else if (ch=='s' && specular>0)
      specular -= 5;
   else if (ch=='S' && specular<100)
      specular += 5;
   //  Emission level
   else if (ch=='e' && emission>0)
      emission -= 5;
   else if (ch=='E' && emission<100)
      emission += 5;
   //  Shininess level
   else if (ch=='n' && shininess>-1)
      shininess -= 1;
   else if (ch=='N' && shininess<7)
      shininess += 1;
   /* Testing removal - shouldn't need ortho anymore
   else if (ch == '[')
      perspec = 1;
   else if (ch == ']')
      perspec = 0;
   */


   //  Translate shininess power to value (-1 => 0)
   shinyvec[0] = shininess<0 ? 0 : pow(2.0,shininess);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (perspec)
      gluPerspective(fov,asp,dim/4,4*dim);
   else {
      //  Tell OpenGL we want to manipulate the projection matrix
      glMatrixMode(GL_PROJECTION);
      //  Undo previous transformations
      glLoadIdentity();
      //  Perspective transformation
      if (perspec)
         gluPerspective(fov,asp,.1,4*dim);
      //  Orthogonal projection
      else
         glOrtho(-asp*dim,+asp*dim, -dim,+dim, -dim,+dim);
         //  Switch to manipulating the model matrix
         glMatrixMode(GL_MODELVIEW);
         //  Undo previous transformations
         glLoadIdentity();
      }
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   glutIdleFunc(move?idle:NULL);
   glutPostRedisplay();
}


/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   //const double dim=2.5;
   //Ratio of the width to the height of the window
   //double w2h = (height>0) ? (double)width/height : 1;

   //  Set the viewport to the entire window
   //glViewport(0,0, width,height);

   if(first_person){
   
      if (height == 0)
            height = 1;
      float ratio =  width * 1.0 / height;
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glViewport(0, 0, width, height);
      gluPerspective(45.0f, ratio, 0.1f, 100.0f);
      glMatrixMode(GL_MODELVIEW);
   }

   //Ortho Mode
   else{
      //  Ratio of the width to the height of the window
      asp = (height>0) ? (double)width/height : 1;
      //  Set the viewport to the entire window
      glViewport(0,0, width,height);

      // TEMP PROJECT
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      if (perspec)
         gluPerspective(fov,asp,dim/4,4*dim);
      else
         glOrtho(-asp*dim,+asp*dim, -dim,+dim, -dim,+dim);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
   }
}




/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
   //  Initialize GLUT and process user parameters
   glutInit(&argc,argv);
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitWindowSize(600,600);
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutCreateWindow("Connor Davis HW3");

   glutIdleFunc(idle);
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   glutSpecialUpFunc(releaseKey);

   //Textures
   texture[0] = LoadTexBMP("electronics.bmp");
   texture[1] = LoadTexBMP("steampunk.bmp");
   texture[2] = LoadTexBMP("nether.bmp");
   texture[3] = LoadTexBMP("forerunner.bmp");

   glutMainLoop();
   return 0;
}
