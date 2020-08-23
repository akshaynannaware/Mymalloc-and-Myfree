/*This is a linked list program in which we insert nodes in it and delete node by its value
Here we have used our own malloc and free functions as MyMalloc and MyFree */

#include<stdio.h>
#include "MyFree.h"
 
typedef struct node{
	int data;
	struct node *next;
}node;

node *DeleteNode(node *head, int key)
{
	node *temp=head;
	node *temp1=head;
	
	while(temp->next->next!=NULL){
		temp1 = temp->next;
		if (temp->next->data == key){
			
			temp->next = temp1->next;
			MyFree(temp1);
			return head;
		}
		temp = temp->next;
	}
	if (temp1->next->data == key){
		MyFree(temp1->next);
		temp1->next = NULL;
		
	}
	return head;
}

void create(node *list){
	int no;
	printf("enter no. elements : \n");
	scanf("%d",&no);
	node *temp=list;
	node *newn;
	
	printf("Enter the data into the nodes : \n");
	for(int i=0;i<no;i++){
		newn=(node *)MyMalloc(sizeof(node));
		newn->next=NULL;
		scanf("%d",&newn->data);
		temp->next=newn;
		temp=newn;		
	}
	temp->next=NULL;	
	
}


void display(node *list1){
	node*list = list1;
	while(list->next!=NULL){
		list=list->next;
		printf("%d	",list->data);
		
	}

}

void main()
{
	node *list;
	list = (node*)MyMalloc(sizeof(node));
	list->next=NULL;
	
	
	create(list);
	printf("Original list is : \n");
	display(list);
	int n;
	printf("\n Enter the node data at which the node you want to delete : \n");
	scanf("%d",&n);
	list = DeleteNode(list, n);
	printf("Linked list after deleting node : \n");
	display(list);
	printf("\n");
}


