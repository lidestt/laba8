#include <iostream>
#include "marathon_results.h"
#include "file_reader.h"
#include "filter.h"
#include "sort.h"
#include "utils.h"

using namespace std;

void showMenu() {
    cout << "\n=== МЕНЮ ОБРАБОТКИ РЕЗУЛЬТАТОВ МАРАФОНА ===\n";
    cout << "1. Вывести всех участников\n";
    cout << "2. Фильтрация данных\n";
    cout << "3. Сортировка данных\n";
    cout << "4. Выход\n";
    cout << "Выберите опцию: ";
}

void showFilterMenu() {
    cout << "\n=== ФИЛЬТРАЦИЯ ДАННЫХ ===\n";
    cout << "1. Участники из клуба 'Спартак'\n";
    cout << "2. Участники с результатом лучше 2:50:00\n";
    cout << "3. Назад\n";
    cout << "Выберите опцию: ";
}

void showSortMenu() {
    cout << "\n=== СОРТИРОВКА ДАННЫХ ===\n";
    cout << "1. Метод сортировки:\n";
    cout << "   1. Сортировка обменом (Bubble sort)\n";
    cout << "   2. Быстрая сортировка (Quick sort)\n";
    cout << "2. Критерий сортировки:\n";
    cout << "   1. По времени забега (по возрастанию)\n";
    cout << "   2. По клубу и фамилии\n";
    cout << "3. Назад\n";
    cout << "Выберите опцию: ";
}

int main() {
    setlocale(LC_ALL, "Russian");
    
    cout << "Лабораторная работа: Обработка результатов марафона\n";
    cout << "Вариант #1: Результаты марафона\n";
    cout << "Автор: [Артём Базылев]\n";
    cout << "Группа: [25ПИНЖ1Д]\n\n";
    
    Participant* participants[MAX_FILE_ROWS_COUNT];
    int size = 0;
    
    try {
        // Чтение данных из файла
        readParticipants("data.txt", participants, size);
        cout << "Загружено " << size << " участников\n";
        
        int choice;
        do {
            showMenu();
            cin >> choice;
            
            switch (choice) {
                case 1: {
                    // Вывод всех участников
                    printParticipants(participants, size);
                    break;
                }
                case 2: {
                    // Фильтрация данных
                    int filterChoice;
                    do {
                        showFilterMenu();
                        cin >> filterChoice;
                        
                        if (filterChoice == 1 || filterChoice == 2) {
                            int filteredSize = 0;
                            Participant** filtered = nullptr;
                            
                            if (filterChoice == 1) {
                                filtered = filterParticipants(participants, size, isFromSpartak, filteredSize);
                                cout << "\nУчастники из клуба 'Спартак':\n";
                            } else {
                                filtered = filterParticipants(participants, size, hasResultBetterThan250, filteredSize);
                                cout << "\nУчастники с результатом лучше 2:50:00:\n";
                            }
                            
                            if (filteredSize > 0) {
                                printParticipants(filtered, filteredSize);
                                cout << "Найдено: " << filteredSize << " участников\n";
                            } else {
                                cout << "Участники не найдены\n";
                            }
                            
                            delete[] filtered;
                        }
                    } while (filterChoice != 3);
                    break;
                }
                case 3: {
                    // Сортировка данных
                    int sortChoice;
                    do {
                        showSortMenu();
                        cin >> sortChoice;
                        
                        if (sortChoice == 1 || sortChoice == 2) {
                            // Выбор метода сортировки
                            int methodChoice;
                            cout << "\nВыберите метод сортировки (1 - Bubble sort, 2 - Quick sort): ";
                            cin >> methodChoice;
                            
                            // Выбор критерия сортировки
                            int criteriaChoice;
                            cout << "Выберите критерий сортировки (1 - по времени, 2 - по клубу и фамилии): ";
                            cin >> criteriaChoice;
                            
                            // Создаем копию массива для сортировки
                            Participant* sorted[MAX_FILE_ROWS_COUNT];
                            for (int i = 0; i < size; i++) {
                                sorted[i] = participants[i];
                            }
                            
                            // Выбор функции сравнения
                            int (*compareFunction)(Participant*, Participant*) = nullptr;
                            if (criteriaChoice == 1) {
                                compareFunction = compareByRaceTime;
                            } else {
                                compareFunction = compareByClubAndLastName;
                            }
                            
                            // Выбор метода сортировки
                            if (methodChoice == 1) {
                                bubbleSort(sorted, size, compareFunction);
                                cout << "\nСортировка выполнена методом Bubble sort\n";
                            } else {
                                quickSortWrapper(sorted, size, compareFunction);
                                cout << "\nСортировка выполнена методом Quick sort\n";
                            }
                            
                            printParticipants(sorted, size);
                        }
                    } while (sortChoice != 3);
                    break;
                }
                case 4: {
                    cout << "Выход из программы...\n";
                    break;
                }
                default: {
                    cout << "Неверный выбор. Попробуйте снова.\n";
                }
            }
        } while (choice != 4);
        
        // Освобождение памяти
        for (int i = 0; i < size; i++) {
            delete participants[i];
        }
        
    } catch (const char* error) {
        cout << "Ошибка: " << error << endl;
    }
    
    return 0;
}