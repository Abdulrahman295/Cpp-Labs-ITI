#ifndef LAB13_QUEUELIST_H
#define LAB13_QUEUELIST_H
#include "LinkedList.h"
class QueueList {
private:
    LinkedList list;
public:
    void enqueue(int value) {
        list.insert_end(value);
    }

    int dequeue() {
        int front_value = list.getValueAt(0);
        list.delete_front();
        return front_value;
    }

    void print() {
        list.print();
    }

    bool isEmpty() {
        return list.getLength() == 0;
    }
};

#endif