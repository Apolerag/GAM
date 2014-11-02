#include "enveloppe.h"
#include "fenetre.h"
#include "FilePrioriteVertex.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void initialiseEnveloppe(enveloppe *e)
{
	e->premier = NULL;
	e->dernier = NULL;
	e->nb = 0;
}

void ajouteElement(enveloppe *e, vertex *v)
{
	if(e->nb == 0)
	{
		v->precedent = v->suivant = NULL;
		e->premier = e->dernier = v;
	}
	else
	{
		e->dernier->suivant = v;

		v->suivant = NULL;
		v->precedent = e->dernier;
		e->dernier = v;
	}
	e->nb ++;
}

void enlevePremierElement(enveloppe *e)
{	
	if(e->nb == 1 || e->nb == 0)
	{
		e->premier = e->dernier = NULL;
		e->nb = 0;
	}
	else
	{
		vertex *t = e->premier->suivant;
		t->precedent = NULL;
		e->premier->suivant = NULL;
		e->premier = t;

		e->nb --;
	}
}

void enleveDernierElement(enveloppe *e)
{
	if(e->nb == 1 || e->nb == 0)
	{
		e->premier = e->dernier = NULL;
		e->nb = 0;
	}
	else
	{
		vertex *t = e->dernier->precedent;
		t->suivant = NULL;
		e->dernier->precedent = NULL;
		e->dernier = t;

		e->nb --;
	}
}

void permuteElement(enveloppe *e, vertex *v1, vertex *v2)
{
	if(e->nb == 2)
	{
		vertex *t = e->premier;
		e->premier = e->dernier;
		e->dernier = t;

		e->premier->suivant = e->dernier;
		e->dernier->precedent = e->premier;

		e->premier->precedent = e->dernier->suivant = NULL;
	}
	else
	{
		vertex *p1 = v1->precedent, *s1 = v1->suivant;
		vertex *p2 = v2->precedent, *s2 = v2->suivant;

		v1->precedent = p2;
		v2->precedent = p1;
		v1->suivant = s2;
		v2->suivant = s1;

		if(p1 != NULL) p1->suivant = v2;
		if(p2 != NULL) p2->suivant = v1;
		if(s1 != NULL) s1->precedent = v2;
		if(s2 != NULL) s2->precedent = p2;
	}
	
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
    vertex *t, *courant;
     /*demarrage du chrono*/
	t1 = clock();

	int i;
	File_Priorite *file;
	file = creerFile(nb);
	for ( i = 0; i < nb; ++i)
	{
		insererVertexFile(file, &v[i]);
	}
	//afficherFile(file);
	printf("creation triangle de base\n");
	for (i = 0; i < 3; ++i)
	{
		t = extremierFile(file);
		afficherVertex(t);
		ajouteElement(e, t);
	}

	if(orientationPolaire(e->premier, e->premier->suivant,e->dernier) == DROITE)
		permuteElement(e, e->premier, e->dernier);

	printf("insertion des points\n");
	while(file->nbElementsCourant > 0)
	{
		t = extremierFile(file);
		afficherVertex(t);

		if(t->coords[1] > e->dernier->coords[1])
		{
			printf("pijhgf\n");
			while((e->nb > 2) && 
				orientationPolaire(e->premier->suivant, e->premier, t) 
			== GAUCHE)
			{
				printf("enleve premier sup\n");
				enlevePremierElement(e);
			}
			printf("caca\n");
			while((e->nb > 2) &&  orientationPolaire(e->dernier->precedent, e->dernier, t ) 
				== DROITE )
			{
				printf("e->dernier\n");
				afficherVertex(e->dernier);
				printf("enleve dernier sup\n");
				enleveDernierElement(e);
				afficherVertex(e->dernier);

			}
			ajouteElement(e, t);
			printf("e->nb %d\n", e->nb);

		}
		else
		{
			printf("qsfg\n");
			while( (e->nb > 2)  && orientationPolaire(e->premier, e->dernier, t) 
				== GAUCHE)
			{
				printf("enleve dernier inf\n");
				enleveDernierElement(e);
			}
			printf("azert\n");
			while((e->nb > 2) && 
				orientationPolaire(e->dernier->precedent, e->dernier, t ) 
				== DROITE )
			{
				printf("enleve dernier inf\n");
				enleveDernierElement(e);
			}
			ajouteElement(e, t);

			permuteElement(e, e->dernier, e->dernier->precedent);
			printf("e->nb %d\n", e->nb);

		}	
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
