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

void ajouteFin(enveloppe *e, vertex *v)
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
	e->nb++;
}

void ajouteDebut(enveloppe *e, vertex *v)
{
	if(e->nb == 0)
	{
		v->precedent = v->suivant = NULL;
		e->premier = e->dernier = v;
	}
	else
	{
		e->premier->precedent = v;

		v->suivant = e->premier;
		v->precedent = NULL;
		e->premier = v;
	}
	e->nb++;
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
		ajouteFin(e,&v[i]);

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
		ajouteFin(e,&v[courant]);
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
	ajouteFin(e, &v[min]);

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
	ajouteFin(e,precedent);
	while (courant != NULL)
	{
		while((e->premier != e->dernier) && (orientationPolaire(e->dernier->precedent,e->dernier,courant) == DROITE))
		{
        	enleveDernierElement(e);
		}

		suivant = courant->suivant;
		ajouteFin(e,courant);
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
    vertex *t;
    vertex **bas, **haut;
    ALLOUER(bas,nb);
    ALLOUER(haut,nb);

     /*demarrage du chrono*/
	t1 = clock();

	int i,h,b;
	File_Priorite *file;
	file = creerFile(nb);
	for ( i = 0; i < nb; ++i)
	{
		insererVertexFile(file, &v[i]);
	}
	//afficherFile(file);
	printf("creation triangle de base\n");
	
	t = extremierFile(file);
	afficherVertex(t);
	bas[0] = t;
	haut[0] = t;
	//ajouteFin(&haute,t);
	//ajouteFin(e,t);

	t = extremierFile(file);
	afficherVertex(t);
	bas[1] = t;
	haut[1] = t;;
	//ajouteFin(e,t);
	h = b = 1;
	printf("insertion des points\n");
	while(file->nbElementsCourant > 0)
	{
		b++;h++;
		t = extremierFile(file);
		//afficherVertex(t);
		bas[b] = t;
		haut[h] = t;
		/* enveloppe basse*/
		while(b > 1 && 
		 	orientationPolaire(bas[b],bas[b-2],bas[b-1])
			== GAUCHE)
			{ 
				bas[b-1] = bas[b];
				b--;
			} 
		
		/* enveloppe haute*/
			while(h > 1 && 
		 	orientationPolaire(haut[h],haut[h-2],haut[h-1])
			== DROITE)
			{ 
				haut[h-1] = haut[h];
				h--;
			} 
	}
	printf("b %d, h %d\n",b,h );
	for (i = 0; i < b; ++i)
	{
		ajouteFin(e,bas[i]);
	}
	for (i = h; i > 0; --i)
	{
		ajouteFin(e,haut[i]);
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

	free(haut);
	free(bas);
}
