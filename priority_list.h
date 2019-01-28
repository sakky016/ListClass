#include "list.h"

class PriorityList : public List
{
    private:

    public:
        PriorityList();
        ~PriorityList();
        virtual int insert(int val);
};
