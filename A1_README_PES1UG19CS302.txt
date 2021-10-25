Memory Manager Best Fit Readme


Best Fit Logic: When a new request is made it searches for a free block with the smallest sufficient space as the new blocks address. If multiple blocks have same smallest size first one is picked as the new location. 

Hey This shit is so easy

1.BOOK KEEP STRUCTURE(  24 BYTES  )
* The book keeping struct has 2 integer members (blk_size and status) and two book keep pointers next and prev which points to the next and previous book keep structure. 



2.ALLOCATE FUNCTION
* The allocate function uses malloc to assign size bytes to p and also initializes the first empty blocks book keep. 
* additional global variable tot_space(total space allocated at the start) 



3.MYMALLOC FUNCTION
* The mymalloc function assigns a block depending on the request and makes a new book keeping structure accordingly.
* It uses Best Fit Method of assigning oooh



4.MYFREE FUNCTION 
* I used a big combination of if-else statements for each for different scenarios while freeing a block.
*Example : merging 2 blocks, at front.
	   merging 3 blocks.  etc 

	   

CHANGES MADE SINCE LAST SUBMISSION :  Removed int blk_address element from bookkeeping, fixed myfree merging, fixed mymalloc code logic.
