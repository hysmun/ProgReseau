#ifndef __LIB2016BM_H__
#define __LIB2016BM_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "data.h"

void APropos(char *Version,char *Nom1,char* Nom2) ;
int Recherche(char *NomFichier,int Reference,Seance *UnRecord);
void AfficheLog(char *Message);
int Reservation(char* NomFichier,int Reference ,int Quantite );
int Facturation(char NomFichier[80], char NomClient[60], int Date,int Quantite,int Reference);
void PAchat(char* FichSean,char* FichFact);

#endif
