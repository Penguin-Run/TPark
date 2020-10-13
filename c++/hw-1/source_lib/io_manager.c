#include "io_manager.h"

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
