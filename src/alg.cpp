// Copyright 2021 NNTU-CS

#include <iostream>

struct SYM {
    char ch;
    int prior;
};

template<typename T>
struct Node {
    explicit Node(const T& d) : data(d), next(nullptr) {}
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

int main() {
    TPQueue<SYM> pqueue;
    pqueue.push({'a', 4});
    pqueue.push({'b', 7});
    pqueue.push({'c', 1});

    while (!pqueue.isEmpty()) {
        SYM c = pqueue.front();
        std::cout << c.ch << "(" << c.prior << ") ";
        pqueue.pop();
    }
    std::cout << std::endl;
    return 0;
}

struct SYM {
  char ch;
  int prior;

  SYM(char c = 0, int p = 0) : ch(c), prior(p) {}
};

template <typename T>
class TPQueue {
 private:
  static const int SIZE = 100;
  T data[SIZE];
  int count;

 public:
  TPQueue() : count(0) {}

  void push(const T& val) {
    int i = count - 1;
    while (i >= 0 && val.prior >= data[i].prior) {
      data[i + 1] = data[i];
      --i;
    }
    data[i + 1] = val;
    ++count;
  }

  T pop() {
    if (count == 0) throw std::out_of_range("Queue is empty");
    return data[--count];
  }

  bool isEmpty() const {
    return count == 0;
  }

  T top() const {
    if (count == 0) throw std::out_of_range("Queue is empty");
    return data[count - 1];
  }
};
