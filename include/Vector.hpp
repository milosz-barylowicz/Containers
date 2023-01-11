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
		// TODO: add resize if needed
		m_data[m_size] = value;
		m_size++;
	}

private:
	T* m_data = nullptr;
	size_t m_size{};
	size_t m_capacity{10};
};

} // namespace containers
