#ifdef COMPILETIME
#include <stdio.h>
#include <malloc.h>
/* calloc wrapper function */
void *mycalloc(size_t size, size_t sizeint)
{
void *ptr = calloc(size,sizeof(int));
printf("calloc:%p\n",ptr);
return ptr;
}
/* free wrapper function */
void myfree(void *ptr)
{
free(ptr);
printf("free:%p\n", ptr);
}
#endif

#ifdef LINKTIME
#include <stdio.h>
void *__real_calloc(size_t size, size_t sizeint);
void __real_free(void *ptr);
/* calloc wrapper function */
void *__wrap_calloc(size_t size, size_t sizeint)
{
void *ptr = __real_calloc(size,sizeof(int)); /* Call libc calloc */
printf("calloc:%p\n", ptr);
return ptr;
}
/* free wrapper function */
void __wrap_free(void *ptr)
{
__real_free(ptr); /* Call libc free */
printf("free:%p\n", ptr);
}
#endif

#ifdef RUNTIME
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
/* calloc wrapper function */
void *calloc(size_t size, size_t sizeint)
{
void *(*callocp)(size_t size, size_t sizeint);
char *error;
callocp = dlsym(RTLD_NEXT, "calloc"); /* Get addr of libc calloc */
if ((error = dlerror()) != NULL) {
fputs(error, stderr);
exit(1);
}
char *ptr = callocp(size, sizeof(int)); /* Call libc calloc */
printf("calloc:%p\n", ptr);
return ptr;
}
/* free wrapper function */
void free(void *ptr)
{
void (*freep)(void *) = NULL;
char *error;
if (!ptr)
return;
freep = dlsym(RTLD_NEXT, "free"); /* Get address of libc free */
if ((error = dlerror()) != NULL) {
fputs(error, stderr);
exit(1);
}
freep(ptr); /* Call libc free */
printf("free:%p\n", ptr);
}
#endif

