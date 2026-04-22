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
    void push_front(T value) {
        auto newNode = std::make_shared<Node<T>>(value);
        newNode->next = head;
        head = newNode;
        listSize++;
    }

    void push_back(T value) {
        auto newNode = std::make_shared<Node<T>>(value);
        if (is_empty()) {
            head = newNode;
        } else {
            auto current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
        listSize++;
    }

    void insert_at(int index, T value) {
        if (index < 0 || index > listSize) throw std::out_of_range("Index out of bounds");
        if (index == 0) { push_front(value); return; }

        auto newNode = std::make_shared<Node<T>>(value);
        auto current = head;
        for (int i = 0; i < index - 1; ++i) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
        listSize++;
    }
};

#endif
