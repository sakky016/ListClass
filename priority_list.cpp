#include "priority_list.h"

PriorityList::PriorityList()
{
}

PriorityList::~PriorityList()
{
}

int PriorityList::insert(int val)
{
    Node_t *newnode = new Node_t;
    newnode->data = val;
    newnode->next = NULL;
    
    /* If list is empty */
    if (m_pHead == NULL)
    {
        m_pHead = newnode;
        m_size++;
        return SUCCESS;
    }

    Node_t *crawler = m_pHead;

    /* If new value is smaller than 1st entry of list */
    if (val < crawler->data)
    {
        m_pHead = newnode;
        newnode->next = crawler;
        m_size++;
        return SUCCESS;
    }

    /* Handle all other cases */
    while (1)
    {
        if (crawler->next == NULL)
        {
            /* Reached last node */
            break;
        }

        if (val < (crawler->next)->data)
        {
            /* Reached the required node */
            break;
        }
        else
        {
            crawler = crawler->next;
        }
    } /* End of while */

    /* Insert the newnode now */
    Node_t *tmp = crawler->next;
    crawler->next = newnode;
    newnode->next = tmp;
    m_size++;

    return SUCCESS;
}
