/*
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
|					       +
+	Author : Wang Wang		       |
|	Unit   : Nccu cs		       +
+					       |
|+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*/

#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
typedef struct array Array;
struct array{
	char *data;
	Array *next;
};


class  ArrayList{
	Array *ptr;//end
	Array *Head;//head
	int length;	

	public :
	
		
		 ArrayList(){	
		//	printf("Arraylist start!\n");
			Array *head=(Array *)malloc(sizeof(Array));
			ptr=head;
			Head=head;
			length=0;
		
		}

	
		int put( char *data,int num){
			if(Head->data== NULL){	
			
				ptr->data=allmem(num);
				memcpy(ptr->data , data , num);
			
			}else{
			
				Array *newarr=(Array *)malloc(sizeof(struct array));
				newarr->data=allmem(num);
				memcpy(newarr->data,data,num);
				ptr->next=newarr;
				ptr=newarr;	
			
			}
		//	printf("put length= %d\n",length);
			length++;
		
			return 0;
		}
		char *pop(){
			char *data;		
			//printf("pop length= %d \n",length);
			if(length==0){

				return NULL;
			}
			else if(length--==1){
				data=allmem(sizeof(Head->data));
				strcpy(data,Head->data);
				free(Head);
				ptr=NULL;
			//	free(ptr);
				return data;
	
			}else{
				data=allmem(sizeof(Head->data));
				Array *hptr=Head->next;
				strcpy(data,Head->data);
				free(Head);
				Head=hptr;
				return data;
			}
			return data;
		}
		int length(){
			return this.length;
		}

		char *allmem(int num){
			void *ptr;
			ptr=(char *)malloc(sizeof(char)*num);
			return (char*)ptr;
		}

};
/*
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
|					       +
+	TEST PROGTAM			       |
|					       +
+					       |
|+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*/
/*
int main(void){
	ArrayList *arr=new ArrayList();
	char *data="123456";
	char *data1="1234567";	
	char *data2="12345678";
	arr->put(data,7);
	arr->put(data1,8);
	arr->put(data2,9);

	printf("%s\n",arr->pop());
	printf("%s\n",arr->pop());
	printf("%s\n",arr->pop());
	return 0;
}
*/
