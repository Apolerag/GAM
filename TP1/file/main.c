#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>

#include "FilePrioriteVertex.h"

extern char *optarg;
extern int opterr;

int main(int argc, char **argv)
{
	int i, c, nb_pts_file;
	opterr = 0;
	while ((c = getopt(argc, argv, "n:")) != EOF)
	{
		switch (c)
		{
			case 'n': 
				sscanf(optarg, "%d", &nb_pts_file);
				break;
			default : 
				printf("Usage : -nX où X > 0. \n");
				return 1;
				break;
		}
	}

	Vertex vertices[nb_pts_file];
	File_Priorite * file;
	file = creerFile(nb_pts_file);
	Vertex v;

	srand(time(NULL));

	for(i = 0; i < nb_pts_file; i++) {
		vertices[i].coords[0] = rand()%400;
		vertices[i].coords[1] = rand()%400;

		insererVertexFile(file, &vertices[i]);
	}
	printf("Affichage de la file \n");
	afficherFile(file);
	for(i = 0; i < nb_pts_file; i++) {
		v = extremierFile(file);
		printf("Extraction du maximum \n");
		afficherVertex(&v);
	}

	freeFile(file);
	return 0;
}
