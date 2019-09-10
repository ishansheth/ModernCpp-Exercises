#include<assert.h>
#include<stddef.h>
#include<unistd.h> 
#include<stdio.h>


// every block will be marked if its free or not and future malloc calls can reuse this 

struct block_meta{
	size_t size;
	struct block_meta * next;
	int free;
	int magic;
};

#define META_SIZE sizeof(struct block_meta)

void *global_base = NULL;

// for our malloc we want to reuse free space if possible, allocating space when we cant reuse existing space
// when we get request of some size, we iterate through our linked list to see if there is a block large enough

struct block_meta* find_free_block(struct block_meta** last, size_t size){
	printf("finding a free block\n");
	struct block_meta* current = global_base;
	while(current && !(current->free && current->size >= size)){
		*last = current;
		current = current->next;
	}
	return current;
}

struct block_meta* request_space(struct block_meta* last,size_t size){
	printf("requesting new space \n");
	struct block_meta* block;
	block = sbrk(0);	// get the current top of the heap pointer
	void* request = sbrk(size + META_SIZE);	//increment the size of heap by (size + meta block) size
	assert((void*)block == request);
	if(request == (void*) - 1)
		return NULL;	//sbrk failed

	if(last)	// NULL on first request
		last->next = block;

	block->size = size;
	block->next = NULL;
	block->free = 0;
	block->magic = 0x1234;
	return block;
}

void* mymalloc(size_t size){
	struct block_meta* block;

	if(size <= 0)
		return NULL;

	if(!global_base){	// first call
		block = request_space(NULL,size);
		if(!block)
			return NULL;
		global_base = block;
	}else{
		struct block_meta* last = global_base;
		block = find_free_block(&last,size);	// pass global_base, and find the next available with fitting size
		if(!block){
			block = request_space(last,size);
			if(!block)
				return NULL;
		}else{
			block->free = 0;
			block->magic = 0x7777;
		}			
	}

	return (block+1);
}


struct block_meta* get_block_ptr(void* ptr){
	return (struct block_meta*)ptr -1;
}


void free(void* ptr){
	if(!ptr)
		return;

	struct block_meta* block_ptr = get_block_ptr(ptr);
//	assert(block_ptr->free == 0);
	block_ptr->free = 1;
	block_ptr->magic = 0x5555;
}



void main(){
	
	int* iPointer = (int*)mymalloc(sizeof(int));
	
	*iPointer = 5;
	printf("pointer val:%d \n",*iPointer);

	free(iPointer);

	int* dPointer = (int*)mymalloc(sizeof(int));
	*dPointer = 5.34234;
	printf("pointer val:%d \n",*dPointer);

	free(dPointer);
	printf("memory freed \n");
}




