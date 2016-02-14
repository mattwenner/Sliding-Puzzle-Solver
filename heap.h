#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>
#include <iostream>

template <typename T, typename Comparator >
class Heap
{
 public:
  /// Constructs an m-ary heap for any m >= 2
  Heap(int m, Comparator c);

  /// Destructor as needed
  ~Heap();

  /// Adds an item
  void push(const T& item);

  /// returns the element at the top of the heap 
  ///  max (if max-heap) or min (if min-heap)
  T const & top() const;

  /// Removes the top element
  void pop();

  /// returns true if the heap is empty
  bool empty() const;

  //allows us to output heap contents
  void printHeap() const;

 private:
  /// Add whatever helper functions and data members you need below
 	std::vector <T> myArray;
 	void bubbleUp(int pos);
 	void trickleDown(int pos);
 	int m;
 	Comparator comp;

};

//Constructor
template<typename T, typename Comparator>
Heap<T, Comparator>::Heap(int m, Comparator c) {
	this->m=m;
	comp=c;

}
//Destructor
template<typename T, typename Comparator>
Heap<T,Comparator>::~Heap(){}

// Add implementation of member functions here


// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename Comparator>
T const & Heap<T,Comparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    throw std::logic_error("can't top an empty heap");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return myArray[0];

}

// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename Comparator>
void Heap<T,Comparator>::pop()
{
  if(empty()){
    throw std::logic_error("can't pop an empty heap");
  }
  myArray[0]=myArray.back();
  myArray.pop_back();
  trickleDown(0);
}

template<typename T, typename Comparator>
void Heap<T,Comparator>::trickleDown(int pos){
	//index of left child
	int child=m*pos+1;
	//index that will switch with pos
	int finalChild=child;
	if(child>=myArray.size()){//done trickling down
		return;
	}	
		for(int i=1; i<m; i++){
			//make comparison
			if(child+i<myArray.size()&&comp(myArray[child+i], myArray[child])){
				finalChild=child+i;
			}
		}
		//switch contents
		if(comp(myArray[finalChild], myArray[pos])){
			T temp=myArray[finalChild];
			myArray[finalChild]=myArray[pos];
			myArray[pos]=temp;
			trickleDown(finalChild);

		}
	
}

template<typename T, typename Comparator>
bool Heap<T, Comparator>::empty() const{
	return myArray.empty();
}

//adding new item
template<typename T, typename Comparator>
void Heap<T, Comparator>::push(const T& item){
	myArray.push_back(item);
	bubbleUp(myArray.size()-1);
}
template<typename T, typename Comparator>
void Heap<T, Comparator>::bubbleUp(int pos){
	//if pos=0, them we are at the top
	if(pos>0&&comp(myArray[pos], myArray[(pos-1)/m])){
		//need to continue bubbling up
		T parent=myArray[(pos-1)/m];
		T temp=myArray[pos];
		myArray[pos]=parent;
		myArray[(pos-1)/m]=temp;
		
		bubbleUp((pos-1)/m);

	}
}

//allows for output of heap contents
template<typename T, typename Comparator>
void Heap<T, Comparator>::printHeap() const{
	
	for(unsigned int i=0; i<myArray.size(); i++){
		std::cout<<myArray[i]<<std::endl;
	}
}
#endif

