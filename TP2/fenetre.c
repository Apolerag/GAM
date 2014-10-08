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
	int i;

	printf("displayPolygone\n");
	glColor3f(0.0, 0.0, 0.0); 
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	glBegin(GL_LINE_LOOP);

	for(i = 0; i < P.nbOccupe ; i++)
	{
		glVertex2f(P.p[i].coords[0], f.maxY - P.p[i].coords[1]);
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
				if( (x > P.p[0].coords[0] + 5 || x < P.p[0].coords[0] - 5) || (y > P.p[0].coords[1] + 5 || y < P.p[0].coords[1] - 5) )
				{
					ajoutePoint(&P,v);
					displayPoint();
					printf("%d %d\n",x,y );
					ecrireFichier(out , &P);
				}
				else
				{
					displayPolygone();
				}
			}
		break;
	}

	glutDisplayFunc(displayPoint);
}


int controlePolygoneSimple()
{
	int i = 1, j;
	int intersectionI = 0;
	int intersectionJ = 0;
	int min = minLexicographique(P.p, P.nbOccupe);
	vertex *n1 = NULL,*n2 = NULL;
	vertex A,B;
	vertex C,D;
	Orientation o;

	/* contrôle du nombre de sommet distinct */
	if(P.nbOccupe <= 2)
		return 0;

	n1 = &P.p[0];

	while (memeVertex(n1,&P.p[i]))
	{
		if(i == P.nbOccupe)
			return 0;
		i++;
	}
	n2 = &P.p[i];

	while (memeVertex(n1, &P.p[i]) || memeVertex(n2,&P.p[i]))
	{
		if(i == P.nbOccupe)
			return 0;
		i++;
	}

	/* controle si au moins un des points n'est pas aligné*/
	o = orientationPolaire(&P.p[0], &P.p[1], &P.p[2]);
	while( (o == ALIGNES) && (i < P.nbOccupe) )
	{
		o = orientationPolaire(&P.p[0], &P.p[1], &P.p[i]);
		i++;
	}

	if(i == P.nbOccupe)
		return 0;

	glColor3f(0.0, 0.0, 0.0); 
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	glBegin(GL_LINES);

	i = min;
	do
	{
		A = P.p[i];
		B = P.p[(i+1)%P.nbOccupe];
		j = min;
		do
		{
			if(i != j)
			{
				C = P.p[j];
				D = P.p[(j+1)%P.nbOccupe];
				if(!(memeVertex(&A,&C) || memeVertex(&A,&D) 
					|| memeVertex(&B, &C) || memeVertex(&B,&D) ) )
				{
					Orientation ABC = orientationPolaire(&A,&B,&C);
					Orientation ABD = orientationPolaire(&A,&B,&D);
					if(ABC != ABD && ABC != ALIGNES && ABD != ALIGNES)
					{
						Orientation CDA = orientationPolaire(&C,&D,&A);
						Orientation CDB = orientationPolaire(&C,&D,&B);
						if(CDA != CDB)
						{
							intersectionI = 1;
							intersectionJ = 1;
						}
					}
				}

			}	
			if (intersectionJ)
			{
				glColor3f(1.0, 0.0, 0.0);
				glVertex2f(C.coords[0], f.maxY - C.coords[1]);
				glVertex2f(D.coords[0], f.maxY - D.coords[1]);
			}
			intersectionJ = 0;

			j++;
			j %= P.nbOccupe;
		}
		while(j != min);


		if (intersectionI)
		{
			glColor3f(1.0, 0.0, 0.0);
		}
		else glColor3f(1.0, 1.0, 1.0);
		
		glVertex2f(A.coords[0], f.maxY - A.coords[1]);
		glVertex2f(B.coords[0], f.maxY - B.coords[1]);

		intersectionI = 0;
		i++;
		i %= P.nbOccupe;
	}
	while(i != min);

	glEnd();

	glFlush();

	return 1;
}
