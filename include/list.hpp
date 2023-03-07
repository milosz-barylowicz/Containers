#pragma once

namespace containers {

template<typename T>
class List {
public:
	List() = default;
	~List() {
        while (m_head and m_head != m_tail) {
            Node<T>* temp = m_head->next;
            delete m_head;
            m_head = temp;
        }

        delete m_head;
	}

    friend bool operator==(const List<T>& lhs, const List<T>& rhs)
    {
        const auto& size = lhs.m_size;
        if (size != rhs.m_size)
        {
            return false;
        }

        for (size_t i = 0; i < size; ++i)
        {
            Node<T>* left = lhs.m_head;
            Node<T>* right = rhs.m_head;

            if (left->data != right->data)
            {
                return false;
            }
        }

        return true;
    }

    friend std::ostream& operator<<(std::ostream& os, const List<T>& other) {
        Node<T>* temp = other.m_head;
        while (temp != other.m_tail) {
            os << temp->data << " ";
            temp = temp->next;
        }
        os << std::endl;

        return os;
    }

	void push_back(const T& value) {
        Node<T>* temp = new Node<T>();
        temp->data = value;
        m_size++;

        if (not m_head) {
            m_head = m_tail = temp;
            return;
        }

        if (m_head == m_tail) {
            m_head->next = temp;
        }
        m_tail = temp;
    }

	void pop_back() {
        if (not m_head) {
            return;
        }

        if (m_head == m_tail) {
            delete m_head;
            m_size--;
            return;
        }

        Node<T>* temp = m_head;
        while (temp->next->next) {
            temp = temp->next;
        }

        delete m_tail;
        m_tail = temp;
        m_tail->next = nullptr;
        m_size--;
    }

    size_t size() const { return m_size; }
    bool empty() const { return m_size == 0; }
    const T& back() const { return m_tail->data; }
private:
	template <typename N>
	struct Node {
		N data;
		Node* next;
	};

	Node<T>* m_head = nullptr;
	Node<T>* m_tail = nullptr;
    size_t m_size = 0;
};

} // namespace containers
