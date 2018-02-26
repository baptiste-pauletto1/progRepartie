#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


using namespace std;

void exitErreur(const char * msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}

int main(int argc, char const *argv[]){
	int sock_client = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in sockaddr_serveur;
	sockaddr_serveur.sin_family = AF_INET;
	sockaddr_serveur.sin_port = htons(atoi(argv[2]));

	inet_aton(argv[1],&sockaddr_serveur.sin_addr);
	
	if(connect(sock_client,(struct sockaddr *) &sockaddr_serveur,sizeof(struct sockaddr_in)) == -1){
		exitErreur("Connection failed");	
	}
	char const *requete = "GET /index.html\r\n";
	write(sock_client,requete,strlen(requete));

	char buf [1];
	ssize_t nbOctetsLus = 0;
	string resultat;
	while(nbOctetsLus = read(sock_client,buf,sizeof(buf)) > 0){	
		resultat += string(buf,nbOctetsLus);
	}
	cout << resultat <<endl;
	close(sock_client);
	return 0;
}
