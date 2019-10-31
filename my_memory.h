//Camryn Buonamassa
#include <iostream>
#ifndef MYPOINTERS
#define MYPOINTERS

template <typename T>
struct my_unique_ptr{
	private:
		T* uptr;
	public:
		//default constructor
		my_unique_ptr();
		//default constructor with data
		my_unique_ptr(T* data);
		//disabling copy constructor
		my_unique_ptr(const my_unique_ptr<T> &) = delete;
		//disabling copy assignment
		my_unique_ptr & operator=(const my_unique_ptr<T> &) = delete;
		//move constructor
		my_unique_ptr(my_unique_ptr<T> && ptr);
		//move assignment
		my_unique_ptr & operator=(my_unique_ptr<T> && ptr);
		//destructor
		~my_unique_ptr();
		//-> operator
		T* operator->();
		//* operator
		T& operator*();
		//isNullptr function
		bool isNullptr();
};

template <typename T>
struct my_shared_ptr{
	private:
		T* sptr;
		int* count;
	public:
		//default constructor
		my_shared_ptr();
		//default constructor with data
		my_shared_ptr(T* data);
		//copy constructor
		my_shared_ptr(const my_shared_ptr<T> & ptr);
		//copy assignment
		my_shared_ptr & operator=(const my_shared_ptr<T> & ptr);
		//move constructor
		my_shared_ptr(my_shared_ptr<T> && ptr);
		//move assignment
		my_shared_ptr & operator=(my_shared_ptr<T> && ptr);
		//destructor
		~my_shared_ptr();
		//-> operator
		T* operator->();
		//* operator
		T& operator*();
		//isNullptr function
		bool isNullptr();
};

#include "my_memory.cpp"
#endif
