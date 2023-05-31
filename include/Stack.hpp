#pragma once

#include <optional>
#include <ostream>

namespace containers {

static constexpr size_t DEFAULT_STACK_SIZE = 0;
static constexpr size_t EMPTY = 0;

template<typename T>
class Stack {
public:
    Stack() noexcept = default;

    Stack(const Stack<T>& other) {
        CopyData(other);
    }

    virtual ~Stack() {
        delete[] m_data;
    }

    void operator=(const Stack<T>& other) {
        m_size = other.m_size;
        m_data = new T[m_size];

        for (size_t i = 0; i < m_size; ++i) {
            m_data[i] = other.m_data[i];
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Stack<T>& data) {
        os << "size: " << data.size() << ", elements: ";
        for (size_t i = 0; i < data.size(); ++i) {
            os << data.m_data[i] << " ";
        }
        return os;
    }

    friend bool operator!=(const Stack<T>& base, const Stack<T>& other) {
        if (other.m_size == base.m_size) {
            for (size_t i = 0; i < base.m_size; ++i) {
                if (base.m_data[i] != other.m_data[i]) {
                    return true;
                }
            }
            return false;
        }
        return true;
    }

    friend bool operator==(const Stack<T>& base, const Stack<T>& other) {
        if (other.m_size != base.m_size) {
            return false;
        }

        for (size_t i = 0; i < base.m_size; ++i) {
            if (base.m_data[i] != other.m_data[i]) {
                return false;
            }
        }
        return true;
    }

    void push(const T& value) {
        if (not m_data) {
            InsertWhenStackIsEmpty(value);
        }
        else {
            InsertWhenStackInNotEmpty(value);
        }
    }

    void emplace(const T&& value) {
        if (not m_data) {
            InsertWhenStackIsEmpty(value);
        }
        else {
            InsertWhenStackInNotEmpty(value);
        }
    }

    std::optional<std::reference_wrapper<T>> top() const {
        if (not m_data) {
            return std::nullopt;
        }

        return m_data[m_size - 1];
    }

    void swap(Stack<T>& other) {
        if (not m_data) {
            m_size = other.m_size;
            m_data = other.m_data;

            other.m_size = EMPTY;
            other.m_data = nullptr;
        }
        else {
            T* temp = other.m_data;
            size_t temp_size = other.m_size;

            other.m_data = m_data;
            other.m_size = m_size;

            m_data = temp;
            m_size = temp_size;
        }
    }

    bool empty() const {
        return m_size == EMPTY;
    }

    size_t size() const {
        return m_size;
    }

private:
    void CopyData(const Stack<T>& other) {
        m_size = other.m_size;
        m_data = new T[m_size];

        for (size_t i = 0; i < m_size; ++i) {
            m_data[i] = other.m_data[i];
        }
    }

    void InsertWhenStackIsEmpty(const T& value) {
        m_size++;
        m_data = new T[m_size];
        m_data[0] = value;
    }

    void InsertWhenStackInNotEmpty(const T& value) {
        T* temp = new T[m_size + 1];
        for (size_t i = 0; i < m_size; ++i) {
            temp[i] = m_data[i];
        }
        temp[m_size] = value;
        m_size++;

        delete[] m_data;
        m_data = temp;
    }

    T* m_data{nullptr};
    size_t m_size{DEFAULT_STACK_SIZE};
};

} // namespace containers
