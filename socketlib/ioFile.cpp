#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>

class IOfile{
	private:
	
	public: 
		IOfile(char *filename){
			ofstream ifile(filename,ios::in);
		}
}
