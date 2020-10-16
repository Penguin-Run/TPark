#include <iostream>

int main() {
    // input
    int n, m, k;
    std::cin >> n;
    int* a_arr = new int[n];
    for (int i = 0; i < n; i++) std::cin >> a_arr[i];
    std::cin >> m;
    int* b_arr = new int[m];
    for (int i = 0; i < m; i++) std::cin >> b_arr[i];
    std::cin >> k;

    // logic
    int index = 0;
    int pairs_count = 0;
    for (int i = m-1; i >= 0; i--) {
        for (int j = index; j < n; j++) {
            if ((b_arr[i] + a_arr[j]) == k) {
                index = j;
                pairs_count++;
                break;
            }
            if ((b_arr[i] + a_arr[j]) > k) {
                index = j;
                break;
            }
        }
    }

    std::cout << pairs_count;

    // free memory
    delete[] a_arr;
    delete[] b_arr;
    return 0;
}
