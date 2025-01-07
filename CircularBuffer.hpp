#pragma once
#include <iostream>

namespace ss
{
    /**
     * \brief Implementation of a circular buffer.
     *
     * This class implements a circular buffer that stores elements of type T with a fixed capacity.
     * It overwrites the oldest elements when the buffer becomes full.

     * \param T Type of elements stored in the buffer.
     */

    template <typename T>
    class CircularBuffer
    {
    private:
        T *m_buffer;
        size_t m_capacity;
        size_t m_head;
        size_t m_tail;
        size_t m_count;

        static constexpr size_t def_capacity = 5; /**< Default buffer capacity */

    public:
        /**
         * \brief Default constructor for CircularBuffer.
         * Initializes the buffer with a default capacity.
         */
        CircularBuffer() : m_capacity(def_capacity), m_head(0), m_tail(0), m_count(0)
        {
            m_buffer = new T[m_capacity];
        }

        /**
         * \brief Parameterized constructor for CircularBuffer.
         * \param capacity Desired capacity of the buffer.
         */
        CircularBuffer(size_t capacity) : m_capacity(capacity), m_head(0), m_tail(0), m_count(0)
        {
            if (capacity == 0)
            {
                std::cout << "Capacity must be greater than zero." << std::endl;
                m_capacity = def_capacity;
            }
            m_buffer = new T[m_capacity];
        }

        /**
         * \brief Copy constructor.
         * \param other The CircularBuffer to copy from.
         */
        CircularBuffer(const CircularBuffer &other)
            : m_capacity(other.m_capacity), m_head(other.m_head), m_tail(other.m_tail), m_count(other.m_count)
        {
            m_buffer = new T[m_capacity];

            for (size_t i = 0; i < m_capacity; ++i)
            {
                m_buffer[i] = other.m_buffer[i];
            }
        }

        /**
         * \brief Destructor for CircularBuffer.
         */
        ~CircularBuffer()
        {
            delete[] m_buffer;
        }

        /**
         * \brief Checks if the buffer is full.
         * \return True if full, otherwise false.
         */
        bool is_full() const
        {
            return m_count == m_capacity;
        }

        /**
         * \brief Checks if the buffer is empty.
         * \return True if empty, otherwise false.
         */
        bool is_empty() const
        {
            return m_count == 0;
        }

        /**
         * \brief Adds an element to the buffer.
         *        If the buffer is full, it overwrites the oldest element.
         * \param item The element to add.
         */
        void push(const T &item)
        {
            m_buffer[m_tail] = item;
            m_tail = (m_tail + 1) % m_capacity;
            if (is_full())
            {
                m_head = (m_head + 1) % m_capacity; // Overwrite the oldest element
            }
            else
            {
                ++m_count;
            }
        }

        /**
         * \brief Removes the oldest element from the buffer.
         */
        void pop()
        {
            if (is_empty())
            {
                std::cout << "Buffer is empty. Cannot remove element." << std::endl;
                return;
            }

            m_head = (m_head + 1) % m_capacity;
            --m_count;
        }

        /**
         * \brief Displays the current state of the buffer.
         */
        void display() const
        {
            if (is_empty())
            {
                std::cout << "Buffer is empty." << std::endl;
                return;
            }

            for (size_t i = 0; i < m_count; ++i)
            {
                std::cout << m_buffer[(m_head + i) % m_capacity] << " ";
            }
            std::cout << std::endl;
        }

        /**
         * \brief Overloaded "=" operator.
         * \param other The CircularBuffer to assign from.
         * \return Reference to the assigned object.
         */
        CircularBuffer &operator=(const CircularBuffer &other)
        {
            if (this != &other)
            {
                m_capacity = other.m_capacity;
                m_head = other.m_head;
                m_tail = other.m_tail;
                m_count = other.m_count;
                m_buffer = new T[m_capacity];
                for (size_t i = 0; i < m_capacity; ++i)
                {
                    m_buffer[i] = other.m_buffer[i];
                }
            }
            return *this;
        }

        /**
         * \brief Overloaded "==" operator.
         * \param other The CircularBuffer to compare to.
         * \return True if equal, otherwise false.
         */
        bool operator==(const CircularBuffer &other) const
        {
            if (m_capacity != other.m_capacity || m_count != other.m_count)
            {
                return false;
            }
            for (size_t i = 0; i < m_count; ++i)
            {
                if (m_buffer[(m_head + i) % m_capacity] != other.m_buffer[(other.m_head + i) % other.m_capacity])
                {
                    return false;
                }
            }
            return true;
        }

        /**
         * \brief Overloaded inequality operator.
         * \param other The CircularBuffer to compare to.
         * \return True if not equal, otherwise false.
         */
        bool operator!=(const CircularBuffer &other) const
        {
            return !(*this == other);
        }
    };
}
