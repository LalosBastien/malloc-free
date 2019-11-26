/* 
 * tests.c
 *
 * This program contains a variety of tests for malloc and free.
 * XXX most tests leak on error.
 *
 * These tests (subject to restrictions and limitations noted below) should
 * work once user-level malloc is implemented.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <err.h>
#include "malloc.h"

#define SMALLSIZE   72
#define MEDIUMSIZE  896
#define BIGSIZE     16384
#define HUGESIZE    (1024 * 1024 * 1024)

/* Maximum amount of space per block we allow for indexing structures */
#define OVERHEAD         (sizeof(struct m_data))

/* Point past which we assume something else is going on */
#define ABSURD_OVERHEAD  256

static
int
geti(void)
{
	int val=0;
	int ch, digits=0;

	while (1) {
		ch = getchar();
		if (ch=='\n' || ch=='\r') {
			putchar('\n');
			break;
		}
		else if ((ch=='\b' || ch==127) && digits>0) {
			printf("\b \b");
			val = val/10;
			digits--;
		}
		else if (ch>='0' && ch<='9') {
			putchar(ch);
			val = val*10 + (ch-'0');
			digits++;
		}
		else {
			putchar('\a');
		}
	}

	if (digits==0) {
		return -1;
	}
	return val;
}

////////////////////////////////////////////////////////////

/*
 * Fill a block of memory with a test pattern.
 */
static
void
markblock(volatile void *ptr, size_t size, unsigned bias, int doprint)
{
	size_t n, i;
	unsigned long *pl;
	unsigned long val;

	pl = (unsigned long *)ptr;
	n = size / sizeof(unsigned long);

	for (i=0; i<n; i++) {
		val = ((unsigned long)i ^ (unsigned long)bias);
		pl[i] = val;
		if (doprint && (i%64==63)) {
			//printf(".");
		}
	}
	if (doprint) {
		printf("\n");
	}
}

/*
 * Check a block marked with markblock()
 */
static
int
checkblock(volatile void *ptr, size_t size, unsigned bias, int doprint)
{
	size_t n, i;
	unsigned long *pl;
	unsigned long val;

	pl = (unsigned long *)ptr;
	n = size / sizeof(unsigned long);

	for (i=0; i<n; i++) {
		val = ((unsigned long)i ^ (unsigned long)bias);
		if (pl[i] != val) {
			if (doprint) {
				printf("\n");
			}
			printf("FAILED: data mismatch at offset %lu of block "
			       "at 0x%lx: %lu vs. %lu\n",
			       (unsigned long) (i*sizeof(unsigned long)),
			       (unsigned long)(uintptr_t)pl,
			       pl[i], val);
			return -1;
		}
		if (doprint && (i%64==63)) {
			//printf(".");
		}
	}
	if (doprint) {
		printf("\n");
	}

	return 0;
}

////////////////////////////////////////////////////////////

/*
 * Test 1
 *
 * This test checks if all the bytes we asked for are getting
 * allocated.
 */

static
void
test1(void)
{
	volatile unsigned *x;

	printf("*** Malloc test 1 ***\n");
	printf("Allocating %u bytes\n", BIGSIZE);
	x = malloc(BIGSIZE);
	if (x==NULL) {
		printf("FAILED: malloc failed\n");
		return;
	}

	markblock(x, BIGSIZE, 0, 0);
	if (checkblock(x, BIGSIZE, 0, 0)) {
		printf("FAILED: data corrupt\n");
		return;
	}

	free((void *)x);

	printf("Passed malloc test 1.\n");
}


////////////////////////////////////////////////////////////

/* 
 * Test 2
 *
 * Tests if malloc gracefully handles failing requests.
 *
 * This test assumes that one of the following conditions holds:
 *    1. swap is not overcommitted; or
 *    2. user processes are limited to some maximum size, and enough
 *       swap exists to hold a maximal user process.
 *
 * That is, it assumes that malloc returns NULL when out of memory,
 * and that the process will not be killed for running out of
 * memory/swap at other times.
 *
 * If mallocing more memory than the system can actually provide
 * backing for succeeds, this test will blow up. That's ok, but please
 * provide a way to switch on one of the above conditions so this test
 * can be run.
 *
 * This test works by trying a huge malloc, and then trying
 * successively smaller mallocs until one works. Then it touches the
 * whole block to make sure the memory is actually successfully
 * allocated. Then it frees the block and allocates it again, which
 * should succeed.
 *
 * Note that this test may give spurious failures if anything else is
 * running at the same time and changing the amount of memory
 * available.
 */

static
void
test2(void)
{
	volatile unsigned *x;
	size_t size;
	
	printf("Testing how much memory we can allocate:\n");
	
	for (size = HUGESIZE; (x = malloc(size))==NULL; size = size/2) {
		printf("  %9lu bytes: failed\n", (unsigned long) size);
	}
	printf("  %9lu bytes: succeeded\n", (unsigned long) size);

	printf("Passed part 1\n");

	printf("Touching all the words in the block.\n");
	markblock(x, size, 0, 1);

	printf("Validating the words in the block.\n");
	if (checkblock(x, size, 0, 1)) {
		printf("FAILED: data corrupt\n");
		return;
	}
	printf("Passed part 2\n");


	printf("Freeing the block\n");
	free((void *)x);
	printf("Passed part 3\n");
	printf("Allocating another block\n");
	
	x = malloc(size);
	if (x==NULL) {
		printf("FAILED: free didn't return the memory?\n");
		return;
	}
	free((void *)x);

	printf("Passed malloc test 2.\n");
}


////////////////////////////////////////////////////////////

/*
 * Test 3
 *
 * Tries to test in detail if malloc coalesces the free list properly.
 *
 * This test will likely fail if something other than a basic first-fit/
 * next-fit/best-fit algorithm is used.
 */

static
void
test4(void)
{
  void *x, *y, *z, *b;
  unsigned long lx, ly, lz, overhead, zsize;

	printf("Entering malloc test 3.\n");
	printf("This test is intended for first/best-fit based mallocs.\n");
	printf("This test may not work correctly if run after other tests.\n");

	printf("Testing free list coalescing:\n");

	x = malloc(SMALLSIZE);
	if (x==NULL) {
		printf("FAILED: malloc(%u) failed\n", SMALLSIZE);
		return;
	}

	y = malloc(MEDIUMSIZE);
	if (y==NULL) {
		printf("FAILED: malloc(%u) failed\n", MEDIUMSIZE);
		return;
	}
	b = malloc(BIGSIZE);
	if (b==NULL) {
                printf("FAILED: malloc(%u) failed\n", BIGSIZE);
                return;
        }
	
	if (sizeof(unsigned long) < sizeof(void *)) {
		printf("Buh? I can't fit a void * in an unsigned long\n");
		printf("ENVIRONMENT FAILED...\n");
		return;
	}

	lx = (unsigned long)x;
	ly = (unsigned long)y;

	printf("x is 0x%lx; y is 0x%lx\n", lx, ly);

	/*
	 * The memory should look something like this:
	 *
	 *     OXXXOYYYYYYYYYYY
	 *
	 * where O are optional overhead (indexing) blocks.
	 */

	/* This is obviously wrong. */
	if (lx == ly) {
		printf("FAIL: x == y\n");
		return;
	}

	/*
	 * Check for overlap. It is sufficient to check if the start
	 * of each block is within the other block. (If the end of a
	 * block is within the other block, either the start is too,
	 * or the other block's start is within the first block.)
	 */
	if (lx < ly && lx + SMALLSIZE > ly) {
		printf("FAIL: y starts within x\n");
		return;
	}
	if (ly < lx && ly + MEDIUMSIZE > lx) {
		printf("FAIL: x starts within y\n");
		return;
	}

	/*
	 * If y is lower than x, some memory scheme we don't
	 * understand is in use, or else there's already stuff on the
	 * free list.
	 */
	if (ly < lx) {
		printf("TEST UNSUITABLE: y is below x\n");
		return;
	}

	/*
	 * Compute the space used by index structures.
	 */
	overhead = ly - (lx + SMALLSIZE);
	printf("Apparent block overhead: %lu\n", overhead);

	if (overhead > ABSURD_OVERHEAD) {
		printf("TEST UNSUITABLE: block overhead absurdly large.\n");
		return;
	}
	if (overhead > OVERHEAD) {
		printf("FAIL: block overhead is too large.\n");
		return;
	}

	printf("Freeing blocks...\n");
	free(x);
	free(y);

	zsize = SMALLSIZE + MEDIUMSIZE;
	
	printf("Now allocating %lu bytes... should reuse the space.\n", zsize);

	z = malloc(zsize);
	if (z == NULL) {
		printf("FAIL: Allocation failed...\n");
		return;
	}

	lz = (unsigned long) z;

	printf("z is 0x%lx (x was 0x%lx, y 0x%lx)\n", lz, lx, ly);

	if (lz==lx) {
		printf("Passed.\n");
	}
	else {
		printf("Failed.\n");
	}
	list_block();
	free(z);
	free(b);
}

////////////////////////////////////////////////////////////

/*
 * Test 4/5
 *
 * Generally beats on malloc/free.
 *
 * Test 5 uses random seed 0.
 * Test 6 seeds the random number generator from random:.
 * Test 7 asks for a seed.
 */

static
void
test567(int testno, unsigned long seed)
{
	static const int sizes[8] = { 13, 17, 69, 176, 433, 871, 1150, 6060 };
	
	void *ptrs[32];
	int psizes[32];
	int i, n, size, failed=0;

	srandom(seed);
	printf("Seeded random number generator with %lu.\n", seed);

	for (i=0; i<32; i++) {
		ptrs[i] = NULL;
		psizes[i] = 0;
	}

	for (i=0; i<100000; i++) {
		n = random()%32;
		if (ptrs[n] == NULL) {
			size = sizes[random()%8];
			ptrs[n] = malloc(size);
			psizes[n] = size;
			if (ptrs[n] == NULL) {
				printf("\nmalloc %u failed\n", size);
				failed = 1;
				break;
			}
			markblock(ptrs[n], size, n, 0);
		}
		else {
			size = psizes[n];
			if (checkblock(ptrs[n], size, n, 0)) {
				failed = 1;
				break;
			}
			free(ptrs[n]);
			ptrs[n] = NULL;
			psizes[n] = 0;
		}
		if (i%256==0) {
			printf(".");
		}
	}
	printf("\n");

	for (i=0; i<32; i++) {
		if (ptrs[i] != NULL) {
			free(ptrs[i]);
		}
	}

	if (failed) {
		printf("FAILED malloc test %d\n", testno);
	}
	else {
		printf("Passed malloc test %d\n", testno);
	}
}

static
void
test5(void)
{
	printf("Beginning malloc test 4\n");
	test567(4, 0);
}

static
void
test7(void)
{
	unsigned long seed;

	printf("Beginning malloc test 5\n");

	printf("Enter random seed: ");
	seed = geti();

	test567(5, seed);
}

////////////////////////////////////////////////////////////

static struct {
	int num;
	const char *desc;
	void (*func)(void);
} tests[] = {
	{ 1, "== Simple allocation test ==", test1 },
	{ 2, "== Allocate all memory in a big chunk ==", test2 },
	{ 3, "== Free list coalescing test ==", test4 },
	{ 4, "== Stress test ==", test5 },
	{ 5, "== Stress test with particular seed ==", test7 },
	{ -1, NULL, NULL }
};

static
int
dotest(int tn)
{
	int i;
	for (i=0; tests[i].num>=0; i++) {
		if (tests[i].num == tn) {
			tests[i].func();
			
			return 0;
		}
	}
	return -1;
}

int
main(int argc, char *argv[])
{
	int i, tn, menu=1;

	if (argc > 1) {
		for (i=1; i<argc; i++) {
			dotest(atoi(argv[i]));
		}
		return 0;
	}

	while (1) {
		if (menu) {

            ascii("test.ascii");

			for (i=0; tests[i].num>=0; i++) {
				printf(" %2d  %s\n", tests[i].num, 
				       tests[i].desc);
			}
			menu = 0;
		}
		printf("\n  ~> ");
		tn = geti();
		if (tn < 0) {
			break;
		}

		if (dotest(tn)) {
			menu = 1;
		}
	}

	return 0;
}
