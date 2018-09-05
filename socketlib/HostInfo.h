#ifndef _HostInfo_H_
#define _HostInfo_H_

class infoHost{
	private:
		int send;
		char src_mac[6];
		char srcIP[4];
		char srcIP6[16];
		void setHostmac(char **interface);
		void setHostip( char *interface);
	public:
		infoHost(char *interface);
		~infoHost();
		infoHost(infoHost &host);
		char *getMac();
		char *getIP();
		char *getIP6();
};

#endif
