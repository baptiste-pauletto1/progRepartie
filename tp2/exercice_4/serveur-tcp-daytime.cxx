#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define NUM_PORT 50013
#define BACKLOG 50
#define NB_CLIENTS 100
#define TAILLE_BUFFER 50

using namespace std;

void exitErreur(const char * msg) {
	perror(msg);
	exit( EXIT_FAILURE);

}

int main() {

	//Déclaration générales 
	
	int port;

	struct sockaddr_in sockaddr_serveur;

	sockaddr_serveur.sin_family = AF_INET;
	sockaddr_serveur.sin_port = htons(NUM_PORT);
	sockaddr_serveur.sin_addr.s_addr = htonl(INADDR_ANY);	
	//inet_aton("10.203.9.143",&sockaddr_serveur_tcp.sin_addr);

	// Partie dédiée aux clients UDP
	int sock_serveur_udp = socket(AF_INET, SOCK_DGRAM, 0);

	if (bind(sock_serveur_udp, (struct sockaddr *) &sockaddr_serveur,sizeof(sockaddr_in)) == -1)
		exitErreur("bind");

	// Partie dédiée aux clients TCP
	int sock_serveur_tcp = socket(AF_INET, SOCK_STREAM, 0);

	if (bind(sock_serveur_tcp, (struct sockaddr *) &sockaddr_serveur,sizeof(sockaddr_in)) == -1)
		exitErreur("bind");

	if (listen(sock_serveur_tcp, BACKLOG) == -1)
		exitErreur("listen");

	sockaddr_in sockaddr_client;
	socklen_t size = sizeof(sockaddr_client);	

	char buf[TAILLE_BUFFER];
	
	char * msg;
	time_t date;

	cout << "Serveur DayTime lancé  sur le port " << NUM_PORT << endl;

	fd_set readfds, writefds, exceptfds;
	
	int max;

	for (int i = 1; i <= NB_CLIENTS; i++) {

		//mettre à jour les listes

		FD_ZERO(&readfds);
		FD_SET(sock_serveur_udp, &readfds);
		FD_SET(sock_serveur_tcp, &readfds);
		FD_ZERO(&writefds);
		FD_ZERO(&exceptfds);

		if(sock_serveur_udp > sock_serveur_tcp)
			max = sock_serveur_udp;
		else
			max = sock_serveur_tcp;
		
		//Scruter pour les deux sockets (TCP & UDP)
		select(max + 1,&readfds,NULL,NULL,NULL);
		
		if (FD_ISSET(sock_serveur_udp,&readfds)) {
			//On a un message pour la socket UDP, on sort alors du select()
			cout<<" Salut, client UDP ! "<<endl;
			recvfrom(sock_serveur_udp,buf,sizeof(buf), 0, (struct sockaddr *) &sockaddr_client, &size);
			
			date = time(NULL); msg = ctime(&date);
			sendto(sock_serveur_udp, msg, strlen(msg), 0, (struct sockaddr *) &sockaddr_client, size);
			size = sizeof(sockaddr_client);
		}
		else if (FD_ISSET(sock_serveur_tcp,&readfds)) {
			//On a une demande d'un client TCP, on sort alors du select()
			cout<<" Salut, cient TCP ! "<<endl;
			int sock_client = accept(sock_serveur_tcp, NULL, NULL);

			if (sock_client == -1)
				exitErreur("accept");

		date = time(NULL); msg = ctime(&date);

		if (write(sock_client, msg, strlen(msg)) == -1)
			exitErreur("write");

		close(sock_client);
		}
	}
	close(sock_serveur_tcp);
	close(sock_serveur_udp);
	return 0;
}
