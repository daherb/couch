#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include<X11/Xlib.h>

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>

float xRotationAngle;
float yRotationAngle;
float zRotationAngle;

void display (void) {
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Clear the background of our window to  black
  glClear(GL_COLOR_BUFFER_BIT); //Clear the colour buffer (more buffers later on)
  glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations
  xRotationAngle+=drand48()*10.0;
  yRotationAngle+=drand48()*10.0;
  zRotationAngle+=drand48()*10.0;
  usleep(50000);
  glTranslatef(0.0f, 0.0f, -5.0f); // Push eveything 5 units back into the scene, otherwise we won't see the primitive
  glRotatef(xRotationAngle, 1.0f, 0.0f, 0.0f); // Rotate our object around the x axis
  glRotatef(yRotationAngle, 0.0f, 1.0f, 0.0f); // Rotate our object around the y axis
  glRotatef(zRotationAngle, 0.0f, 0.0f, 1.0f); // Rotate our object around the z axis
  glScalef(1.0f,0.2f,0.5f);
  glutWireCube(2.0f); // Render the primitive
  glScalef(1.0f,5.0f,2.0f);
  glTranslatef(0.0f,0.3f,-0.75f);
  glScalef(1.2f,0.5f,0.2f);
  glutWireCube(2.0f);
  glScalef(0.84f,2.0f,5.0f);
  glTranslatef(-1.0f,-0.1f,0.2f);
  glScalef(0.25f,0.25f,0.8f);
  glutWireCylinder(1.0f, 1.5f, 10.0f, 1.0f);
  glTranslatef(8.0f,-0.0f,0.0f);
  glutWireCylinder(1.0f, 1.5f, 10.0f, 1.0f);
  glScalef(4.0f,4.0f,1.25f);
  glFlush(); // Flush the OpenGL buffers to the window
}

void reshape (int width, int height) {
  glViewport(0, 0, (GLsizei)width, (GLsizei)height); // Set our viewport to the size of our window
  glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed
  glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)
  gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 100.0); // Set the Field of view angle (in degrees), the aspect ratio of our window, and the new and far planes
  glMatrixMode(GL_MODELVIEW); // Switch back to the model view matrix, so that we can start drawing shapes correctly
}

void keyPressed (unsigned char key, int x, int y) {
  if (key=='q')
    exit(0);
  else
    printf("Normal %d\n",key);
}

void keySpecial (int key, int x, int y) {
  if (key==GLUT_KEY_LEFT)
    yRotationAngle-=0.5f;
  else if (key==GLUT_KEY_RIGHT)
    yRotationAngle+=0.5f;
  else if (key==GLUT_KEY_UP)
    xRotationAngle-=0.5f;
  else if (key==GLUT_KEY_DOWN)
    xRotationAngle+=0.5f;
  else
    printf("Special %d\n",key);
  printf("%f\n",yRotationAngle);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv); // Initialize GLUT
  glutInitDisplayMode (GLUT_SINGLE); // Set up a basic display buffer (only single buffered for now)
  glutCreateWindow("GLEW Test");
  glutInitWindowSize (500, 500); // Set the width and height of the window
  glutInitWindowPosition (100, 100); // Set the position of the window
  GLenum err = glewInit();
  if (GLEW_OK != err)
    {
      /* Problem: glewInit failed, something is seriously wrong. */
      fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
      exit(-1);
    }
  fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

  glutDisplayFunc(display); // Tell GLUT to use the method "display" for rendering
  glutReshapeFunc(reshape); // Tell GLUT to use the method "reshape" for rendering
  glutKeyboardFunc(keyPressed); // Tell GLUT to use the method "keyPressed" for key presses
  glutSpecialFunc(keySpecial); // Tell GLUT to use the method "keySpecial" for special key presses
  glutIdleFunc(display); // Tell GLUT to use the method "display" as our idle method as well
  glutMainLoop(); // Enter GLUT's main loop
}
