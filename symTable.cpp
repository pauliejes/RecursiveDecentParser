#include "symTable.h"
#include <iostream>
#include "general.h"
using namespace std;

Symbol_node::Symbol_node(char * id) {
    this->id = new char[strlen(id)+1];
  strcpy(this->id,id);
}

Symbol_node::~Symbol_node(void){}

void Symbol_node::putval(int val) {
  this->val = val;
} 

int Symbol_node::getval(void) {
  return this->val;
}

Symbol_node * Symbol_node::getNext() {
  return this->next;
}

void Symbol_node::setNext(Symbol_node * next) {
  this->next = next;
}

char * Symbol_node::getId() {
  return this->id;
}

void Symbol_node::setId(char * id) {
  this->id = id;
}

Symbol_table::Symbol_table(void)
{
  table = new Symbol_ptr[211];
  for (int i = 0; i < 211; ++i)
  {
    table[i] = 0;
  }
}

Symbol_table::~Symbol_table(void){

}

/* Description: 
    This function hashes the name of the symbol into a bucket number
  Input:
    The name (id) of the symbol to  hash
  Output:
    and integer between 0 - 211. The index of the bucket the variable belongs in
*/
unsigned int Symbol_table::hash(const char * str)
{
  unsigned int seed = 131; /* 31 131 1313 13131 131313 etc.. */ 
  unsigned int hash = 0;
  unsigned int i = 0; 

  int length = strlen(str);
  for (i = 0; i < length; ++str, ++i)
  {
    hash = (hash * seed) + (*str);
  }
  return hash % 211;
}


/* Description: 
    This function inserts a symbol into the table if it is not already present in the table
    then returns a pointer to the symbols location in memory
  Input:
    The name (id) of the symbol to find/insert
  Output:
    the pointer to where the symbol is located in memory
*/
Symbol_ptr Symbol_table::insert (char * name) 
{
 
  
  //check if the symbol is already in the table
  Symbol_ptr ptr = this->lookup(name);
  
  //if lookup returns null (ptr is null)
  //then insert into head of bucket
  if(!ptr){
    int hashVal = this->hash(name);
    Symbol_ptr new_node = new Symbol_node(name);
    new_node->setNext(this->table[hashVal]);
    this->table[hashVal] = new_node;
    ptr = new_node;
  }

  return ptr;
}

/* Description: 
    This function searches the symbol table for the symbol name it is given
  Input:
    The name (id) of the symbol to find
  Output:
    the pointer to where the symbol is located in memory if it is in the table.
    if the symbol is not found function returns a null pointer
*/
Symbol_ptr Symbol_table::lookup(char * name) 
{
  Symbol_ptr ptr = NULL;
  int hashVal = this->hash(name);
  //while loop vars
  Symbol_ptr cur_ptr = table[hashVal];
  bool found = false;

  //if the root of the bucket points to a node then travers the linked list
  //looking for the symbol
  while(cur_ptr != NULL && found == false) {
    //if this is the variable being looked for
    if(strcmp(cur_ptr->getId(), name) == 0) {
      found = true;
      ptr = cur_ptr;
    } 
    //if the variable is not this node, go to the next one
    else {
      cur_ptr = cur_ptr->getNext();
    }
  }

  return ptr;
}

/* Description: 
    Prints out all of the symbols in the symbol table organized by
    which bucket it is in
  Output:
    The full symbol table organized as described above
*/
void Symbol_table::dump_table() {
  cout << "============================"<<endl;

  Symbol_ptr ptrz = NULL;
  for (int i = 0; i < 211; ++i)
  {
    //if this bucket is empty
    if (this->table[i] == 0)
    {

    
    } 
    //if this bucket contains a list of symbols
    else {
    
      ptrz = this->table[i];
      do{
            
      	cout << ptrz->getId() << " = " << ptrz->getval() << endl;    
        ptrz = ptrz->getNext();
      }while(ptrz != 0);
    }
  }
  cout << "============================"<<endl;
}
