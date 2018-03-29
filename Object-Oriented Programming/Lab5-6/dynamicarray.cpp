#include "dynamicarray.h"

template <typename T>
DynamicArray<T>::DynamicArray(int len){
    this -> capacity = len;
    this -> length = 0;
    this -> elems = new T[len];
}

template <typename T>
DynamicArray<T>::~DynamicArray(){
    delete[] this -> elems;
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& DA){
    this -> capacity = DA.capacity;
    this -> length = DA.length;
    this -> elems = new T[this -> capacity];
    for(int i = 0; i < DA.length; ++i)
        this -> elems[i] = DA.elems[i];
}

template <typename T>
void DynamicArray<T>::add(T el){
    this -> elems[length++] = el;
}

template <typename T>
T& DynamicArray<T>::operator[](int pos){
    return this -> elems[pos];
}

