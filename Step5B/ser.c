/*--------------------------------------
  Herman Vanstapel
  
  ex02\ser.c 
  
  Un serveur recevant une structure 
----------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <time.h>
#include <limits.h>

#include "../udplib/udplib.h"
#include "structure.h"
#include "data.h"
#include "utils.h"
#include "lib2016BM.h"

void die(char *s);
void handlerSIGSTOP(int sig);

int main(int argc,char *argv[])
{
	int rc ;
	int Desc ;
	int res;
	int send = 0;
	char ctmp[255];
	struct sockaddr_in sthis ; /* this ce programme */
	struct sockaddr_in sos ; /* s = serveur */
	struct sockaddr_in sor ; /* r = remote */

	u_long  IpSocket ;
	u_short PortSocket ;

	int tm ;
	struct Requete UneRequete ;
	struct Seance UneSeance;

	memset(&sthis,0,sizeof(struct sockaddr_in)) ;
	memset(&sos,0,sizeof(struct sockaddr_in)) ; 
	memset(&sor,0,sizeof(struct sockaddr_in)) ;
	
	
	struct sigaction sigAct;

	sigAct.sa_handler = handlerSIGSTOP;
	sigAct.sa_flags = SA_RESTART;
	sigemptyset(&sigAct.sa_mask);
	sigaction(SIGINT,&sigAct,NULL);  

	printf("Ceci est le serveur\n") ;
	if ( argc!=3)
	{
		printf("ser ser port cli\n") ;
		exit(1) ;
	}

	/* Récupération IP & port   */
	IpSocket= inet_addr(argv[1]);
	PortSocket = atoi(argv[2]);
	// Desc = CreateSockets(&psoo,&psos,,atoi(argv[2]),argv[3],atoi(argv[4])) ;
	Desc=creer_socket(SOCK_DGRAM,&IpSocket,PortSocket,&sthis);

	if ( Desc == -1 )
		die("CreateSockets:") ;
	else
		fprintf(stderr,"CreateSockets %d\n",Desc) ;
	while(1)
	{
		tm = sizeof(struct Requete) ;
		rc = ReceiveDatagram( Desc,&UneRequete ,tm, &sor ) ;
		if ( rc == -1 )
			printf("ReceiveDatagram") ;
		else
			fprintf(stderr,"bytes recus:%d Reference :%d\n",rc,UneRequete.Reference ) ;
		
		printf("Received packed from %s   --   %d\n",ipString(sor, ctmp), (int)UneRequete.Type);
		send = 0;
		switch((int)UneRequete.Type)
		{
			case Question:
				printf("Type recu %d\n", UneRequete.Type) ;
				res = Recherche("Seances",UneRequete.Reference,&UneSeance);
				if(res != -1)
					fprintf(stderr,"res:%d -- Reference:%s -- Realisateur:%s -- Quantite :%d\n",res,UneSeance.Film,UneSeance.Realisateur,UneSeance.Places);
				else
				{
					UneRequete.Type = Fail ;
					send = 1;
					break;
				}
				strcpy(UneRequete.Film,UneSeance.Film);
				strcpy(UneRequete.Realisateur,UneSeance.Realisateur);
				UneRequete.Places = UneSeance.Places;
				send = 1;
				break;
			case Achat:
				printf("Achat\n");
				int ret;
				if( (ret = VerifAchat("Factures", UneRequete.NomClient, UneRequete.Date)) > 0 )
				{
					//l'achat a deja ete fait
					printf("Doublon\n");
					UneRequete.NumeroFacture = ret;
					send = 1;
					break;
				}
				else
				{
					if(Reservation("Seances", UneRequete.Reference, UneRequete.Places) < 1)
					{
						printf("Erreur reservation !!!\n");
						break;
					}
					UneRequete.NumeroFacture = Facturation("Factures", UneRequete.NomClient, UneRequete.Date, UneRequete.Places, UneRequete.Reference);
					printf("Mise à jour réussi !");
				
					send = 1;
				}
				break;
			case Livraison:
				break;
			case Fail:
				UneRequete.Type = Fail ;
				printf("\n\n ERROR envois de FAIL \n\n");
				send = 1;
				break;
			default:
				UneRequete.Type = Fail;
				send = 1;
				break;
		}
		
		/* attention l'enum peut être codé en short */
		/* reponse avec psos */

		/* Début partie modifiée*/
		
		
		
		/* Fin partie modifiée*/
		if(send == 1)
		{
			rc = SendDatagram(Desc,&UneRequete,sizeof(struct Requete) ,&sor ) ;
			if ( rc == -1 )
				printf("SendDatagram:") ;
			else
				printf("bytes envoyes:%d   --  %d\n",rc, (int)UneRequete.Type ) ;
		}

	}

	close(Desc) ;
	return 1;
}

void die(char *s)
{
    perror(s);
    exit(1);
}

void handlerSIGSTOP(int sig)
{
	printf("interrupted from CTRL Z\n");
	waitTime(30, 0);
	printf("fin du sleep\n");
}





















