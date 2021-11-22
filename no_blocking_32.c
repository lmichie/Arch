#include <stdio.h>
#include <math.h>

#define XSIZE 400
#define YSIZE 400
#define CACHE_SIZE 32768 
#define BLOCK_SIZE 8
#define BLOCKS CACHE_SIZE/(BLOCK_SIZE * 4)
#define INDEX_MASK 0x7FE0
#define OFFSET_MASK 0x1F
#define TAG_MASK 0xFFFFFFFFFFFE0000

int hits = 0;
int misses = 0;

int validBit[BLOCKS];
int tag[BLOCKS];

void cache(void * addr) {
    printf("%p \n", addr); 
	int index = ((unsigned long)addr & (unsigned long)INDEX_MASK) >> 5;
		   
			
	int currTag = ((unsigned long)addr & TAG_MASK) >> 17;
	//printf("addr: %p, Index: %x, currTag: %x, BLOCKS %u \n", addr, index, currTag, BLOCKS); 
	if (validBit[index] && (tag[index] == currTag)) {
			hits++;
	}
	else{
		misses++;
		validBit[index] = 1;
		tag[index] = currTag;
	}
}

int main(void) {
  int x[XSIZE][YSIZE];
  int y[XSIZE][YSIZE];
  int z[XSIZE][YSIZE];
  int i, j, k;

  int r;
  

  //initialize tag & bit matrix
	for(i=0; i<BLOCKS; i++) {
    	validBit[i] = 0;
	    tag[i] = 0;
	}

/* Initialize x matrix */
  for(i=0; i<XSIZE; i++) {
    for(j=0; j<YSIZE; j++) {
      x[i][j] = 0;
    }
 }
  /* Initialize y matrix */
  for(i=0; i<XSIZE; i++) {
    for(j=0; j<YSIZE; j++) {
	    y[i][j] = i + j;
    }
  }

  /* Initialize z matrix */
  for(i=0; i<XSIZE; i++) {
    for(j=0; j<YSIZE; j++) {
		z[i][j] = i + j;
    }
  }
  //multiply
 for(i=0; i<XSIZE; i=i+1) {
    for(j=0; j<YSIZE; j=j+1) {
      r = 0;
      for(k=0; k<XSIZE; k=k+1) {
        r = r + y[i][k] * z[k][j];
        cache(&y[i][k]);
		cache(&z[k][j]);
		}
		x[i][j] = r;
		cache(&x[i][j]);
    }
  }
	printf("Hits: %u, Misses: %u, Miss rate: %f\n", hits, misses, (float)misses/(hits+misses));
}
