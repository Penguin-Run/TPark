#include <iostream>
#include <vector>

// TODO: реализовать шаблоны и параметр-функтор для сравнения сложных объектов

class Heap {
public:
    Heap();
    explicit Heap( std::vector<int>& _arr );
    ~Heap() = default;

    void print();
    int size();

// Добавить элемент в кучу за O(logn)
    void insert( int element );
// Извлечь максимум из кучи за O(logn)
    int extractMax();
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
}

Heap::Heap(std::vector<int> &_arr) {
    arr = _arr;
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
    return !arr.empty() ? arr[0] : -1; // -1 обработка случая, когда нету элементов
}

void Heap::insert(int element) {
    arr.push_back(element);
    siftUp((int)arr.size() - 1);
}

int Heap::extractMax() {
    if (arr.empty()) return -1; // -1 обработка случая, когда нету элементов
    int old_max = arr[0];
    arr[0] = arr[arr.size()-1];
    arr.pop_back();
    siftDown(0);
    return old_max;
}

int Heap::size() {
    return arr.size();
}


int main() {
    int n;
    std::cin >> n;
    std::vector<int> input_vector(n);
    for (int i = 0; i < n; i++) std::cin >> input_vector[i];
    int k;
    std::cin >> k;

    Heap basket(input_vector);

    int count = 0;
    while (true) {
        if (basket.size() == 0) break;
        int pocket_weight = 0;
        std::vector<int> pocket;
        while (true) {
            if ((pocket_weight + basket.peekMax()) > k)
                break;
            int current_max = basket.extractMax();
            if (current_max == -1)
                break;
            pocket.push_back(current_max);
            pocket_weight += pocket[pocket.size()-1];
        }
        for (int & i : pocket) {
            if (i != 1) {
                i = i / 2;
                basket.insert(i);
            }
        }
        count++;
    }

    std::cout << count;

    return 0;
}


/*
3
4 3 5
6
 */