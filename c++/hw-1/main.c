#include "source.c"

int main() {
    // ввод данных
    int* num_of_elements;
    softConfig* configs = setHardData(num_of_elements);
    assert(*num_of_elements > 0);

    // сортировка по датам
    softConfig** configs_ptrs = (softConfig**) calloc(*num_of_elements, sizeof(softConfig*));
    dateSort(configs, configs_ptrs, *num_of_elements);

    
    softConfig*** config_groups_ptrs = groupSort(configs_ptrs, *num_of_elements);

    alphabetical_sort(config_groups_ptrs);

    groupPrint(config_groups_ptrs);

    free(configs);
    free_groups(config_groups_ptrs);
    return 0;
}
