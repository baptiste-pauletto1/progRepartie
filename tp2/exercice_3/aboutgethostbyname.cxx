#include <arpa/inet.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>


#define TAILLE_BUFFER 50

using namespace std;

void exitErreur(const char * msg) {
	perror(msg);
	exit( EXIT_FAILURE);

}

void testgethostbyname(const char * name){

struct  hostent  * h= gethostbyname(name);

if(h == NULL) {cout << "Erreur gethostbyname " << endl; 
exit(EXIT_FAILURE);}

cout << "Première adresse IP de ce nom de machine : " << endl;

cout << inet_ntoa(*(struct in_addr *)(h->h_addr)) <<endl ;

char ** p;

cout << "Liste de toutes les adresses IP de ce nom de machine : " << endl;

for(p = h->h_addr_list; *p != NULL ; p++) {
cout << inet_ntoa(*(struct in_addr *) (*p)) << endl;
}

cout << "Liste de tous les alias de ce nom de machine : " << endl;

for(p = h->h_aliases; *p != NULL ; p++) {
cout << *p << endl;
}
}

int getadresseIP(const char * name, struct in_addr * adr){

struct  hostent  * h= gethostbyname(name);

if(h == NULL) return 0 ;

* adr = *(struct in_addr *)(h->h_addr) ;
return 1;

}


int main(int argc, char * argv[]){
		

testgethostbyname("www.yahoo.com");


struct in_addr  adrip;
getadresseIP("www.yahoo.com", &adrip);
cout << inet_ntoa(adrip) <<endl ;

return EXIT_SUCCESS;
 
}
