/*
 * Author: Milosz Barylowicz
 * Date:   2023
 */

#pragma once

#include <iostream>

namespace containers
{

template <typename T>
class Vector
{
public:
    Vector()
    {
        m_data = new T[m_capacity];
    }

    Vector(const std::initializer_list<T>& args)
    {
        m_capacity = args.size();
        m_data = new T[m_capacity];

        for (const auto& arg : args)
        {
            push_back(arg);
        }
    }

    ~Vector()
    {
        delete[] m_data;
    }

    T& operator[](size_t index)
    {
        return m_data[index];
    }

    void push_back(const T& value)
    {
        if (m_size == m_capacity)
        {
            m_capacity = m_capacity * 10;
            T* temp = new T[m_capacity];

            for (size_t i = 0; i < m_size; ++i)
            {
                temp[i] = m_data[i];
            }

            delete[] m_data;
            m_data = temp;
        }

        m_data[m_size] = value;
        m_size++;
    }

    size_t size() const
    {
        return m_size;
    }

private:
    T* m_data = nullptr;
    size_t m_size{};
    size_t m_capacity{10};
};

} // namespace containers
