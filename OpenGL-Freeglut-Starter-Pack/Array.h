#ifndef Array
#define Array

#include "main.h"

template <typename T>
class CArray {
    int ArrayCapacity = 0;
    int CollectionSize = 0;
    T* Collection = nullptr;

    const int ResizeMultiplier = 4;

    void Resize() {
        ArrayCapacity = (ArrayCapacity == 0) ? 1 : ArrayCapacity * ResizeMultiplier;
        T* CollectionTemp = new T[ArrayCapacity];

        for (int i = 0; i < CollectionSize; i++) {
            CollectionTemp[i] = std::move(Collection[i]);
        }

        delete[] Collection;
        Collection = CollectionTemp;
    }

public:
    CArray() {
        ArrayCapacity = 1;
        Collection = new T[ArrayCapacity];
    }

    CArray(const CArray& other) {
        ArrayCapacity = other.Capacity;
        CollectionSize = other.CollectionSize;
        Collection = new T[ArrayCapacity];
        for (int i = 0; i < CollectionSize; i++) {
            Collection[i] = other.Collection[i];
        }
    }

    CArray& operator=(const CArray& other) {
        if (this != &other) {
            delete[] Collection;
            ArrayCapacity = other.Capacity;
            CollectionSize = other.CollectionSize;
            Collection = new T[ArrayCapacity];
            for (int i = 0; i < CollectionSize; i++) {
                Collection[i] = other.Collection[i];
            }
        }
        return *this;
    }

    ~CArray() {
        delete[] Collection;
    }

    void Append(const T& value) {
        if (ArrayCapacity == CollectionSize) {
            Resize();
        }
        Collection[CollectionSize] = value;
        CollectionSize++;
    }

    T& operator[](int index) {
        if (index < 0 || index >= CollectionSize)
            throw std::out_of_range("operator[]: index out of range");
        return Collection[index];
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= CollectionSize)
            throw std::out_of_range("operator[]: index out of range");
        return Collection[index];
    }

    T& GetReference(int index) {
        if (index < 0 || index >= CollectionSize)
            throw std::out_of_range("GetRef: index out of range");
        return Collection[index];
    }

    const T& GetReference(int index) const {
        if (index < 0 || index >= CollectionSize)
            throw std::out_of_range("GetRef: index out of range");
        return Collection[index];
    }

    T* Data() const {
        if (CollectionSize == 0) return nullptr;

        T* copy = new T[CollectionSize];
        for (int i = 0; i < CollectionSize; i++) {
            copy[i] = Collection[i];
        }
        return copy;
    }

    void Remove(int index) {
        if (index >= 0 && index < CollectionSize) {
            for (int i = index; i < CollectionSize - 1; i++) {
                Collection[i] = Collection[i + 1];
            }
            CollectionSize--;
        }
    }

    int Size() const {
        return CollectionSize;
    }

    bool Empty() const {
        return CollectionSize == 0;
    }

    int Capacity() const {
        return ArrayCapacity;
    }

    void Clear() {
        CollectionSize = 0;
    }

    void Reserve(int capacity) {
        if (capacity > ArrayCapacity) {
            T* newCollection = new T[capacity];
            for (int i = 0; i < CollectionSize; i++) {
                newCollection[i] = std::move(Collection[i]);
            }
            delete[] Collection;
            Collection = newCollection;
            ArrayCapacity = capacity;
        }
    }
};

#endif
