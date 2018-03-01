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
	char const *init = "Bonjour !\n";
	write(sock_client,init,strlen(init));

	char buf [256];
	ssize_t nbOctetsLus = 0;
	string resultat;
	
	while(0<1){
		if (nbOctetsLus = read(sock_client,buf,sizeof(buf))){
			resultat = string(buf,nbOctetsLus); 
			cout << resultat << endl;
		}
		string message;
		getline(cin,message);
		if (-1 == write(sock_client,message.c_str(),sizeof(message))){ exitErreur("write"); }

	}

	close(sock_client);
	return 0;
}
