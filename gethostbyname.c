#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>

#define SILLYLIMIT 256

int main(int argc,char *argv[]) {
 char buf[SILLYLIMIT];
 struct in_addr saddr;
 struct in6_addr saddr6;
 struct hostent *he;
 if(argc<2) return 1;
 if(!(he=gethostbyname2(
   argc<3
   ?inet_aton(argv[1],&saddr)
     ?inet_ntoa(saddr)
     :argv[1]
   :inet_pton(AF_INET6,argv[1],&saddr6)
     ?inet_ntop(AF_INET6,&saddr6,buf,SILLYLIMIT) //no point, but whatever
     :argv[1]
  ,argc<3?AF_INET:AF_INET6))) return 1;
 for(;*(he->h_addr_list);he->h_addr_list++) {
  printf("%s\n",inet_ntop(argc<3?AF_INET:AF_INET6,*(he->h_addr_list),buf,SILLYLIMIT));
 }
 return 0;
}
