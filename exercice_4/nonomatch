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

using namespace std;

void exitErreur(const char * msg) {
	perror(msg);
	exit( EXIT_FAILURE);

}

int main() {

	int sock_serveur = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in sockaddr_serveur;

	sockaddr_serveur.sin_family = AF_INET;
	sockaddr_serveur.sin_port = htons(NUM_PORT);
	inet_aton("10.203.9.209",&sockaddr_serveur.sin_addr);

	int yes = 1;
	if (setsockopt(sock_serveur, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int))
			== -1)
		exitErreur("setsockopt");

	if (bind(sock_serveur, (struct sockaddr *) &sockaddr_serveur,
			sizeof(sockaddr_in)) == -1)
		exitErreur("bind");

	if (listen(sock_serveur, BACKLOG) == -1)
		exitErreur("listen");

	cout << "Serveur de chat lancé sur le port " << NUM_PORT << endl;

	int sock_client;

	sock_client = accept(sock_serveur, NULL, NULL);
	if (sock_client == -1)
		exitErreur("accept");

	ssize_t nbOctetsLus = 0;
	char buf [1];
	string resultat = "";

	while (nbOctetsLus = read(sock_client,buf,sizeof(buf)) > 0) {
		resultat += string(buf,nbOctetsLus);
		if(string(buf,nbOctetsLus) == "\n"){
			if(resultat == "bye\r\n") break;
			cout<<resultat;
			resultat ="";
			string msg;
			getline(cin,msg);
			if (msg == "bye") return 0;
			msg += "\n";
			const char * stringMessage = msg.c_str();
			if (write(sock_client,stringMessage,strlen(stringMessage)) == -1) exitErreur("write");
		}
	}
	close(sock_serveur);
	close(sock_client);
	return 0;
}
