// Zach Duncan

#ifndef _STACK_HPP
#define _STACK_HPP

////////////////////CLASS Stack<T> DEFINITIONS/////////////////////

template <typename T>
Stack<T>::Stack() // default zero parameter constructor
{} //default vector already initialized

template <typename T>
Stack<T>::~Stack() // destructor
{ clear(); } // vector destrutor will be called to deallocate vector myStack

template <typename T>
Stack<T>::Stack(const Stack<T>& rhs) // copy constructor
{
  for (int i = 0; i < rhs.size(); i++)
    push( rhs.myStack[i] );
}

template <typename T>
Stack<T>::Stack(Stack<T> && rhs) // move constructor
{ myStack.swap(rhs.myStack); }

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T> & rhs) // copy assignment operator=
{
  Stack<T> copy = rhs;              // make copy of Stack<T>, swap, return this
  std::swap(*this, copy);
  return *this;
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack<T> && rhs)// move assignment operator=
{
  myStack.swap(rhs.myStack);
  return *this;
}

template <typename T>
bool Stack<T>::empty() const // true if empty, false otherwise
{ return myStack.empty(); }

template <typename T>
void Stack<T>::clear() // clears stack
{ myStack.clear(); }

template <typename T>
void Stack<T>::push(const T& x) // add x to stack -- copy version
{ myStack.push_back(x); }

template <typename T>
void Stack<T>::push(T && x) // add x to stack -- move version
{ myStack.push_back(std::move(x)); }

template <typename T>
void Stack<T>::pop() // remove and discard most recent item on stack
{ myStack.pop_back(); }

template <typename T>
T& Stack<T>::top() // returns reference to top element (modifiable L-value)
{ return myStack[ myStack.size() - 1 ]; }

template <typename T>
const T& Stack<T>::top() const // returns const reference to top of stack
{ return myStack[ myStack.size() - 1 ]; }

template <typename T>
int Stack<T>::size() const // returns num of elements stored in stack
{ return myStack.size(); }

// print elements of Stack to ostream os. ofc is the separator between elements
// in the stack when they are printed out. Note that print() prints elements in
// the opposite order of the Stack (that is, the oldest element should be printed first).
template <typename T>
void Stack<T>::print(std::ostream& os, char ofc) const
{
  //Use iterator
  if (myStack.size() == 0)              //If nothing to print
      os << "";
  else
  {
    auto itr = myStack.rbegin();
    auto itr2 = myStack.rend();
    while (itr != itr2)                 //Traverse through vector
    {
      os << *itr << ofc;
      itr++;                            //Update iterator to next
    }
  }
}

template <typename T>
typename std::vector<T>::const_iterator Stack<T>::GetIterator() const // return iterator to first item
{ return myStack.begin(); }

template <typename T>
typename std::vector<T>::const_iterator Stack<T>::GetIteratorEnd() const // return iterator to last item
{ return myStack.end(); }

/////////////////////////////STAND ALONE DEFINITIONS////////////////////////////

// invokes the print() method to print the Stack<T> a in the specified ostream
template <typename T>
std::ostream & operator<<(std::ostream &os, const Stack<T> &l)
{
  l.print(os);                //Call Stack<T> print function to do work
  return os;
}

// OVERLOADING COMPARISON OPERATORS

// returns true if the two compared Stacks have the same elements, in the same
// order, and false otherwise
template <typename T>
bool operator==(const Stack<T> & lhs, const Stack<T> &rhs)
{
  if (lhs.size() != rhs.size())
    return false;
  else
  {
    auto l_itr = lhs.GetIterator();
    auto l_ritr = lhs.GetIteratorEnd();
    auto r_itr = rhs.GetIterator();
    while (l_itr != l_ritr)   //Traverse through vector
    {
      if (*l_itr != *r_itr)
        return false;
      l_itr++;                //Update lhs iterator to next
      r_itr++;                //Update rhs iterator to next
    }
    return true;              //True if made it through while loop
  }
}

// opposite of operator==()
template <typename T>
bool operator!=(const Stack<T> & lhs, const Stack<T> &rhs)
{
  if (lhs.size() != rhs.size())
    return true;
  else
  {
    auto l_itr = lhs.GetIterator();
    auto l_ritr = lhs.GetIteratorEnd();
    auto r_itr = rhs.GetIterator();
    while (l_itr != l_ritr)   //Traverse through vector
    {
      if (*l_itr != *r_itr)
        return true;
      l_itr++;                //Update lhs iterator to next
      r_itr++;                //Update rhs iterator to next
    }
    return false;             //False if made it through while loop
  }
}

// returns true if every element in Stack a is smaller than or equal to the corresponding
// element of Stack b, i.e., if repeatedly invoking top() and pop() on both a and b,  we
// will generate a sequence of elements ai from a and bi from b, and for every i,  ai ≤ bi,
// until a is empty. (Note that this also means that a cannot have more elements than b for
// this condition to be true). Return false otherwise.
template <typename T>
bool operator<=(const Stack<T> & lhs, const Stack<T> &rhs)
{
  if (lhs.size() > rhs.size())
    return false;
  else
  {
    auto l_itr = lhs.GetIterator();
    auto l_ritr = lhs.GetIteratorEnd();
    auto r_itr = rhs.GetIterator();
    while (l_itr != l_ritr)   //Traverse through vector
    {
      if (*l_itr > *r_itr)
        return false;
      l_itr++;                //Update lhs iterator to next
      r_itr++;                //Update rhs iterator to next
    }
    return true;             //False if made it through while loop
  }
}

#endif
