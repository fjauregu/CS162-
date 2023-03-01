/**
 * @brief Assignment 6
 * @name Felipe Jauregui
 * */

#ifndef BAG_H
#define BAG_H

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <random>
#include <string>

template <typename T>
class Bag
{
public:
    Bag() :
        array{new T[10]}, capacity{10}
    {}

    Bag(const Bag& other) :
        array{new T[other.capacity]}, size{other.size}, capacity{other.capacity}
    {
        std::copy(other.array, other.array + other.size, this->array);
    }

    Bag& operator=(const Bag& rhs)
    {
        if (&rhs == this)
            return *this;

        delete[] this->array;

        this->array = new T[rhs.capacity];
        this->size = rhs.size;
        this->capacity = rhs.capacity;

        std::copy(rhs.array, rhs.array + rhs.size, this->array);

        return *this;
    }

    ~Bag()
    {
        delete[] this->array;
    }

    void addItem(const T& item)
    {
        if (this->size == this->capacity)
            expand();

        this->array[this->size++] = item;
    }

    bool contains(const T& item) const
    {
        return std::find(this->array, this->array + this->size, item) != this->array + this->size;
    }

    friend std::ostream& operator<<(std::ostream& lhs, const Bag& rhs)
    {
        lhs << '{';
        for (std::size_t i = 0; i < rhs.size; ++i)
        {
            lhs << rhs.array[i];
            if (i < rhs.size - 1)
                lhs << ", ";
        }
        lhs << '}';

        return lhs;
    }

    bool removeItem(const T& item)
    {
        T* const it = std::find(this->array, this->array + this->size, item);

        if (it != this->array + this->size)
        {
            std::swap(*it, this->array[this->size - 1]);
            --this->size;
            return true;
        }
        else
        {
            return false;
        }
    }

    bool isEmpty() const
    {
        return this->size == 0;
    }

    void dump()
    {
        this->size = 0;
    }

    int numberOf(const T& item)
    {
        int count = 0;

        for (std::size_t i = 0; i < this->size; ++i)
        {
            if (this->array[i] == item)
                ++count;
        }

        return count;
    }

    void removeAll(const T& item)
    {
        while (removeItem(item));
    }

    T pickRandom()
    {
        static std::random_device dev;
        std::mt19937 gen(dev());
        std::uniform_int_distribution<std::size_t> rand(0, this->size - 1);

        T result = this->array[rand(gen)];
        removeItem(result);

        return result;
    }

    void dumpInto(Bag<T>& other)
    {
        while (other.capacity < other.size + this->size)
        {
            other.expand();
        }

        std::copy(this->array, this->array + this->size, other.array + other.size);
        other.size += this->size;

        dump();
    }

    Bag<T> extractAll(const T& item)
    {
        Bag<T> result;

        const int count = numberOf(item);
        for (int i = 0; i < count; ++i)
        {
            result.addItem(item);
            removeItem(item);
        }

        return result;
    }
private:
    T* array = nullptr;
    std::size_t size = 0;
    std::size_t capacity = 0;

    void expand()
    {
        const T* const old = this->array;

        this->capacity *= 2;
        this->array = new T[this->capacity];

        std::copy(old, old + this->size, this->array);

        delete[] old;
    }
};

#endif // BAG_H

