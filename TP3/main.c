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


/*! variable externe permettant de lire les parametres sur le ligne de commande.*/
extern char *optarg;

/*! bascule pour autoriser ou interdire (0) les messages d'erreurs envoyes par getopt. */
extern int opterr;

int main(int argc, char **argv)  
{  

	int c;
	int nbPoints = 50;
	vertex *v;
	
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
	glutInitWindowSize(500,500);

	glutCreateWindow("fenêtre"); 
	definitionFenetre(0, 500, 0, 500, 10);
	winInit();

	ALLOUER(v,nbPoints);

	selectPoints (v, nbPoints);
 
	enveloppeConvexeBrut(v, nbPoints);

	glutMainLoop(); 
	free(v);
	clearFenetre();
	return EXIT_SUCCESS;  
}  	
