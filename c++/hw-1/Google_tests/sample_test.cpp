#include "lib/googletest/include/gtest/gtest.h"
extern "C" {
#include "../source_lib/source.c"
}


TEST(sort_test, date_sort) {
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

    softConfig** sorted = dateSort(configs);

    // should sort only 0 and 3 config
    ASSERT_EQ(sorted[0]->versionNumber, configs[0].versionNumber);
    ASSERT_EQ(sorted[1]->versionNumber, configs[3].versionNumber);
    ASSERT_EQ(sorted[2], nullptr);

    free(configs);
    free(sorted);
}

TEST(sort_test, group_sort) {
    const size_t TEST_DATA_SIZE = 3;
    auto* configs = (softConfig*) calloc(TEST_DATA_SIZE, sizeof(softConfig));

    configs[0].functionalClass = "Utilities"; configs[0].versionNumber = 101;
    configs[1].functionalClass = "Entertainment"; configs[1].versionNumber = 102;
    configs[2].functionalClass = "DevTools"; configs[2].versionNumber = 103;
    configs[3].functionalClass = "Utilities"; configs[3].versionNumber = 104;
    configs[4].functionalClass = "DevTools"; configs[4].versionNumber = 105;

    auto** configs_ptr = (softConfig**) malloc(TEST_DATA_SIZE * sizeof(softConfig*));
    for (int i = 0; i < TEST_DATA_SIZE; i++) configs_ptr[i] = &configs[i];

    // softConfig*** sorted = groupSort(configs_ptr);

    // ASSERT_EQ(sorted[0][0]->versionNumber, configs[0].versionNumber);
    // ASSERT_EQ(sorted[0][1]->versionNumber, configs[3].versionNumber);
    // ASSERT_EQ(sorted[0][2], nullptr);
    // ASSERT_EQ(sorted[1][0]->versionNumber, configs[1].versionNumber);

    free(configs_ptr);
    free(configs);
}

TEST(sort_test, alphabetical_sort) {

}
