#include "list.h"

/* Constructor */
List::List()
{
    printf("\n>> List created.\n");
    m_pHead = NULL;
    m_size = 0;
    m_bFreed = false;
}

/* Destructor */
List::~List()
{
    /* Free memory used by list */
    Node_t *crawler = m_pHead;
    unsigned int delete_count = 0;

    if (!m_bFreed)
    {

        while (crawler != NULL)
        {
            Node_t *tmp = crawler;
            crawler = crawler->next;
            delete tmp;
            delete_count++;
        }

        if (m_size == delete_count)
        {
            printf("\n>> Destroyed the list. %u nodes freed.\n", delete_count);
            m_bFreed = true;
        }
        else
        {
            printf("\n>> All nodes could not be freed. Total: %u, Freed: %u\n", m_size, delete_count);
        }
    }

}

/* Insert node to last */
int List::insert(int val)
{
    Node_t *newnode = new Node_t;
    newnode->data = val;
    newnode->next = NULL;

    /* Insert new node at the end */ 
    if (m_pHead == NULL)
    {
        m_pHead = newnode;
    }
    else
    {
        Node_t *crawler = m_pHead;

        while (crawler->next != NULL)
        {
            crawler = crawler->next;
        }

        crawler->next = newnode;
    }

    m_size++;
    return SUCCESS;
}

/* Delete a node */
int List::deleteNodeWithValue(int val)
{
    if (this->isEmpty())
    {
        return FAILURE;
    }

    Node_t *crawler = m_pHead;
    if (crawler->data == val)
    {
        m_pHead = crawler->next;
        delete crawler;
        m_size--;
        return SUCCESS;
    }

    while (crawler->next != NULL)
    {
        if (val == (crawler->next)->data)
        {
            Node_t *tmp = crawler->next->next;
            delete crawler->next;
            m_size--;
            crawler->next = tmp;
            return SUCCESS;
        }

        crawler = crawler->next;
    }

    return FAILURE;
}

bool List::isEmpty()
{
    return (m_size == 0);
}

/* Display elements of the list */
void List::display()
{
    Node_t *crawler = m_pHead;

    printf("List [%u element(s)]: ", m_size);
    if (m_pHead == NULL)
    {
        printf("X\n");
    }
    else
    {
        while(crawler != NULL)
        {
            printf("%d ", crawler->data);
            crawler = crawler->next;
        }
        printf("\n");
    }
    sleep(1);
}

int List::deleteAllNodesWithValue(int val)
{
    int retval = 0;
    int delete_count = 0;
    while (1)
    {
        retval = deleteNodeWithValue(val);
        if (retval != SUCCESS)
        {
            break;
        }
        else
        {
            delete_count++;
        }
    }

    return delete_count;
}

/* Reverse the links of the linked list */
void List::reverse()
{
    Node_t *current = m_pHead;
    Node_t *prev = NULL;
    Node_t *next = NULL;

    if (m_pHead == NULL)
    {
        return;
    }

    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    m_pHead = prev;
}

/* Swaps 2 nodes whose data values are val1 and val2. 
   Returns false if either is not present */
bool List::swapNodes(int val1, int val2)
{
    bool found1 = false;
    bool found2 = false;

    Node_t *val1_ptr = m_pHead;
    Node_t *val1_prev_ptr = NULL;

    Node_t *val2_ptr = m_pHead;
    Node_t *val2_prev_ptr = NULL;

    Node_t *crawler = m_pHead;

    /* Find the nodes with val1 and val2 values */
    while (crawler != NULL)
    {
        if (!found1 && crawler->data == val1)
        {
            printf("val1 found\n");
            found1 = true;
            val1_ptr = crawler;
        }
        else if (!found2 && crawler->data == val2)
        {
            printf("val2 found\n");
            found2 = true;
            val2_ptr = crawler;
        }
        else
        {
            // Nothing
        }

        /* Track previous nodes */
        if (found1 == false)
        {
            val1_prev_ptr = crawler;
        }

        if (found2 == false)
        {
            val2_prev_ptr = crawler;
        }

        /* Move to next node */
        crawler = crawler->next;

    }/* end of while loop */

    if (found1 && found2)
    {
        Node_t *tmp = NULL;

        if (val1_prev_ptr != NULL)
        {
            val1_prev_ptr->next = val2_ptr;
        }
        else
        {
            m_pHead = val2_ptr;
        }

        tmp = val2_ptr->next;

        /* Special case if val1 and val2 are consecutive nodes */
        if (val1_ptr->next == val2_ptr)
        {
            val2_ptr->next = val1_ptr;
        }
        else
        {
            val2_ptr->next = val1_ptr->next;
        }

        if (val2_prev_ptr != NULL)
        {
            val2_prev_ptr->next = val1_ptr;
        }
        else
        {
            m_pHead = val1_ptr;
        }
        val1_ptr->next = tmp;

        return true;
    }
    else
    {
        return false;
    }
}

Node_t* List::reverseInGroupsInList(Node_t *root, int k)
{
    Node_t *cur = root;
    Node_t *prev = NULL;
    Node_t *next = NULL;
    int count = 0;

    /* reverse a group of k nodes */
    while (cur != NULL && count < k)
    {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;

        count++;
    }

    while (next != NULL)
    {
        root->next = reverseInGroupsInList(cur, k);
    }
    
    return prev;
}

void List::reverseInGroups(int k)
{
    m_pHead = reverseInGroupsInList(m_pHead, k);
}
