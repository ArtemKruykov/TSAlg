#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <locale>

using namespace std;

/**
 * @brief Сортирует массив методом выбора с использованием size_t и локальных счетчиков.
 * @param arr Вектор целых чисел для сортировки.
 * @param comp Ссылка на счетчик сравнений.
 * @param assign Ссылка на счетчик присваиваний.
 */
void selectionSort(vector<int>& arr, long long& comp, long long& assign) {
    size_t n = arr.size();
    for (size_t i = 0; i < n - 1; ++i) {
        size_t minIndex = i;
        for (size_t j = i + 1; j < n; ++j) {
            comp++;
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
            assign += 3;
        }
    }
}

/**
 * @brief Сортирует массив методом вставок.
 * @param arr Вектор целых чисел для сортировки.
 * @param comp Ссылка на счетчик сравнений.
 * @param assign Ссылка на счетчик присваиваний.
 */
void insertionSort(vector<int>& arr, long long& comp, long long& assign) {
    size_t n = arr.size();
    for (size_t i = 1; i < n; ++i) {
        int key = arr[i];
        assign++;

        size_t left = 0;
        size_t right = i;

        // Поиск места вставки методом половинного деления
        while (left < right) {
            size_t mid = left + (right - left) / 2;
            comp++;

            if (arr[mid] <= key) {
                left = mid + 1;
            }
            else {
                right = mid;
            }
        }

        size_t j = left;

        if (j < i) {
            arr.erase(arr.begin() + i);
            assign++;
            arr.insert(arr.begin() + j, key);
            assign++;
        }
    }
}

/**
 * @brief Сортировка Хоара.
 * @param arr Вектор целых чисел для сортировки.
 * @param comp Ссылка на счетчик сравнений.
 * @param assign Ссылка на счетчик присваиваний.
 */
void hoareSortExtraMemory(vector<int>& arr, long long& comp, long long& assign) {
    if (arr.size() <= 1) {
        return;
    }

    int pivot = arr[arr.size() / 2];
    assign++;

    vector<int> left;
    vector<int> right;
    vector<int> equals;

    for (size_t i = 0; i < arr.size(); i++) {
        comp++;
        if (arr[i] < pivot) {
            left.push_back(arr[i]);
        }
        else {
            comp++;
            if (arr[i] > pivot) {
                right.push_back(arr[i]);
            }
            else {
                equals.push_back(arr[i]);
            }
        }

        assign++;
    }

    hoareSortExtraMemory(left, comp, assign);
    hoareSortExtraMemory(right, comp, assign);

    size_t index = 0;
    for (size_t i = 0; i < left.size(); ++i) {
        arr[index++] = left[i];
        assign++;
    }
    for (size_t i = 0; i < equals.size(); ++i) {
        arr[index++] = equals[i];
        assign++;
    }
    for (size_t i = 0; i < right.size(); ++i) {
        arr[index++] = right[i];
        assign++;
    }
}

/**
 * @brief Генерирует массив заданного размера, заполненный случайными числами от -100 до 100.
 * @param size Количество элементов в массиве.
 * @return Вектор со случайными числами.
 */
vector<int> generateRandomArray(size_t size) {
    vector<int> arr(size);
    for (size_t i = 0; i < size; ++i) {
        arr[i] = rand() % 201 - 100;
    }
    return arr;
}


int main() {
    setlocale(LC_ALL, "RUSSIAN");
    srand(static_cast<unsigned int>(time(0)));
    size_t N = 10000;

    cout << "Генерируем массив из " << N << " элементов..." << endl;
    vector<int> originalArray = generateRandomArray(N);

    // 1. Сортировка Выбором
    vector<int> arr1 = originalArray;
    long long comp1 = 0, assign1 = 0;
    selectionSort(arr1, comp1, assign1);
    cout << "\n1. Сортировка Выбором (в лоб):" << endl;
    cout << "Сравнений: " << comp1 << endl;
    cout << "Присваиваний: " << assign1 << endl;

    // 2. Сортировка Вставками
    vector<int> arr2 = originalArray;
    long long comp2 = 0, assign2 = 0;
    insertionSort(arr2, comp2, assign2);
    cout << "\n2. Сортировка Вставками :" << endl;
    cout << "Сравнений: " << comp2 << endl;
    cout << "Присваиваний: " << assign2 << endl;

    // 3. Сортировка Хоара
    vector<int> arr3 = originalArray;
    long long comp3 = 0, assign3 = 0;
    hoareSortExtraMemory(arr3, comp3, assign3);
    cout << "\n3. Сортировка Хоара :" << endl;
    cout << "Сравнений: " << comp3 << endl;
    cout << "Присваиваний: " << assign3 << endl;

    return 0;
}