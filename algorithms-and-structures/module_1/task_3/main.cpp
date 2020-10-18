#include <iostream>
#include <cassert>
#include <utility>

#define FRONT 31
#define BACK 32


class Deque {
public:
    Deque();
    Deque(const Deque& obj);
    Deque& operator = (const Deque& obj);
    ~Deque();

    void push_front(unsigned int b);
    void push_back(unsigned int b);
    unsigned int pop_front();
    unsigned int pop_back();

    void print() {
        std::cout << "Printing array elements:" << std::endl;
        for (int i = tail+1; i < head; i++) {
            std::cout << array[i] << " ";
        }
        std::cout << std::endl;
    }
private:
    unsigned int* array;
    size_t size;
    size_t capacity;

    int tail;
    int head;

    void grow(int direction);
    void swap(Deque& deque);
};

Deque::Deque() {
    this->array = new unsigned int[10];
    this->capacity = 10;
    this->size = 0;
    this->head = 5;
    this->tail = 4;
}

Deque::Deque(const Deque &obj) {
    this->array = new unsigned int[obj.capacity];
    for (int i = obj.tail+1; i < obj.head; i++)
        this->array[i] = obj.array[i];

    this->capacity = obj.capacity;
    this->size = obj.size;
    this->head = obj.head;
    this->tail = obj.tail;
}

void Deque::swap(Deque &deque) {
    std::swap(array, deque.array);

    std::swap(size, deque.size);
    std::swap(capacity, deque.capacity);

    std::swap(tail, deque.tail);
    std::swap(head, deque.head);
}

Deque &Deque::operator=(const Deque &obj) {
    if (this != &obj) {
        Deque(obj).swap(*this);
    }
    return *this;
}

Deque::~Deque() {
    delete[] this->array;
}

void Deque::push_front(unsigned int b) {
    array[head] = b;
    head++;
    size++;

    assert(head <= capacity);
    if (head == capacity) grow(FRONT);
}

void Deque::push_back(unsigned int b) {
    array[tail] = b;
    tail--;
    size++;

    assert(tail >= -1);
    if (tail == -1) grow(BACK);
}

unsigned int Deque::pop_front() {
    if (head-1 == tail) return -1;
    head--;
    size--;

    return array[head];
}

unsigned int Deque::pop_back() {
    if (head-1 == tail) return -1;
    tail++;
    size--;

    return array[tail];
}

void Deque::grow(int direction) {
    unsigned int* temp = this->array;

    this->array = new unsigned int[capacity + capacity/2];

    if (direction == FRONT) {
        for (int i = 0; i < this->size; i++) {
            this->array[i + tail + 1] = temp[i + tail + 1];
        }
    }
    if (direction == BACK) {
        for (int i = 0; i < this->size; i++) {
            this->array[i + capacity/2] = temp[i];
        }

        tail = capacity/2 -1;
        head += capacity/2;
    }

    capacity += capacity/2;
    delete[] temp;
}

void run(std::istream& input, std::ostream& output) {
    Deque deque;

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