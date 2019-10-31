//Camryn Buonamassa
//default constructor
template <typename T>
my_unique_ptr<T>::my_unique_ptr(){
	uptr = nullptr;
}

//constructor with data
template <typename T>
my_unique_ptr<T>::my_unique_ptr(T* data){
	uptr = data;
}

//move constructor
template <typename T>
my_unique_ptr<T>::my_unique_ptr(my_unique_ptr<T> && ptr){
	uptr = ptr.uptr;
	ptr.uptr = nullptr;
}

//move assignment
template <typename T>
my_unique_ptr<T>& my_unique_ptr<T>::operator=(my_unique_ptr<T> && ptr){
	if(&ptr != this){ //checks if we are moving pointer into itself
		delete uptr; //deallocating memory uptr points to
		uptr = ptr.uptr; //transfer lvalue pointer to rvalue pointer
		ptr.uptr = nullptr; //set lvalue pointer to null
		return *this;
	}
	return *this;
}

//destructor
template <typename T>
my_unique_ptr<T>::~my_unique_ptr(){
	if(uptr != nullptr){
		delete uptr;
		uptr = nullptr;
	}
}

//-> operator
template <typename T>
T* my_unique_ptr<T>::operator->(){
	return uptr;
}

//* operator
template <typename T>
T& my_unique_ptr<T>::operator*(){
	//check if ptr is nullptr
	if(uptr == nullptr){
		//throw exception 
		throw "Pointer points to null and cannot be dereferenced.";
	}
	else{
		//return dereferenced pointer
		return *uptr;
	}
}

//isNullptr function
template <typename T>
bool my_unique_ptr<T>::isNullptr(){
	//returns true if pointer points to null
	return (uptr == nullptr);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~SHARED

//default constructor
template <typename T>
my_shared_ptr<T>::my_shared_ptr(){
	sptr = nullptr;
	count = nullptr;
}

//constructor with data
template <typename T>
my_shared_ptr<T>::my_shared_ptr(T* data){
	sptr = data;
	if(sptr != nullptr){
		count = new int{1};
	}
	else{
		count = nullptr;
	}
}

//copy constructor
template <typename T>
my_shared_ptr<T>::my_shared_ptr(const my_shared_ptr<T> & ptr){
	if(ptr.sptr == nullptr){
		sptr = ptr.sptr;
	}
	sptr = ptr.sptr;
	count = ptr.count;
	if(sptr != nullptr){	
		*count+=1;
	}
}

//copy assignment 
template <typename T>
my_shared_ptr<T>& my_shared_ptr<T>::operator=(const my_shared_ptr<T> & ptr){
	if(&ptr == this){
		return *this;
	}	
	else if(sptr == nullptr || count == nullptr){
		sptr = ptr.sptr;
		count = ptr.count;
		if(count != nullptr){
			*count+=1;
		}
	}
	else if(*count == 1){
		T* temp = sptr; //using temp here to try and fix issues with heae->next
		int* temp1 = count;
		sptr = ptr.sptr;
		count = ptr.count;
		delete temp;
		delete temp1;
		temp = nullptr;
		temp1 = nullptr;
	}
	else if (*count > 1){
		*count-=1;
		sptr = ptr.sptr;
		count = ptr.count;
	}
	return *this;
}

//move constructor
template <typename T>
my_shared_ptr<T>::my_shared_ptr(my_shared_ptr<T> && ptr){
	sptr = ptr.sptr;
	count = ptr.count;
	ptr.sptr = nullptr;
	ptr.count = nullptr;
}

//move assignment
template <typename T>
my_shared_ptr<T>& my_shared_ptr<T>::operator=(my_shared_ptr<T> && ptr){
	if(&ptr == this){ //checks if we are moving pointer into itself
		return *this;
	} 
	else if(count == nullptr){
		sptr = ptr.sptr;
		count = ptr.count;
		ptr.sptr = nullptr;
		ptr.count = nullptr;
	}
	else if(*count <= 1){ //we are the only pointer pointing to memory block, so we have to delete it before taking the new memory
		T* tempPtr{sptr}; 
		int* tempCount{count}; 
		sptr = ptr.sptr; 
		count = ptr.count; 
		ptr.sptr = nullptr;
		ptr.count = nullptr;
		delete tempPtr;
		delete tempCount;
	}
	else if(*count > 1){ //other pointers pointing to this memory block, so decrease count before taking new memory
		*count-=1;
		sptr = ptr.sptr;
		count = ptr.count;
		ptr.sptr = nullptr;
		ptr.count = nullptr;
	}
	return *this;
}

//destructor
template <typename T>
my_shared_ptr<T>::~my_shared_ptr(){
	if(count != nullptr){
		if(*count <= 1){ //if count is 1 or 0, we can release the memory
			delete sptr;
			delete count;
		}	
		else if(*count > 1){
			*count-=1;
		}
	sptr = nullptr;
	count = nullptr;
	}
}

//-> operator
template <typename T>
T* my_shared_ptr<T>::operator->(){
	return sptr;
}

//* operator
template <typename T>
T& my_shared_ptr<T>::operator*(){
	//check if ptr is nullptr
	if(sptr == nullptr){
		//throw exception 
		throw "Pointer points to null and cannot be dereferenced.";
	}
	else{
		//return dereferenced pointer
		return *sptr;
	}
}

//isNullptr function
template <typename T>
bool my_shared_ptr<T>::isNullptr(){
	//returns true if pointer points to null
	return (sptr == nullptr);
}

