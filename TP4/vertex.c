#include "vertex.h"
#include <stdlib.h>
#include <stdio.h>

double determinant(const double a, const double b, const double c,
				const double d, const double e, const double f,
				const double g, const double h, const double i)
{
	return (a*e*i + d*h*c + g*b*f) - (g*e*c + a*h*f + d*b*i);
}

Orientation orientationPolaire(const vertex *A, const vertex *B, const vertex *C)
{
	double det = determinant(1,1,1,
						   A->coords[0],B->coords[0],C->coords[0],
						   A->coords[1],B->coords[1],C->coords[1]);
	if(det < 0) return DROITE;
	else if(det > 0) return GAUCHE;
	else return ALIGNES;
}

int comparePolaire(const vertex *A, const vertex *B, const vertex *C, const vertex *D)
{
	double det1 = determinant(1,1,1,
						   A->coords[0],B->coords[0],C->coords[0],
						   A->coords[1],B->coords[1],C->coords[1]);
	double det2 = determinant(1,1,1,
						   A->coords[0],B->coords[0],D->coords[0],
						   A->coords[1],B->coords[1],D->coords[1]);
	printf("det1 = %lf\n", det1);
	printf("det2 = %lf\n", det2);
	return 0;
}

int memeVertex(const vertex *A, const vertex *B)
{
	int i = 0;
	while(i < DIM)
	{
		if(A->coords[i] != B->coords[i])
			return 0;
		i++;
	}
	return 1;
}

vertex minimum(const vertex *A, const vertex *B)
{
	int i = 0;
	while(i < DIM)
	{
		if(A->coords[i] <= B->coords[i])
			return *A;
		i++;
	}
	return *B;
}

int minLexicographique(const vertex *v, const int taille)
{
	vertex minL = v[0], n;
	int indice = 0 ;
	
	int i ;
	for(i = 1; i < taille; i++) 
	{
		n = minimum(&v[i], &minL);
		if( memeVertex( &n, &minL) )
		{
			minL = v[i]; 
			indice = i ;
		}
	}
	return indice ;
}

/*! Calcul la position des vertices par rapport au triangle
* 
*/
Position positionPointTriangle(const vertex *A, const vertex *B, 
										const vertex *C, const vertex *N)
{
	Position position;
	Orientation O1 = orientationPolaire(A,B,N) ;
	Orientation O2 = orientationPolaire(B,C,N) ;
	Orientation O3 = orientationPolaire(C,A,N) ;
	if(O1 == DROITE || O2 == DROITE || O3 == DROITE)
		position = DEHORS; 
	else if(O1 == ALIGNES || O2 == ALIGNES  || O3 == ALIGNES )
		position = DESSUS; 
	else position = DEDANS; 
	
	return position;
}