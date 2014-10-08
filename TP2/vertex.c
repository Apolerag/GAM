#include "vertex.h"

double determinant(const double a, const double b, const double c,
				const double d, const double e, const double f,
				const double g, const double h, const double i)
{
	return (a * e * i + d * h * c + g * b * f ) - ( g * e * c + a * h * f + d * b * i);
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
