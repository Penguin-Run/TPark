#include <iostream>

void run(std::istream& input, std::ostream& output) {
    // input
    int n, m, k;
    input >> n;
    int* a_arr = new int[n];
    for (int i = 0; i < n; i++) input >> a_arr[i];
    input >> m;
    int* b_arr = new int[m];
    for (int i = 0; i < m; i++) input >> b_arr[i];
    input >> k;

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

    output << pairs_count;

    // free memory
    delete[] a_arr;
    delete[] b_arr;
}

int main() {

    run(std::cin, std::cout);

    return 0;
}
