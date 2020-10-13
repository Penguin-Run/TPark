#include "lib/googletest/include/gtest/gtest.h"
extern "C" {
#include "config_sort.h"
#include "io_manager.h"
}


TEST(sort_test, date_sort) {
    // подготовка исходных данных
    const size_t TEST_DATA_SIZE = 4;
    auto* configs = (softConfig*) malloc(TEST_DATA_SIZE * sizeof(softConfig));

    // correct
    configs[0].versionNumber = 101;
    configs[0].installDate = {
            21,
            6,
            2019
    };
    configs[0].lastUpdateDate = configs[0].installDate;

    // incorrect (has been updated)
    configs[0].versionNumber = 102;
    configs[1].installDate = {
            21,
            6,
            2019
    };
    configs[1].lastUpdateDate = {
            17,
            3,
            2020
    };

    // incorrect (installed less than half a year ago)
    configs[0].versionNumber = 103;
    configs[2].installDate = {
            21,
            6,
            2020
    };
    configs[2].lastUpdateDate = configs[2].installDate;

    // correct
    configs[3].versionNumber = 104;
    configs[3].installDate = {
            11,
            2,
            1999
    };
    configs[3].lastUpdateDate = configs[3].installDate;


    // вызов тестируемой функции
    auto** sorted = (softConfig**) calloc(TEST_DATA_SIZE, sizeof(softConfig*));
    dateSort(configs, sorted, TEST_DATA_SIZE);

    // тесты
    // should sort only 0 and 3 config
    ASSERT_EQ(sorted[0]->versionNumber, configs[0].versionNumber);
    ASSERT_EQ(sorted[1]->versionNumber, configs[3].versionNumber);
    ASSERT_EQ(sorted[2], nullptr);

    // очистка памяти
    free(configs);
    free(sorted);
}

TEST(sort_test, group_sort) {
    // подготовка исходных данных
    const size_t TEST_DATA_SIZE = 5;
    auto* configs = (softConfig*) calloc((TEST_DATA_SIZE+1), sizeof(softConfig));

    configs[0].functionalClass = (char*) "Utilities"; configs[0].versionNumber = 101;
    configs[1].functionalClass = (char*) "Entertainment"; configs[1].versionNumber = 102;
    configs[2].functionalClass = (char*) "DevTools"; configs[2].versionNumber = 103;
    configs[3].functionalClass = (char*) "Utilities"; configs[3].versionNumber = 104;
    configs[4].functionalClass = (char*) "DevTools"; configs[4].versionNumber = 105;

    auto** configs_ptr = (softConfig**) malloc(TEST_DATA_SIZE * sizeof(softConfig*));
    for (int i = 0; i < TEST_DATA_SIZE; i++) configs_ptr[i] = &configs[i];
    configs_ptr[TEST_DATA_SIZE] = nullptr;


    // вызов тестируемых функций
    char** classNames = (char**) calloc(TEST_DATA_SIZE, sizeof(char*));
    int num_of_groups = find_group_names(configs_ptr, classNames, TEST_DATA_SIZE);

    auto*** sorted = (softConfig***) calloc(num_of_groups, sizeof(softConfig**));
    for (int i = 0; i < num_of_groups; i++) {
        sorted[i] = (softConfig**) calloc(TEST_DATA_SIZE, sizeof(softConfig*));
    }
    groupSort(configs_ptr, sorted, classNames, num_of_groups);


    // тесты
    ASSERT_EQ(sorted[0][0]->versionNumber, configs[0].versionNumber); // Utilities 101
    ASSERT_EQ(sorted[0][1]->versionNumber, configs[3].versionNumber); // Utilities 104
    ASSERT_EQ(sorted[0][2], nullptr); // only 2 Utilities structs, should be empty
    ASSERT_EQ(sorted[1][0]->versionNumber, configs[1].versionNumber); // Entertainment 102
    ASSERT_EQ(sorted[2][0]->versionNumber, configs[2].versionNumber); // DevTools 103
    ASSERT_EQ(sorted[2][1]->versionNumber, configs[4].versionNumber); // DevTools 105


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
    auto* configs = (softConfig*) calloc((TEST_DATA_SIZE+1), sizeof(softConfig));

    configs[0].name = (char*) "Zbc";
    configs[1].name = (char*) "Cbc";
    configs[2].name = (char*) "Fbc";
    configs[3].name = (char*) "Abc";
    configs[4].name = (char*) "Ebc";


    // вызов тестируемой функции
    auto** configs_ptr = (softConfig**) malloc((TEST_DATA_SIZE+1) * sizeof(softConfig*));
    for (int i = 0; i < TEST_DATA_SIZE; i++) configs_ptr[i] = &configs[i];
    configs_ptr[TEST_DATA_SIZE] = nullptr;

    ascendingSort(configs_ptr);


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