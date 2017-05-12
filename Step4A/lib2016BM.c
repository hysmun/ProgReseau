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
			return i;
		}	
		ret = fread(UnRecord, sizeof(Seance), 1, fp);			
	}
	AfficheLog("Reccord non trouver");
	UnRecord = NULL;
	fclose(fp);
	return -1;
}

int Reservation(char* NomFichier,int Reference ,int Quantite )
{
	if(NomFichier == NULL || Reference < 1)
	{
		AfficheLog("Erreur param Reservation()");
		return -1;
	}
	
	Seance tmp;
	int placefichier = Recherche(NomFichier, Reference, &tmp );
	
	FILE *fp = fopen(NomFichier, "rb");
	
	if(fp == NULL)
	{
		AfficheLog("Erreur ouverture fichier");
		return -1;
	}
	//AfficheLog("Ouverture reussie");
	fseek(fp, 0, SEEK_SET);
	
	if(tmp.Places < 0)
	{
		return -1;
	}
	if(tmp.Places < Quantite)
	{
		return 0;
	}
	else
	{
		tmp.Places = tmp.Places - Quantite;
		fseek(fp, placefichier * sizeof(Seance), SEEK_SET);
		fwrite(&tmp, sizeof(Seance), 1, fp );
	}
	
	fclose(fp);
	return Quantite;
}

int Facturation(char NomFichier[80], char NomClient[60], int Date,int Quantite,int Reference)
{
	FILE *fp = fopen(NomFichier, "ab");
	
	if(fp == NULL)
	{
		AfficheLog("Erreur ouverture fichier");
		return -1;
	}
	Facture UneFacture;
	UneFacture.NumeroFacturation = ftell(fp) / sizeof(Facture) + 1;
	sprintf(UneFacture.NomClient, "%s", NomClient);
	UneFacture.DateFacturation = Date;
	UneFacture.Places = Quantite;
	UneFacture.Reference = Reference;
	
	fwrite(&UneFacture, sizeof(Facture), 1, fp);
	
	fclose(fp);
	return 0;
}


























