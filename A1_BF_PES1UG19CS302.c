#include<stdio.h>
#include<stdlib.h>
#include "assignment_1.h"
char *p;
int size;
int tot_space = 0;
int t = 12;

struct book
{	
	int blk_size;
	int blk_status;
	struct book* next;
	struct book* prev;
}typedef BOOK;

long int size_of_structure = sizeof(BOOK);


void print_book( ){
	printf("%ld\n", size_of_structure);
}



void allocate(int size){
	tot_space = size;
	p = (void*)(malloc(size*sizeof(char)));//taking a block from our mev mory 
	BOOK* temp = (BOOK*)p;
	temp->blk_status = 2;
	temp->blk_size = size-sizeof(BOOK);
	temp->next = NULL;
	temp->prev = NULL;
}




void* mymalloc(int msize){
	if(msize<0 || msize > tot_space ) return NULL;
	BOOK* tmp1 = (BOOK*)p;
	BOOK* tmp2 = NULL;
	int rem_space=0;
	int small = 100000;
	for(tmp1;tmp1!=NULL;tmp1=tmp1->next){
		if((tmp1->blk_size<small) && (tmp1->blk_status==2)){
			small = tmp1->blk_size;
			rem_space = tmp1->blk_size-msize;
			if(rem_space>=0)tmp2=tmp1;
		}
	}
	if(tmp2!=NULL){
		if(rem_space>sizeof(BOOK)){
            BOOK* temp= tmp2 + msize + 1;
            temp->blk_size = rem_space - sizeof(BOOK);
            temp->blk_status=2;
            temp->prev=tmp2;
            temp->next=tmp2->next;
            tmp2->blk_size=msize;
            tmp2->blk_status=1;
            tmp2->next=temp;
            return tmp2 + 1; 
		}
		else if(rem_space>=0){
			tmp2->blk_size=rem_space+msize;
			tmp2->blk_status = 1;
			return tmp2 + 1;		}
	}
	else return NULL;

}

void display_mem_map(){
	int a =0;
	//This just traverses through the linked book keeping stucts and prints its data
	BOOK* t = (BOOK*)p;
	while(t!=NULL){
		printf("%d\t%ld\t%d\n",a , sizeof(BOOK), 0);
		printf("%ld\t%d\t%d\n", a+sizeof(BOOK), t->blk_size, t->blk_status);
		a += sizeof(BOOK) + t->blk_size;
		t = t->next;
	}
}


void myfree(void* f_tmp){
	BOOK* tmp2; //block to be freed
	BOOK* tmp3; //extra pointer 
	tmp2 = (BOOK*)f_tmp - 1;
	tmp2->blk_status = 2;
	//Below are the different cases for merging the free blocks with its neighbours
	if(tmp2->prev == NULL && tmp2->next!=NULL) {//if its the first block of memory
		if(tmp2->next->blk_status == 2){
			//if the next block is to be mergerd  
		tmp2->blk_size = tmp2->blk_size + sizeof(BOOK) + tmp2->next->blk_size;
		tmp2->next = tmp2->next->next;
		if(tmp2->next == NULL){//if only 2 blocks left
			return;
		}
		tmp2->next->prev = tmp2;
		return;
		}
		else{
			//if next block occupied
			tmp2->blk_status = 2;
			return;
			}
	}
	else if(tmp2->prev!=NULL && tmp2->next==NULL){ //if its the last block 
		if(tmp2->prev->blk_status==2){
			//merge the block with the one before it
		tmp3 = tmp2->prev;
		tmp3->blk_size = tmp3->blk_size + tmp2->blk_size + sizeof(BOOK);
		tmp3->next = NULL;
		return;
		}
		else{
			//if previous block is occupied
			tmp2->blk_status = 2;
			return;
			}
	}
	else if(tmp2->next!=NULL && tmp2->prev!=NULL){ // if its a block in the middle 
		if(tmp2->next->blk_status==2 && tmp2->prev->blk_status==1){
			//merge the block with the one after it
			tmp2->blk_size += tmp2->next->blk_size + sizeof(BOOK);
			tmp2->next = tmp2->next->next;
			if(tmp2->next == NULL){ //special case when its last but one element to avoid seg error
			return;
		}
			tmp2->next->next->prev = tmp2;
			tmp2->next = tmp2->next->next;
			return;
		}
		else if(tmp2->next->blk_status==1 && tmp2->prev->blk_status==2){
			//merge the block with the one before it
			tmp3 = tmp2->prev;
			tmp2->next->prev = tmp3;
			tmp3->blk_size += tmp2->blk_size + sizeof(BOOK);
			tmp3->next = tmp2->next;
			return;
		}
		else if(tmp2->next->blk_status!=2 && tmp2->prev->blk_status!=2){
			//no merge because neighbouring are occupied 
			tmp2->blk_status = 2;
			return;
		}
		else{
		//merge the 3 blocks(1 before and one after)
		if(tmp2->next->next == NULL){
			tmp2->prev->blk_size += tmp2->blk_size + tmp2->next->blk_size + sizeof(BOOK) + sizeof(BOOK);
			tmp2->prev->blk_status = 2;
			tmp2->prev->next = tmp2->next->next;
			return;
		}
		tmp2->next->next->prev = tmp2->prev;
		tmp2->prev->next = tmp2->next->next;

		tmp2->prev->blk_size += tmp2->blk_size + tmp2->next->blk_size + sizeof(BOOK) + sizeof(BOOK);
		tmp2->prev->blk_status = 2;
		return;
		}	
	}
	else{return;}

}
