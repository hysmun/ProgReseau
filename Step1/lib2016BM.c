#include "lib2016BM.h"

void APropos(char *Version,char *Nom1,char* Nom2)
{
 printf("Version : %s \n",Version ) ;
 printf("Nom1 : %s \n",Nom1 ) ;
 printf("Nom2 : %s \n",Nom2 ) ;
}



int Recherche(char* NomFichier, int Reference, Seance *UnRecord)
{
	//recherche d'un reccord dans le fichier 
	int i, ret;
	FILE *fp = fopen(NomFichier, "rb");
	
	if(fp == null)
	{
		printf("Erreur ouverture fichier");
		UnRecord = null;
		return -1;
	}
	printf("Ouverture reussie");
	fseek(fp, 0, SEEK_SET);
	
	ret = fread(UnRecord, sizeof(Seance), 1, fp);
	for(i=0; ret != 0; i++)
	{
		if(UnRecord->Reference == Reference)
		{
			printf("trouver");
			return 1;
		}				
	}
	
}





























