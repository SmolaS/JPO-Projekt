#include "CircularBuffer.hpp"
#include <iostream>

int main()
{
    // ss::CircularBuffer<int> buffer;
    ss::CircularBuffer<int> buffer1(5); // Create a buffer with a capacity of 5

    // Add elements to the first buffer
    buffer1.push(1);
    buffer1.push(2);
    buffer1.push(3);

    std::cout << "Buffer 1 after adding 3 elements: ";
    buffer1.display();

    // Create a copy of the buffer
    ss::CircularBuffer<int> buffer2 = buffer1;

    std::cout << "Buffer 2 (copy of Buffer 1): ";
    buffer2.display();

    // Add more elements to buffer 1, exceeding the capacity
    buffer1.push(4);
    buffer1.push(5);
    buffer1.push(6); // Overwrite the oldest element

    std::cout << "Buffer 1 after adding 3 more elements (exceeding capacity): ";
    buffer1.display();

    // Create a new buffer and assign buffer 2 to it
    ss::CircularBuffer<int> buffer3(5);
    buffer3 = buffer2;

    std::cout << "Buffer 3 (assigned from Buffer2): ";
    buffer3.display();

    // Compare buffer 2 and buffer 3
    if (buffer2 == buffer3)
    {
        std::cout << "Buffer 2 is equal to Buffer 3." << std::endl;
    }
    else
    {
        std::cout << "Buffer 2 is not equal to Buffer 3." << std::endl;
    }

    // Remove an element from buffer 3 and compare again
    buffer3.pop();

    std::cout << "Buffer 2: ";
    buffer2.display();

    std::cout << "Buffer 3: ";
    buffer3.display();

    if (buffer2 != buffer3)
    {
        std::cout << "Buffer 2 is not equal to Buffer 3." << std::endl;
    }

    return 0;
}
