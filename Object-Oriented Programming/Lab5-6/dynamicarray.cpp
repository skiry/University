#include "dynamicarray.h"
#include <utility>

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

template<typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& DA){
    this -> capacity = DA.capacity;
    this -> length = DA.length;
    this -> elems = new T[this -> capacity];
    for(int i = 0; i < DA.length; ++i)
        this -> elems[i] = DA.elems[i];

    return *this;
}

template <typename T>
void DynamicArray<T>::add(T el){
    if(this -> length == this -> capacity)
        this -> resize();
    this -> elems[this -> length++] = el;
}

template <typename T>
T& DynamicArray<T>::operator[](int pos){
    return this -> elems[pos];
}

template <typename T>
void DynamicArray<T>::resize(){
    this -> capacity *= 2;
    T* aux = new T[this -> capacity];
    for(int i = 0; i < this -> capacity / 2; ++i)
        aux[i] = this -> elems[i];
    this -> elems = aux;
    delete[] this -> elems;
}

template <typename T>
void DynamicArray<T>::operator-(T& el){
    for(int i = 0; i < this -> length; ++i)
        if(this -> elems[i] == el)
            std::swap(this -> elems[i], this -> elems[--(this -> length)]);
}
