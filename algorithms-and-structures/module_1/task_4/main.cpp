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
    explicit Heap( std::vector<T>& _arr );
    ~Heap() = default;

    void print();
    int size();

// Добавить элемент в кучу за O(logn)
    void insert(T element);
// Извлечь максимум из кучи за O(logn)
    T extractMax();
// Посмотреть значение максимума в куче за O(1)
    T peekMax() const;
private:
    std::vector<T> arr; // динамический массив для хранения элементов кучи
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
    if ((left < arr.size()) && (arr[left] > arr[index]))
        largest = left;
    if ((right < arr.size()) && (arr[right] > arr[largest]))
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
    for(int i = (int)(arr.size() / 2 - 1); i >= 0; --i) {
        siftDown(i);
    }
}

template <class T>
Heap<T>::Heap(std::vector<T> &_arr) {
    arr = _arr;
    buildHeap();
}

template <class T>
Heap<T>::Heap() {
    arr = {};
}

template <class T>
void Heap<T>::print() {
    for (int i : arr) std::cout << i << " ";
    std::cout << std::endl;
}

template <class T>
T Heap<T>::peekMax() const {
    return !arr.empty() ? arr[0] : NULL; // NULL обработка случая, когда нету элементов
}

template <class T>
void Heap<T>::insert(T element) {
    arr.push_back(element);
    siftUp((int)arr.size() - 1);
}

template <class T>
T Heap<T>::extractMax() {
    if (arr.empty()) return NULL; // -1 обработка случая, когда нету элементов
    T old_max = arr[0];
    arr[0] = arr[arr.size()-1];
    arr.pop_back();
    siftDown(0);
    return old_max;
}

template <class T>
int Heap<T>::size() {
    return arr.size();
}

// сначала
template<class T>
class CmpDefault {
public:
    bool operator()( const T& l, const int& r ) { return l < r; }
};

template<class T, class Compare = CmpDefault<T>>
void run(std::vector<T>& input_vector, size_t k, Compare cmp = CmpDefault<T>()) {
    Heap<T> basket(input_vector);

    int count = 0;
    while (true) {
        if (basket.size() == 0) break;
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
    int n;
    std::cin >> n;
    std::vector<int> input_vector(n);
    for (int i = 0; i < n; i++) std::cin >> input_vector[i];
    int k;
    std::cin >> k;

    run(input_vector, k);

    return 0;
}


/*
3
4 3 5
6
 */