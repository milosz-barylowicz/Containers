#pragma once

#include <limits>
#include <ostream>
#include <optional>
#include <functional>
#include <initializer_list>

namespace containers {

template<typename T>
class list {
private:
    template<typename N>
    struct Node {
        N data;
        Node* next;
    };

public:
    using size_type = size_t;
    using iterator = Node<T>*;
    using value_type = T;
    using reference_type = std::reference_wrapper<T>;

    list() = default;

    list(const list<T>& other) {
        iterator temp = other.m_head;
        while (temp) {
            push_back(temp->data);
            temp = temp->next;
        }
    }

    list(const list<T>&& other) {
        m_head = std::move(other.m_head);
        m_tail = std::move(other.m_tail);
        m_size = std::move(other.m_size);
    }

    list(const std::initializer_list<T>& args) {
        auto temp = args.begin();
        while (temp != args.end()) {
            push_back(*temp);
            temp++;
        }
    }

    list<T>& operator=(const list<T>& other) {
        iterator temp = other.m_head;
        while (temp) {
            push_back(temp->data);
            temp = temp->next;
        }

        return *this;
    }

    ~list() { remove_all_elements(); }

    friend bool operator==(const list<T>& lhs, const list<T>& rhs) {
        if (lhs.m_size != rhs.m_size) {
            return false;
        }

        iterator lhsTemp = lhs.m_head;
        iterator rhsTemp = rhs.m_head;

        while (lhsTemp and rhsTemp) {
            if (lhsTemp->data != rhsTemp->data) {
                return false;
            }

            lhsTemp = lhsTemp->next;
            rhsTemp = rhsTemp->next;
        }

        return true;
    }

    friend std::ostream& operator<<(std::ostream& os, const list<T>& list) {
        iterator temp = list.m_head;
        while (temp) {
            os << temp->data << " ";
            temp = temp->next;
        }
        os << std::endl;

        return os;
    }

    void push_back(const T& value) {
        m_size++;

        if (not m_head) {
            m_head = m_tail = new Node<T>();
            m_head->data = value;
            return;
        }

        iterator temp = new Node<T>();
        temp->data = value;

        m_tail->next = temp;
        m_tail = temp;
    }

    void pop_front() {
        if (not m_head) {
            return;
        }

        m_size--;
        iterator temp = m_head->next;
        delete m_head;
        m_head = temp;
    }

    void pop_back() {
        if (not m_head) {
            return;
        }

        iterator temp = m_head;
        while (temp and temp->next != m_tail) {
            temp = temp->next;
        }

        temp->next = nullptr;
        delete m_tail;
        m_size--;
        m_tail = temp;
    }

    void assign(size_type count, const T& value) {
        remove_all_elements();
        for (size_type i = 0; i < count; ++i) {
            push_back(value);
        }
    }

    std::optional<reference_type> front() const {
        if (not m_head) {
            return std::nullopt;
        }

        return m_head->data;
    }

    std::optional<reference_type> back() const {
        if (not m_head) {
            return std::nullopt;
        }

        return m_tail->data;
    }

    void clear() {
        remove_all_elements();
    }

    size_type size() const {
        return m_size;
    }

    bool empty() const {
        return m_size == 0;
    }

    size_type max_size() const {
        return std::numeric_limits<size_t>::max();
    }

private:
    void remove_all_elements() {
        while (m_head) {
            iterator temp = m_head->next;
            delete m_head;
            m_head = temp;
        }
        m_size = 0;
    }

    iterator m_head = nullptr;
    iterator m_tail = nullptr;
    size_type m_size {0};
};

} // namespace containers
