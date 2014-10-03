/*! \file fenetre.c
* \author A Chemier, R Lhomme
* \date 2014
*/

#include "fenetre.h"

void definitionFenetre(const double X_min, const double X_max, const double Y_min, const double Y_max, const double margin)
{
	f.minX = X_min;
	f.maxX = X_max;
	f.minY = Y_min;
	f.maxY = Y_max;
	f.margin = margin;
	initialisePolygone(&P, 10);
}

void clearFenetre(fenetre *f)
{
	videPolygone(&P);
}

double myRandom (const double a, const 	double b)
{
	double tmp = random(); /* long int in [0, RAND_MAX] */

	return a+tmp*((b-a)/RAND_MAX);
}

void winInit()
{
	gluOrtho2D(f.minX, f.maxX, f.minY, f.maxY);
}

void selectPoints (polygone *P)
{
	int n = P->nbVertex;

	while (--n >= 0)
	{
		P->p[n].coords[0] = myRandom(f.minX + 10, f.maxX-10);
		P->p[n].coords[1] = myRandom(f.minY + 10, f.maxY-10);
	}
	
}

void displayPolygone()
{
	int i = P.nbVertex;

	glColor3f(0.0, 0.0, 0.0); 
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	glBegin(GL_LINES);

	while (--i > 0)
	{
		glVertex2f(P.p[i].coords[0], P.p[i].coords[1]);
		glVertex2f(P.p[i+1].coords[0], P.p[i+1].coords[1]);
	}

	glEnd();

	glFlush();
}


void display()
{
	glColor3f(0.0, 0.0 , 0.0); 
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	glBegin(GL_POINTS);

	glEnd();

	glFlush();
}

void displayPoint()
{
	int i;
	glColor3f(0.0, 0.0 , 0.0); 
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	if(P.nbOccupe == 1)
	{
		glBegin(GL_POINTS);

		glVertex2f(P.p[0].coords[0], f.maxY - P.p[0].coords[1]);

		glEnd();
	}
	else 
	{
		glBegin(GL_LINES);
		for(i = 0; i < P.nbOccupe - 1; i++)
		{
			glVertex2f(P.p[i].coords[0], f.maxY - P.p[i].coords[1]);
			glVertex2f(P.p[i+1].coords[0], f.maxY - P.p[i+1].coords[1]);
		}

		glEnd();
	}

	glFlush();
}


void coordonnesPoint(const int button, const int state, const int x, const int y)
{

	switch (button)
	{
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_UP)
			{
				vertex v;
				v.coords[0] = x;
				v.coords[1] = y;
				if( (x > P.p[0].coords[0] + 5 || x < P.p[0].coords[0] - 5) && (y > P.p[0].coords[1] + 5 || y < P.p[0].coords[1] - 5) )
				{
					ajoutePoint(&P,v);
					displayPoint();
					printf("%d %d\n",x,y );
					ecrireFichier(out , &P);
				}
			}
		break;
	}

	glutDisplayFunc(displayPoint);
}
