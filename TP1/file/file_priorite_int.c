#include "file_priorite_int.h"
#include "base.h"

#include <assert.h>

void initialiser_file_defaut_int(file *f)
{ 
	ALLOUER(f->file,2);
	f->nbElem = 0;
	f->nbMax = 2;
}

void initialiser_file_int(file *f, const unsigned int taille)
{
	ALLOUER(f->file,taille);
	f->nbElem = 0;
	f->nbMax = taille;
}

void free_file_int(file *f)
{
	free(f->file);
	f->nbElem = 0;
	f->nbMax = 0;
}

void inserer_file_int(file *f, const int n)
{
	unsigned int i;
	int * tampon;
	if( (f->nbElem + 1) == f->nbMax)
	{
		tampon = f->file;
		f->nbMax *= 2;	
		ALLOUER(f->file,f->nbMax );
		for(i = 0; i < f->nbMax; i++)
		{
			f->file[i] = tampon[i];
		}
		free(tampon);	
	}

	f->file[f->nbElem+1] = n;
	f->nbElem ++;

	i = f->nbElem;
	while(f->file[i] > f->file[i/2] && i > 1)
	{	
		echange_case(f, i, i/2);
		i /= 2;
	}
}

void afficher_file_int(file *f)
{
	unsigned int i;

	for(i = 1; i < f->nbElem + 1; i++)
		printf("%d ", f->file[i]);
	
	printf("\n");
}

int recupere_element(file *f)
{
	int retour = f->file[1];
	unsigned int i;
	int fg,fd;
	f->file[1] = f->file[f->nbElem];
	f->nbElem --;

	i = 1;

	while(f->nbElem > 2*i)
	{
		fg = f->file[2*i];
		fd = f->file[2*i+1];

		if( (fg > f->file[i]) && (fd > f->file[i]) )
		{
			if(fg > fd)
				echange_case(f, i, 2*i);
			else echange_case(f, i, 2*i+1);
			
		}

		else if(fg > f->file[i])
			echange_case(f, i, 2*i);

		else if(fd > f->file[i])
			echange_case(f, i, 2*i+1);

		else break;

		i *= 2;
	}

	return retour;
}

void echange_case(file *f, const unsigned int i, const unsigned int j)
{
	int tamp;
	assert(i <= f->nbElem);
	assert(j <= f->nbElem);
	tamp = f->file[i];
	f->file[i] = f->file[j];
	f->file[j] = tamp;
}
