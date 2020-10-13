#include "source.c"

/*
 Для более наглядного выделения памяти все функции работают с указателями на уже выделенную память.
 Исключение - функции ввода данных setHardData и consoleInput, которые возвращают указатель на выделенную память.
 */

int main() {
    // ввод данных
    int* num_of_elements;
    softConfig* configs = setHardData(num_of_elements);
    assert(*num_of_elements > 0);

    // сортировка по датам
    softConfig** configs_ptrs = (softConfig**) calloc(*num_of_elements, sizeof(softConfig*));
    dateSort(configs, configs_ptrs, *num_of_elements);

    // определение групп по именам функциональных классов
    char** classNames = (char**) calloc(*num_of_elements, sizeof(char*));
    int num_of_groups = find_group_names(configs_ptrs, classNames, *num_of_elements);

    // сортировка по группам
    softConfig*** config_groups_ptrs = (softConfig***) calloc(num_of_groups, sizeof(softConfig**));
    for (int i = 0; i < num_of_groups; i++) {
        config_groups_ptrs[i] = (softConfig**) calloc(*num_of_elements, sizeof(softConfig*));
    }
    groupSort(configs_ptrs, config_groups_ptrs, classNames, num_of_groups, *num_of_elements);

    // сортировка по алфавиту в рамках групп
    alphabetical_sort(config_groups_ptrs);

    // печать всех групп
    groupPrint(config_groups_ptrs);

    // освобождение выделенной памяти
    free(configs);
    free(configs_ptrs);
    free(classNames);
    for (int i = 0; i < num_of_groups; i++) free(config_groups_ptrs[i]);
    free(config_groups_ptrs);
    return 0;
}
