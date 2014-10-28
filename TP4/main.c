/*! \file main.c
* \author A Chemier, R Lhomme
* \date 2014
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>  
#include <math.h>  
#include <time.h>

#include "fenetre.h"
#include "enveloppe.h"


/*! variable externe permettant de lire les parametres sur le ligne de commande.*/
extern char *optarg;

/*! bascule pour autoriser ou interdire (0) les messages d'erreurs envoyes par getopt. */
extern int opterr;

int main(int argc, char **argv)  
{  
	int c;
	int nbPoints = 50;
	vertex *v = NULL;
	enveloppe e;
	initialiseEnveloppe(&e);
	
	opterr = 0;
	while ((c = getopt(argc, argv, "n:")) != EOF)
	{
		switch (c)
		{	
			case 'n': 
				if ((sscanf(optarg, "%d", &nbPoints) != 1) || nbPoints <= 0)
					nbPoints = 50;
				break;
			case 'h': 
			case '?': 
				return EXIT_SUCCESS;  
				break;
			default : printf("Shouldn't be here, really...\n");
				break;
		}
	}

	glutInit(&argc, argv);  
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);  
	glutInitWindowPosition(5,5);  
	glutInitWindowSize(700,700);

	glutCreateWindow("fenêtre"); 
	definitionFenetre(0, 700, 0, 700, 10);

	winInit();
	ALLOUER(v,nbPoints);
	selectPoints (v, nbPoints);
	enveloppeConvexeBrut(v, &e,nbPoints);


	glutMainLoop(); 
	clearFenetre(v,nbPoints);
	return EXIT_SUCCESS;  
	/*
	int i; vertex *v;
	vertex *j;
	ALLOUER(v,5);
	definitionFenetre(0, 700, 0, 700, 10);	
	selectPoints (v, 5);
	enveloppe *e = NULL;
	ALLOUER(e,1);
	initialiseEnveloppe(e);
	for ( i = 0; i < 5; ++i)
		ajouteElement(e,&v[i]);
	
	for ( i = 0; i < 5; ++i)
	{
	
		printf("vertex %f %f\n", v[i].coords[0],v[i].coords[1]);

	}
	j = e->premier;
	do
	{
		printf("vertex %f %f\n", j->coords[0],j->coords[1]);
		j = j->suivant;
	}
	while(j != e->premier);
	printf("\n");
	enleveElement(e);
	do
	{
		printf("vertex %f %f\n", j->coords[0],j->coords[1]);
		j = j->suivant;
	}
	while(j != e->premier);*/
}  	
	
