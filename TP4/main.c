/*! \file main.c
* \author A Chemier, R Lhomme
* \date 2014
*/

/*
1 millions de points
algo "naïf": 10.886148 s
algo jarvis : 1.216959 s
algo grahon : 1.858054 s

10 millions de points
algo "naïf": 169.494484 s
algo jarvis : 13.946895 s

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
	//printf("\E[34;1mhel\E[mlo\n");
	int c;
	int nbPoints = 50;
	vertex *v = NULL;
	enveloppe e1,e2,e3,e4;
	initialiseEnveloppe(&e1);
	initialiseEnveloppe(&e2);
	initialiseEnveloppe(&e3);
	initialiseEnveloppe(&e4);
	
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

	//jarvis(v, &e1,nbPoints);
	//enveloppeConvexeBrut(v, &e2,nbPoints);
	//graham(v, &e3,nbPoints);
	insertionLexicographique( v, &e4, nbPoints);
	printf("fin\n");

	glutMainLoop(); 
	clearFenetre(v,nbPoints);
	return EXIT_SUCCESS;  


}  	
	
