#include "source.c"

int main() {
    int *num_of_elements;
    softConfig* configs = setHardData(num_of_elements);

    softConfig** configs_ptrs = dateSort(configs, *num_of_elements);
    softConfig*** config_groups_ptrs = groupSort(configs_ptrs, *num_of_elements);
    alphabetical_sort(config_groups_ptrs);

    // softConfig*** sortedConfigs = groupSort(dateSort(consoleInput()));
    // alphabetical_sort(sortedConfigs);

    groupPrint(config_groups_ptrs);

    free(configs);
    free_groups(config_groups_ptrs);
    return 0;
}
