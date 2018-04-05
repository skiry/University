#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

template <typename T>
class DynamicArray{
private:
    T* elems;
    int capacity;
    int length;
public:
    DynamicArray(int len = 15);
    DynamicArray(const DynamicArray& DA);
    //copy constructor

    DynamicArray& operator=(const DynamicArray& DA);
    ~DynamicArray();
    void add(T el);
    //add an element of type T in the DA

    T& operator[](int pos);
    void resize();
    //double the capacity of the DA

    void operator-(T& el);
    //delete el from the DA

    int len() const {return this->length;};
    //length getter
};

#endif // DYNAMICARRAY_H
