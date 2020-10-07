#include <stdio.h>
#include <stdlib.h>
#include "soft_config.h"

// add time.h ???

#define HARD_DATA_SIZE 4
#define HALF_YEAR_IN_SECONDS 15768000

void consoleInput();
    /*
        int argsSize = -1;
        scanf("%d", &argsSize);
        printf("%d\n", argsSize);
        softConfig* configs = malloc(argsSize * sizeof(softConfig));
        softConfig current;
        int count = 0;
        while(count < argsSize) {
            // configs[count] = current;
            printf("dddd\n");
            char* name;
            int a = scanf("%s", name);
            printf("%s  %d", name, a);
            count++;
        }
    */

void hardData(softConfig* configs) {
    softConfig a = { "Word",
        "Utilities",
        1293,
        {21, 6, 2019},
        {17, 3, 2020}
    };
    configs[0] = a;

    softConfig b = { "Excel",
                     "Utilities",
                     1344,
                     {23, 6, 2019},
                     {23, 6, 2019}
    };
    configs[1] = b;

    softConfig c = { "Clion",
                     "DevTools",
                     3764,
                     {12, 1, 2020},
                     {12, 1, 2020}
    };
    configs[2] = c;

    softConfig d = { "Spotify",
                     "Entertainment",
                     2948,
                     {21, 8, 2020},
                     {21, 8, 2020}
    };
    configs[3] = d;

}

// returns current date - deltaAgo (deltaAgo in seconds)
date getDate(time_t deltaAgo) {
    time_t curTime;
    time(&curTime);
    curTime -= deltaAgo;
    struct tm* halfYear = localtime(&curTime);
    date halfYearDate = {
            halfYear->tm_mday,
            halfYear->tm_mon,
            halfYear->tm_year + 1900
    };
    return halfYearDate;
}

// first > second = 1; first < second = 2; first == second = 0;
int datecmp(date first, date second) {
    if (first.year > second.year) return 1;
    else if (first.year < second.year) return 2;
    else {
        if (first.month > second.month) return 1;
        else if (first.month < second.month) return 2;
        else {
            if (first.day > second.day) return 1;
            else if (first.day < second.day) return 2;
            else return 0;
        }
    }

}

// 0 - has been updated at least one time, 1 - no updates done
int isUnupdated(date first, date second) {
    return ((first.year == second.year) && (first.month == second.month) && (first.day == second.day));
}

softConfig** sortOutput(softConfig* configs) {
    date halfYear = getDate(HALF_YEAR_IN_SECONDS);
    printf("%d %d\n", halfYear.year, halfYear.month);

    softConfig** sortedConfigs = malloc(HARD_DATA_SIZE * sizeof(softConfig*));

    int sortCount = 0;
    for (int i = 0; i < HARD_DATA_SIZE; i++) {
        if (datecmp(configs[i].installDate, halfYear) == 2 && isUnupdated(configs[i].installDate, configs[i].lastUpdateDate)) {
            sortedConfigs[sortCount] = &configs[i];
            sortCount++;
        }
    }

    return sortedConfigs;
}

void print(softConfig** configs) {
    int i = 0;
    while(configs[i]) {
        printf("%s      %d %d\n", configs[i]->name, configs[i]->installDate.year, configs[i]->installDate.month);
        i++;
    }
}



int main() {
    softConfig* configs = malloc(HARD_DATA_SIZE * sizeof(softConfig));
    hardData(configs);

    softConfig** sortedConfigs = sortOutput(configs);
    print(sortedConfigs);
    return 0;
}
