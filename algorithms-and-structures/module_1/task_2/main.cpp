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

void run(std::istream& input, std::ostream& output) {
    // input
    int n, m;
    input >> n;
    int* a_arr = new int[n];
    for (int i = 0; i < n; i++) input >> a_arr[i];
    input >> m;
    int* b_arr = new int[m];
    for (int i = 0; i < m; i++) input >> b_arr[i];

    // logic
    for (int i = 0; i < m; i++) {
        int element = b_arr[i];
        int j = 1;
        while (j < n) {
            if (element <= a_arr[j]) {
                int index = binary_search_index(a_arr, element, j / 2, j);
                output << index << " ";
                break;
            }
            j *= 2;
        }
        if (j >= n) output << binary_search_index(a_arr, element, 0, n) << " ";
    }

    // free memory
    delete[] a_arr;
    delete[] b_arr;
}

int main() {

    run(std::cin, std::cout);

    return 0;
}