#include <iostream>

int binary_search_index(const int* a_arr, int element, int start_index, int end_index) {
        int first = start_index;
        int last = end_index;
        while (first < last) {
            int mid = (first + last) / 2;
            if (a_arr[mid] < element) {
                first = mid + 1;
            }
            else {
                last = mid;
            }
        }

        // если элементы совпадают
        if (a_arr[first] == element) {
            return first;
        }
        // если элемент больше последнего
        if (a_arr[first] < element) {
            return first-1;
        }
        // если элемент между двумя
        if ((a_arr[first] > element) && (element >= a_arr[0])) {
            if (std::abs(element - a_arr[first]) < std::abs(element - a_arr[first-1]))
                return first;
            else
                return first - 1;
        }
        // если элемент меньше первого
        if (a_arr[first] > element) {
            return first;
        }
        return -1;
}

int main() {
    // input
    int n, m;
    std::cin >> n;
    int* a_arr = new int[n];
    for (int i = 0; i < n; i++) std::cin >> a_arr[i];
    std::cin >> m;
    int* b_arr = new int[m];
    for (int i = 0; i < m; i++) std::cin >> b_arr[i];

    // logic
    for (int i = 0; i < m; i++) {
        int element = b_arr[i];
        int j = 1;
        while (j < n) {
            if (element <= a_arr[j]) {
                int index = binary_search_index(a_arr, element, j / 2, j);
                std::cout << index << " ";
                break;
            }
            j *= 2;
        }
        if (j >= n) std::cout << binary_search_index(a_arr, element, 0, n) << " ";
    }

    // free memory
    delete[] a_arr;
    delete[] b_arr;
    return 0;
}

/*
5
5 10 20 25 30
11
4 5 7 8 10 11 15 20 29 30 31
 */