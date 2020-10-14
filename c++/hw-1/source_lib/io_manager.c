#include "io_manager.h"

void input_date(date* date) {
    assert(date);
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
soft_config* console_input(int* number_of_elements) {
    // ввод количества структур
    printf("Please, enter the number of apps you want to add configs about:\n");
    // int num_of_elements = -1;
    scanf("%d", number_of_elements);
    assert(*number_of_elements > 0);

    soft_config* configs = (soft_config*) calloc(*number_of_elements, sizeof(soft_config));
    assert(configs);
    for (int i = 0; i < *number_of_elements; i++) {
        printf("Enter information about app #%d:\n", i+1);
        printf("Enter name:\n");
        size_t linecap = 0;

        if (i == 0) getline(&configs[i].name, &linecap, stdin);
        getline(&configs[i].name, &linecap, stdin);

        while (!configs[i].functional_class || configs[i].functional_class[0] <= 65 || configs[i].functional_class[0] >= 90) {
            printf("Enter functional class of the app. Please, start with upper-case letter:\n");
            getline(&configs[i].functional_class, &linecap, stdin);
        }

        char *version_number_str = NULL;
        while (!configs[i].version_number || configs[i].version_number <= 0) {
            printf("Enter version number (9 digits or less): ");
            getline(&version_number_str, &linecap, stdin);
            configs[i].version_number = atoi(version_number_str);
        }

        printf("Enter app installation date:\n");
        input_date(&configs[i].install_date);

        printf("Enter app last update date:\n");
        input_date(&configs[i].last_update_date);
    }

    return configs;
}

// allocate memory!
soft_config* set_hard_data(int* number_of_elements) {
    *number_of_elements = HARD_DATA_SIZE;
    soft_config* configs = (soft_config*) calloc(*number_of_elements, sizeof(soft_config));
    assert(configs);
    soft_config a = {"Word",
                     "Utilities",
                     1293,
                     {21, 6, 2019},
                     {21, 6, 2019}
    };
    configs[0] = a;

    soft_config b = {"Excel",
                     "Utilities",
                     1344,
                     {23, 6, 2019},
                     {23, 6, 2019}
    };
    configs[1] = b;

    soft_config c = {"Clion",
                     "DevTools",
                     3764,
                     {12, 1, 2020},
                     {12, 1, 2020}
    };
    configs[2] = c;

    soft_config d = {"RubyMine",
                     "DevTools",
                     2948,
                     {12, 1, 2020},
                     {12, 1, 2020}
    };
    configs[3] = d;

    soft_config e = {"Spotify",
                     "Entertainment",
                     2948,
                     {12, 1, 2020},
                     {12, 1, 2020}
    };
    configs[4] = e;
    return configs;
}

void group_print(soft_config*** configs) {
    assert(configs);
    int i = 0;
    while(configs[i]) {
        assert(configs[i]);
        printf("%s:\n", configs[i][0]->functional_class);
        int j = 0;
        while (configs[i][j]) {
            assert(configs[i][j]);
            printf("-- %s  (install date: %d.%d.%d)\n", configs[i][j]->name, configs[i][j]->install_date.day, configs[i][j]->install_date.month, configs[i][j]->install_date.year);
            j++;
        }
        printf("\n");
        i++;
    }
}
