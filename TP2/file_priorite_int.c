/*! \file file_priorite_int.c
* \author A Chemier, R Lhomme
* \date 2014
*/


#include "file_priorite_int.h"
#include "base.h"

#include <assert.h>

void initialiserFileDefautInt(file *f)
{ 
	ALLOUER(f->file,2);
	f->nbElem = 0;
	f->nbMax = 2;
}

void initialiserFileInt(file *f, const unsigned int taille)
{
	ALLOUER(f->file,taille);
	f->nbElem = 0;
	f->nbMax = taille;
}

void freeFileInt(file *f)
{
	free(f->file);
	f->nbElem = 0;
	f->nbMax = 0;
}

void insererFileInt(file *f, const int n)
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
		echangeCase(f, i, i/2);
		i /= 2;
	}
}

void afficherFileInt(file *f)
{
	unsigned int i;

	for(i = 1; i < f->nbElem + 1; i++)
		printf("%d ", f->file[i]);
	
	printf("\n");
}

int recupereElement(file *f)
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
				echangeCase(f, i, 2*i);
			else echangeCase(f, i, 2*i+1);
			
		}

		else if(fg > f->file[i])
			echangeCase(f, i, 2*i);

		else if(fd > f->file[i])
			echangeCase(f, i, 2*i+1);

		else break;

		i *= 2;
	}

	return retour;
}

void echangeCase(file *f, const unsigned int i, const unsigned int j)
{
	int tamp;
	assert(i <= f->nbElem);
	assert(j <= f->nbElem);
	tamp = f->file[i];
	f->file[i] = f->file[j];
	f->file[j] = tamp;
}
