/*---------------------------------------------------------------
   Vanstapel Herman
   ex02\cli.c

 Le client dit bonjour en utilisant un structure  et
 le serveur fait de même
------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <time.h>
#include <limits.h>
#include "../udplib/udplib.h"
#include "structure.h"
#include "utils.h"

int interrupted = FALSE;

void handlerSIGALRM(int sig);

void die(char *s)
{
    perror(s);
    exit(1);
}

int main(int argc, char *argv[])
{
	int rc ;
	int Desc ;
	int tm ;
	int choix = '0';
	int i=0, y, num;
	int resend = TRUE;
	interrupted = FALSE;
	
	char ctmp[255];
	u_long  IpSocket , IpServer;
	u_short PortSocket, PortServer ; 

	struct sockaddr_in sthis ; /* this ce programme */
	struct sockaddr_in sos ; /* s = serveur */
	struct sockaddr_in sor ; /* r = remote */
	struct Requete UneRequete ;
	
	srand((unsigned)time(NULL));
	
	
	sigset_t mask, unmask;
	sigfillset(&mask);
	sigprocmask(SIG_SETMASK, &mask, &unmask);
	
	struct sigaction sigAct;

	sigAct.sa_handler = handlerSIGALRM;
	sigAct.sa_flags = 0;
	sigemptyset(&sigAct.sa_mask);
	sigaction(SIGALRM,&sigAct,NULL); 

	memset(&sthis,0,sizeof(struct sockaddr_in)) ;
	memset(&sos,0,sizeof(struct sockaddr_in)) ; 
	memset(&sor,0,sizeof(struct sockaddr_in)) ; 

	if (argc!=5)

	{
		printf("cli client portc serveur ports\n") ;
		exit(1) ;
	}

	/* Récupération IP & port   */
	IpSocket= inet_addr(argv[1]);
	PortSocket = atoi(argv[2]);

	IpServer = inet_addr(argv[3]) ;
	PortServer = atoi(argv[4]);

	// Desc = CreateSockets(&psoo,&psos,,atoi(argv[2]),argv[3],atoi(argv[4])) ;
	Desc=creer_socket(SOCK_DGRAM,&IpSocket,PortSocket,&sthis);

	if ( Desc == -1 )
		die("CreateSockets:") ; 
	else
		fprintf(stderr,"CreateSockets %d\n",Desc) ;

	sos.sin_family = AF_INET ;
	sos.sin_addr.s_addr= IpServer ;
	sos.sin_port = htons(PortServer) ;
	/* Début partie modifée */

	while(choix != 'q')
	{
		printf("----------------------    \n") ;
		printf("1) Demander une reference\n");
		printf("2) Acheter une reference\n");
		printf("6) A propos           \n") ;
		printf("7) Exit               \n") ; 
		printf("----------------------\n") ;
		choix=ReadChar();
		switch(choix)
		{
			case '1':
				UneRequete.Type = Question;
				printf("Saisie numero de seance : ");
				fgets(ctmp,sizeof ctmp,stdin );
				choix = atoi(ctmp);
				UneRequete.Reference = choix;
				break;
			case '2':
				UneRequete.Type = Achat;
				printf("Nom Client : ");
				fgets(UneRequete.NomClient,sizeof(UneRequete.NomClient),stdin);
				printf("Reference : ");
				fgets(ctmp,sizeof(ctmp),stdin);
				UneRequete.Reference = atoi(ctmp);
				printf("Places : ");
				fgets(ctmp,sizeof(ctmp),stdin);
				UneRequete.Places = atoi(ctmp);
				printf("Date : ");
				fgets(ctmp,sizeof(ctmp),stdin);
				UneRequete.Date = atoi(ctmp);
				num = (rand()%(100000000-1))+1;
				UneRequete.Numero = num;
				break;
			case '6':
				break;
			case '7':
				choix = 'q';
				break;
		}
		
		/* Fin partie modifée*/
		if(choix != 'q')
		{
			sigprocmask(SIG_SETMASK, &unmask, NULL);
			for(resend = TRUE;resend == TRUE;)
			{
				printf("Send");
				rc = SendDatagram(Desc,&UneRequete,sizeof(struct Requete) ,&sos ) ;
				i++;
				alarm(8);
				if ( rc == -1 )
					printf("SendDatagram") ;
				else
					fprintf(stderr,"Envoi de %d bytes\n",rc ) ;

				
				tm = sizeof(struct Requete) ;
				
				for(y=0; y!= i; y++)
				{
					printf("Receive");
					rc = ReceiveDatagram( Desc, &UneRequete,tm, &sor );
					if(interrupted == TRUE)
					{
						interrupted = FALSE;
						break;
					}
					sigprocmask(SIG_SETMASK, &mask, NULL);
					//memset(&UneRequete,0,sizeof(struct Requete)) ;
					alarm(0);
					resend = FALSE;
					if ( rc == -1 )
						printf("ReceiveDatagram") ;
					else
					{
						fprintf(stderr,"%d : bytes recus:%d\n",y,rc) ;
						switch((int)UneRequete.Type)
						{
							case Question:
								fprintf(stderr,"Film:%s\t\tRealisateur:%s\t\tPlaces:%d\n",UneRequete.Film,UneRequete.Realisateur,UneRequete.Places);
								break;
							case Achat:
								if(num == UneRequete.Numero && y != 0)
								{
									printf("Double\n");
								}
								else
								{
									printf("Achat reussi Facture: %d\n", UneRequete.NumeroFacture);
								}
								break;
							case Fail:
								printf("\n\n ERROR fail serv\n\n");
								break;
							default:
								printf("Erreur\n");
								break;
						}//fin switch type
					}//fin else rc
				}// for  receive
			}//for resend
		}//if choix == 'q'
		UneRequete.Type = Fail;
	}

	close(Desc) ;
	return 1;
}

void handlerSIGALRM(int sig)
{
	printf("interrupted system call \n");
	interrupted = TRUE;
}




































