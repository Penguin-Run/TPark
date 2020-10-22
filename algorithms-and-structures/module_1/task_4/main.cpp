#include <iostream>
#include <vector>

class Heap {
public:
    Heap();
    explicit Heap( std::vector<int>& _arr );
    ~Heap() = default;

    void print();

// Добавить элемент в кучу за O(logn)
    void insert( int element );
// Извлечь максимум из кучи за O(logn)
    int ExtractMax();
// Посмотреть значение максимума в куче за O(1)
    int peekMax() const;
private:
    std::vector<int> arr; // динамический массив для хранения элементов кучи
    void buildHeap(); // Построение кучи за 0(n)
    void siftDown( int i );
    void siftUp( int i );
};

void Heap::siftDown(int i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // ищем большего сына если такой есть
    int largest = i;
    if ((left < arr.size()) && (arr[left] > arr[i]))
        largest = left;
    if ((right < arr.size()) && (arr[right] > arr[largest]))
        largest = right;

    // если больший сын есть, то проталкиваем его в корень
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        siftDown(largest);
    }
}

// Проталкивание элемента наверх.
void Heap::siftUp(int index) {
    while( index > 0 ) {
        int parent = ( index - 1 ) / 2;
        if( arr[index] <= arr[parent] )
            return;
        std::swap( arr[index], arr[parent] );
        index = parent;
    }
}

void Heap::buildHeap() {
    for(int i = (int)(arr.size() / 2 - 1); i >= 0; --i) {
        siftDown(i);
    }
    std::cout << std::endl << "start index in buildheap(): " << (int)(arr.size() / 2 - 1) << std::endl;
}

Heap::Heap(std::vector<int> &_arr) {
    arr = _arr; // !
    this->print();
    buildHeap();
}

Heap::Heap() {
    arr = {};
}

void Heap::print() {
    for (int i : arr) std::cout << i << " ";
    std::cout << std::endl;
}

int Heap::peekMax() const {
    return arr[0];
}

void Heap::insert(int element) {
    arr.push_back(element);
    siftUp((int)arr.size() - 1);
}

int Heap::ExtractMax() {
    int old_max = arr[0];
    arr[0] = arr[arr.size()-1];
    arr.pop_back();
    siftDown(0);
    return old_max;
}


int main() {
    std::vector<int> vect{1, 2, 2};
    Heap heap(vect);
    heap.print();

    heap.insert(4);
    heap.print();

    heap.ExtractMax();
    heap.print();
    return 0;
}
