#ifndef LIST_H
#define LIST_H

class List
{
    public:

        List();

        void insert(int value);

        int index(int i) const;

    private:

        struct Node 
        {
            int value;
            Node* next;
            Node* prev;
        };

        Node* first;
        Node* last;


};

#endif