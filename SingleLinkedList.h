#ifndef SINGLE_LINKED_LIST_H
#define SINGLE_LINKED_LIST_H

#include "Node.h"
#include <iostream>
#include <stdexcept>
#include <memory>

template <typename T>
class SingleLinkedList {
private:
    std::shared_ptr<Node<T>> head;
    int listSize;

public:
    SingleLinkedList() : head(nullptr), listSize(0) {}

    int size() const { return listSize; }
    bool is_empty() const { return head == nullptr; }
};

#endif
