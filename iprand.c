#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc,char *argv[]) {
 srandom(time(0)+getpid());
 unsigned int ip;
 unsigned int net=argc>1?htonl(inet_addr(argv[1])):0x0;
 unsigned int mask=argc>2?htonl(inet_addr(argv[2])):0x0;
 unsigned int a=argc>3?atoi(argv[3]):3;
 net &= mask;
 for(;a>0;a--) {
  ip=random();
  ip &= ~mask;
  ip |= net;
  printf("%d.%d.%d.%d\n",ip>>24&255,ip>>16&255,ip>>8&255,ip&255);
 }
 return 0;
}
