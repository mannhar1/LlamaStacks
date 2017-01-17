#ifndef _LLAMA_CPP_
#define _LLAMA_CPP_

/*******************************
 File: Llama.cpp

 Project: CMSC 341 Project 1, fall 2016

 Author: Harrison Mann

 Date: 9/29/16

 Section: 4

 Email: mannhar1@umbc.edu

This is the cpp file for the Llama class in Project 1, it implements
all of the functions of the stack as well as a copy constructor, overloaded
equals operator, and destructor


*********************************/


#include <stdexcept>
#include <string>
#include <iostream>
#include "LlamaNode.h"
#include "Llama.h"

using namespace std ;



template <class T, int LN_SIZE> 
Llama<T,LN_SIZE>::Llama() {
  arrSize = LN_SIZE;
  itemsInArr = 0;
  totalItems = 0;
  
  frontPtr = new LlamaNode<T, LN_SIZE>;
  endPtr = frontPtr;

  currentNode = frontPtr;

  cursor = NULL;
  insert = NULL;
  previous = NULL;
}



template <class T, int LN_SIZE> 
Llama<T,LN_SIZE>::Llama(const Llama<T,LN_SIZE>& other){   // copy constructor

  arrSize = other.arrSize;//final value for arrSize
  itemsInArr = other.itemsInArr;//final value for itemsInArr
  totalItems = other.totalItems;//final value for totalItems

  cursor = NULL;
  insert = NULL;
  previous = NULL;


  int totalCounter = totalItems; //will be used to know when to stop adding elements

  //int numNodes = other.frontPtr->newCount - other.frontPtr->deleteCount;
  int numNodes = 1;
  cursor = other.frontPtr;
  while(cursor->m_next){
    numNodes = numNodes + 1;
    cursor = cursor->m_next;
  }


  for (int i = 0; i < numNodes; i++){
    cursor = other.frontPtr;//cursor will increment through other's LL to the matching node to the one we are creating

    for (int k = 0; k < i; k++){
      cursor = cursor->m_next;
    }
    

    
    insert = new LlamaNode<T, LN_SIZE>;

    if (i == 0){
      frontPtr = insert;//final value for frontPtr
    }
    

    for (int j = 0; j < arrSize; j++){//will add all of the elements of other's array into the host
      if (totalCounter > 0){//if all of the items in the whole LL have already been added, we dont add any more, just leave the arrays empty
	insert->arr[j] = cursor->arr[j];

	totalCounter = totalCounter - 1;//keeps track of total elements added
      }
    }


    cursor = NULL;
    cursor = frontPtr;

    while(cursor->m_next != NULL){
      cursor = cursor->m_next;
    }//cursor is moved to the current last node in the list, so we can link insert in


    if (i != 0){//if weve already added the first node
      cursor->m_next = insert;
    
    }
    cursor = NULL;
    insert = NULL;
    
  } 

  cursor = NULL;
  cursor = frontPtr;

  while(cursor->m_next != NULL){
    cursor = cursor->m_next;
  }//cursor is moved to the current last node in the list so we can attatch endPtr to it

  
  endPtr = cursor;//final value for endPtr;

  cursor = NULL;
  


  //this if else sets the location of currentNode (either the final node, or the one before the final node)
  if (other.currentNode == other.endPtr){
    currentNode = endPtr;//possible final value for currentNode
  }else{
    cursor = frontPtr;
    while (cursor->m_next != endPtr){
      cursor = cursor->m_next;
    }
    currentNode = cursor;//other possible final value for currentNode
  }


  cursor = NULL;//final value for cursor
  insert = NULL;//final value for insert
  previous = NULL;//final value for previous


}



template <class T, int LN_SIZE> 
Llama<T,LN_SIZE>::~Llama() {

  cursor = frontPtr;
  
  while(cursor != NULL){
    previous = cursor;
    cursor = cursor->m_next;
    delete previous;
  }
  
  cursor = NULL;
  previous = NULL;
  insert = NULL;
  frontPtr = NULL;
  endPtr = NULL;
  currentNode = NULL;


}


template <class T, int LN_SIZE> 
int Llama<T,LN_SIZE>::size() {
  return totalItems;
}

template <class T, int LN_SIZE> 
void Llama<T,LN_SIZE>::dump() {

  previous = NULL;
  cursor = NULL;

  cerr << "LN_SIZE = " << arrSize << endl;
  cerr << "# of items in the stack = " << totalItems << endl;
  frontPtr->report();
  
  //int numNodes = frontPtr->newCount - frontPtr->deleteCount;
  int numNodes = 1;
  cursor = frontPtr;
  while(cursor->m_next){
    numNodes = numNodes + 1;
    cursor = cursor->m_next;
  }
  
  cursor = NULL;

  int maxItems = numNodes * arrSize;
  if (maxItems - totalItems >= arrSize){//if the linked list has an "extra" node
    cerr << "\nThis stack has an extra node: " << endPtr  << ".\n"  << endl;

    cerr << "Stack contents, top to bottom" << endl;
    if (totalItems == 0){//if there are no items present, just print empty
      cerr << "EMPTY" << endl;
    }else{//otherwise print the items from the top of LL excluding unused node
      cursor = frontPtr;
      previous = endPtr;//this will be the stopping point each time so we know which node to print out
      for (int i = 0; i < numNodes - 1; i++){
	cursor = frontPtr;
	while (cursor->m_next != previous){
	  cursor = cursor->m_next;//cursor keeps moving to the next node until its one before the final "empty" node
	  
	}
	previous = cursor;//we now set previous to cursor so next time through the loop it finds the next node down to print
	cerr << "----- " << cursor << " -----" << endl;
	if(cursor->m_next == endPtr){//if we are printing the last used node, we need to print a particular number of items

	  for (int j = itemsInArr - 1; j >= 0; j--){//starting at the top of the last used node, we move down to index 0
            cerr << cursor->arr[j] << endl;
	  }
	  
	  
	}else{//otherwise we know the node has LN_SIZE number of elements in it

	  for (int j = arrSize - 1; j >= 0; j--){
	    cerr << cursor->arr[j] << endl;
	  }

	}
      }
    }
    
  }else{//if the linked list does not have an "extra" node
    cerr << "\nThis stack does not have an extra node.\n" << endl;

    cerr << "Stack contents, top to bottom" << endl;

    cerr << "----- " << endPtr << " -----" << endl;//prints endPtr first because it may have a variable number of elements as it's last used node
    for (int i = itemsInArr - 1; i >= 0; i--){//starting at the top of the last used node, we move down to index 0
      cerr << endPtr->arr[i] << endl;
    }

    //now that weve already printed the last node, we just print the rest of them which we know how many elements they hold
    cursor = frontPtr;
    previous = endPtr;//this will be the stopping point each time so we know which node to print out
    for (int i = 0; i < numNodes - 1; i++){
      cursor = frontPtr;
      while (cursor->m_next != previous){
	cursor = cursor->m_next;//cursor keeps moving to the next node until its one before the final "empty" node

      }
      previous = cursor;//we now set previous to cursor so next time through the loop it finds the next node down to print
      cerr << "----- " << cursor << " -----" << endl;

      for (int j = arrSize - 1; j >= 0; j--){//prints contents of array of each node
	cerr << cursor->arr[j] << endl;
      }
    }
  }
  previous = NULL;
  cursor = NULL;



}



template <class T, int LN_SIZE> 
void Llama<T,LN_SIZE>::push(const T& data) {


  
  T copy = data;
  previous = NULL;
  cursor = NULL;
  insert = NULL;

  itemsInArr = itemsInArr + 1;
  totalItems = totalItems + 1;

  if (itemsInArr > arrSize){//if adding an item will make us move out of index of the array
    itemsInArr = 1;//restart with the next array
    if (currentNode == endPtr){
      insert = new LlamaNode<T, LN_SIZE>;
      endPtr->m_next = insert;
      endPtr = insert;
      currentNode = insert;//adds a new node to the list if there wasnt an extra already
    }else{
      currentNode = currentNode->m_next;//if there was an extra node, just move to that one
    }
  }
  
  currentNode->arr[itemsInArr - 1] = copy;//add the data to the array


  previous = NULL;
  cursor = NULL;
  insert = NULL;

}



template <class T, int LN_SIZE> 
T Llama<T,LN_SIZE>::pop() {

  cursor = NULL;
  
  T poppedItem;
  
  if (totalItems == 0){
    //should throw llama underflow exception
    throw LlamaUnderflow("\nPopped from an empty stack!\n");
    
  }else{

    if (itemsInArr - 1 < 0){//if we need to pop the element on the node previous to currentNode
      
      itemsInArr = arrSize;//itemsInArr becomes the max number it could be again because the next node down is currently full
      
      cursor = frontPtr;
      while(cursor->m_next != endPtr){
	cursor = cursor->m_next;
      }
      currentNode = cursor;//currentNode becomes the previous node
      
      poppedItem = currentNode->arr[itemsInArr - 1];//pop top item off of the previous node

      itemsInArr = itemsInArr - 1;
      totalItems = totalItems - 1;
      
    }else{

      poppedItem = currentNode->arr[itemsInArr - 1];//pop top item of currentNode

      itemsInArr = itemsInArr - 1;
      totalItems = totalItems - 1;
      

      if (itemsInArr <= arrSize / 2 && currentNode->m_next == endPtr){//if taking away an element will make the array half full and there is an extra node present
	
	currentNode->m_next = NULL;
	delete endPtr;
	endPtr = currentNode;

      }
    }
  }

  cursor = NULL;

  return poppedItem;

}



template <class T, int LN_SIZE> 
void Llama<T,LN_SIZE>::dup() {    //  (top) A B C D -> A A B C D

  if (totalItems == 0){
    //should throw llama underflow exception
    throw LlamaUnderflow("\nTried to dup an empty stack!\n");
  }else{
    T itemToDup = peek(0);
    push(itemToDup);

  }

}



template <class T, int LN_SIZE> 
void Llama<T,LN_SIZE>::swap() {   //  (top) A B C D -> B A C D 


  cursor = NULL;
  previous = NULL;

  if (totalItems < 2){
    //should throw llama underflow exception
    throw LlamaUnderflow("\nTried to swap a stack with less than 2 items!\n");
  }else{
    
    if (itemsInArr == 0 || currentNode->m_next == endPtr){//if there is an extra node
      cursor = frontPtr;
      while (cursor->m_next !=endPtr && cursor != endPtr){
	
	if(cursor->m_next->m_next == endPtr){
	  previous = cursor;
	}
	cursor = cursor->m_next;
      }//sets cursor to the node before the extra, and previous to the one before that, or leave previous as null if there are 2 or less nodes

      if(totalItems % arrSize == 1){//if there is only 1 item left in cursor, swap it with top item in previous
	T topStack = cursor->arr[0];
	cursor->arr[0] = previous->arr[arrSize - 1];
	previous->arr[arrSize - 1] = topStack;

      }else{//if there are 2 or more items left in cursor, swap the top 2
	int itemsInCursor = totalItems % arrSize;
	if (itemsInCursor == 0){//if the array is full
          itemsInCursor = arrSize;
        }
	T topStack = cursor->arr[itemsInCursor - 1];
	cursor->arr[itemsInCursor - 1] = cursor->arr[itemsInCursor - 2];
	cursor->arr[itemsInCursor - 2] = topStack;
      }
    }else{//there isnt an extra node
      
      cursor = frontPtr;
      while(cursor->m_next != endPtr && cursor != endPtr){
	cursor = cursor->m_next;
      }//sets cursor to the node before currentNode if there is one, and otherwise just leaves it at frontPtr
      
      if (itemsInArr == 1){//if there is only one item in currentNode, we swap it with the item on the top of the array in cursor
	T topStack = currentNode->arr[0];
	currentNode->arr[0] = cursor->arr[arrSize - 1];
	cursor->arr[arrSize - 1] = topStack;
      }else{//if there is 2 or more items in currentNode, just swap the top 2
	T topStack = currentNode->arr[itemsInArr - 1];
	currentNode->arr[itemsInArr - 1] = currentNode->arr[itemsInArr - 2];
	currentNode->arr[itemsInArr - 2] = topStack;
      }
      
    }
    
    
  }
  
  cursor = NULL;
  previous = NULL;

}




template <class T, int LN_SIZE> 
void Llama<T,LN_SIZE>::rot() {    //  (top) A B C D -> C A B D

  cursor = NULL;
  previous = NULL;

  if (totalItems < 3){
    //should throw llama underflow exception
    throw LlamaUnderflow("\nTried to rotate a stack with less than 3 items!\n");
  }else{

    if (itemsInArr == 0 || currentNode->m_next == endPtr){//if there is an extra node

      cursor = frontPtr;
      while (cursor->m_next !=endPtr && cursor != endPtr){

	if(cursor->m_next->m_next == endPtr){
	  previous = cursor;
	}
	cursor = cursor->m_next;
      }//sets cursor to the node before the extra, and previous to the one before that, or leave previous as null if there are 2 or less nodes
  
      if(totalItems % arrSize == 1){//if there is only 1 item left in cursor, rotate it with the top 2 items in previous
        T top = cursor->arr[0];
	T second = previous->arr[arrSize - 1];
	cursor->arr[0] = previous->arr[arrSize - 2];
	previous->arr[arrSize - 1] = top;
	previous->arr[arrSize - 2] = second;

      }else if(totalItems % arrSize == 2){//if there are only 2 items left in cursor, rotate them with the top item in previous
	T top = cursor->arr[1];
        T second = cursor->arr[0];
        cursor->arr[1] = previous->arr[arrSize - 1];
        cursor->arr[0] = top;
        previous->arr[arrSize - 1] = second;

      }
      else{//if there are 3 or more items left in cursor, rotate them
        int itemsInCursor = totalItems % arrSize;
	if (itemsInCursor == 0){//if the array is full
	  itemsInCursor = arrSize;
	}
        T top = cursor->arr[itemsInCursor - 1];
        T second = cursor->arr[itemsInCursor - 2];
	cursor->arr[itemsInCursor - 1] = cursor->arr[itemsInCursor - 3];
	cursor->arr[itemsInCursor - 2] = top;
	cursor->arr[itemsInCursor - 3] = second;
      }
    }else{//there isnt an extra node

      cursor = frontPtr;
      while(cursor->m_next != endPtr && cursor != endPtr){
        cursor = cursor->m_next;
      }//sets cursor to the node before currentNode if there is one, and otherwise just leaves it at frontPtr

      if (itemsInArr == 1){//if there is only one item in currentNode, we rotate it with the top two items in cursor
	T top = currentNode->arr[0];
        T second = cursor->arr[arrSize - 1];
        currentNode->arr[0] = cursor->arr[arrSize - 2];
        cursor->arr[arrSize - 1] = top;
        cursor->arr[arrSize - 2] = second;

      }else if ( itemsInArr == 2){//if there are only two items in currentNode, we rotate them with the top item in cursor
	T top = currentNode->arr[1];
        T second = currentNode->arr[0];
        currentNode->arr[1] = cursor->arr[arrSize - 1];
        currentNode->arr[0] = top;
        cursor->arr[arrSize - 1] = second;

	
      }
      else{//if there are 3 or more items left in currentNode, we rotate them with each other
        T top = currentNode->arr[itemsInArr - 1];
	T second = currentNode->arr[itemsInArr - 2];
        currentNode->arr[itemsInArr - 1] = currentNode->arr[itemsInArr - 3];
        currentNode->arr[itemsInArr - 2] = top;
	currentNode->arr[itemsInArr - 3] = second;
      }

    }    
    
  }
  
  cursor = NULL;
  previous = NULL;

}




template <class T, int LN_SIZE> 
T Llama<T,LN_SIZE>::peek(int offset) const {

  LlamaNode<T, LN_SIZE>* traverse = frontPtr;  

  T peekedItem;

  if (offset > totalItems - 1 || offset < 0){
    //should throw llama underflow exception
    throw LlamaUnderflow("\nTried to peek at an index that isnt used!\n");

  }else{
    //find the difference of the total number of items and the index to be peeked
    int difference = totalItems - offset;
    int elementSeen = difference % arrSize;
    int nodesToTraverse = difference / arrSize;
    
    if (elementSeen == 0){//special case for peeking final element in the array
      nodesToTraverse = nodesToTraverse - 1;
      elementSeen = arrSize;
    }

    for(int i = 0; i < nodesToTraverse; i++){
      traverse = traverse->m_next;
    }//moves cursor to the correct node for the element to peek
    
    peekedItem = traverse->arr[elementSeen - 1];//finds the correct element to peek in that array

  }

  traverse = NULL;

  return peekedItem;
  
}






// overloaded assignment operator
//

template <class T, int LN_SIZE> 
const Llama<T,LN_SIZE>& Llama<T,LN_SIZE>::operator=(const Llama<T,LN_SIZE>& rhs) {

  if (frontPtr == rhs.frontPtr){//self assignment
    return *this;
  }
  

  cursor = frontPtr;

  while(cursor != NULL){
    previous = cursor;
    cursor = cursor->m_next;
    delete previous;
  }//deallocates old memory in host object

  cursor = NULL;
  previous = NULL;
  insert = NULL;
  frontPtr = NULL;
  endPtr = NULL;
  currentNode = NULL;


  arrSize = rhs.arrSize;//final value for arrSize
  itemsInArr = rhs.itemsInArr;//final value for itemsInArr
  totalItems = rhs.totalItems;//final value for totalItems

  int totalCounter = totalItems; //will be used to know when to stop adding elements

  //int numNodes = rhs.frontPtr->newCount - rhs.frontPtr->deleteCount;
  int numNodes = 1;
  cursor = rhs.frontPtr;
  while(cursor->m_next){
    numNodes = numNodes + 1;
    cursor = cursor->m_next;
  }



  for (int i = 0; i < numNodes; i++){
    cursor = rhs.frontPtr;//cursor will increment through other's LL to the matching node to the one we are creating

    for (int k = 0; k < i; k++){
      cursor = cursor->m_next;
    }



    insert = new LlamaNode<T, LN_SIZE>;

    if (i == 0){
      frontPtr = insert;//final value for frontPtr
    }


    for (int j = 0; j < arrSize; j++){//will add all of the elements of other's array into the host
      if (totalCounter > 0){//if all of the items in the whole LL have already been added, we dont add any more, just leave the arrays empty
        insert->arr[j] = cursor->arr[j];

        totalCounter = totalCounter - 1;//keeps track of total elements added
      }
    }


    cursor = NULL;
    cursor = frontPtr;

    while(cursor->m_next != NULL){
      cursor = cursor->m_next;
    }//cursor is moved to the current last node in the list, so we can link insert in


    if (i != 0){//if weve already added the first node
      cursor->m_next = insert;

    }
    cursor = NULL;
    insert = NULL;

  }

  cursor = NULL;
  cursor = frontPtr;

  while(cursor->m_next != NULL){
    cursor = cursor->m_next;
  }//cursor is moved to the current last node in the list so we can attatch endPtr to it


  endPtr = cursor;//final value for endPtr;

  cursor = NULL;



  //this if else sets the location of currentNode (either the final node, or the one before the final node)
  if (rhs.currentNode == rhs.endPtr){
    currentNode = endPtr;//possible final value for currentNode
  }else{
    cursor = frontPtr;
    while (cursor->m_next != endPtr){
      cursor = cursor->m_next;
    }
    currentNode = cursor;//other possible final value for currentNode
  }


  cursor = NULL;//final value for cursor
  insert = NULL;//final value for insert
  previous = NULL;//final value for previous

  return *this;


  
  
}



#endif
