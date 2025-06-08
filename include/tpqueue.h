// Copyright 2025 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <stdexcept>

struct SYM {
  char ch;
  int prior;

  SYM() : ch('\0'), prior(0) {}
  explicit SYM(char c) : ch(c), prior(0) {} 
  SYM(char c, int p) : ch(c), prior(p) {}
};

template <typename T>
class TPQueue {
 private:
  struct Node {
    T data;
    Node* next;
    Node(const T& d) : data(d), next(nullptr) {}
  };

  Node* head = nullptr;

 public:
  TPQueue() = default;

  void push(const T& val) {
    Node* newNode = new Node(val);
    if (!head || val.prior > head->data.prior) {
      newNode->next = head;
      head = newNode;
    } else {
      Node* current = head;
      while (current->next && val.prior <= current->next->data.prior) {
        current = current->next;
      }
      newNode->next = current->next;
      current->next = newNode;
    }
  }

  T pop() {
    if (!head) throw std::out_of_range("Queue is empty");
    Node* temp = head;
    T result = head->data;
    head = head->next;
    delete temp;
    return result;
  }

  bool isEmpty() const {
    return head == nullptr;
  }

  T top() const {
    if (!head) throw std::out_of_range("Queue is empty");
    return head->data;
  }

  ~TPQueue() {
    while (head) {
      Node* temp = head;
      head = head->next;
      delete temp;
    }
  }
};

#endif  // INCLUDE_TPQUEUE_H_
