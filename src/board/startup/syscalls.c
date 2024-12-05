#include <stdarg.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

extern int _end;

void *_sbrk(int incr){
    static unsigned char *heap = NULL;
    unsigned char *prev_heap;
    if(heap == NULL){
        heap = (unsigned char *)&_end;
    }
    prev_heap = heap;
    heap += incr;
    return prev_heap;
}

int _close(int file){
    return -1;
}

int _fstat(int file, struct stat * st){
    st->st_mode = S_IFCHR; 
    return 0;
}

int _isatty(int file){
    return 1;
}

int _lseek(int file, int ptr, int dir){
    return 0;
}

void _exit(int status){
    //__asm("BKPT #0");
    while(1);
}

void _kill(int pid, int sig){
    return;
}

int _getpid(void){
    return -1;
}

int _write(int file, char * ptr, int len){
    int written = 0;
    if((file != 1) && (file != 2) && (file != 3)){
        return -1;
    }
    for(; len != 0; --len){
        //uart0_putchar(UART0_BASE_PTR, *ptr);
        ++written;
    }
    return written;
}

int _read(int file, char* ptr, int len){
    int read = 0;
    if(file != 0){
        return -1;
    }
    return read;
}