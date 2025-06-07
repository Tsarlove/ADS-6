// Copyright 2025 NNTU-CS
#include <string>
#include <sstream>
#include <cctype>
#include <stdexcept>

// Простая реализация шаблонного стека
template<typename T, int size>
class TStack {
 private:
  T arr[size];
  int topIndex;

 public:
  TStack() : topIndex(-1) {}

  void push(const T& val) {
    if (topIndex < size - 1) arr[++topIndex] = val;
  }

  void pop() {
    if (topIndex >= 0) --topIndex;
  }

  T top() const {
    if (topIndex >= 0) return arr[topIndex];
    throw std::out_of_range("stack is empty");
  }

  bool empty() const {
    return topIndex == -1;
  }
};

int priority(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> stack;
  std::string res;
  for (size_t i = 0; i < inf.size(); ++i) {
    if (isdigit(inf[i])) {
      while (i < inf.size() && isdigit(inf[i])) {
        res += inf[i];
        ++i;
      }
      res += ' ';
      --i;
    } else if (inf[i] == '(') {
      stack.push('(');
    } else if (inf[i] == ')') {
      while (!stack.empty() && stack.top() != '(') {
        res += stack.top();
        res += ' ';
        stack.pop();
      }
      if (!stack.empty()) stack.pop();
    } else if (inf[i] == '+' || inf[i] == '-' || inf[i] == '*' || inf[i] == '/') {
      while (!stack.empty() &&
             priority(stack.top()) >= priority(inf[i])) {
        res += stack.top();
        res += ' ';
        stack.pop();
      }
      stack.push(inf[i]);
    }
  }
  while (!stack.empty()) {
    res += stack.top();
    res += ' ';
    stack.pop();
  }
  if (!res.empty() && res.back() == ' ') res.pop_back();
  return res;
}

int eval(const std::string& post) {
  TStack<int, 100> stack;
  std::istringstream iss(post);
  std::string token;
  while (iss >> token) {
    if (isdigit(token[0])) {
      stack.push(std::stoi(token));
    } else {
      int b = stack.top(); stack.pop();
      int a = stack.top(); stack.pop();
      switch (token[0]) {
        case '+': stack.push(a + b); break;
        case '-': stack.push(a - b); break;
        case '*': stack.push(a * b); break;
        case '/': stack.push(a / b); break;
      }
    }
  }
  return stack.top();
}

struct SYM {
  char ch{};
  int prior{};

  explicit SYM(char c) : ch(c), prior(0) {}
  SYM(char c, int p) : ch(c), prior(p) {}
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
