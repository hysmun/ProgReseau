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
	AfficheLog("Ouverture reussie recherche");
	fseek(fp, 0, SEEK_SET);
	
	ret = fread(UnRecord, sizeof(Seance), 1, fp);
	for(i=0; ret != 0; i++)
	{
		if(UnRecord->Reference == Reference)
		{
			fclose(fp);
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
	
	FILE *fp = fopen(NomFichier, "r+b");
	
	if(fp == NULL)
	{
		AfficheLog("Erreur ouverture fichier Reservation");
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
		fp = fopen(NomFichier, "w+b");
	}
	Facture UneFacture;
	UneFacture.NumeroFacturation = ftell(fp) / sizeof(Facture) + 1;
	sprintf(UneFacture.NomClient, "%s", NomClient);
	UneFacture.DateFacturation = Date;
	UneFacture.Places = Quantite;
	UneFacture.Reference = Reference;
	
	fwrite(&UneFacture, sizeof(Facture), 1, fp);
	
	fclose(fp);
	return UneFacture.NumeroFacturation;
}

void PAchat(char* FichSean,char* FichFact)
{
	char NomClient[20];
	char RefBuf[20];
	char NbPlaces[20];
	int Ref = 0;
	int NbPla = 0;
	
	fflush(stdin);
	printf("Nom Client : ");
	fgets(NomClient,sizeof(NomClient),stdin);
	fflush(stdin);
	printf("Reference : ");
	fgets(RefBuf,sizeof(RefBuf),stdin);
	Ref = atoi(RefBuf);
	fflush(stdin);
	printf("Nombre places : ");
	fgets(NbPlaces,sizeof(NbPlaces),stdin);
	NbPla = atoi(NbPlaces);
	if(Reservation(FichSean,Ref,NbPla) < 1)
	{
		fprintf(stderr,"Erreur de reservation\n");
		return;
	}
	if(Facturation(FichFact,NomClient,0,NbPla,Ref) == -1)
	{
		fprintf(stderr,"Erreur de facturation\n");
		return;
	}
	
}

int VerifAchat(char * NomFichier, char *nomClient, int Date)
{
	//recherche d'un reccord dans le fichier 
	if(NomFichier == NULL )
	{
		AfficheLog("Erreur param Recherche()");
		return -1;
	}
	int i, ret;
	Facture fac;
	FILE *fp = fopen(NomFichier, "rb");
	
	if(fp == NULL)
	{
		AfficheLog("Erreur ouverture fichier verifAchat");
		return -1;
	}
	AfficheLog("Ouverture reussie verifAchat");
	fseek(fp, 0, SEEK_SET);
	
	ret = fread(&fac, sizeof(Facture), 1, fp);
	for(i=0; ret != 0; i++)
	{
		if(strcmp(fac.NomClient,nomClient) == 0 && fac.DateFacturation == Date)
		{
			fclose(fp);
			AfficheLog("trouver");
			return fac.NumeroFacturation;
		}	
		ret = fread(&fac, sizeof(Facture), 1, fp);			
	}
	AfficheLog("Reccord non trouver");
	fclose(fp);
	return -1;
}
























