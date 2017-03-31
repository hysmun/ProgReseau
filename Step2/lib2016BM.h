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


#endif
