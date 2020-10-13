#include <stdio.h>
#include <stdlib.h>
#include "soft_config.h"
#include "string.h"
#include "assert.h"

// TODO: распределить функции по файлам

#define HARD_DATA_SIZE 5
#define HALF_YEAR_IN_SECONDS 15768000

void input_date(date* date) {
    char *str = NULL;
    while (!date->day || date->day > 31 || date->day < 1) {
        printf("Enter day in range 1..31: ");
        size_t linecap = 0;
        getline(&str, &linecap, stdin);
        date->day = atoi(str);
    }

    str = NULL;
    while (!date->month || date->month > 12 || date->month < 1) {
        printf("Enter month in range 1..12: ");
        size_t linecap = 0;
        getline(&str, &linecap, stdin);
        date->month = atoi(str);
    }

    str = NULL;
    while (!date->year || date->year < 0) {
        printf("Enter year as a positive integer: ");
        size_t linecap = 0;
        getline(&str, &linecap, stdin);
        date->year = atoi(str);
    }
    printf("\n");
}

// allocate memory!
softConfig* consoleInput(int* number_of_elements) {
    // ввод количества структур
    printf("Please, enter the number of apps you want to add configs about:\n");
    // int num_of_elements = -1;
    scanf("%d", number_of_elements);
    assert(*number_of_elements > 0);

    softConfig* configs = (softConfig*) calloc(*number_of_elements, sizeof(softConfig));
    for (int i = 0; i < *number_of_elements; i++) {
        printf("Enter information about app #%d:\n", i+1);
        printf("Enter name:\n");
        size_t linecap = 0;

        // TODO: убрать костыль
        if (i == 0) getline(&configs[i].name, &linecap, stdin);
        getline(&configs[i].name, &linecap, stdin);

        while (!configs[i].functionalClass || configs[i].functionalClass[0] <= 65 || configs[i].functionalClass[0] >= 90) {
            printf("Enter functional class of the app. Please, start with upper-case letter:\n");
            getline(&configs[i].functionalClass, &linecap, stdin);
        }

        char *version_number_str = NULL;
        while (!configs[i].versionNumber || configs[i].versionNumber <= 0) {
            printf("Enter version number (9 digits or less): ");
            getline(&version_number_str, &linecap, stdin);
            configs[i].versionNumber = atoi(version_number_str);
        }

        printf("Enter app installation date:\n");
        input_date(&configs[i].installDate);

        printf("Enter app last update date:\n");
        input_date(&configs[i].lastUpdateDate);
    }

    return configs;
}

// allocate memory!
softConfig* setHardData(int* number_of_elements) {
    *number_of_elements = HARD_DATA_SIZE;
    softConfig* configs = (softConfig*) calloc(*number_of_elements, sizeof(softConfig));
    softConfig a = { "Word",
                     "Utilities",
                     1293,
                     {21, 6, 2019},
                     {21, 6, 2019}
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
    return configs;
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

softConfig*** groupSort(softConfig** configs, softConfig*** configGroups, char** group_names, int num_of_groups, int num_of_elements) {
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

void groupPrint(softConfig*** configs) {
    int i = 0;
    while(configs[i]) {
        printf("%s:\n", configs[i][0]->functionalClass);
        int j = 0;
        while (configs[i][j]) {
            printf("-- %s  (install date: %d.%d.%d)\n", configs[i][j]->name, configs[i][j]->installDate.day, configs[i][j]->installDate.month, configs[i][j]->installDate.year);
            j++;
        }
        printf("\n");
        i++;
    }
}
