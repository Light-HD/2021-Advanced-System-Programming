#define calloc(size, sizeint) mycalloc(size, sizeint)
#define free(ptr) myfree(ptr)
void *mycalloc(size_t size, size_t sizeint);
void myfree(void *ptr);
