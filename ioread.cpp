#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
using namespace std;

class IOstream{
	private:
		char filename[50];
	public :
		IOstream(char *filename){
			int fd;
			if((fd=open(filename,O_RDONLY)==-1)){
				creat(filename,0751);
			}
			close(fd);
			strcpy(this->filename,filename);
			
		}
		void write(char *data){
			ofstream ofile(this->filename,ios::app);
			ofile<< data <<endl;	
			ofile.close();
		}
		void read(){
			char text[100];
			ifstream ifile(this->filename,ios::in);
			while(!ifile.eof()){
				ifile.getline(text,100,';');
				printf("%s\n",text);
			}
			ifile.close();
		}
};

int main(void){
	IOstream io("test.txt");
	io.write("test;");
	io.read();	
	return 0;
}
