#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<netdb.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/ioctl.h>
#include<net/if.h>
#include<net/ethernet.h>
#include<ifaddrs.h>

class infoHost{
	private:
		int send;
		char src_mac[6];
		char srcIP[4];
		char srcIP6[16];

		void setHostmac(char **interface){
			struct ifreq ifr;
			memset(&ifr,0,sizeof(ifr));
			memcpy(ifr.ifr_name,*interface,strlen(*interface));	
			if(ioctl(this->send,SIOCGIFHWADDR ,&ifr)<0){
				perror("Failed to get scr_mac");
				exit(0);
			}
			memcpy(this->src_mac,ifr.ifr_hwaddr.sa_data,sizeof(ifr.ifr_hwaddr.sa_data));
		}	
		void setHostip( char *interface){
			struct 	ifaddrs *ifaddr,*ifaptr;
			getifaddrs(&ifaddr);
			ifaptr=ifaddr;
			while(ifaddr->ifa_next != NULL){
			
				if(ifaddr->ifa_addr->sa_family == AF_INET && strcmp(ifaddr->ifa_name,interface)==0){
				
					void *ptr;
					ptr=&((struct sockaddr_in *)ifaddr->ifa_addr)->sin_addr;
					memcpy(srcIP,ptr,4);
				
				}else if(ifaddr->ifa_addr->sa_family == AF_INET6 && strcmp(ifaddr->ifa_name,interface)==0){
				
					void *ptr;
					ptr=&((struct sockaddr_in6 *)ifaddr->ifa_addr)->sin6_addr;
					memcpy(srcIP6,(char* )ptr,16);
				
				}
				ifaddr=ifaddr->ifa_next;
			};
			freeifaddrs(ifaptr);
		}

	public : 
		infoHost(char *interface){
			if((send=socket(PF_PACKET,SOCK_RAW,htons(ETH_P_ALL)))<0){
				perror("Failed to open socket");
				exit(0);
			}
			memset(srcIP,0,4);
			memset(srcIP6,0,16);
			setHostmac(&interface);
			setHostip(interface);
		}
		~infoHost(){
			close(send);
		}
		infoHost(infoHost &host){
		
		}
		char *getMac(){
			return src_mac;
		}
		char *getIP(){
			return srcIP;
		}
		char *getIP6(){
			return srcIP6;
		}
	
};
