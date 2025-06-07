// Copyright 2021 NNTU-CS

#pragma once

#include <iostream>

struct SYM {
    char ch;
    int prior;
};

template<typename T>
struct Node {
    explicit Node(const T& d) : data(d), next(nullptr) {}  // explicit constructor
    T data;
    Node* next;
};

template<typename T>
class TPQueue {
 public:
    TPQueue() : head(nullptr) {}
    ~TPQueue() {
        while (!isEmpty()) pop();
    }

    void push(const T& value) {
        Node<T>* newNode = new Node<T>(value);

        if (!head || value.prior > head->data.prior) {
            newNode->next = head;
            head = newNode;
        } else {
            Node<T>* current = head;
            while (current->next && current->next->data.prior >= value.prior) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    void pop() {
        if (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    const T& front() const {
        if (!head) throw std::runtime_error("Queue is empty");
        return head->data;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    void print() const {
        Node<T>* current = head;
        while (current) {
            std::cout << current->data.ch << "(" << current->data.prior << ") ";
            current = current->next;
        }
        std::cout << std::endl;
    }

 private:
    Node<T>* head;
};
