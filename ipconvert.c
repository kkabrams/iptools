#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc,char *argv[]) {
 struct in6_addr in6_addr;
 char in6s[40];// 8 sections, 4 bytes each, 7 1byte separators, 1 null byte. = 40
 unsigned int addr;
 if(strchr(argv[1],':')) {
  inet_pton(AF_INET6,argv[1],&in6_addr);
  inet_ntop(AF_INET6,&in6_addr,in6s,sizeof(in6s));
  printf("normalized: %s\n",in6s);
 } else {
  inet_pton(AF_INET,argv[1],&addr);
  printf("hex: %x\n",htonl(addr));
  printf("dec: %u\n",htonl(addr));
  printf("dotted-quad: %u.%u.%u.%u\n",addr&255,addr>>8&255,addr>>16&255,addr>>24&255);
 }
 return 0;
}
