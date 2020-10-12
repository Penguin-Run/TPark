#include "source.c"

void free_groups(softConfig*** configs) {
    int i = 0;
    while (configs[i]) {
        free(configs[i]);
        i++;
    }
}

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
