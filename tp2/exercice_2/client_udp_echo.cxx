#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define TAILLE_BUFFER 50

using namespace std;

void exitErreur(const char * msg) {
	perror(msg);
	exit( EXIT_FAILURE);

}

int main(int argc, char * argv[]) {

	int nbOctetsRecus;

	int port;

	port = atoi(argv[2]);

	char buf[TAILLE_BUFFER];

	int sock_client = socket(AF_INET, SOCK_DGRAM, 0);

	struct sockaddr_in sockaddr_serveur;

	socklen_t size = sizeof(struct sockaddr_in);

	sockaddr_serveur.sin_family = AF_INET;
	sockaddr_serveur.sin_port = htons(port);
	inet_aton(argv[1],&sockaddr_serveur.sin_addr);

	string message;
	getline(cin,message);

	if (sendto(sock_client, message.c_str(), message.size(), 0, (struct sockaddr *) &sockaddr_serveur, sizeof(sockaddr_serveur)) == -1)
		exitErreur("sendto");

	nbOctetsRecus = recvfrom(sock_client, buf, sizeof(buf), 0, (struct sockaddr *) &sockaddr_serveur, &size);
		
	if(nbOctetsRecus == -1)
		exitErreur("recvfrom");
		
	string messageRecu(buf,nbOctetsRecus);				
	cout << messageRecu << endl;
	close(sock_client);
	return EXIT_SUCCESS;
}

