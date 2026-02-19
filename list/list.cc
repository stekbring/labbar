#include "list.h"
#include <stdexcept>


List::List() : first{nullptr}, last{nullptr} {}

void List::insert(int value) 
{
    if (first == nullptr)
    {
        first = new Node{value, nullptr, nullptr};
        last = first;
    }
    else
    {
        //när ej tom
    }
}

int List::index(int i) const
{
    if (first == nullptr) 
    {
        throw std::out_of_range("Listan är tom");
    }

    Node* current = first;
    int current_index = 1;

    while (current != nullptr && current_index < i)
    {
        current = current->next;
        current_index++;
    }

    if (current == nullptr)
    {
        throw std::out_of_range("index finns inte i listan");
    }

    return current->value;
}

