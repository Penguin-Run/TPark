#include <iostream>
#include <vector>

/*
Вовочка ест фрукты из бабушкиной корзины.
В корзине лежат фрукты разной массы. Вовочка может поднять не более K грамм. Каждый фрукт весит не более K грамм. За раз он выбирает несколько самых тяжелых фруктов, которые может поднять одновременно, откусывает от каждого половину и кладет огрызки обратно в корзину. Если фрукт весит нечетное число грамм, он откусывает большую половину. Фрукт массы 1гр он съедает полностью.

Определить за сколько подходов Вовочка съест все фрукты в корзине.
 */

template <class T>
class Heap {
public:
    Heap();
    explicit Heap(const T* _arr, size_t arr_size);
    ~Heap() = default;

    void print();
    bool is_empty() const;

// Добавить элемент в кучу за O(logn)
    void insert(T& element);
// Извлечь максимум из кучи за O(logn)
    T extractMax();
// Посмотреть значение максимума в куче за O(1)
    T peekMax() const;

private:
    T* arr; // динамический массив для хранения элементов кучи
    size_t size;
    size_t capacity;

    void grow_arr();

    void buildHeap(); // Построение кучи за 0(n)
    void siftDown( int index );
    void siftUp( int i );
};

// Проталкивание элемента вниз
template <class T>
void Heap<T>::siftDown(int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    // ищем большего сына если такой есть
    int largest = index;
    if ((left < size) && (arr[left] > arr[index]))
        largest = left;
    if ((right < size) && (arr[right] > arr[largest]))
        largest = right;

    // если больший сын есть, то проталкиваем его в корень
    if (largest != index) {
        std::swap(arr[index], arr[largest]);
        siftDown(largest);
    }
}

// Проталкивание элемента наверх
template <class T>
void Heap<T>::siftUp(int index) {
    while( index > 0 ) {
        int parent = ( index - 1 ) / 2;
        if( arr[index] <= arr[parent] )
            return;
        std::swap( arr[index], arr[parent] );
        index = parent;
    }
}

template <class T>
void Heap<T>::buildHeap() {
    for(int i = (int)(size / 2 - 1); i >= 0; --i) {
        siftDown(i);
    }
}

template<class T>
void Heap<T>::grow_arr() {
    T* temp = arr;
    capacity *= 2;
    arr = new T[capacity];

    delete[] temp;
}

template<class T>
bool Heap<T>::is_empty() const {
    return size == 0;
}

template <class T>
Heap<T>::Heap(const T* _arr, size_t arr_size) : size(arr_size), capacity(arr_size), arr(new T[arr_size]){
    for (int i = 0; i < arr_size; i++)
        arr[i] = _arr[i];
    buildHeap();
}

template <class T>
Heap<T>::Heap() : capacity(10), size(0), arr(new T[10]) { }

template <class T>
void Heap<T>::print() {
    for (int i : arr) std::cout << i << " ";
    std::cout << std::endl;
}

template <class T>
T Heap<T>::peekMax() const {
    return !is_empty() ? arr[0] : NULL; // NULL обработка случая, когда нету элементов
}

template <class T>
void Heap<T>::insert(T& element) {
    // arr.push_back(element);
    if (size == capacity)
        grow_arr();
    arr[size++] = element;
    siftUp((int)size - 1);
}

template <class T>
T Heap<T>::extractMax() {
    if (is_empty()) return NULL; // -1 обработка случая, когда нету элементов
    T old_max = arr[0];
    arr[0] = arr[size-1];

    size--;

    siftDown(0);
    return old_max;
}


// сначала
template<class T>
class CmpDefault {
public:
    bool operator()( const T& l, const int& r ) { return l < r; }
};

template<class T, class Compare = CmpDefault<T>>
void run(T* _arr, size_t _arr_size, size_t k, Compare cmp = CmpDefault<T>()) {
    Heap<T> basket(_arr, _arr_size);

    int count = 0;
    while (true) {
        if (basket.is_empty()) break;
        T pocket_weight = 0;
        std::vector<T> pocket;
        while (true) {
            if (cmp(k, (pocket_weight + basket.peekMax())))
                break;
            T current_max = basket.extractMax();
            if (current_max == NULL)
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
}

// насколько я понимаю, чтобы в действительности использовать в этой программе объекты кастомных классов,
// эти классы должны поддерживать также арифметику +, /
int main() {
    // input
    size_t n;
    std::cin >> n;
    int* input_arr = new int[n];
    for (int i = 0; i < n; i++) std::cin >> input_arr[i];
    int k;
    std::cin >> k;

    run(input_arr, n, k);

    return 0;
}


/*
3
4 3 5
6
 */