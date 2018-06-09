#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>

typedef struct Node node;
struct Node{
	char str[1024];	
	node *father;
	node *left;
	node *right;
};

class dosthfile{
	private:
		char *filename;
		node *root;
	public:
		
		int fd;
		int count=0;
		int length=0;
		dosthfile(char *filename){
			this->filename=filename;
			if(fd=open(this->filename,0)==-1){
				perror("failed to open file");
				this->fd=creat(filename,777);
			}
			close(fd);
			fileread();
			//memset(root->str,0,1024);
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
		
		void fileread(){
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
			memset(data,0,1024);
			while(read(fd,buf,1)!= -1 && buf[0]!=0 && (buf[0]>31 && buf[0]<127) || buf[0]==10){
//				printf("buf[0]=%d\n",buf[0]);
				if(buf[0]==10){
					count++;
					if(count>64){
						break;
					}
				}
				if(buf[0] !=';'&& buf[0]!='\n'&& buf[0]!=10 ){
					data[i++]=buf[0];
				//	printf("i= %d \t buf[0]=%c\n",i,buf[0]);
				}else if(buf[0]!=10){
			//		printf("data= %s\n",data);
//					printf("strlen=%d\n",strlen(data));
					if(strlen(data)>0){
						insert(this->root,data);
					}
					memset(data,0,1024);
					i=0;
					continue;
				}
			}
			close(fd);
		}
		
		void insert(node *root,char *data){
			node *ptr;
			ptr=root;
	
			if(length==0){
//				printf("insert into root %s \n\n",data);
				ptr=(node *)malloc(sizeof( struct Node));
				memcpy(ptr->str,data,strlen(data));
				ptr->father=NULL;
				this->length+=1;
				ptr->right=NULL;
				ptr->left=NULL;
				this->root=ptr;
				
			
			}else if(this->length>0 && strlen(data)<= strlen(root->str) && root->left!=0){
				
//				printf("into recursive left\n");

				insert(root->left,data);
				
			}else if(this->length >0 && strlen(data) <= strlen(root->str) && root->left==0){
//				printf("insert into left %s \n\n",data);
				//printf("into  left\n");
				node *n;
				n=(node *)malloc(sizeof( struct Node));
				memcpy(n->str,data,strlen(data));
				ptr->left=n;
				n->father=ptr;
				this->length+=1;
			}else  if(this->length >0 && strlen(data) > strlen(root->str) && root->right!=0){
				
//				printf("into recursive right\n");
				insert(ptr->right,data);

			}else if(this->length >0 && strlen(data) > strlen(root->str) && root->right==0){
//				printf("insert into right %s \n\n",data);
				node *n;
				n=(node *)malloc(sizeof( struct Node));
				memcpy(n->str,data,strlen(data));
				ptr->right=n;
				n->father=ptr;
				this->length+=1;
			}
			
		}

		node *PALL( node *father,node *root,char d){
			
			node *ptr;
			ptr=root;	
			if( root->left != NULL){	
				PALL(root,root->left,'L');			
			}
			if(ptr->right!= NULL){	
				PALL(root,root->right,'R');
			}	
			if(ptr->left==NULL && ptr->right==NULL && this->length >0){
				this->length-=1;

				printf("release= %s\n",ptr->str);
				
				free(ptr);
				if(this->length!=0){
					if(d=='L' && father!=NULL){
						father->left=NULL;
						if(father->right!=NULL){
							PALL(father,father->right,'R');		
						}else{
							PALL(father->father,father,'L');
						}
					}
					if(d=='R' && father !=NULL){
						father->right=NULL;
						father->left=NULL;
						PALL(father->father,father,'M');
					}
					if(d=='M' && father != NULL && length!=1){
						father->left=NULL;
						PALL(father->father,father,'M');
					}else{
						father->left=NULL;
						father->right=NULL;
						PALL(father->father,father,'M');
	
					}	
				}
			}
			
			return NULL;
		}
		
		void inorder(node *father, node *root, char f){
		//	printf();
			if(this->length ==0){
				exit(1);
			}

			if(root->left != NULL){
				//printf("into left \n");
				inorder(root,root->left,'L');
			}
		
			if(root->left==NULL && root->right==NULL){
				if(root->str!=NULL){
					printf("#release=%s\n",root->str);
				}
				node *ptr=root;

				if(father!=0 && f=='R'){
					father->right=NULL;
				}else if(father !=0 && f=='L'){
					father->left=NULL;
				}else if(f=='O'){
			//		printf("######\n");
					//free(root->father);
					//root->father=0;
					root->right=0;
					root->left=0;
					root->father->right=0;
					root->father=0;
			//		printf("-----FATHER_STr= %d\n",root->right);
					//root->father->left=0;
					//root->father=0;
				}

				this->length--;
				free(ptr);
			}
			
			if(father!=0 && father->right != NULL){
				printf("&release=%s\n",father->str);
				memset(father->str,0,strlen(father->str));
				if(father->left==0 && father->right->left==0 && father->right->right==0){
			//		printf("orphan\n");
					node *orphan=father->right;
					father=0;
					free(father);	
					inorder(NULL,orphan,'O');
				//	inorder(father->father,father->father->right,'R');				
				
				}else{
			//		printf("father =%s root=%s \n",father->str,root->str);
			//:wq		free(father);	
					inorder(father,father->right,'R');
				}
			}
								
		}
		void pre_order(){	
	//		PALL(NULL,this->root,'M');		
			inorder(NULL,this->root,'M');	
		}	
};


int main(void){
	dosthfile f("test.txt");
//	f.fileread();
	/*
	char *str="bbbb::100ee;\n";
	printf("%d",f.filewrite(str,strlen(str),O_RDWR|O_APPEND));	
	printf("length=%d\n",f.length);
	printf("%d",f.filewrite(str,strlen(str),O_RDWR|O_APPEND));	
	printf("length=%d\n",f.length);
	printf("%d",f.filewrite(str,strlen(str),O_RDWR|O_APPEND));	
	printf("length=%d\n",f.length);
	*/
//	f.fileread();
	
	f.pre_order();
	
	//dosthfile f2("test2.txt");
	//f2.pre_order();
	
	
	return 0;
}
