# lib
## socketlib
取得本機IPv4、IPv6、Mac 的資料，透過呼叫infoHost類別並輸入所要的介面，
就能使用以下Instance，以下都是回傳16進位char 陣列
````C++
infoHost host("wlan0");
char * getMac(); // print Mac address by hex char array back;
char * getIP(); // print IPv4 address by hex char array back;
char * getIP6(); // print IPv6 address by hex char array back;


