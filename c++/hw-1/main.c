#include "source.c"

int main() {

    softConfig* configs = calloc(HARD_DATA_SIZE, sizeof(softConfig));
    setHardData(configs);

    softConfig*** config_groups = groupSort(dateSort(configs));
    alphabetical_sort(config_groups);

    // softConfig*** sortedConfigs = groupSort(dateSort(consoleInput()));
    // alphabetical_sort(sortedConfigs);

    groupPrint(config_groups);

    free(configs);
    free_groups(config_groups);
    return 0;
}
