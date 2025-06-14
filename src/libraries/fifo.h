#ifndef _FIFO_H_
    #define _FIFO_H_

    #include <stdint.h>
    #include <stdbool.h>

    struct FIFO{
        struct Node* ptFront;
        struct Node* ptEnd;
    };

    struct FIFO* createQueue();
    bool fifoEmpty();
    void pushData(struct FIFO* fifo, uint16_t data);
    uint16_t popData(struct FIFO* fifo);
#endif
