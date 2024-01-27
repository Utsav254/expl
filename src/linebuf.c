#include <stdlib.h>
#include <string.h>

#include "linebuf.h"
#include "terminal.h"
#include "expl.h"

//allocate memory using calloc which will initialise with nullstring terminators
//this simplifies the append function
struct linebuf * lbAllocate(size_t buf_size) {

	struct linebuf *lb = calloc(1, sizeof(struct linebuf) + buf_size);
	
	if(lb == NULL) die("calloc(linebuf)");
    
    //initialise values
    lb->s = buf_size;
	lb->p = 0;
	lb->e = 0;
	
	return lb;
}

void lbAppend(struct linebuf *lb , const char *s , int len) {
    //check for buffer overflow error
	if((lb->p + len) > (short int)lb->s - 1) { 
		die("linebuffer overflow");
	}
    //check for esacpe sequence
	else if(*s == '\x1b') {
		strncpy((lb->b + lb->p) , s , len);
		lb->p += len;
		lb->e += len;
	}
    //append using the pointer
	else {
		strncpy((lb->b + lb->p) , s , len);
		lb->p += len;
	}
}

void lbFree(struct linebuf *lb) {
	free(lb);
}