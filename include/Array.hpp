/*
 * Author: Milosz Barylowicz
 * Date:   2022-2023
 */

#pragma once

#include <optional>
#include <stdexcept>
#include <functional>

namespace containers
{

template<typename T, std::size_t element_count>
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

    Array(const std::initializer_list<T>& args)
    {
        m_size = args.size();
        m_data = new T[m_size];

        auto current = args.begin();
        int index = 0;
       
        while (current != args.end())
        {
            m_data[index] = *current;
            index++; current++;
        }
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
        m_data = std::move(other.m_data);
        m_size = std::move(other.m_size);
    }

    ~Array() noexcept
    {
        delete[] m_data;
    }

    Array <T, element_count>& operator=(const Array <T, element_count>& other)
    {
        m_size = other.m_size;
        delete[] m_data;
        m_data = new int[m_size];

        for (size_t i = 0; i < m_size; ++i)
        {
            m_data[i] = other.m_data[i];
        }

        return *this;
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

    T& operator[](size_t index) const
    {
        return m_data[index];
    }

    T& at(size_t index) const
    {
        if (not m_data or m_size == 0)
        {
            throw std::out_of_range("There are no data to access!");
        }

        return m_data[index];
    }

    T* data() const
    {
        if (not m_data or m_size == 0)
        {
            return nullptr;
        }

        return m_data;
    }

    std::optional<std::reference_wrapper<T>> front() const
    {
        if (not m_data or m_size == 0)
        {
            throw std::out_of_range("There is no data to access");
        }

        return m_data[0];
    }

    std::optional<std::reference_wrapper<T>> back() const
    {
        if (not m_data or m_size == 0)
        {
            throw std::out_of_range("There is no data to access");
        }

        return m_data[m_size - 1];
    }

    size_t size() const
    {
        return m_size;
    }

    size_t max_size() const
    {
        return std::numeric_limits<size_t>::max();
    }

    bool empty() const
    {
        return m_size == 0;
    }

    void fill(T value)
    {
        for (size_t i = 0; i < m_size; ++i)
        {
            m_data[i] = value;
        }
    }

private:
    T* m_data = nullptr;
    size_t m_size = element_count;
};

} // namespace containers
