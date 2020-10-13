#include <stdio.h>
#include <stdlib.h>
#include "soft_config.h"
#include "string.h"
#include "assert.h"

// TODO: распределить функции по файлам

#define HARD_DATA_SIZE 5
#define HALF_YEAR_IN_SECONDS 15768000

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

void dateSort(softConfig* configs, softConfig** sortedConfigs, int num_of_elements) {
    date halfYear = getDate(HALF_YEAR_IN_SECONDS);

    int sortCount = 0;
    for (int i = 0; i < num_of_elements; i++) {
        if (datecmp(configs[i].installDate, halfYear) == 2 && isUnupdated(configs[i].installDate, configs[i].lastUpdateDate)) {
            sortedConfigs[sortCount] = &configs[i];
            sortCount++;
        }
    }
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

int find_group_names(softConfig** configs, char** group_names, int num_of_elements) {
    // найти все названия функц. классов
    int funcClassCount = 0;

    for (int i = 0; i < num_of_elements; i++) {
        group_names[i] = "";
    }
    int i = 0;
    while (configs[i] != NULL) {
        int isInTheNames = 0;
        for (int j = 0; j < num_of_elements; j++) {
            if ((configs[i]->functionalClass != NULL) && (group_names[j] != NULL)) {
                if (strcmp(configs[i]->functionalClass, group_names[j]) == 0) {
                    isInTheNames = 1;
                }
            }
        }
        if (!isInTheNames) {
            group_names[funcClassCount] = configs[i]->functionalClass;
            funcClassCount++;
        }
        i++;
    }
    return funcClassCount;
}

softConfig*** groupSort(softConfig** configs, softConfig*** configGroups, char** group_names, int num_of_groups) {
    // добавить элементы в соответствующие группы
    int groupElemCounter[num_of_groups];
    for (int i = 0; i < num_of_groups; i++) groupElemCounter[i] = 0;
    int i = 0;
    while(configs[i]) {
        for (int j = 0; j < num_of_groups; j++) {
            if (strcmp(group_names[j], configs[i]->functionalClass) == 0) {
                configGroups[j][groupElemCounter[j]] = configs[i];
                groupElemCounter[j]++;
                // printf("Element %s added in the group %s\n", configs[i]->name, classNames[j]);
            }
        }
        i++;
    }
    return configGroups;
}

void alphabetical_sort(softConfig*** config_groups) {
    int i = 0;
    while (config_groups[i]) {
        ascendingSort(config_groups[i]);
        i++;
    }
}


