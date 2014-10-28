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

void winInit()
{
	gluOrtho2D(f.minX, f.maxX, f.minY, f.maxY);
}

double myRandom (double a, double b)
{
	double tmp = random(); /* long int in [0, RAND_MAX] */

	return a+tmp*((b-a)/RAND_MAX);
}

void selectPoints (vertex *v, const int nb)
{
	int n = nb;

	while (--n >= 0)
	{
		v[n].coords[0] = myRandom(f.minX + 10, f.maxX-10);
		v[n].coords[1] = myRandom(f.minY + 10, f.maxY-10);
	}
	
}

void displayPolygone()
{
	int i;

	glColor3f(0.0, 0.0, 0.0); 
	//glClear(GL_COLOR_BUFFER_BIT);
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
	int retour = 1;
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

	if (P.nbOccupe == 3)
	{
		displayPolygone();
	}

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
							retour = 0;
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

	return retour;
}

int estConvexe()
{
	int i = 2;
	int i1,i2,i3;
	int convexe = 1;
	int min = minLexicographique(P.p, P.nbOccupe);

	while(orientationPolaire(&P.p[min],&P.p[min+1],&P.p[min+i]) == ALIGNES)
		i++;


	//controle sens de rotation du polygone
	if(orientationPolaire(&P.p[min],&P.p[(min+1)%P.nbOccupe],&P.p[(min+i)%P.nbOccupe]) == DROITE)
	{
		//on inverse
		vertex *v = P.p;
		ALLOUER(P.p,P.nbOccupe);
		for(i = 0; i<P.nbOccupe; i++)
		{
			P.p[i] = v[P.nbOccupe - 1 - i];
		}
		free(v);
		P.nbVertex = P.nbOccupe;		
	}

	//controle polygone convexe
	glColor3f(0.0, 0.0, 0.0); 
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	glBegin(GL_LINES);
	i1 = min;
	i2 = (i1+1)%P.nbOccupe;
	i3 = (i2+1)%P.nbOccupe;

	do
	{
		if(orientationPolaire(&P.p[i1],&P.p[i2],&P.p[i3]) == DROITE)
		{
			convexe = 0;
			glColor3f(0.0, 1.0, 0.0);
		}
		else glColor3f(1.0, 1.0, 1.0);

		glVertex2f(P.p[i1].coords[0], f.maxY - P.p[i1].coords[1]);
		glVertex2f(P.p[i2].coords[0], f.maxY - P.p[i2].coords[1]);
		
		i1 = i2;
		i2 = i3;
		i3++;	
		i3 %= P.nbOccupe;
	}
	while(i1 != min);

	glEnd();

	glFlush();
	return convexe;
}

void positionPointsParRapportPolygone(const vertex *v, const int nb)
{
	vertex centre;
	int i,j, x = 0,y = 0;
	Position p;
	int min = minLexicographique(P.p, P.nbOccupe);

	/* calcul du barycentre*/
	for(i = 0; i < P.nbOccupe; i++)
	{
		x += P.p[i].coords[0];
		y += P.p[i].coords[1];
	}
	centre.coords[0] = x / P.nbOccupe;
	centre.coords[1] = y / P.nbOccupe;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBegin(GL_POINTS);
	for(i = 0; i < nb; i++)
	{
		j = min ;
		while( !(orientationPolaire(&centre, &P.p[j], &v[i]) == GAUCHE && 
			orientationPolaire(&centre, &P.p[(j+1)%P.nbOccupe], &v[i]) == DROITE) )
		{
			j++;
			j %= P.nbOccupe;
		}

		p = positionPointTriangle(&centre, &P.p[j],  &P.p[(j+1)%P.nbOccupe], &v[i]);

		if(p == DEDANS) glColor3f(0.0, 1.0, 0.0);
		else if(p == DESSUS) glColor3f(0.0, 0.0, 1.0);
		else glColor3f(1.0, 0.0, 0.0);
		glVertex2f(v[i].coords[0], f.maxY - v[i].coords[1]);
	}
	glEnd();

	displayPolygone();
	glFlush();
}
