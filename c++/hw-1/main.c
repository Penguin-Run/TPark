#include "source.c"

int main() {

    softConfig* configs = calloc(HARD_DATA_SIZE, sizeof(softConfig));
    setHardData(configs);

    softConfig*** sortedConfigs = groupSort(dateSort(configs));

    // softConfig*** sortedConfigs = groupSort(dateSort(consoleInput()));

    groupPrint(sortedConfigs);
    return 0;
}
