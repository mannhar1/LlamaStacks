/*******************************
 File: Driver.cpp

 Project: CMSC 341 Project 1, fall 2016

 Author: Harrison Mann

 Date: 10/2/16

 Section: 4 

 Email: mannhar1@umbc.edu

This file runs the main driver for Project 1, it tests all the functions
and uses 2 different types (int and string) to test the templating of the
class


*********************************/

#include <iostream>
#include <string>
using namespace std ;

#include "Llama.h"

int main() {

  Llama<string, 4> S ;
  

  S.push("cdef") ;
  S.push("yzab") ;
  S.push("vwx") ;
  S.push("stu") ;

   
  S.push("pqr") ;
  S.push("mno") ;
  S.push("jkl") ;
  S.push("ghi") ;


  S.push("def") ;
  S.push("abc") ;


  S.dump();

  
  string s1 ; 

  cerr << "\n***** Pop Test *****\n" ;
  s1 = S.pop() ;
  cerr << "popped " << s1 << endl ;
  s1 = S.pop() ;
  cerr << "popped " << s1 << endl ;
  s1 = S.pop() ;
  cerr << "popped " << s1 << endl ;

  S.dump() ;  

  
  
  cerr << "\n***** Pop Test *****\n" ;
  s1 = S.pop() ;
  cerr << "popped " << s1 << endl ;
  s1 = S.pop() ;
  cerr << "popped " << s1 << endl ;

  S.dump() ;  

  
  

  cerr << "\n***** Pop Test *****\n" ;
  s1 = S.pop() ;
  cerr << "popped " << s1 << endl ;
  s1 = S.pop() ;
  cerr << "popped " << s1 << endl ;
  s1 = S.pop() ; 
  cerr << "popped " << s1 << endl ;
  s1 = S.pop() ;
  cerr << "popped " << s1 << endl ;
  

  S.dump() ;  


  cerr << "\n***** Pop Test *****\n" ;
  s1 = S.pop() ;
  cerr << "popped " << s1 << endl ;
  try{
    s1 = S.pop() ;
    cerr << "popped " << s1 << endl ;
  }catch(LlamaUnderflow &e){

    cerr <<"\n" << "****************************" << endl;
    cerr << e.what() << endl;
    cerr << "****************************\n" << endl;

  }



  cerr << "\n***** Dup Exception Test *****\n" ;

  try{
    S.dup();
  }catch(LlamaUnderflow &e){

    cerr <<"\n" << "****************************" << endl;
    cerr << e.what() << endl;
    cerr << "****************************\n" << endl;
    
  }



  S.dump();

  cerr << "\n***** Push test *****\n" ;
  cerr << "push pqr" << endl;
  cerr << "push mno" << endl;
  cerr << "push jkl" << endl;
  cerr << "push ghi" << endl;
  cerr << "push def" << endl;
  cerr << "push abc" << endl;


  S.push("pqr") ;
  S.push("mno") ;
  S.push("jkl") ;
  S.push("ghi") ;


  S.push("def") ;
  S.push("abc") ;


  S.dump();
  

  cerr << "\n***** Peek Test *****\n" ;
  
  s1 = S.peek(0) ;
  cerr << "peeked " << s1 << endl ;
  s1 = S.peek(1) ;
  cerr << "peeked " << s1 << endl ;
  s1 = S.peek(2) ;
  cerr << "peeked " << s1 << endl ;
  s1 = S.peek(3) ;
  cerr << "peeked " << s1 << endl ;
  s1 = S.peek(4) ;
  cerr << "peeked " << s1 << endl ;
  s1 = S.peek(5) ;
  cerr << "peeked " << s1 << endl ;


  try{
    s1 = S.peek(6) ;
    cerr << "peeked " << s1 << endl ;
  }catch(LlamaUnderflow &e){

    cerr <<"\n" << "****************************" << endl;
    cerr << e.what() << endl;
    cerr << "****************************\n" << endl;

  }
  try{
    s1 = S.peek(-1) ;
    cerr << "peeked " << s1 << endl ;
  }catch(LlamaUnderflow &e){

    cerr <<"\n" << "****************************" << endl;
    cerr << e.what() << endl;
    cerr << "****************************\n" << endl;

  }
  try{
    s1 = S.peek(7) ;
    cerr << "peeked " << s1 << endl ;
  }catch(LlamaUnderflow &e){

    cerr <<"\n" << "****************************" << endl;
    cerr << e.what() << endl;
    cerr << "****************************\n" << endl;

  }

  
  
  cerr << "\n***** Dup Test *****\n" ;

  S.dup();

  S.dump();



  cerr << "\n***** Push test *****\n" ;
  cerr << "push test1" << endl;
  cerr << "push test2" << endl;
  cerr << "push test3" << endl;
  cerr << "push test4" << endl;
  cerr << "push test5" << endl;
  cerr << "push test6" << endl;


  S.push("test1") ;
  S.push("test2") ;
  S.push("test3") ;
  S.push("test4") ;


  S.push("test5") ;
  S.push("test6") ;


  S.dump();


  cerr << "\n***** Swap Test *****\n" ;

  S.swap();

  S.dump();


  cerr << "\n***** Pop Test *****\n" ;
  s1 = S.pop() ;
  cerr << "popped " << s1 << endl ;
  s1 = S.pop() ;
  cerr << "popped " << s1 << endl ;


  S.dump();



  cerr << "\n***** Rot Test *****\n" ;

  S.rot();
  
  S.dump();


  cerr << "\n***** Copy Constructor Test *****\n" ;

  Llama<string, 4> S2(S);

  S2.dump();

  

  cerr << "\n***** Pop Test *****\n" ;
  cerr << "Items will be popped from newly copy constructed stack" << endl;
  s1 = S2.pop() ;
  cerr << "popped " << s1 << endl ;
  s1 = S2.pop() ;
  cerr << "popped " << s1 << endl ;
  s1 = S2.pop() ;
  cerr << "popped " << s1 << endl ;
  s1 = S2.pop() ;
  cerr << "popped " << s1 << endl ;
  s1 = S2.pop() ;
  cerr << "popped " << s1 << endl ;
  s1 = S2.pop() ;
  cerr << "popped " << s1 << endl ;

  S2.dump();


  cerr << "\n***** Overloaded = Test *****\n" ;
  cerr << "List that was just popped from will now be set equal to the list it was initially constructed to" << endl;
  
  S2 = S;

  S2.dump();
  

  Llama<int, 7> I;

  cerr << "\n***** Push Test *****\n" ;

  I.push(523) ;
  I.push(235) ;
  I.push(234) ;
  I.push(736) ;


  I.push(864) ;
  I.push(913) ;
  I.push(724) ;
  I.push(426) ;


  I.push(503) ;
  I.push(19) ;

  cerr << "pushed 523" << endl;
  cerr << "pushed 235" << endl;
  cerr << "pushed 234" << endl;
  cerr << "pushed 736" << endl;
  cerr << "pushed 864" << endl;
  cerr << "pushed 913" << endl;
  cerr << "pushed 724" << endl;
  cerr << "pushed 426" << endl;
  cerr << "pushed 503" << endl;
  cerr << "pushed 19" << endl;


  I.dump();


  int i1 ;

  cerr << "\n***** Pop Test *****\n" ;
  i1 = I.pop() ;
  cerr << "popped " << i1 << endl ;
  i1 = I.pop() ;
  cerr << "popped " << i1 << endl ;
  i1 = I.pop() ;
  cerr << "popped " << i1 << endl ;
  i1 = I.pop() ;
  cerr << "popped " << i1 << endl ;
  i1 = I.pop() ;
  cerr << "popped " << i1 << endl ;


  I.dump() ;


  cerr << "\n***** Dup Test *****\n" ;

  I.dup();

  I.dump();



  cerr << "\n***** Push Test *****\n" ;

  I.push(3485) ;
  I.push(91) ;
  I.push(1237) ;
  I.push(572) ;


  I.push(6034) ;
  I.push(858) ;
  I.push(2000) ;
  I.push(12111) ;


  I.push(239) ;
  I.push(12) ;

  cerr << "pushed 3485" << endl;
  cerr << "pushed 91" << endl;
  cerr << "pushed 1237" << endl;
  cerr << "pushed 572" << endl;
  cerr << "pushed 6034" << endl;
  cerr << "pushed 858" << endl;
  cerr << "pushed 2000" << endl;
  cerr << "pushed 12111" << endl;
  cerr << "pushed 239" << endl;
  cerr << "pushed 12" << endl;


  I.dump();



  cerr << "\n***** Swap Test *****\n" ;

  I.swap();

  I.dump();

  
  cerr << "\n***** Rot Test *****\n" ;

  I.rot();

  I.dump();

  
  

  return 0 ;


}
