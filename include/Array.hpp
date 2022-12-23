/*
 * Author: Milosz Barylowicz
 * Date:   2022
 */

#pragma once

namespace containers
{

template<typename T, size_t size>
class Array
{
public:
    Array()
    {
        m_size = size;
        m_data = new T[m_size];

        for (size_t i = 0; i < m_size; ++i)
        {
            m_data[i] = 0;
        }
    }

    Array(std::initializer_list<T> args)
    {
        m_size = size;
        m_data = new T[m_size];

        for (size_t i = 0; i < m_size; ++i)
        {
            m_data[i] = args[i];
        }
    }

    Array(const Array<T>& other)
    {
        m_size = other.m_size;
        m_data = new T[m_size];

        for (size_t i = 0; i < m_size; ++i)
        {
            m_data[i] = other.m_data[i];
        }
    }

    Array(const Array<T>&& other)
    {
        m_size = other.m_size;
        m_data = new T[m_size];

       for (size_t i = 0; i < m_size; ++i)
       {
           m_data[i] = other.m_data[i];
       }
    }

    ~Array()
    {
        delete[] m_data;
    }

    T& operator[](size_t index)
    {
        return m_data[index];
    }

    friend bool operator==(const T& other) const
    {
        if (other.m_size != m_size)
        {
            return false;
        }

        for (size_t i = 0; i < m_size; ++i)
        {
            if (m_data[i] != other.m_data[i])
            {
                return false;
            }
        }
        return true;
    }

    size_t size() const
    {
        return m_size;
    }

private:
    T* m_data = nullptr;
    size_t m_size = size;
};

} // namespace containers
