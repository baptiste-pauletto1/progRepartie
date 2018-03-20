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
#define TAILLE_BUFFER 512

using namespace std;

void exitErreur(const char * msg) {
	perror(msg);
	exit( EXIT_FAILURE);

}

int main(int argc, char * argv[]) {
	int port;

	if (argc < 3){
		cout << "Usage : client adresse_IP_serveur port_serveur";
		exit(EXIT_FAILURE);
	}

	int sock_client = socket(AF_INET, SOCK_DGRAM, 0);

	struct sockaddr_in sockaddr_serveur;

	sockaddr_serveur.sin_family = AF_INET;
	sockaddr_serveur.sin_port = htons(atoi(argv[2]));
	inet_aton(argv[1], &sockaddr_serveur.sin_addr);
	
	socklen_t size = sizeof(struct sockaddr_in);



	char buf[TAILLE_BUFFER];
	
	// envoyer n'importe quoi au serveur
	// c'est juste pour lui donner l'adresse de client
	
	if (sendto(sock_client, buf, sizeof(buf), 0, (struct sockaddr *) &sockaddr_serveur, sizeof(sockaddr_serveur))== -1)
		exitErreur("sendto");


	// si le message est trop long, il sera tronqué
	int n = recvfrom(sock_client, buf, sizeof(buf), 0,
				(struct sockaddr *) &sockaddr_serveur, &size);
				
	if (n == -1)
		exitErreur("recvfrom");
				
	string date(buf,n);
	
	cout << date ;
	
	close(sock_client);
	return 0;
}
