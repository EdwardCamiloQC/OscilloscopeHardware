#include <fifo.h>
#include <stdlib.h>

struct Node{
    struct Node* ptNext;
    uint16_t data;
};

struct FIFO* createQueue(){
    struct FIFO* ptFIFO = (struct FIFO*)malloc(sizeof(struct FIFO));
    ptFIFO->ptFront = ptFIFO->ptEnd = NULL;
    return ptFIFO;
}

bool fifoEmpty(struct FIFO* fifo){
    if(fifo->ptEnd == NULL){
        return 1;
    }
    return 0;
}

void pushData(struct FIFO* fifo, uint16_t data){
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->ptNext = node;
    if(fifoEmpty(fifo)){
        fifo->ptFront = node;
    }else{
        (fifo->ptEnd)->ptNext = node;
    }
    fifo->ptEnd = node;
}

uint16_t popData(struct FIFO* fifo){
    uint16_t data;
    struct Node* ptDelNode; //puntero de a nodo a eliminar
    if(fifoEmpty(fifo)){
        return 0;
    }
    data = (fifo->ptFront)->data;
    ptDelNode = fifo->ptFront;
    fifo->ptFront = (fifo->ptFront)->ptNext;
    if(fifo->ptFront == fifo->ptEnd){
        fifo->ptFront = fifo->ptEnd = NULL;
    }
    free(ptDelNode);
    return data;
}
