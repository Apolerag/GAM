#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  
#include <math.h>  
#include <assert.h>
#include <GL/glut.h> 

extern char *optarg;
extern int opterr;

int displayChoice = 0;
char *lineOption[] = { "GL_POINTS", "GL_LINES", "GL_LINE_STRIP", "GL_LINE_LOOP", "GL_POLYGON"};

void winInit (void)
{
  gluOrtho2D(0.0, 200, 0.0, 200);
}


void display (void)
{
  glColor3f(0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0, 1.0, 1.0);
  /* glColor3f(1.0, 0.0, 0.0); */
		
  switch (displayChoice)
  {
		  case 0: glBegin(GL_POINTS);
				  break;
		  case 1: glBegin(GL_LINES);
				  break;
		  case 2: glBegin(GL_LINE_STRIP);
				  break;
		  case 3: glBegin(GL_LINE_LOOP);
				  break;
		  default: glBegin(GL_POLYGON);
				  break;
  }

  glVertex2f(50.0, 50.0);
  glVertex2f(100.0, 50.0);
  glVertex2f(100.0, 100.0);
  glVertex2f(50.0, 100.0);

  glEnd();

  glFlush();
}

int main(int argc, char **argv)  
{  
  int option;

  opterr = 0; /* set off std error messages in case wrong option is chosen */
  while ((option = getopt(argc, argv, "c:")) != EOF)
  {
		  switch (option)
		  {
			case 'c': if ((sscanf(optarg, "%d", &displayChoice) == 1) && displayChoice >= 0 && displayChoice <= 4)
						break;
			case '?': /* value returned by getopt if invalid option chosen */
			default : printf("Usage: %s -cX, with X = 1, 2, 3 or 4.\n", argv[0]);
					  displayChoice = 0;
					  break;
		  }
  }
  assert(displayChoice >= 0 && displayChoice <= 4);
  printf("Executing %s with line option %d = %s.\n", argv[0], displayChoice, lineOption[displayChoice]);
  glutInit(&argc, argv);  
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);  

  glutInitWindowPosition(5,5);  
  glutInitWindowSize(300,300);  

  glutCreateWindow("My first OpenGL window...");  
  
  winInit();

  glutDisplayFunc(display);  

  glutMainLoop();  
  
  return EXIT_SUCCESS;  
}  
