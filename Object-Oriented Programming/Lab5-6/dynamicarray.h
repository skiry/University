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
    DynamicArray& operator=(const DynamicArray& DA);
    ~DynamicArray();
    void add(T el);
    T& operator[](int pos);
};

#endif // DYNAMICARRAY_H
