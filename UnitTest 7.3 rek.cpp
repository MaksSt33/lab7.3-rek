
#include "pch.h"
#include "CppUnitTest.h"
#include "../lab 7.3 it/lab 7.3 it.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest73it
{
    TEST_CLASS(UnitTest73it)
    {
    public:

        TEST_METHOD(TestFindFirstZeroColumn)
        {
            int rowCount = 3;
            int colCount = 3;
            int** matrix = new int* [rowCount];
            for (int i = 0; i < rowCount; i++)
                matrix[i] = new int[colCount];

            matrix[0][0] = 1; matrix[0][1] = 0; matrix[0][2] = 3;
            matrix[1][0] = 4; matrix[1][1] = 5; matrix[1][2] = 6;
            matrix[2][0] = 7; matrix[2][1] = 8; matrix[2][2] = 0;

            int firstZeroCol = FindFirstZeroColumn(matrix, rowCount, colCount);
            Assert::AreEqual(1, firstZeroCol);

            for (int i = 0; i < rowCount; i++)
                delete[] matrix[i];
            delete[] matrix;
        }

        TEST_METHOD(TestCalculateRowCharacteristic)
        {
            int colCount = 3;
            int row[] = { -4, -3, -2 };
            int characteristic = CalculateRowCharacteristic(row, colCount);
            Assert::AreEqual(-6, characteristic);
        }

        TEST_METHOD(TestSortRowsByCharacteristic)
        {
            int rowCount = 3;
            int colCount = 3;
            int** matrix = new int* [rowCount];
            for (int i = 0; i < rowCount; i++)
                matrix[i] = new int[colCount];
            matrix[0][0] = -4; matrix[0][1] = -3; matrix[0][2] = -2;
            matrix[1][0] = -1; matrix[1][1] = -2; matrix[1][2] = 1;
            matrix[2][0] = -8; matrix[2][1] = -6; matrix[2][2] = -4;

            SortRowsByCharacteristic(matrix, rowCount, colCount);

            Assert::AreEqual(-2, CalculateRowCharacteristic(matrix[0], colCount));
            Assert::AreEqual(-6, CalculateRowCharacteristic(matrix[1], colCount));
            Assert::AreEqual(-18, CalculateRowCharacteristic(matrix[2], colCount));

            for (int i = 0; i < rowCount; i++)
                delete[] matrix[i];
            delete[] matrix;
        }
    };
}
