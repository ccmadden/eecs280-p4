#ifndef LIST_HPP
#define LIST_HPP
/* List.hpp
 *
 * doubly-linked, double-ended list with Iterator interface
 * EECS 280 Project 4
 */

#include <iostream>
#include <iterator> //std::bidirectional_iterator_tag
#include <cassert>  //assert

//why can a public function access private variables

template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:

  //constructor 
  //edit: unsure why this made a difference but i j chnaged the constructor format

  List(){
    first = nullptr;
    last = nullptr;
    list_size = 0;
  }

  //copy constructor 
  List(const List &other) { 
    first = nullptr; 
    copy_all(other);
  }

  List& operator= (const List &rhs) { 
    
    if (this == &rhs) { 
      //list_size = rhs.list_size;
      return *this;
    }
    clear(); 
    copy_all(rhs);
    list_size = rhs.list_size;
    return *this;
  }

  //destructor
  ~List() { 
    clear();
    
  }

  //EFFECTS:  returns true if the list is empty
  bool empty() const { 
    return first == nullptr;
  }

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow. Instead, keep track of the size
  //         with a private member variable. That's how std::list does it.
  int size() const {
    return list_size;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T & front() { 
    assert(!empty());
    return first->datum;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T & back() { 
    assert(!empty());
    return last->datum;
  }

  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum) { 
    Node *at_front = new Node; //create a new node that will be the new first
    at_front->datum = datum;
     //assign its datum
     if(empty()){
      first = at_front;
      last = at_front;
      // edit since there is only one element, make the next and prev = nullptr
      at_front->next = nullptr;
      at_front->prev = nullptr;
    }
    else{
      // edit
      // doubel check push_back aswell for this
    at_front -> prev = nullptr;
    first-> prev = at_front;
    at_front->next = first; //assign the next node to be the original first node
    first = at_front; //update first so now it points to the new first
    }
    list_size++;
  }

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum) {
    // address leak
      Node *at_back = new Node;
      at_back->datum = datum;
      // edit cosnider if its empty
      if (empty()) {
          first = at_back;
          last = at_back;
          // edit since there is only one element, make the next and prev = nullptr
          at_back->next = nullptr;
          at_back->prev = nullptr;
      } else {
          // create a new node that will be the new last
          // assign its datum
          //  edit: need to make at_front-> next the nullptr
          at_back->next = nullptr;
          last->next = at_back;
          at_back->prev = last;  // assign the previous node to be the original last node
          last = at_back;        // update last so now it points to the new last
      }
      list_size++;
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
  // edit: dont need to make new node, creating some issues
  void pop_front() { 
    assert(!empty());
    // account for previous pointers
    Node *target = first; 
    first = first->next;
    // if list only has one 
    if (first == nullptr){
      last = nullptr;
    }
    else {
      first -> prev = nullptr;
    }
    //?? causing issues but idk why
   //first->prev = nullptr;
    delete target;
    list_size--;
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
  void pop_back() { 

    // edit: there is something wrong with this she is saying
    // that is causing a memory leak
    // doubel check the pops and pushes for memory leaks
    assert(!empty());
    Node *target = last; 
    last = last->prev; 
    if (last == nullptr){
      first = nullptr;
    }
    else {
      last -> next = nullptr;
    }
    //last->next = nullptr;
    delete target;
    list_size--;
  }

  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes all items from the list
  void clear() {
    while (!empty()) { 
      pop_front();
    }
  }

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you should omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists.

private: 
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other) { 
    assert(empty()); 
    list_size = 0;
    Node *last = nullptr;
    for (Node *p = other.first; p != nullptr; p = p->next) { 
      list_size++;
      Node *q = new Node; 
      q->datum = p->datum; 
      q->next = nullptr; 
      if (last ==nullptr) { 
        first = last = q; 
      } else { 
        last->next = q; 
        last = q;
      }
    }
  }

  int list_size; //number of elements in list
  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty

public:
  ////////////////////////////////////////
  class Iterator {
  public:
    //OVERVIEW: Iterator interface to List

    // Add a default constructor here. The default constructor must set both
    // pointer members to null pointers.
    Iterator(){
      list_ptr = nullptr;
      node_ptr = nullptr;

    } 

    friend class List; //COME BACK TO THIS: do i put this here??

    // Add custom implementations of the destructor, copy constructor, and
    // overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you should omit them. A user
    // of the class must be able to copy, assign, and destroy Iterators.
    
    // Your iterator should implement the following public operators:
    // *, ++ (both prefix and postfix), == and !=.
    // Equality comparisons must satisfy the following rules:
    // - two default-constructed iterators must compare equal
    // - a default-constructed iterator must compare unequal to an
    //   iterator obtained from a list, even if it is the end iterator
    // - two iterators to the same location in the same list must
    //   compare equal
    // - two iterators to different locations in the same list must
    //   compare unequal
    // - comparing iterators obtained from different lists results in
    //   undefined behavior
    //   - Your implementation can handle this however you like, but
    //     don't assume any particular behavior in your test cases --
    //     comparing iterators from different lists essentially
    //     violates the REQURES clause.
    // Note: comparing both the list and node pointers should be
    // sufficient to meet these requirements.
    T& operator* () const { //want to modify value returned
      assert(node_ptr);
      return node_ptr->datum;
    }

    Iterator& operator++() { //prefix
      assert(list_ptr);
      if (node_ptr) { 
        node_ptr = node_ptr->next;
      } else { 
        node_ptr = list_ptr->first;
      }
      return *this;
    }

    Iterator operator++(int /*dummy*/) { //postfix
    //  THIS DOESNT WORK IDK WHY
      Iterator copy = *this;
      operator++();
      return copy;
    }

//edit: wanna use the dot operator here versus the arrow becuase you 
// want the pointer not the value
    bool operator== (const Iterator& rhs) const { 
     if(node_ptr == rhs.node_ptr){
      if(list_ptr == rhs.list_ptr){
        return true;
      }
     }
      return false;
    }
  

    bool operator!= (const Iterator &rhs) const { 
      if (node_ptr != rhs.node_ptr) { 
        return true;
      } else if (list_ptr != rhs.list_ptr) { 
        return true; 
      }
      return false;
    }

    // Type aliases required to work with STL algorithms. Do not modify these.
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    // This operator will be used to test your code. Do not modify it.
    // REQUIRES: Iterator is either dereferenceable or an end Iterator
    // EFFECTS:  moves this Iterator to point to the previous element
    //           and returns a reference to this Iterator
    Iterator& operator--() { // prefix -- (e.g. --it)
      assert(list_ptr);
      if (node_ptr) {
        node_ptr = node_ptr->prev;
      } else { // decrementing an end Iterator moves it to the last element
        node_ptr = list_ptr->last;
      }
      return *this;
    }

    // This operator will be used to test your code. Do not modify it.
    // REQUIRES: Iterator is either dereferenceable or an end Iterator
    // EFFECTS:  moves this Iterator to point to the previous element
    //           and returns a copy of the original Iterator
    Iterator operator--(int /*dummy*/) { // postfix -- (e.g. it--)
      Iterator copy = *this;
      operator--();
      return copy;
    }

    // REQUIRES: Iterator is dereferenceable
    // EFFECTS: returns the underlying element by pointer
    // NOTE: T must be a class type to use the syntax it->. If T has a
    //       member variable f, then it->f accesses f on the
    //       underlying T element.
    T* operator->() const {
      return &operator*();
    }

  private:
    const List *list_ptr; //pointer to the List associated with this Iterator
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here


    // add any friend declarations here

    // construct an Iterator at a specific position in the given List
    Iterator(const List *lp, Node *np) { 
      list_ptr = lp; 
      node_ptr = np;

    }

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const { 
    Iterator  i(this, first);
    return i;
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const { 
    // edit: end it at null pointer
    Iterator i(this, nullptr);
    return i;
  }

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container.
  //         Returns An iterator pointing to the element that followed the
  //         element erased by the function call
  
Iterator erase(Iterator i){
   if (i.node_ptr == first){
     pop_front();
     return begin();
   }
   // make it to the nullptr??
   else if (i.node_ptr == last){
     pop_back();
     return end();
   }
   else{
     Node* previousValue = i.node_ptr->prev;
     Node* nextValue = i.node_ptr->next;
     // the next value for the previous should become the deleted's next
    previousValue->next = nextValue;
    // the previous value should be the deleted's prev
   nextValue->prev = previousValue;
   delete i.node_ptr;
   list_size--;
   return Iterator(this, nextValue);
   }
 }


  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: Inserts datum before the element at the specified position.
  //         Returns an iterator to the the newly inserted element.

  // do special base if its the last
  // anolgous thing for erase aswell
  Iterator insert(Iterator i, const T &datum) { 
    if (i.node_ptr == first) { 
      push_front(datum);
      return Iterator(this,first);
    }
    else if(i.node_ptr == nullptr){
      push_back(datum);
      return Iterator(this,last);
    }
    
    else {
      Node *inserted = new Node;
      inserted->next = i.node_ptr;
      inserted->prev = i.node_ptr->prev;
      i.node_ptr->prev->next = inserted;
      i.node_ptr->prev = inserted;
      inserted->datum = datum;
      list_size++;
      return Iterator(this,inserted);
    }
  }

};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.


#endif // Do not remove this. Write all your code above this line.