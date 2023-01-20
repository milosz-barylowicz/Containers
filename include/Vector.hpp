/*
 * Author: Milosz Barylowicz
 * Date:   2023
 */

#pragma once

#include <iostream>
#include <optional>
#include <functional>

namespace containers
{

template <typename T>
class Vector
{
public:
    Vector() {}

    Vector(const Vector<T>& other)
    {
        CreateNewDataContainer_(other);
        CopyData_(other.m_data, m_data);
    }

    Vector(Vector<T>&& other)
    {
        m_data = other.m_data;
        other.m_data = nullptr;

        m_size = other.m_size;
        m_capacity = other.m_capacity;
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

    Vector<T>& operator=(const Vector<T>& other)
    {
        CreateNewDataContainer_(other);
        CopyData_(other.m_data, m_data);

        return *this;
    }

    ~Vector()
    {
        delete[] m_data;
    }

    friend bool operator==(const Vector<T>& lhs, const Vector<T>& rhs)
    {
        const auto size = lhs.size();
        if (size != rhs.size())
        {
            return false;
        }

        for (size_t i = 0; i < size; ++i)
        {
            if (lhs[i] != rhs[i])
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

    T& at(size_t index)
    {
        if (index >= m_size or not m_data)
        {
            throw std::out_of_range("Trying access data out of range");
        }

        return m_data[index];
    }

    void push_back(const T& value)
    {
        if (not m_data)
        {
            m_data = new T[m_capacity];
        }

        if (m_size == m_capacity)
        {
            m_capacity = m_capacity * 10;
            T* temp = new T[m_capacity];

            CopyData_(temp, m_data);

            delete[] m_data;
            m_data = temp;
        }

        m_data[m_size] = value;
        m_size++;
    }

    void emplace_back(const T&& value)
    {
        if (not m_data)
        {
            m_data = new T[m_capacity];
        }

        if (m_size == m_capacity)
        {
            m_capacity = m_capacity * 10;
            T* temp = new T[m_capacity];

            CopyData_(temp, m_data);

            delete[] m_data;
            m_data = temp;
        }

        m_data[m_size] = std::move(value);
        m_size++;
    }

    void pop_back()
    {
        if (m_data)
        {
            m_size--;
        }
    }

    size_t size() const
    {
        return m_size;
    }

    size_t capacity() const
    {
        return m_capacity;
    }

    bool empty() const
    {
        return m_size == 0;
    }

    T* begin() const
    {
        return m_data;
    }

    std::optional<std::reference_wrapper<T>> front() const
    {
        if (not m_data or m_size == 0)
        {
            return std::nullopt;
        }

        return m_data[0];
    }

    T* end() const
    {
        if (not m_data)
        {
            return nullptr;
        }

        return m_data + (m_size - 1);
    }

    std::optional<std::reference_wrapper<T>> back() const
    {
        if (not m_data or m_size == 0)
        {
            return std::nullopt;
        }

        return m_data[m_size - 1];
    }

private:
    void CopyData_(const T* src, T* dest)
    {
        for (size_t i = 0; i < m_size; ++i)
        {
            dest[i] = src[i];
        }
    }

    void CreateNewDataContainer_(const Vector<T>& other)
    {
        m_size = other.m_size;
        m_capacity = other.m_capacity;

        if (m_data)
        {
            delete[] m_data;
        }
        m_data = new T[m_capacity];
    }


    size_t m_size{};
    size_t m_capacity{10};
    T* m_data = nullptr;
};

} // namespace containers
