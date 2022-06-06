#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/* see if there is any different using 16, 32 or why not 64 pages */
#define PAGES (16)
#define REFS (10*(1024*1024))
/* after above switch back to page size 64 and then try 64 pages again. How large is the memory now? How many real pages are used then?*/
#define PAGESIZE (64)	//(4*1024) 
/* what happens if we step up to 512 pages or why not 4096? #Change code for this# */

int main(int argc, char *argv) {
	
	clock_t c_start, c_stop;

	char *memory = malloc((long)PAGESIZE * PAGES);

	for(int p = 0; p < PAGES; p++) {
		long ref = (long)p * PAGESIZE;
		/* force the page to be allocated */
		memory[ref] +=1;
	}

	printf("#TLB experiment\n");
	printf("#	page size = %d bytes\n", (PAGESIZE));
	printf("#	max number of pages = %d\n", (PAGES));
	printf("#	total number of references = %d Mi\n", (REFS/(1024*1024)));
	printf("#pages\t proc\t sum\n");

	for(int pages = 4; pages <= PAGES; pages+=2) {
		
		int loops = REFS / pages;

		c_start = clock();

		long sum = 0;

		for(int l = 0; l < loops; l++) {
			for(int p = 0; p < pages; p++) {
				/* dummy operation */
				long ref = (long)p * PAGESIZE;
				sum += memory[ref];				
				//sum++;
			}
		}

		c_stop = clock();

		{
			double proc;

			proc = ((double)(c_stop - c_start))/CLOCKS_PER_SEC;

			/* change %.6f\t to write more or less decimals. How many significant 					figures is it reasonable to show? */
			printf("%d\t %.5f\t %ld\n", pages, proc, sum);
		}
	}
	printf("#	time for all references in sec (%ld)\n", (c_stop - c_start));
	return 0;
}
