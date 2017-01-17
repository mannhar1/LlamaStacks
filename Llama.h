#ifndef _LLAMA_H_
#define _LLAMA_H_

/*******************************
 File: Llama.h

 Project: CMSC 341 Project 1, fall 2016

 Author: Harrison Mann

 Date: 9/29/16

 Section: 4

 Email: mannhar1@umbc.edu

This is the header file for the Llama class in Project 1, it declares all
of the functions that will be implemented in the class


*********************************/



#include <stdexcept>
#include <string>
#include "LlamaNode.h"

using namespace std ;


class LlamaUnderflow : public std::out_of_range {
  
 public:
  
 LlamaUnderflow(const string& what) : std::out_of_range(what) { }
  
} ;


template <class T, int LN_SIZE>
  class Llama {
  
 public:
  
  Llama() ;
  Llama(const Llama<T,LN_SIZE>& other) ;   // copy constructor
  
  ~Llama() ;
    
  
  int size() ; 
  void dump() ;
  
  void push(const T& data) ;
  T pop() ;
  
  
  void dup() ;    //  (top) A B C D -> A A B C D
  void swap() ;   //  (top) A B C D -> B A C D 
  void rot() ;    //  (top) A B C D -> C A B D
  
  
  T peek(int offset) const ;
  
  
  // overloaded assignment operator
  //
  const Llama<T,LN_SIZE>& operator=(const Llama<T,LN_SIZE>& rhs) ;
  

 private:

  int arrSize;//basically LN_SIZE
  int itemsInArr;//number of items present in the last node that isnt empty
  int totalItems;//total number of items present in linked list

  LlamaNode<T, LN_SIZE>* frontPtr;
  LlamaNode<T, LN_SIZE>* endPtr;

  LlamaNode<T, LN_SIZE>* currentNode;

  LlamaNode<T, LN_SIZE>* cursor;
  LlamaNode<T, LN_SIZE>* insert;
  LlamaNode<T, LN_SIZE>* previous;


  
} ;


#include "Llama.cpp"


#endif
