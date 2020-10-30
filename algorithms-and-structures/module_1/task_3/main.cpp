#include <iostream>
#include <cassert>
#include <utility>

#define FRONT 31
#define BACK 32

template <class T>
class Deque {
public:
    Deque();
    Deque(const Deque& obj);
    Deque& operator = (const Deque& obj);
    ~Deque();

    void push_front(T b);
    void push_back(T b);
    T pop_front();
    T pop_back();

    void print() {
        std::cout << "Printing array elements:" << std::endl;
        for (int i = tail+1; i < head; i++) {
            std::cout << array[i] << " ";
        }
        std::cout << std::endl;
    }
private:
    T* array;
    size_t size;
    size_t capacity;

    int tail;
    int head;

    void grow(int direction);
    void swap(Deque& deque);
};

template <class T>
Deque<T>::Deque() {
    array = new T[10];
    capacity = 10;
    size = 0;
    head = 5;
    tail = 4;
}

template <class T>
Deque<T>::Deque(const Deque<T> &obj) {
    array = new T[obj.capacity];
    for (int i = obj.tail+1; i < obj.head; i++)
        array[i] = obj.array[i];

    capacity = obj.capacity;
    size = obj.size;
    head = obj.head;
    tail = obj.tail;
}

template <class T>
void Deque<T>::swap(Deque<T> &deque) {
    std::swap(array, deque.array);

    std::swap(size, deque.size);
    std::swap(capacity, deque.capacity);

    std::swap(tail, deque.tail);
    std::swap(head, deque.head);
}

template <class T>
Deque<T>& Deque<T>::operator=(const Deque<T> &obj) {
    if (this != &obj) {
        Deque(obj).swap(*this);
    }
    return *this;
}

template <class T>
Deque<T>::~Deque() {
    delete[] array;
}

template <class T>
void Deque<T>::push_front(T b) {
    array[head] = b;
    head++;
    size++;

    assert(head <= capacity);
    if (head == capacity) grow(FRONT);
}

template <class T>
void Deque<T>::push_back(T b) {
    array[tail] = b;
    tail--;
    size++;

    assert(tail >= -1);
    if (tail == -1) grow(BACK);
}

template <class T>
T Deque<T>::pop_front() {
    if (head-1 == tail) return -1;
    head--;
    size--;

    return array[head];
}

template <class T>
T Deque<T>::pop_back() {
    if (head-1 == tail) return -1;
    tail++;
    size--;

    return array[tail];
}

template <class T>
void Deque<T>::grow(int direction) {
    T* temp = array;

    array = new T[capacity + capacity/2];

    if (direction == FRONT) {
        for (int i = 0; i < size; i++) {
            array[i + tail + 1] = temp[i + tail + 1];
        }
    }
    if (direction == BACK) {
        for (int i = 0; i < size; i++) {
            array[i + capacity/2] = temp[i];
        }

        tail = (int) capacity/2 -1;
        head += (int) capacity/2;
    }

    capacity += capacity/2;
    delete[] temp;
}

void run(std::istream& input, std::ostream& output) {
    Deque<unsigned int> deque;

    int n = 0;
    input >> n;

    bool result = true;

    for (int i = 0; i < n; i++) {
        int command = 0;
        int value = 0;
        input >> command >> value;
        switch (command) {
            case 1: // push front
                deque.push_front(value);
                break;

            case 2: // pop front
                result = result && value == deque.pop_front();
                break;

            case 3: // push back
                deque.push_back(value);
                break;

            case 4: // pop back
                result = result && value == deque.pop_back();
                break;

            default:
                assert(false);
        }
    }

    output << ( result ? "YES" : "NO");
}

int main() {

    run(std::cin, std::cout);

    return 0;
}