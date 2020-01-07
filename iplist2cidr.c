#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>

struct net {
 unsigned int ip;
 unsigned char cidr;
};

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

int main(int argc,char *argv[]) {
 short in;
 int maxcidr;
 int i=0,j=0,len=0;
 struct net list[65536];//don't do more than a /16!
 char ips[64];//why not?
 char *cidrs;
 while((in=fgetc(stdin)) != -1) {
  if(in=='\n') {
   ips[i]=0;
   if((cidrs=strchr(ips,'/')) != 0) {
    *cidrs=0;
    cidrs++;
   }
   list[len].ip=htonl(inet_addr(ips));
   list[len].cidr=cidrs?atoi(cidrs):32;
   i=0;
   cidrs=0;
   len++;
   continue;
  }
  ips[i]=in;
  i++;
  if(i>63) {
   printf("your have a line that is TOOO long. stick to IPv4.\n");
   return 0;
  }
 }
 //!!!warning!!! inefficient algo ahead!
 for(i=0;i<len;i++) {
  for(j=0;j<len;j++) {
   if(list[i].cidr == list[j].cidr) {
    if((list[i].ip ^ list[j].ip) >> (32-list[i].cidr) == 1) {
     list[i].cidr--;
     list[j].cidr--;
     list[i].ip &= (0xffffffff << (32-list[i].cidr));
     list[j].ip &= (0xffffffff << (32-list[j].cidr));
     i=-1;//start over!
     j=-1;//start over!
     continue;
    }
   }
   if(list[i].ip == list[j].ip && list[i].cidr != list[j].cidr) {
    list[i].cidr = min(list[i].cidr,list[j].cidr);
    list[j].cidr = min(list[i].cidr,list[j].cidr);
    i=-1;//start over!
    j=-1;//start over!
    continue;
   }
   maxcidr=min(list[i].cidr,list[j].cidr);
   if(list[i].cidr != list[j].cidr) {
    if(list[i].ip >> (32-maxcidr) == list[j].ip >> (32-maxcidr) ) {
     list[i].cidr = min(list[i].cidr,list[j].cidr);
     list[j].cidr = min(list[i].cidr,list[j].cidr);
     list[i].ip &= (0xffffffff << (32-list[i].cidr));
     list[j].ip &= (0xffffffff << (32-list[j].cidr));
     i=-1;//start over!
     j=-1;//start over!
     continue;
    }
   }
  }
 }
 for(i=0;i<len;i++) {
  printf("%d.%d.%d.%d/%d\n",list[i].ip>>24&255,list[i].ip>>16&255,list[i].ip>>8&255,list[i].ip&255,list[i].cidr);
 }
 return 0;
}
