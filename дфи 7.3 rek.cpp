#include <iostream>
#include <iomanip>
using namespace std;

void Input(int** a, const int rowCount, const int colCount, int row = 0, int col = 0);
void Print(int** a, const int rowCount, const int colCount, int row = 0, int col = 0);
int FindFirstZeroColumn(int** a, const int rowCount, const int colCount, int col = 0, int row = 0);
int CalculateRowCharacteristic(int* row, const int colCount, int col = 0);
void SortRowsByCharacteristic(int** a, const int rowCount, const int colCount, int row = 0, int iteration = 0);
void SwapRows(int** a, int row1, int row2);

int main() {
    int rowCount, colCount;
    cout << "rowCount = "; cin >> rowCount;
    cout << "colCount = "; cin >> colCount;

    int** a = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        a[i] = new int[colCount];

    Input(a, rowCount, colCount);
    // Виведення матриці
    Print(a, rowCount, colCount);

    // Пошук першого стовпця з нульовим елементом
    int firstZeroCol = FindFirstZeroColumn(a, rowCount, colCount);
    if (firstZeroCol != -1)
        cout << "First column with a zero element: " << firstZeroCol + 1 << endl; // 1-based індекс
    else
        cout << "No columns with zero elements." << endl;

    // Сортування рядків за спаданням характеристик
    SortRowsByCharacteristic(a, rowCount, colCount);

    // Виведення відсортованої матриці
    cout << "Matrix after sorting rows by decreasing characteristics:" << endl;
    Print(a, rowCount, colCount);

    // Очищення пам'яті
    for (int i = 0; i < rowCount; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}

// Рекурсивне введення елементів матриці
void Input(int** a, const int rowCount, const int colCount, int row, int col) {
    if (row == rowCount) return; // Умова завершення для рядків

    if (col < colCount) {
        cout << "a[" << row << "][" << col << "] = ";
        cin >> a[row][col];
        Input(a, rowCount, colCount, row, col + 1); // Рекурсія для стовпців
    }
    else {
        Input(a, rowCount, colCount, row + 1, 0); // Переходимо до наступного рядка
    }
}

// Рекурсивне виведення елементів матриці
void Print(int** a, const int rowCount, const int colCount, int row, int col) {
    if (row == rowCount) return; // Умова завершення для рядків

    if (col < colCount) {
        cout << setw(4) << a[row][col];
        Print(a, rowCount, colCount, row, col + 1); // Рекурсія для стовпців
    }
    else {
        cout << endl;
        Print(a, rowCount, colCount, row + 1, 0); // Переходимо до наступного рядка
    }
}

// Рекурсивний пошук першого стовпця з нульовим елементом
int FindFirstZeroColumn(int** a, const int rowCount, const int colCount, int col, int row) {
    if (col == colCount) return -1; // Якщо стовпці закінчилися

    if (row < rowCount) {
        if (a[row][col] == 0) return col;
        return FindFirstZeroColumn(a, rowCount, colCount, col, row + 1); // Рекурсія по рядках
    }
    else {
        return FindFirstZeroColumn(a, rowCount, colCount, col + 1, 0); // Переходимо до наступного стовпця
    }
}

// Рекурсивне обчислення характеристики рядка (сума від’ємних парних елементів)
int CalculateRowCharacteristic(int* row, const int colCount, int col) {
    if (col == colCount) return 0; // Якщо стовпці закінчилися

    if (row[col] < 0 && row[col] % 2 == 0) {
        return row[col] + CalculateRowCharacteristic(row, colCount, col + 1); // Додаємо елемент і викликаємо рекурсію
    }
    return CalculateRowCharacteristic(row, colCount, col + 1); // Пропускаємо елемент і викликаємо рекурсію
}

// Рекурсивне сортування рядків за спаданням характеристик
void SortRowsByCharacteristic(int** a, const int rowCount, const int colCount, int row, int iteration) {
    if (iteration == rowCount - 1) return; // Якщо ітерації завершилися

    if (row < rowCount - iteration - 1) {
        int characteristic1 = CalculateRowCharacteristic(a[row], colCount);
        int characteristic2 = CalculateRowCharacteristic(a[row + 1], colCount);

        if (characteristic1 < characteristic2) {
            SwapRows(a, row, row + 1); // Міняємо місцями рядки
        }
        SortRowsByCharacteristic(a, rowCount, colCount, row + 1, iteration); // Рекурсія по рядках
    }
    else {
        SortRowsByCharacteristic(a, rowCount, colCount, 0, iteration + 1); // Переходимо до наступної ітерації
    }
}

// Функція для обміну рядків
void SwapRows(int** a, int row1, int row2) {
    int* temp = a[row1];
    a[row1] = a[row2];
    a[row2] = temp;
}
