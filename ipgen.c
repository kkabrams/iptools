#include <stdio.h>
#include <arpa/inet.h>

void print_ip(unsigned int i) {
 printf("%d.%d.%d.%d\n",(i>>24)&255,(i>>16)&255,(i>>8)&255,i&255); 
}

int main(int argc,char *argv[]) {
 if(argc < 3) {
  printf("usage: ipgen net mask\n");
  printf("example: ipgen 192.168.0.1 255.255.0.255\n");
  return 1;
 }
 unsigned int net=htonl(inet_addr(argv[1])); 
 unsigned int mask=htonl(inet_addr(argv[2]));
 unsigned int i;
 unsigned int min;
 unsigned int max;
 unsigned int inc=1;
 if(!(~mask)) {//nothing to do. this is a /32
  print_ip(net);
  return 0;
 }
 for(i=0;(mask>>i&1);inc<<=1,i++);
 min=net&mask;
 max=((net&mask)|(~mask));
 if(argc > 3) {
  printf("net: ");
  print_ip(net);
  printf("mask: ");
  print_ip(mask);
  printf("min: ");
  print_ip(min);
  printf("max: ");
  print_ip(max);
  printf("inc: %d\n",inc);
 }
 for(i=min;i<=max;i+=inc) {
  if((i&mask) == (net&mask)) {
   print_ip(i);
  }
 }
 return 0;
}
