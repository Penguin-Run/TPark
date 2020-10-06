#include <stdio.h>
#include <stdlib.h>
#include "soft_config.h"

// add time.h ???

void consoleInput() {
    int argSize = -1;
    scanf("%d", &argSize);
    softConfig* configs = malloc(argSize * sizeof(softConfig));
    softConfig current;
    int count = 0;
    while(scanf("%s%s%d", current.name, current.functionalClass, &current.versionNumber)) {
        configs[count] =
        count++;
    }
}

int main() {

    return 0;
}
