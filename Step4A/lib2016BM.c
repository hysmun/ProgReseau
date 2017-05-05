#include "lib2016BM.h"

void APropos(char *Version,char *Nom1,char* Nom2)
{
 printf("Version : %s \n",Version ) ;
 printf("Nom1 : %s \n",Nom1 ) ;
 printf("Nom2 : %s \n",Nom2 ) ;
}

void AfficheLog(char *Message)
{
	fprintf(stderr,"%s\n",Message);
	return;
}

int Recherche(char* NomFichier, int Reference, Seance *UnRecord)
{
	//recherche d'un reccord dans le fichier 
	if(NomFichier == NULL || Reference < 1)
	{
		AfficheLog("Erreur param Recherche()");
		return -1;
	}
	int i, ret;
	FILE *fp = fopen(NomFichier, "rb");
	
	if(fp == NULL)
	{
		AfficheLog("Erreur ouverture fichier");
		UnRecord = NULL;
		return -1;
	}
	AfficheLog("Ouverture reussie");
	fseek(fp, 0, SEEK_SET);
	
	ret = fread(UnRecord, sizeof(Seance), 1, fp);
	for(i=0; ret != 0; i++)
	{
		if(UnRecord->Reference == Reference)
		{
			AfficheLog("trouver");
			return 1;
		}	
		ret = fread(UnRecord, sizeof(Seance), 1, fp);			
	}
	AfficheLog("Reccord non trouver");
	UnRecord = NULL;
	fclose(fp);
	return -1;
}





























