#include "enveloppe.h"
#include "fenetre.h"
#include "FilePrioriteVertex.h"
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

void permuteElement(vertex *v1, vertex *v2)
{
	vertex *p1 = v1->precedent, *s1 = v1->suivant;
	vertex *p2 = v2->precedent, *s2 = v2->suivant;

	v1->precedent = p2;
	v2->precedent = p1;
	v1->suivant = s2;
	v2->suivant = s1;
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
	int i = min, j, k;
	int surEnveloppe;

 	/*demarrage du chrono*/
	t1 = clock();
	
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

	/*calcul du temps d'execution*/
	t2 = clock();
    temps = (double)(t2-t1)/CLOCKS_PER_SEC;
    printf("durée brute : %lf\n", temps);

    /*affichage de l'enveloppe*/
    effaceFenetre();
	displayEnveloppe(e);
	displayPoints(v, nb);
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
	int courant = min, suivant, i;

 	/*demarrage du chrono*/
	t1 = clock();
	do
	{
		ajouteElement(e,&v[courant]);
		suivant = (courant + 1)%nb;
		for (i = 0; i < nb; ++i)
		{
			if(i != courant && i != suivant)
			{
				if(orientationPolaire(&v[courant], &v[suivant], &v[i]) == DROITE)
					suivant = i;	
			}
		}
		courant = suivant;
	} while (courant != min);	

	/*calcul du temps d'execution*/
	t2 = clock();
    temps = (double)(t2-t1)/CLOCKS_PER_SEC;
    printf("durée jarvis : %lf\n", temps);

    /*affichage de l'enveloppe*/
    effaceFenetre();
	displayEnveloppe(e);
	displayPoints(v, nb);
	glFlush();
}

void graham(vertex *v, enveloppe *e, const int nb)
{
	double temps;
    clock_t t1, t2;
    initialiseEnveloppe(e);

    int i;
	vertex *liste = NULL;
	vertex *courant = NULL, *suivant = NULL, *precedent = NULL;

    /*demarrage du chrono*/
	t1 = clock();
	int min = minLexicographique(v, nb);
	ajouteElement(e, &v[min]);

	/* creation de la liste de vertices*/
	for (i = 0; i < nb; ++i)
	{
		if(i != min) 
		{
  			v[i].suivant = liste;
  			liste = &v[i]; 
		}
	}
	
	//printf("tri fusion\n");
	liste = trier(liste, &v[min]);

	precedent = liste;
	courant = precedent->suivant;
	suivant = courant->suivant;
	ajouteElement(e,precedent);
	while (courant != NULL)
	{
		while((e->premier != e->dernier) && (orientationPolaire(e->dernier->precedent,e->dernier,courant) == DROITE))
		{
        	enleveDernierElement(e);
		}

		suivant = courant->suivant;
		ajouteElement(e,courant);
		courant = suivant;
	}

	t2 = clock();
    temps = (double)(t2-t1)/CLOCKS_PER_SEC;
    printf("durée graham : %lf\n", temps);

    effaceFenetre();
    printf("displayEnveloppe\n");
	displayEnveloppe(e);
	printf("displayPoints\n");
	displayPoints(v, nb);
	glFlush();
}

void insertionLexicographique(vertex *v, enveloppe *e, const int nb)
{
	double temps;
    clock_t t1, t2;
    initialiseEnveloppe(e);
     /*demarrage du chrono*/
	t1 = clock();
	int min = minLexicographique(v, nb);
	
	int i;
	File_Priorite *file;
	file = creerFile(nb);
	for ( i = 0; i < nb; ++i)
	{
		insererVertexFile(file, &v[i]);
	}
	afficherFile(file);

	for (i = 0; i < 3; ++i)
	{
		vertex t = extremierFile(file);
		ajouteElement(e, &t);
	}

	t2 = clock();
    temps = (double)(t2-t1)/CLOCKS_PER_SEC;
    printf("durée insertionLexicographique : %lf\n", temps);

    effaceFenetre();
    printf("displayEnveloppe\n");
	displayEnveloppe(e);
	printf("displayPoints\n");
	displayPoints(v, nb);
	glFlush();
}
