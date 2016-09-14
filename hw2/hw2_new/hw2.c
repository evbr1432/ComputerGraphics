/*Works Cited
http://gamejust4u.webs.com/apps/forums/topics/show/8127559-opengl-color-guide
https://gist.github.com/23ars/4545671
http://www.lighthouse3d.com/tutorials/glut-tutorial/keyboard-example-moving-around-the-world/
*/
/*
 *  3D Objects
 *
 *  Demonstrates how to draw objects in 3D.
 *
 *  Key bindings:
 *  m          Go from model view to first person
 *  a          Toggle axes
 *  page up    Raise Dim
 *  page down  Lower Dim
 *  arrows     Change view angle
 *  p          In model view, changes from perspective mode to orthogonal
 *  0          Reset view angle
 *  ESC        Exit
 */
#include "shapes.h"

int th=0;         //  Azimuth of view angle
int ph=0;         //  Elevation of view angle
double zh=0;      //  Rotation of teapot
int axes=1;       //  Display axes
int mode=0;
int p=0;        //  perspective or orthoganal
double dim=3.5;   // dimension
int fov = 60;     // feild of view
double asp = 1;   // Aspect ratio
int i,j;

// angle of rotation for the camera direction
float angle = 0.0f;

// vector representing the camera's direction
float lx=0.0f,lz=-1.0f,ly=0.0f;

// position of the camera
float x=0.0f, z=5.0f, y=0.0f;

// the key states. These variables will be zero
//when no key is being presses
float CameraAngle = 0.0f;
float CameraPos = 0;
int xOrigin = -2;

//change from ortho and perspective
static void Project()
{
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective transformation
   if (p)
      gluPerspective(fov,asp,0.1,4*dim);
   //  Orthogonal projection
   else
      glOrtho(-asp*dim,+asp*dim, -dim,+dim, -dim,+dim);
   //  Switch to manipulating the model matrix
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   glLoadIdentity();
}
/*
 *  calculates position
 */
void calc_position(float CameraPos) {

   x += CameraPos * lx * 0.1f;
   z += CameraPos * lz * 0.1f;
   y += CameraPos * ly * 0.1f;

}

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

//Draw the bed
void drawbed(){
   //  Draw cubes
   double a = 0.04;
   double b = 0.3;
   double c = 0.05;

   //box frame
   box(1.02,.57,0 , .7,0.1,0.5 , 0);

   //head board
   glColor3f(0.5f, 0.35f, 0.05f);
   cube(.30,.62,0 , .01,.4,0.5 , 0);

   //pillow
   glColor3f(1,1,1);
   cube(.5,.67,0  , .15,.05,.3 , 0);

   //legs
   glColor3f(0.5f, 0.35f, 0.05f);
   cube(1.65,.32,.4  , a,b,c , 0);
   cube(.35,.32,-.4  , a,b,c , 0);
   cube(1.65,.32,-.4 , a,b,c , 0);
   cube(.35,.32,.4  , a,b,c , 0);
}
//Draw ladder
void drawLadder(){
   glColor3f(0.5f, 0.35f, 0.05f);
   cube(1.3,.67,.55  , 0.02,.65,.04 , 0);
   glColor3f(0.5f, 0.35f, 0.05f);
   cube(1.6,.67,.55  , 0.02,.65,.04 , 0);
}
//draw rungs of ladder
void drawRungs(){
   glColor3f(0.5f, 0.35f, 0.05f);
   cube(1.45,.67,.55, 0.15,.03,.04 , 0);
}
//draw stars in sky
void drawStar(){

   star(1,3,2,.1,.1,.1);
}
//draw big star
void drawStar2(){

   star(3,1.5,0,1,1,1);
}

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
   if (mode){
      gluLookAt(x, 1.0f, z,
         x+lx, 1.0f,  z+lz,
         0.0f, 1.0f,  0.0f);
   }

   else{
      //if perpspective is on
      if (p)
      {
         double Ex = -2*dim*Sin(th)*Cos(ph);
         double Ey = +2*dim        *Sin(ph);
         double Ez = +2*dim*Cos(th)*Cos(ph);
         gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,1,0);
      }
      //else do ortho
      else
      {
      //  Set view angle
      glRotatef(ph,1,0,0);
      glRotatef(th,0,1,0);
      }
   }
//draw stuff
   drawLadder();
   drawbed();
   drawStar();

//Draw 2 beds
   for(i = 0; i < 3; i++) {
         glPushMatrix();
         glTranslatef(0,.55,0*1.0);
         drawbed();
         glPopMatrix();
      }

   //Draw rungs of ladder
   for(j = -2; j < 4; j++) {
      glPushMatrix();
      glTranslatef(0,j*.2,0);
      drawRungs();
      glPopMatrix();
   }

  //Stars
   for(int k = 0; k < 3; k++) 
   {
      for (int l = -5; l < 5; ++l)
      {
         for (int dd = -5; dd < 5; ++dd)
         {
         
           glPushMatrix();
           glTranslatef(l*2,k*2,dd*2);
           drawStar();
           glPopMatrix();
         }
      }
      
   }
   //Draw big star
   drawStar2();
  
   //  White
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


   //Color ground
   glColor3f(2.0f, 0.5f, 1.0f);
   glBegin(GL_QUADS);
      glVertex3f(-100.0f, 0.0f, -100.0f);
      glVertex3f(-100.0f, 0.0f,  100.0f);
      glVertex3f( 100.0f, 0.0f,  100.0f);
      glVertex3f( 100.0f, 0.0f, -100.0f);
   glEnd();
   
   //**** Only used for error checking ****
   //int a = glGetError();
   //printf("%i\n",a );
  

   //  Five pixels from the lower left corner of the window
   glWindowPos2i(5,5);
   //  Print the text string
   Print("Angle=%d,%d",th,ph);

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
             case GLUT_KEY_DOWN : CameraPos = 0;break;
             case GLUT_KEY_LEFT : CameraPos = 0; break;
        }
}

//special glut call for camera
void special(int key,int x,int y)
{
  if(mode){

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
      //  PageUp key - increase dim
      else if (key == GLUT_KEY_PAGE_UP)
         dim += 0.1;
      //  PageDown key - decrease dim
      else if (key == GLUT_KEY_PAGE_DOWN && dim>1)
         dim -= 0.1;
      //  Keep angles to +/-360 degrees
      th %= 360;
      ph %= 360;
      //update projection
      Project();
   }
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
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
   else if (ch == 'a' || ch == 'A')
      axes = 1-axes;
   //  Switch display mode
   else if (ch == 'm')
      mode ^= 1;
   //for perspective and ortho views
   else if (ch == 'p')
      p ^= 1;
   //  Tell GLUT it is necessary to redisplay the scene
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (mode){
      gluPerspective(fov,asp,dim/4,dim*4);
   }
   else{
      Project();
   }
   glMatrixMode(GL_MODELVIEW);
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
//if in 1st person we need a differant resize function
   if(mode){
   if (height == 0)
         height = 1;
      float ratio =  width * 1.0 / height;
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glViewport(0, 0, width, height);
      gluPerspective(45.0f, ratio, 0.1f, 100.0f);
      glMatrixMode(GL_MODELVIEW);
   }
//else were in ortho mode
   else{
      //  Ratio of the width to the height of the window
      asp = (height>0) ? (double)width/height : 1;
      //  Set the viewport to the entire window
      glViewport(0,0, width,height);
      //  Set projection
      Project();
   }
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
   //  Create the window
   glutCreateWindow("Evan Brookens - HW2");
   //  Tell GLUT to call "idle" when there is nothing else to do
   glutIdleFunc(idle);
   //  Tell GLUT to call "display" when the scene should be drawn
   glutDisplayFunc(display);
   //  Tell GLUT to call "reshape" when the window is resized
   glutReshapeFunc(reshape);
   //  Tell GLUT to call "special" when an arrow key is pressed
   glutSpecialFunc(special);
   glutSpecialUpFunc(releaseKey);
   //  Tell GLUT to call "key" when a key is pressed
   glutKeyboardFunc(key);

   //  Pass control to GLUT so it can interact with the user
   glutMainLoop();
   return 0;
}
