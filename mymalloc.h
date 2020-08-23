#include<stdio.h>
#include<stddef.h>
#include<stdbool.h>

/* allocate 2 million bytes in an array statically */
char memory[2000000];

struct block{
	size_t size;
	bool is_free;	// if there is free memory it set to true otherwise false
	struct block *next; //ponter to the next data block
};

// here we initallize pointer empty_Block which hold the pointer of starting address of the memory[2000000] 
//i am casting the type of starting address to void, becouse of it we can allocate memory to different types of datatypes
struct block *empty_Block = (void*)memory;

void Memory_split(struct block *inserting_block,size_t size);

void Memory_split(struct block *inserting_block,size_t size){
	struct block *new_Node = (void*)((void*)inserting_block + size + sizeof(struct block));
	new_Node->size = (inserting_block->size) - size - sizeof(struct block);
	new_Node->is_free = true;
	new_Node->next = inserting_block->next;
	inserting_block->size = size;
	inserting_block->is_free = false;
	inserting_block->next = new_Node;
}

// MyMalloc() allocate memory depending on nodesize 
//NOTE : The datatype size_t is unsigned integral type. It represents the size of any object in bytes
// In the MyMalloc() the result pointer return the starting address of allocated memory

void *MyMalloc(size_t nodesize){
	struct block *curr,*prev;
	void *result; 
	
	//1st time it checks whether empty_Block->size is null or not i.e. at first we gives the memory size to fist node and the remaining memory is 		//stored into empty_Block->size now we make is_Free to true because memory is empty then the next pointer is set to NULL 
	
	if(!(empty_Block->size)){
		empty_Block->size = sizeof(memory) - sizeof(struct block);
		empty_Block->is_free = true;
		empty_Block->next = NULL;
	}
	curr = empty_Block;
	// following loop is when we have not met with the required memory so we are moving forword in search of sufficient memory or required memory
	while((((curr->size)<nodesize) || ((curr->is_free)==false)) && (curr->next!=NULL)){
		prev = curr;
		curr = curr->next;
	}
	//here we get the reuired memory for allocation then we make is_free to false indicates that it is allocated and it returns tha starting 		//address of allocated memory
	
	if((curr->size) == nodesize){
		curr->is_free = false;
		result = (void*)(++curr);
		return result;
	}
	// if memory present is greater than the required memory then invoke Memory_split() to allocate only the block which is required and return 	//the starting address of allocated memory blcok
	else if((curr->size)>(nodesize+sizeof(struct block))){
		Memory_split(curr,nodesize);
		result = (void*)(++curr);
		return result;
	}
	//if there is no sufficient memory. It will return NULL 
	else{
		result = NULL;
		return result;
	}
}
