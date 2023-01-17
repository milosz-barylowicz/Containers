/*
 * Author: Milosz Barylowicz
 * Date:   2023
 */

#pragma once


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

    Vector(const Vector<T>& other)
    {
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        m_data = new T[m_capacity];

        for (size_t i = 0; i < m_size; ++i)
        {
            m_data[i] = other.m_data[i];
        }
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
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        delete[] m_data;
        m_data = new T[m_capacity];

        for (size_t i = 0; i < m_size; ++i)
        {
            m_data[i] = other.m_data[i];
        }

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
    size_t m_size{};
    size_t m_capacity{10};
    T* m_data = nullptr;
};

} // namespace containers
