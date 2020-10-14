#include "lib/googletest/include/gtest/gtest.h"
extern "C" {
#include "config_sort.h"
#include "io_manager.h"
}


TEST(sort_test, date_sort) {
    // подготовка исходных данных
    const size_t TEST_DATA_SIZE = 4;
    auto* configs = (soft_config*) malloc(TEST_DATA_SIZE * sizeof(soft_config));

    // correct
    configs[0].version_number = 101;
    configs[0].install_date = {
            21,
            6,
            2019
    };
    configs[0].last_update_date = configs[0].install_date;

    // incorrect (has been updated)
    configs[0].version_number = 102;
    configs[1].install_date = {
            21,
            6,
            2019
    };
    configs[1].last_update_date = {
            17,
            3,
            2020
    };

    // incorrect (installed less than half a year ago)
    configs[0].version_number = 103;
    configs[2].install_date = {
            21,
            6,
            2020
    };
    configs[2].last_update_date = configs[2].install_date;

    // correct
    configs[3].version_number = 104;
    configs[3].install_date = {
            11,
            2,
            1999
    };
    configs[3].last_update_date = configs[3].install_date;


    // вызов тестируемой функции
    auto** sorted = (soft_config**) calloc(TEST_DATA_SIZE, sizeof(soft_config*));
    date_sort(configs, sorted, TEST_DATA_SIZE);

    // тесты
    // should sort only 0 and 3 config
    ASSERT_EQ(sorted[0]->version_number, configs[0].version_number);
    ASSERT_EQ(sorted[1]->version_number, configs[3].version_number);
    ASSERT_EQ(sorted[2], nullptr);

    // очистка памяти
    free(configs);
    free(sorted);
}

TEST(sort_test, group_sort) {
    // подготовка исходных данных
    const size_t TEST_DATA_SIZE = 5;
    auto* configs = (soft_config*) calloc((TEST_DATA_SIZE + 1), sizeof(soft_config));

    configs[0].functional_class = (char*) "Utilities"; configs[0].version_number = 101;
    configs[1].functional_class = (char*) "Entertainment"; configs[1].version_number = 102;
    configs[2].functional_class = (char*) "DevTools"; configs[2].version_number = 103;
    configs[3].functional_class = (char*) "Utilities"; configs[3].version_number = 104;
    configs[4].functional_class = (char*) "DevTools"; configs[4].version_number = 105;

    auto** configs_ptr = (soft_config**) malloc(TEST_DATA_SIZE * sizeof(soft_config*));
    for (int i = 0; i < TEST_DATA_SIZE; i++) configs_ptr[i] = &configs[i];
    configs_ptr[TEST_DATA_SIZE] = nullptr;


    // вызов тестируемых функций
    char** classNames = (char**) calloc(TEST_DATA_SIZE, sizeof(char*));
    int num_of_groups = find_group_names(configs_ptr, classNames, TEST_DATA_SIZE);

    auto*** sorted = (soft_config***) calloc(num_of_groups, sizeof(soft_config**));
    for (int i = 0; i < num_of_groups; i++) {
        sorted[i] = (soft_config**) calloc(TEST_DATA_SIZE, sizeof(soft_config*));
    }
    group_sort(configs_ptr, sorted, classNames, num_of_groups);


    // тесты
    ASSERT_EQ(sorted[0][0]->version_number, configs[0].version_number); // Utilities 101
    ASSERT_EQ(sorted[0][1]->version_number, configs[3].version_number); // Utilities 104
    ASSERT_EQ(sorted[0][2], nullptr); // only 2 Utilities structs, should be empty
    ASSERT_EQ(sorted[1][0]->version_number, configs[1].version_number); // Entertainment 102
    ASSERT_EQ(sorted[2][0]->version_number, configs[2].version_number); // DevTools 103
    ASSERT_EQ(sorted[2][1]->version_number, configs[4].version_number); // DevTools 105


    // очистка памяти
    free(configs);
    free(configs_ptr);
    free(classNames);
    for (int i = 0; i < num_of_groups; i++) free(sorted[i]);
    free(sorted);
}


TEST(sort_test, alphabet_sort) {
    // подготовка исходных данных
    const size_t TEST_DATA_SIZE = 5;
    auto* configs = (soft_config*) calloc((TEST_DATA_SIZE + 1), sizeof(soft_config));

    configs[0].name = (char*) "Zbc";
    configs[1].name = (char*) "Cbc";
    configs[2].name = (char*) "Fbc";
    configs[3].name = (char*) "Abc";
    configs[4].name = (char*) "Ebc";


    // вызов тестируемой функции
    auto** configs_ptr = (soft_config**) malloc((TEST_DATA_SIZE + 1) * sizeof(soft_config*));
    for (int i = 0; i < TEST_DATA_SIZE; i++) configs_ptr[i] = &configs[i];
    configs_ptr[TEST_DATA_SIZE] = nullptr;

    ascending_sort(configs_ptr);


    // тесты
    ASSERT_FALSE(strcmp(configs_ptr[0]->name, "Abc"));
    ASSERT_FALSE(strcmp(configs_ptr[1]->name, "Cbc"));
    ASSERT_FALSE(strcmp(configs_ptr[2]->name, "Ebc"));
    ASSERT_FALSE(strcmp(configs_ptr[3]->name, "Fbc"));
    ASSERT_FALSE(strcmp(configs_ptr[4]->name, "Zbc"));
    ASSERT_EQ(configs_ptr[5], nullptr);


    // очистка памяти
    free(configs);
    free(configs_ptr);
}