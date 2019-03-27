#include<ctype.h>
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<cstring>

#ifndef SYM_NODE
#define SYM_NODE
class Symbol_node {
	friend class Symbol_table;
	public:
		Symbol_node(char * id);
		~Symbol_node(void);
		//void putval(VALUE);
		void putval(int);
		//VALUE getval(void);
		int getval(void);
		Symbol_node * getNext();
		void setNext(Symbol_node * next);
		char * getId();
		void setId(char * id);
	private:
		char * id;
		//int token;
		//VALUE value;
		int val;
		Symbol_node * next;
};
#endif
typedef Symbol_node * Symbol_ptr;
#ifndef SYM_TABLE
#define SYM_TABLE
class Symbol_table {
	public:
		Symbol_table(void);
		~Symbol_table(void);
		//hash function
		unsigned int hash(const char * str);
		//insert something into the table
		Symbol_ptr insert (char * name);
		//void remove(char *);
		//find the variable and return a pointer to it
		Symbol_ptr lookup(char * name);
		void dump_table(void);
		//int table_size = 211;
	private:
		Symbol_ptr *table;
};
#endif
