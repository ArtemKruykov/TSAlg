#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <locale>

using namespace std;

// Глобальные счетчики
long long comparisons = 0;
long long assignments = 0;

void resetCounters() {
    comparisons = 0;
    assignments = 0;
}

// 1. Сортировка выбором ("в лоб") - классическая со свапами (пока оставляем так)
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
        // Классическая перестановка (свап), если нашли элемент меньше
        if (minIndex != i) {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
            assignments += 3; // 3 присваивания при обмене
        }
    }
}

// 2. Сортировка вставками - по умолчанию работает через сдвиги (без свапов)
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        assignments++; // Запомнили элемент
        int j = i - 1;

        while (j >= 0) {
            comparisons++; // Считаем сравнение для while (arr[j] > key)
            if (arr[j] > key) {
                arr[j + 1] = arr[j]; // Сдвиг вправо
                assignments++;
                j--;
            }
            else {
                break;
            }
        }
        arr[j + 1] = key; // Вставка на нужное место
        assignments++;
    }
}

// 3. Быстрая сортировка (Хоара) - через левый и правый массивы (БЕЗ свапов)
void hoareSortExtraMemory(vector<int>& arr) {
    if (arr.size() <= 1) {
        return; // Массив из 1 или 0 элементов уже отсортирован
    }

    // Берем центральный элемент как опорный (pivot)
    int pivot = arr[arr.size() / 2];
    assignments++;

    vector<int> left;
    vector<int> right;
    vector<int> equals; // Для элементов, равных опорному, чтобы избежать бесконечной рекурсии

    // Распределяем элементы по массивам
    for (size_t i = 0; i < arr.size(); i++) {
        comparisons++;
        if (arr[i] < pivot) {
            left.push_back(arr[i]);
            assignments++; // Считаем добавление в массив как присваивание
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

    // Рекурсивно сортируем левую и правую части
    hoareSortExtraMemory(left);
    hoareSortExtraMemory(right);

    // Склеиваем отсортированные части обратно в исходный массив arr
    int index = 0;
    for (int x : left) {
        arr[index++] = x;
        assignments++; // Перезапись элемента
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

// Функция для генерации случайного массива от -100 до 100
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

    // --- Тест 1: Сортировка Выбором ---
    vector<int> arr1 = originalArray;
    resetCounters();
    selectionSort(arr1);
    cout << "\n1. Сортировка Выбором (в лоб):" << endl;
    cout << "Сравнений: " << comparisons << endl;
    cout << "Присваиваний: " << assignments << endl;


    // --- Тест 2: Сортировка Вставками ---
    vector<int> arr2 = originalArray;
    resetCounters();
    insertionSort(arr2);
    cout << "\n2. Сортировка Вставками:" << endl;
    cout << "Сравнений: " << comparisons << endl;
    cout << "Присваиваний: " << assignments << endl;

    // --- Тест 3: Сортировка Хоара (через доп. массивы) ---
    vector<int> arr3 = originalArray;
    resetCounters();
    hoareSortExtraMemory(arr3);
    cout << "\n3. Сортировка Хоара (через левый/правый массивы):" << endl;
    cout << "Сравнений: " << comparisons << endl;
    cout << "Присваиваний: " << assignments << endl;

    return 0;
}