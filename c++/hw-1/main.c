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
                     {23, 06, 2019}
    };
    configs[1] = b;

    softConfig c = { "Clion",
                     "DevTools",
                     3764,
                     {12, 1, 2020},
                     {19, 10, 2020}
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
            halfYear->tm_year
    };
    return halfYearDate;
}

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

void sortOutput(softConfig* configs) {
    date halfYear = getDate(HALF_YEAR_IN_SECONDS);
    
}



// double difftime(time_t time1, time_t time2)


int main() {
    softConfig* configs = malloc(HARD_DATA_SIZE * sizeof(softConfig));
    hardData(configs);

    sortOutput(configs);
    return 0;
}
