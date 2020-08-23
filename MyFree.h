
#include "mymalloc.h"

// Why we use Combine() 
// To join consecutive empty blocks or free memory blocks i.e. suppose we allocate memory for a node and after that we freed that node so 
//there is an empty space in memory is formed. So we combine that empty spaces to avoid external fragmentation

void Combine(){
	struct block *curr,*prev;
	curr = empty_Block;
	while((curr->next) != NULL){
		if((curr->is_free) && (curr->next->is_free)){
			curr->size += (curr->next->size)+sizeof(struct block);
			curr->next = curr->next->next;
	}
	prev = curr;
	curr = curr->next;
	}
}

// Its a good practice to deallocate or free the memory which is not required for further execution so we can use that memory for 
//another perspective operations
// The main thing we notice in the function is we setting our is_free to true which indicate that memory is freed over there and 
// we combine that memory for further allocations

void MyFree(void* pointer){
	if(((void*)memory <= pointer) && (pointer <= (void*)(memory+sizeof(memory)))){
		struct block* curr = pointer;
		--curr;
		curr->is_free = true;
		Combine();
	}
	else	printf("Segmentation Fault\n");
}
