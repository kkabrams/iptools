#include <stdio.h>
#include <arpa/inet.h>

int main(int argc,char *argv[]) {
 int addr=inet_addr(argv[1]);
 printf("hex: %x\n",htonl(addr));
 printf("dec: %u\n",htonl(addr));
 printf("dotted-quad: %u.%u.%u.%u\n",addr&255,addr>>8&255,addr>>16&255,addr>>24&255);
 return 0;
}
