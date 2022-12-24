/*
 * Author: Milosz Barylowicz
 * Date:   2022
 */

#pragma once

namespace containers
{

template<typename T, size_t element_count>
class Array
{
public:
    Array()
    {
        m_data = new T[m_size];

        for (size_t i = 0; i < m_size; ++i)
        {
            m_data[i] = 0;
        }
    }

    Array(std::initializer_list<T> args)
    {
        m_data = new T[element_count];

        for (const auto& arg : args)
        {
            m_data[m_current] = arg;
        }

        T* a = new T[100000];
    }

    Array(const Array<T, element_count>& other)
    {
        m_data = new T[m_size];

        for (size_t i = 0; i < m_size; ++i)
        {
            m_data[i] = other.m_data[i];
        }
    }

    Array(const Array<T, element_count>&& other)
    {
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

    friend bool operator==(const Array<T, element_count>& lhs, const Array<T, element_count>& rhs)
    {
        for (size_t i = 0; i < element_count; ++i)
        {
            if (lhs.m_data[i] != rhs.m_data[i])
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
    size_t m_size = element_count;
    size_t m_current = {};
};

} // namespace containers
