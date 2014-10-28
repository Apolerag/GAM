#include "enveloppe.h"
#include "fenetre.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void initialiseEnveloppe(enveloppe *e)
{
	e->premier = NULL;
	e->dernier = NULL;
}

void ajouteElement(enveloppe *e, vertex *v)
{
	if(e->premier == NULL)
	{
		e->premier = e->dernier = v;
	}
	else
	{
		v->precedent = e->dernier;
		e->dernier->suivant = v;
		v->suivant = e->premier;
		e->dernier = v;
		e->premier->precedent = v;
	}
}

void enleveElement(enveloppe *e)
{
	e->dernier = e->dernier->precedent;
	e->dernier->suivant = e->premier;
	e->premier->precedent = e->dernier; 
}

void enveloppeConvexeBrut(vertex *v, enveloppe *e, const int nb)
{
	/* calcul le temps d'execution*/
	double temps;
    clock_t t1, t2;
    initialiseEnveloppe(e);

	assert(v != NULL);
	assert(nb > 0);

	int min = minLexicographique(v, nb);
	int i, j, k;
	int surEnveloppe;

	/*calcul de l'enveloppe convexe*/
	t1 = clock();
	i = min;

	do
	{
		surEnveloppe = 0;
		j = 0;
		ajouteElement(e,&v[i]);
		while( j < nb && !surEnveloppe)
		{
			printf("%d\n", j);
			if(i != j)
			{
				
				k = 0;
				while(k < nb && orientationPolaire(&v[i],&v[j],&v[k]) == GAUCHE)
				{
					k++;
					while(k == j || k== i)
					{
						k++;
					}
					
				}
				if(k == nb)
				{
					i = j; //j devient la valeur suivante
					surEnveloppe = 1;
				}
			}
			j++;
		}
	} while (i != min);	
	t2 = clock();
    temps = (double)(t2-t1)/CLOCKS_PER_SEC;
    printf("durée : %lf\n", temps);

    effaceFenetre();
	displayEnveloppe(e);
	displayPoints(v, nb);

	glFlush();
}

