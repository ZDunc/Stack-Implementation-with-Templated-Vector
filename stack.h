// Zach Duncan

#ifndef _STACK_H
#define _STACK_H

#include <iostream>
#include <vector>

namespace stack_namespace{

template <typename T>
class Stack {
  public:
    Stack(); // zero-arg constructor
    ~Stack(); // desctructor
    Stack(const Stack<T> &); // copy constrcutor
    Stack(Stack<T> &&); // move constructor
    Stack<T>& operator=(const Stack<T> &); // copy assignment operator
    Stack<T>& operator=(Stack<T> &&); // move assignment operator

    bool empty() const; //returns ture if the Stack contains no elements, false otherwise
    void clear(); // delete all elements from the Stack
    void push(const T& x); // adds x to the Stack -- copy version
    void push(T && x); //adds x to the Stack -- move version
    void pop(); // removes and discards the most recetly added element of the Stack
    T& top(); // returns a reference to the most recently added element of the Stack
              // (as a modifiable L-value)
    const T& top() const; // accessor that returns the most recently added element of
                          // the Stack (as a const reference)
    int size() const; // returns the number of elements stored in the Stack
    void print(std::ostream& os, char ofc = ' ') const; // print elements of Stack
          // to ostream os. ofc is the separator between elements in the stack when
          // they are printed out. Note that print() prints elements in the opposite order
          // of the Stack (that is, the oldest element should be printed first).

    // Added Functions
    typename std::vector<T>::const_iterator GetIterator() const;  // return iterator to first item
    typename std::vector<T>::const_iterator GetIteratorEnd() const; // return iterator to last item

  private:
    std::vector<T> myStack;
};

// overloading output operator
template <typename T>
  std::ostream & operator<<(std::ostream &os, const Stack<T> &l);

// overloading comparison operators
template <typename T>
  bool operator==(const Stack<T> & lhs, const Stack<T> &rhs);

template <typename T>
  bool operator!=(const Stack<T> & lhs, const Stack<T> &rhs);

template <typename T>
  bool operator<=(const Stack<T> & lhs, const Stack<T> &rhs);

#include "stack.hpp"

} // end of namespace stack_namespace


#endif
