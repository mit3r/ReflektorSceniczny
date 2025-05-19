

#ifndef QUEUE_H
#define QUEUE_H

// Create queue of pointer of T type

// This is a template class that creates a queue of pointers to objects of type T with given lenght of buffer.
// It provides methods to enqueue, dequeue, check if the queue is empty, check if the queue is full, and get front element.
// The queue is implemented as a circular buffer, with head and tail pointers to keep track of the current position in the queue.
// The queue is designed to be used with a pointer to an object of type T, allowing for dynamic memory allocation and deallocation.

template <typename T>
class Queue {
  private:
  T *buffer;             // Pointer to the buffer
  unsigned long head;    // Head pointer
  unsigned long tail;    // Tail pointer
  unsigned long length;  // Length of the buffer

  public:
  Queue(unsigned long length) : length(length) {
    buffer = new T[length];
    head = 0;
    tail = 0;
  }

  ~Queue() {
    delete[] buffer;
  }

  bool enqueue(T item) {
    if (isFull()) return false;

    buffer[head] = item;
    head = (head + 1) % length;
    return true;
  }

  void dequeue() {
    if (isEmpty()) return;
    tail = (tail + 1) % length;
  }

  bool isEmpty() const {
    return head == tail;
  }

  bool isFull() const {
    return (head + 1) % length == tail;
  }

  T *front() const {
    return isEmpty() ? nullptr : &buffer[tail];
  }
};

#endif  // QUEUE_H