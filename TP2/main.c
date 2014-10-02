/*! \file main.c
* \author A Chemier, R Lhomme
* \date 2014
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>  
#include <math.h>  

#include "base.h"
#include "fichier.h"
#include "file_priorite_int.h"
#include "polygone.h"
#include "fenetre.h"


/*! variable externe permettant de lire les parametres sur le ligne de commande.*/
extern char *optarg;

/*! bascule pour autoriser ou interdire (0) les messages d'erreurs envoyes par getopt. */
extern int opterr;

int main(int argc, char **argv)  
{  
	int c;
	int option1 = 0, option2 = 0, option3 = 0;
	char *input = NULL, *output = NULL;
	
	opterr = 0;
	while ((c = getopt(argc, argv, "1i:2o:3")) != EOF)
	{
		switch (c)
		{
			case '1': 
				option1 = 1;
				break;
			case '2': 
				option2 = 1;
				break;
			case '3': 
				option3 = 1;
				break;
			case 'o':
				output = optarg;
				break;
			case 'i':
				input = optarg;
				break;
			case 'h': 
			case '?': 
				printf("-1 partie 1 du tp\n");
				printf("-2 partie 2 du tp\n");
				printf("-3 partie 3 du tp\n");
				printf("-ichaine ouvre le fichier \"chaine\" en lecture \n");
				printf("-ochaine ouvre le fichier \"chaine\" en écriture \n");
				return EXIT_SUCCESS;  
				break;
			default : printf("Shouldn't be here, really...\n");
				break;
		}
	}

	printf("option1 : %d\n", option1);
	printf("option2 : %d\n", option2);
	printf("option3 : %d\n", option3);
	printf("input %s\n", input);
	printf("output %s\n", output);

	glutInit(&argc, argv);  
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);  
	glutInitWindowPosition(5,5);  
	glutInitWindowSize(500,500);

	glutCreateWindow("fenetre"); 
	definitionFenetre(0, 500, 0, 500, 10);
	winInit();
	glutDisplayFunc(display);

	if(option1 && output != NULL)
	{
		glutMouseFunc(coordonnesPoint);
		ecrireFichier(output, &P);
	}

	if(option2 && input != NULL)
	{
		printf("option2\n");
		ecrireFichier(input, &P);
		glutDisplayFunc(displayPolygone);
	}
	glutMainLoop(); 



	clearFenetre();
	return EXIT_SUCCESS;  
}  	