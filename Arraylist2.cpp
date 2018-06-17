#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
using namespace std;
class node{
	private:	
		char *data;

	public:
		node *next;

		node(char *str,int size){
	//		printf("struct\n");
			next=0;
			data=new char(size);
			memcpy(data,str,size);
		}
		
		node(const node &n){
	//		printf("copy structure!!\n");
			data=new char[strlen(n.data)];
			memcpy(data,n.data,strlen(n.data));
		}
		char *getData(){
			return this->data;
		}
		~node(){
	//		printf("destructure\n");
			delete [] data;
		}

};

class Arraylist{
	private:
		node *head;
		node *ptr;
	public:
		Arraylist(){
	//		printf("Arraylist struct\n");
			head==0;
		}
		int put(char *data){
			if(strlen(data)<=0){
				return 1;
			}
			if(head==0){
				head=new node(data,strlen(data));
				ptr=head;
			}else{
				node *newNode=new node(data,strlen(data));
				ptr->next=newNode;
				ptr=newNode;
			}
			return 0;
		}
		Arraylist(const Arraylist &arr){
	//		printf("Arraylist Copy struct\n");
		//	memcpy(data,arr.data,strlen(arr.data));
		}
		~Arraylist(){
	//		printf("Arraylist destruct\n");
		//	delete [] data;
		}
		char *pop(){
			node *n;
			if(head!=0){

				char *data=new char[strlen(head->getData())];
				strcpy(data,head->getData());
				//printf("!!!!  head-> data =%s data=%s \n", head->getData(),data);
				if((n=head->next)!=0){
					delete head;
					head=n;	
				}else{
					delete head;
					head=0;
				}
				return data;
			}else{
				return "false";
			}
		}
		

};
int main(void){

	Arraylist *arr=new Arraylist();
	arr->put("test1");
	arr->put("test2");

	printf("%s\n",arr->pop());

	printf("%s\n",arr->pop());
	printf("%s\n",arr->pop());
	delete arr;



	return 0;
}

