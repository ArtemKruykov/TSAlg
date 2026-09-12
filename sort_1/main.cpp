#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <locale>

using namespace std;

/// @brief Глобальный счетчик количества операций сравнения.
long long comparisons = 0;

/// @brief Глобальный счетчик количества операций присваивания.
long long assignments = 0;

/**
 * @brief Сбрасывает глобальные счетчики операций перед запуском нового алгоритма.
 */
void resetCounters() {
    comparisons = 0;
    assignments = 0;
}

/**
 * @brief Сортирует массив методом выбора (в лоб) с использованием временной переменной для обмена.
 * @param arr Ссылка на вектор целых чисел, который нужно отсортировать.
 */
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            comparisons++;
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
            assignments += 3;
        }
    }
}

/**
 * @brief Сортирует массив методом вставок, используя сдвиг элементов вправо.
 * @param arr Ссылка на вектор целых чисел для сортировки.
 */
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        assignments++;
        int j = i - 1;

        while (j >= 0) {
            comparisons++;
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                assignments++;
                j--;
            }
            else {
                break;
            }
        }
        arr[j + 1] = key;
        assignments++;
    }
}

/**
 * @brief Сортирует массив алгоритмом быстрой сортировки (Хоара).
 * @param arr Ссылка на вектор целых чисел для сортировки.
 */
void hoareSortExtraMemory(vector<int>& arr) {
    if (arr.size() <= 1) {
        return;
    }

    int pivot = arr[arr.size() / 2];
    assignments++;

    vector<int> left;
    vector<int> right;
    vector<int> equals;

    for (size_t i = 0; i < arr.size(); i++) {
        comparisons++;
        if (arr[i] < pivot) {
            left.push_back(arr[i]);
            assignments++;
        }
        else {
            comparisons++;
            if (arr[i] > pivot) {
                right.push_back(arr[i]);
                assignments++;
            }
            else {
                equals.push_back(arr[i]);
                assignments++;
            }
        }
    }

    hoareSortExtraMemory(left);
    hoareSortExtraMemory(right);

    int index = 0;
    for (int x : left) {
        arr[index++] = x;
        assignments++;
    }
    for (int x : equals) {
        arr[index++] = x;
        assignments++;
    }
    for (int x : right) {
        arr[index++] = x;
        assignments++;
    }
}

/**
 * @brief Генерирует массив заданного размера, заполненный случайными числами от -100 до 100.
 * @param size Количество элементов в генерируемом массиве.
 * @return Вектор (vector<int>), содержащий случайные числа.
 */
vector<int> generateRandomArray(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 201 - 100;
    }
    return arr;
}


int main() {
    setlocale(LC_ALL, "RUSSIAN");
    srand(time(0));
    int N = 10000;

    cout << "Генерируем массив из " << N << " элементов..." << endl;
    vector<int> originalArray = generateRandomArray(N);

    // Сортировка Выбором
    vector<int> arr1 = originalArray;
    resetCounters();
    selectionSort(arr1);
    cout << "\n1. Сортировка Выбором (в лоб):" << endl;
    cout << "Сравнений: " << comparisons << endl;
    cout << "Присваиваний: " << assignments << endl;

    // Сортировка Вставками
    vector<int> arr2 = originalArray;
    resetCounters();
    insertionSort(arr2);
    cout << "\n2. Сортировка Вставками:" << endl;
    cout << "Сравнений: " << comparisons << endl;
    cout << "Присваиваний: " << assignments << endl;

    // Сортировка Хоара 
    vector<int> arr3 = originalArray;
    resetCounters();
    hoareSortExtraMemory(arr3);
    cout << "\n3. Сортировка Хоара:" << endl;
    cout << "Сравнений: " << comparisons << endl;
    cout << "Присваиваний: " << assignments << endl;

    return 0;
}