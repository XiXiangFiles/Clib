#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>

typedef struct Node node;
struct Node{
	char mac_ip[135];	
	node *left;
	node *right;
};

class dosthfile{
	char *filename;
	node *root;
	public:
		
		int fd;
		int count=0;
		dosthfile(char *filename){
			this->filename=filename;
			if(fd=open(this->filename,0)==-1){
				perror("failed to open file");
				this->fd=creat(filename,777);
			}
			close(this->fd);
			root=NULL;
		}
		~dosthfile(){
			close(this->fd);
		}
		int filewrite(char *data,int strlen,int par){
			int w;	
			int fd;
			if(fd=open(this->filename,par)==-1){
				perror("failed to open file");
			}
			this->fd=fd;
			if((w=write(fd, data , strlen))==-1){
				perror("write failed!");
				return 0;
			}else{
				insert(this->root,data);
				count++;
				return 1;
			}
			close(fd);	
		}
		node *fileread(){
			char buf[2];
			char data[1024];
			int i=0;
			int count=0;
			if((fd=open(this->filename,O_RDONLY)==-1)){
				perror("instance fileread() failed to open");
			}
			off_t off;
			if(off==-1){
				perror("instance fileread() failed to lseek");
			}
			while(read(fd,buf,1)!= -1 ){
				if(buf[0]==10){
					count++;
					if(count>64){
						break;
					}
				}
				if(buf[0] !=';'&& buf[0]!='\n'&& buf[0]!=10 ){
					data[i++]=buf[0];
				}else if(buf[0]!=10){
					printf("data=%s\n",data);
					memset(data,0,1024);
					i=0;
					continue;
				}
			}
			return NULL;
		}
		void insert(node *root,char *data){
			node *ptr;
			ptr=root;
			if(root==NULL){
			
				root=(node *)malloc(sizeof( struct Node));
				memcpy(root->mac_ip,data,strlen(data));
			
			}else if(strlen(ptr->mac_ip)>strlen(data) && root->left == NULL){
				
				node *left=(node *)malloc(sizeof(struct Node));
				memcpy(left->mac_ip,data,strlen(data));
				ptr->left=left;

			}else if(strlen(ptr->mac_ip)<strlen(data) && root->right == NULL){
				
				node *right=(node *)malloc(sizeof(struct Node));
				memcpy(right->mac_ip,data,strlen(data));
				ptr->right=right;
			}else if(strlen(ptr->mac_ip)>strlen(data) && root->left != NULL){

				insert(ptr->left,data);

			}else if(strlen(ptr->mac_ip)<strlen(data) && root->right != NULL){
	
				insert(ptr->right,data);
			}
		}
		char *find(char *keywords){
			
			return NULL;
		}
};





int main(void){
	dosthfile f("test.txt");
	f.fileread();
	/*	
	printf("%d",f.filewrite(";\n",2,O_WRONLY|O_APPEND));	
	printf("%d",f.filewrite("t;\n",3,O_WRONLY|O_APPEND));	
	printf("%d",f.filewrite("te;\n",4,O_WRONLY|O_APPEND));	
	printf("%d",f.filewrite("tes;\n",5,O_WRONLY|O_APPEND));	
	printf("%d",f.filewrite("test;\n",6,O_WRONLY|O_APPEND));	
	printf("%d",f.filewrite("test3;\n",7,O_WRONLY|O_APPEND));	
	printf("%d",f.filewrite("test33;\n",8,O_WRONLY|O_APPEND));	
	printf("%d",f.filewrite("test333;\n",9,O_WRONLY|O_APPEND));	
	printf("%d",f.filewrite("test2222;\n",10,O_WRONLY|O_APPEND));	
	*/
	return 0;
}
