#include <stdio.h>
#include <stdlib.h>
#include "soft_config.h"
#include "string.h"

// add time.h ???

#define HARD_DATA_SIZE 5
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

    softConfig d = { "RubyMine",
                     "DevTools",
                     2948,
                     {12, 1, 2020},
                     {12, 1, 2020}
    };
    configs[3] = d;

    softConfig e = { "Spotify",
                     "Entertainment",
                     2948,
                     {12, 1, 2020},
                     {12, 1, 2020}
    };
    configs[4] = e;
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

softConfig** dateSort(softConfig* configs) {
    date halfYear = getDate(HALF_YEAR_IN_SECONDS);
    printf("%d %d\n", halfYear.year, halfYear.month);

    softConfig** sortedConfigs = calloc(HARD_DATA_SIZE, sizeof(softConfig*));

    int sortCount = 0;
    for (int i = 0; i < HARD_DATA_SIZE; i++) {
        if (datecmp(configs[i].installDate, halfYear) == 2 && isUnupdated(configs[i].installDate, configs[i].lastUpdateDate)) {
            sortedConfigs[sortCount] = &configs[i];
            sortCount++;
        }
    }

    return sortedConfigs;
}

softConfig** ascendingSort(softConfig** configs) {
    int isSorted = 1;
    while(isSorted) {
        isSorted = 0;
        int i = 0;
        while (configs[i+1]) {
            if (strcmp(configs[i]->name, configs[i+1]->name) > 0) {
                char* temp = configs[i]->name;
                configs[i]->name = configs[i+1]->name;
                configs[i+1]->name = temp;
                isSorted = 1;
            }
            i++;
        }
    }

    return configs;
}

softConfig*** groupSort(softConfig** configs) {
    // найти все названия функц. классов
    int funcClassCount = 0;
    char* classNames[HARD_DATA_SIZE];
    for (int i = 0; i < HARD_DATA_SIZE; i++) {
        classNames[i] = "";
    }
    int i = 0;
    while (configs[i]) {
        int isInTheNames = 0;
        for (int j = 0; j < HARD_DATA_SIZE; j++) {
            if ((configs[i]->functionalClass != NULL) && (classNames[j] != NULL)) {
                if (strcmp(configs[i]->functionalClass, classNames[j]) == 0) {
                    isInTheNames = 1;
                }
            }
        }
        if (!isInTheNames) {
            classNames[funcClassCount] = configs[i]->functionalClass;
            printf("%s\n", classNames[funcClassCount]);
            funcClassCount++;
        }
        i++;
    }

    // выделить массив под каждый из них
    softConfig*** configGroups = calloc(funcClassCount, sizeof(softConfig**)); // ***?
    for (i = 0; i < funcClassCount; i++) {
        // count each group to optimize memory
        configGroups[i] = calloc(HARD_DATA_SIZE, sizeof(softConfig*)); // !
    }

    // добавить элементы в соответствующие группы
    int groupElemCounter[funcClassCount];
    for (i = 0; i < funcClassCount; i++) groupElemCounter[i] = 0;
    i = 0;
    while(configs[i]) {
        for (int j = 0; j < funcClassCount; j++) {
            if (strcmp(classNames[j], configs[i]->functionalClass) == 0) {
                configGroups[j][groupElemCounter[j]] = configs[i];
                groupElemCounter[j]++;
                printf("Element %s added in the group %s\n", configs[i]->name, classNames[j]);
            }
        }
        i++;
    }

    // отсортировать элементы по алфавиту в рамках групп
    for (i = 0; i < funcClassCount; i++) ascendingSort(configGroups[i]);
    return configGroups;
}

// check if array of pointers is empty
int isEmpty(softConfig** configs) {
    int i = 0;
    while(i < HARD_DATA_SIZE) {
        if (configs[i])
            return 0; // not empty
        i++;
    }
    return 1; // empty
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

    softConfig** sortedConfigs = dateSort(configs);
    softConfig*** sortedConfigsss = groupSort(sortedConfigs);
    print(sortedConfigsss[1]);
    return 0;
}
