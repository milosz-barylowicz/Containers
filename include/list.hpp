#pragma once

#include <functional>
#include <limits>
#include <optional>
#include <ostream>
#include <initializer_list>

namespace containers {

template <typename T>
class list {
 private:
  template <typename N>
  struct Node {
    N data;
    Node* next;
  };

 public:
  // definition of member types
  using size_type = size_t;
  using iterator = Node<T>*;
  using const_iterator = const Node<T>*;
  using value_type = T;
  using reference_type = std::reference_wrapper<T>;

  // definition of basic methods
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

  void assign(size_type count, const T& value) {
    remove_all_elements();
    for (size_type i = 0; i < count; ++i) {
      push_back(value);
    }
  }

  void assign(const std::initializer_list<T>& args) {
    remove_all_elements();

    for (const auto& arg : args) {
      push_back(arg);
    }
  }

  // definition of elemnets access
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

  // definition of iterators
  iterator begin() const {
    if (not m_head) {
      return nullptr;
    }

    return m_head;
  }

  const_iterator cbegin() const {
    if (not m_head) {
      return nullptr;
    }

    return m_head;
  }

  iterator end() const {
    if (not m_tail) {
      return nullptr;
    }

    return m_tail;
  }

  const_iterator cend() const {
    if (not m_tail) {
      return nullptr;
    }

    return m_tail;
  }

  // definition of modifiers
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

  void push_front(const T& value) {
    iterator temp = new Node<T>();
    temp->data = value;
    temp->next = m_head;
    m_size++;

    m_head = temp;
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

  void clear() { remove_all_elements(); }

  size_type size() const { return m_size; }

  bool empty() const { return m_size == 0; }

  size_type max_size() const { return std::numeric_limits<size_t>::max(); }

  void resize(size_type count) {
    if (count > m_size) {
      size_type size = count - m_size;
      for (size_type i = 0; i < size; ++i) {
        push_back(0);
      }

      return;
    }

    iterator temp = m_head;
    for (size_type i = 0; i < count; ++i) {
      temp = temp->next;
    }

    iterator toDelete = temp;
    while (toDelete and toDelete != m_tail) {
      iterator next = toDelete->next;
      delete toDelete;
      toDelete = next;
    }

    m_tail = temp;
    m_size = count;
  }

  void resize(size_type count, const T& value) {
    if (count > m_size) {
      size_type size = count - m_size;
      for (size_type i = 0; i < size; ++i) {
        push_back(value);
      }

      return;
    }

    iterator temp = m_head;
    for (size_type i = 0; i < count; ++i) {
      temp = temp->next;
    }

    iterator toDelete = temp;
    while (toDelete and toDelete != m_tail) {
      iterator next = toDelete->next;
      delete toDelete;
      toDelete = next;
    }

    m_tail = temp;
    m_size = count;
  }

  void swap(list<T>& other) {
    iterator tempHead = other.m_head;
    iterator tempTail = other.m_tail;
    size_type size = other.m_size;

    other.m_head = m_head;
    other.m_tail = m_tail;
    other.m_size = m_size;

    m_head = tempHead;
    m_tail = tempTail;
    m_size = size;
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
  size_type m_size{0};
};

}  // namespace containers
