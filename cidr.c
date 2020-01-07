#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main(int argc,char *argv[]) {
 unsigned int cidr;
 unsigned int net;
 unsigned int mask;
 if(argc < 2) {
  printf("usage: cidr address/cidr\n");
  printf("example: cidr 192.168.0.1/24\n");
  return 1;
 }
 if(!strchr(argv[1],'/')) cidr=32;
 else {
  cidr=atoi(strchr(argv[1],'/')+1);
  *strchr(argv[1],'/')=0;
 }
 net=htonl(inet_addr(argv[1]));
 printf("%d.%d.%d.%d ",net>>24&255,net>>16&255,net>>8&255,net&255);
 mask=~0;
 mask>>=(32-cidr);
 mask<<=(32-cidr);
 printf("%d.%d.%d.%d\n",mask>>24&255,mask>>16&255,mask>>8&255,mask&255);
 return 0;
}
