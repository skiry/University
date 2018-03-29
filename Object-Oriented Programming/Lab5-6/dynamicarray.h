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
    void resize();
    void operator-(T& el);
    int len() const {return this->length;};
};

#endif // DYNAMICARRAY_H
