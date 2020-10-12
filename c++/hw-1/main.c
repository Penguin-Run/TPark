#include "source.c"

int main() {

    softConfig* configs = calloc(HARD_DATA_SIZE, sizeof(softConfig));
    setHardData(configs);

    softConfig*** sortedConfigs = groupSort(dateSort(configs));

    // softConfig*** sortedConfigs = groupSort(dateSort(consoleInput()));

    groupPrint(sortedConfigs);

    free(configs);
    free_groups(sortedConfigs);
    return 0;
}
