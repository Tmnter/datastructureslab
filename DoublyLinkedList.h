#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include "Node.h"
#include <iostream>
#include <stdexcept>
#include <memory>

template <typename T>
class DoublyLinkedList {
private:
    std::shared_ptr<Node<T>> head;
    std::shared_ptr<Node<T>> tail;
    int listSize;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), listSize(0) {}

    int size() const { return listSize; }
    bool is_empty() const { return listSize == 0; }
    void push_front(T value) {
        auto newNode = std::make_shared<Node<T>>(value);
        if (is_empty()) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        listSize++;
    }

    void push_back(T value) {
        auto newNode = std::make_shared<Node<T>>(value);
        if (is_empty()) {
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        listSize++;
    }

    void insert_at(int index, T value) {
        if (index < 0 || index > listSize) throw std::out_of_range("Index out of bounds");
        if (index == 0) { push_front(value); return; }
        if (index == listSize) { push_back(value); return; }

        auto newNode = std::make_shared<Node<T>>(value);
        auto current = head;
        for (int i = 0; i < index; ++i) current = current->next;

        auto prevNode = current->prev.lock();

        newNode->next = current;
        newNode->prev = prevNode;
        prevNode->next = newNode;
        current->prev = newNode;

        listSize++;
    }
    void pop_front() {
        if (is_empty()) throw std::runtime_error("List is empty");
        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev.reset();
        }
        listSize--;
    }

    void pop_back() {
        if (is_empty()) throw std::runtime_error("List is empty");
        if (head == tail) {
            head = tail = nullptr;
        } else {
            tail = tail->prev.lock();
            tail->next = nullptr;
        }
        listSize--;
    }

    void remove_at(int index) {
        if (index < 0 || index >= listSize) throw std::out_of_range("Index out of bounds");
        if (index == 0) { pop_front(); return; }
        if (index == listSize - 1) { pop_back(); return; }

        auto current = head;
        for (int i = 0; i < index; ++i) current = current->next;

        auto prevNode = current->prev.lock();
        auto nextNode = current->next;

        prevNode->next = nextNode;
        nextNode->prev = prevNode;

        listSize--;
    }
    T at(int index) const {
        if (index < 0 || index >= listSize) throw std::out_of_range("Index out of bounds");
        auto current = head;
        for (int i = 0; i < index; ++i) current = current->next;
        return current->data;
    }

    int find(T value) const {
        auto current = head;
        int index = 0;
        while (current) {
            if (current->data == value) return index;
            current = current->next;
            index++;
        }
        return -1;
    }

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const DoublyLinkedList<U>& list) {
        auto current = list.head;
        os << "NULL <- ";
        while (current) {
            os << "[" << current->data << "]";
            if (current->next) os << " <-> ";
            current = current->next;
        }
        os << " -> NULL";
        return os;
    }
};

#endif
