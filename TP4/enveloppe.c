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

void permuteElement(vertex *v1, vertex *v2)
{
	vertex *p1 = v1->precedent, *s1 = v1->suivant;
	vertex *p2 = v2->precedent, *s2 = v2->suivant;

	v1->precedent = p2;
	v2->precedent = p1;
	v1->suivant = s2;
	v2->suivant = s1;
}

// coupe la liste en 2 listes en prenant un terme sur deux
vertex* separer(vertex *liste)
{
	vertex * m = NULL;
	
	if (liste == NULL || liste->suivant == NULL)
		return NULL;
	else
	{
		m = liste->suivant;
		liste->suivant = m->suivant;
		m->suivant=separer(m->suivant);
		return m;
	}
}

vertex* fusion(vertex *lg,vertex *ld, const vertex *origin)
{
	if (lg == NULL)
	{
		return ld;
	}
	if (ld == NULL)
	{
		return lg;
	}
	if(orientationPolaire(origin, lg,ld) == DROITE)
	{
		ld->suivant = fusion(lg,ld->suivant,origin);
		return ld;
	}
	else
	{
		lg->suivant = fusion(lg->suivant,ld,origin);
		return lg;
	}
}

vertex* trier(vertex* l, const vertex *origin)
{
	vertex * m;

	if (l != NULL && l->suivant != NULL) 
	{
		m = separer(l);
		l = trier(l,origin);
		m = trier(m,origin);
		l = fusion(l,m,origin);
	}
	return l;
}

void afficherListe(vertex *v)
{
	vertex *j = v;
	while (j != NULL)
	{
		printf("%lf, %lf \n",j->coords[0], j->coords[1]);
		j = j->suivant;
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
    effaceFenetre();

	/*glBegin(GL_LINE_LOOP);
	glColor3f(1.0, 1.0, 1.0);
	precedent = liste;
	courant = precedent->suivant;
	suivant = courant->suivant;


	glVertex2f(v[min].coords[0],f.maxY - v[min].coords[1]);
	i=0;
	while (suivant != NULL)
	{
		printf("%d\n", orientationPolaire(precedent,courant,suivant));
		precedent = courant;
		courant = suivant;
		suivant = suivant->suivant;
	}
	glEnd();*/

	precedent = liste;
	courant = precedent->suivant;
	suivant = courant->suivant;
	ajouteElement(e,precedent);
	ajouteElement(e,courant);
	courant = suivant;
	suivant = suivant->suivant;
	while (suivant != NULL)
	{
		if(e->dernier == e->premier)
		{
			ajouteElement(e,courant);
			courant = suivant;
			suivant = courant->suivant;

		}
		else if(e->premier->suivant == e->dernier)
		{
			ajouteElement(e,courant);
			courant = suivant;
			suivant = courant->suivant;

		}
		else if(orientationPolaire(e->dernier->precedent,e->dernier,courant) == GAUCHE)
		{
			ajouteElement(e,courant);
			courant = suivant;
			suivant = courant->suivant;

		}
		else 
		{
			enleveDernierElement(e);
		}
	}

	t2 = clock();
    temps = (double)(t2-t1)/CLOCKS_PER_SEC;
    printf("durée graham : %lf\n", temps);

	displayEnveloppe(e);
	displayPoints(v, nb);
	glFlush();
//	printf("fin graham\n");
}
