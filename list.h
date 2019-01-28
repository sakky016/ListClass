#ifndef _LIST_H_
#define _LIST_H_

#include "header.h"

typedef struct Node_tag
{
    int data;
    Node_tag *next;
}Node_t;

/* Regular Linked list class */
class List
{
    protected:
        Node_t *m_pHead;
        bool m_bFreed;
        unsigned int m_size;

    public:
        List();
        ~List();
        virtual int insert(int val);
        virtual int deleteNodeWithValue(int val);
        virtual int deleteAllNodesWithValue(int val);
        virtual bool swapNodes(int val1, int val2);
        void display();
        bool isEmpty();
        void reverse();
        Node_t* reverseInGroupsInList(Node_t *, int);
        void reverseInGroups(int);
};

#endif
