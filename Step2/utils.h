#ifndef __UTILS_H__
#define __UTILS_H__
#include "structure.h"
#include "data.h"

void DelNewLine(char *Chaine);

char ReadChar();

void MonPrintf(char* tempo, int espace,int taille );

void SaiSieRecord(struct Seance *UnRecord );

void CreationAjoutFichier(char *NomFichier,struct Seance  *UnRecord );

void AfficheRecord(struct Seance  *UnRecord);

void AfficheFacture(struct Facture *UneFacture);

void Listing(char *NomFichier);

void ListingFacture(char *NomFichier);


#endif
