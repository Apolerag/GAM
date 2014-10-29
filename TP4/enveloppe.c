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
		e->premier->precedent = v;

		e->dernier = v;
	}
}

void enleveDernierElement(enveloppe *e)
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

 	/*demarrage du chrono*/
	t1 = clock();
	i = min;
	
	/*calcul de l'enveloppe convexe*/
	do
	{
		ajouteElement(e,&v[i]);

		surEnveloppe = 0;
		j = 0;
		while( j < nb && !surEnveloppe)
		{
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
	/* fon du chrono */
	t2 = clock();
    temps = (double)(t2-t1)/CLOCKS_PER_SEC;
    printf("durée : %lf\n", temps);

    effaceFenetre();
	printf("displayPoints\n");
	displayPoints(v, nb);
    printf("displayEnveloppe\n");
	displayEnveloppe(e);

	glFlush();
}

void jarvis(vertex *v, enveloppe *e, const int nb)
{
	double temps;
    clock_t t1, t2;

    initialiseEnveloppe(e);
	assert(v != NULL);
	assert(nb > 0);

	int min = minLexicographique(v, nb);
	int courant, suivant;
	
	int i;

 	/*demarrage du chrono*/
	t1 = clock();
	/*ajouteElement(e,&v[min]);*/

	courant = min;
	/*ALLOUER(precedent,1);
	//l
	precedent->coords[0] = courant->coords[0] + 10;
	precedent->coords[1] = courant->coords[1];*/


	do
	{
		ajouteElement(e,&v[courant]);
		
		suivant = (courant + 1)%nb;
		for (i = 0; i < nb; ++i)
		{
			if(i != courant && i != suivant)
			{
				if(orientationPolaire(&v[courant], &v[suivant], &v[i]) == DROITE)
				{
					suivant = i;
				}
			}
			
		}
		courant = suivant;
	} while (courant != min);	


	t2 = clock();
    temps = (double)(t2-t1)/CLOCKS_PER_SEC;
    printf("durée : %lf\n", temps);

    effaceFenetre();
	printf("displayPoints\n");
	displayPoints(v, nb);
    printf("displayEnveloppe\n");
	displayEnveloppe(e);

	glFlush();
}
