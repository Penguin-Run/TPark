#include <iostream>

int main() {
    // input
    int n, m;
    std::cin >> n;
    int* a_arr = new int[n];
    for (int i = 0; i < n; i++) std::cin >> a_arr[i];


    std::cin >> m;
    int* b_arr = new int[m];
    for (int i = 0; i < m; i++) std::cin >> b_arr[i];

    /*
    for (int i = 0; i < n; i++) std::cout << a_arr[i] << std::endl;
    std::cout << std::endl;
    for (int i = 0; i < m; i++) std::cout << b_arr[i] << std::endl;
    */

    // TODO: реализовать корректную обработку, что между 10 и 20 16 пойдет к индексу 20 (если так вообще надо)
    // logic
    int start_index = 0;

    for (int i = 0; i < m; i++) {
        int first = start_index;
        int last = n;
        while (first < last) {
            int mid = (first + last) / 2;
            if (a_arr[mid] < b_arr[i]) {
                first = mid + 1;
            }
            else {
                last = mid;
            }
        }

        // если элементы совпадают
        if (a_arr[first] == b_arr[i]) {
            std::cout << b_arr[i] << ": " << first << " " << std::endl;
            start_index = first + 1;
        }
        // если элемент больше последнего
        else if (a_arr[first] < b_arr[i]) {
            std::cout << b_arr[i] << ": " << first-1 << " " << std::endl;
            start_index = first - 1;
        }
        // если элемент между двумя
        else if ((a_arr[first] > b_arr[i]) && (b_arr[i] >= a_arr[0])) {
            std::cout << b_arr[i] << ": " << first-1 << " " << std::endl;
            start_index = first;
        }
        // если элемент меньше первого
        else if (a_arr[first] > b_arr[i]) {
            std::cout << b_arr[i] << ": " << first << " " << std::endl;
            start_index = first;
        }
    }
    return 0;
}

/*
5
5 10 20 25 30
11
4 5 7 8 10 11 15 20 29 30 31
 */