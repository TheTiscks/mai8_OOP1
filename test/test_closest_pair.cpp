#include <gtest/gtest.h>
#include "closest_pair.h"
#include <cmath>
#include <chrono>
#include <vector>

// проверка корректности пары
void ValidatePair(const std::pair<int, int>& result, int upper_limit) {
    int m = result.first;
    int n = result.second;
    // грань > m > n > 0
    EXPECT_LT(m, upper_limit) << "m должно быть меньше upper_limit";
    EXPECT_GT(m, n) << "m должно быть больше n";
    EXPECT_GT(n, 0) << "n должно быть больше 0";
    int sum = m + n; // сумма - полный квадрат?
    EXPECT_TRUE(isPerfectSquare(sum)) << "Сумма " << sum << " должна быть полным квадратом";
    int diff = m - n; // разность - полный квадрат?
    EXPECT_TRUE(isPerfectSquare(diff)) << "Разность " << diff << " должна быть полным квадратом";
}

// Тестовый класс для группировки тестов
class ClosestPairTest : public ::testing::Test {
protected:
    void SetUp() override {
        // инициализация перед каждым тестом
    }

    void TearDown() override {
        // очистка после каждого теста
    }
};


// Тесты isPerfectSquare
TEST_F(ClosestPairTest, IsPerfectSquare_BasicCases) {
    EXPECT_TRUE(isPerfectSquare(0));   // 0² = 0
    EXPECT_TRUE(isPerfectSquare(1));   // 1² = 1
    EXPECT_TRUE(isPerfectSquare(4));   // 2² = 4
    EXPECT_TRUE(isPerfectSquare(9));   // 3² = 9
    EXPECT_TRUE(isPerfectSquare(16));  // 4² = 16
    EXPECT_TRUE(isPerfectSquare(25));  // 5² = 25
    EXPECT_TRUE(isPerfectSquare(36));  // 6² = 36
    EXPECT_TRUE(isPerfectSquare(49));  // 7² = 49
    EXPECT_TRUE(isPerfectSquare(64));  // 8² = 64
    EXPECT_TRUE(isPerfectSquare(81));  // 9² = 81
    EXPECT_TRUE(isPerfectSquare(100)); // 10² = 100
}

TEST_F(ClosestPairTest, IsPerfectSquare_NonSquares) {
    EXPECT_FALSE(isPerfectSquare(2));
    EXPECT_FALSE(isPerfectSquare(3));
    EXPECT_FALSE(isPerfectSquare(5));
    EXPECT_FALSE(isPerfectSquare(6));
    EXPECT_FALSE(isPerfectSquare(7));
    EXPECT_FALSE(isPerfectSquare(8));
    EXPECT_FALSE(isPerfectSquare(10));
    EXPECT_FALSE(isPerfectSquare(15));
    EXPECT_FALSE(isPerfectSquare(99));
}

TEST_F(ClosestPairTest, IsPerfectSquare_EdgeCases) {
    EXPECT_FALSE(isPerfectSquare(-1));
    EXPECT_FALSE(isPerfectSquare(-4));
    EXPECT_TRUE(isPerfectSquare(0));
}

// Тесты для основной функции
TEST_F(ClosestPairTest, ClosestPairTonum_BasicExamples) {
    // из условия: closest_pair_tonum(10) == (5, 4)
    auto result = closest_pair_tonum(10);
    EXPECT_EQ(result.first, 5);
    EXPECT_EQ(result.second, 4);
    ValidatePair(result, 10);

    // 5+4=9=3^2, 5-4=1=1^2
    EXPECT_EQ(5 + 4, 9);
    EXPECT_EQ(static_cast<int>(std::sqrt(9)), 3);
    EXPECT_EQ(5 - 4, 1);
    EXPECT_EQ(static_cast<int>(std::sqrt(1)), 1);
}

TEST_F(ClosestPairTest, ClosestPairTonum_Example30) {
    // из условия
    auto result = closest_pair_tonum(30);
    EXPECT_EQ(result.first, 29);
    EXPECT_EQ(result.second, 20);
    ValidatePair(result, 30);

    // 29+20=49=7^2, 29-20=9=3^2
    EXPECT_EQ(29 + 20, 49);
    EXPECT_EQ(static_cast<int>(std::sqrt(49)), 7);
    EXPECT_EQ(29 - 20, 9);
    EXPECT_EQ(static_cast<int>(std::sqrt(9)), 3);
}

TEST_F(ClosestPairTest, ClosestPairTonum_Example50) {
    // из условия: closest_pair_tonum(50) == (45, 36)
    auto result = closest_pair_tonum(50);
    EXPECT_EQ(result.first, 45);
    EXPECT_EQ(result.second, 36);
    ValidatePair(result, 50);

    // 45+36=81=9^2, 45-36=9=3^2
    EXPECT_EQ(45 + 36, 81);
    EXPECT_EQ(static_cast<int>(std::sqrt(81)), 9);
    EXPECT_EQ(45 - 36, 9);
    EXPECT_EQ(static_cast<int>(std::sqrt(9)), 3);
}

// Тесты граничных случаев
TEST_F(ClosestPairTest, ClosestPairTonum_SmallNumbers) {
    // Для очень малых чисел
    auto result = closest_pair_tonum(5);
    // Должен вернуть (-1, -1), нет подходящих пар
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, -1);
    result = closest_pair_tonum(6);
    EXPECT_EQ(result.first, 5);
    EXPECT_EQ(result.second, 4);
}

TEST_F(ClosestPairTest, ClosestPairTonum_EdgeCase1) {
    auto result = closest_pair_tonum(1);
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, -1);
}

TEST_F(ClosestPairTest, ClosestPairTonum_EdgeCase2) {
    auto result = closest_pair_tonum(2);
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, -1);
}

// Тесты для больших чисел
TEST_F(ClosestPairTest, ClosestPairTonum_LargerNumbers) {
    auto result = closest_pair_tonum(100);
    EXPECT_NE(result.first, -1);  // Должна быть найдена пара
    EXPECT_NE(result.second, -1);
    ValidatePair(result, 100);

    // это действительно максимальная пара? нет пары с большим m?
    bool found_larger = false;
    for (int m = result.first + 1; m < 100; m++) {
        for (int n = m - 1; n > 0; n--) {
            if (isPerfectSquare(m + n) && isPerfectSquare(m - n)) {
                found_larger = true;
                break;
            }
        }
        if (found_larger) break;
    }
    EXPECT_FALSE(found_larger) << "Найдена пара с большим m";
}

// Параметризованный тест для проверки различных значений
class ClosestPairParameterizedTest : public ::testing::TestWithParam<std::pair<int, std::pair<int, int>>> {
};

TEST_P(ClosestPairParameterizedTest, VariousUpperLimits) {
    int upper_limit = GetParam().first;
    int expected_m = GetParam().second.first;
    int expected_n = GetParam().second.second;
    auto result = closest_pair_tonum(upper_limit);
    if (expected_m == -1) {
        // Ожидается, что пара не найдена
        EXPECT_EQ(result.first, -1);
        EXPECT_EQ(result.second, -1);
    } else {
        // Ожидается конкретная пара
        EXPECT_EQ(result.first, expected_m);
        EXPECT_EQ(result.second, expected_n);
        // Дополнительная проверка корректности
        ValidatePair(result, upper_limit);
    }
}

// Значения для параметризованного теста
INSTANTIATE_TEST_SUITE_P(
    DifferentUpperLimits,
    ClosestPairParameterizedTest,
    ::testing::Values(
        std::pair<int, std::pair<int, int>>(1, std::pair<int, int>(-1, -1)),     // Нет решения
        std::pair<int, std::pair<int, int>>(2, std::pair<int, int>(-1, -1)),     // Нет решения
        std::pair<int, std::pair<int, int>>(5, std::pair<int, int>(-1, -1)),     // Нет решения
        std::pair<int, std::pair<int, int>>(6, std::pair<int, int>(5, 4)),       // (5,4)
        std::pair<int, std::pair<int, int>>(10, std::pair<int, int>(5, 4)),      // (5,4)
        std::pair<int, std::pair<int, int>>(30, std::pair<int, int>(29, 20)),    // (29,20)
        std::pair<int, std::pair<int, int>>(50, std::pair<int, int>(45, 36))     // (45,36)
    )
);

// Тест производительности
TEST_F(ClosestPairTest, Performance_ReasonableTime) {
    // Проверим, функция работает ли за разумное время для умеренно больших чисел
    auto start = std::chrono::high_resolution_clock::now();
    auto result = closest_pair_tonum(200);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    // Ожидаем, что выполнение займет менее 1 секунды
    EXPECT_LT(duration.count(), 1000) << "Функция работает слишком медленно";
    if (result.first != -1) {
        ValidatePair(result, 200);
    }
}

// Дополнительный тест для проверки математической корректности
TEST_F(ClosestPairTest, MathematicalProperties) {
    std::vector<int> test_limits = {10, 20, 30, 50, 70, 100};
    for (int limit : test_limits) {
        auto result = closest_pair_tonum(limit);
        if (result.first != -1) {
            int m = result.first;
            int n = result.second;
            int sum = m + n;
            int diff = m - n;
            int sum_root = static_cast<int>(std::sqrt(sum)); // корни целые?
            int diff_root = static_cast<int>(std::sqrt(diff));
            EXPECT_EQ(sum_root * sum_root, sum)
                << "Для limit=" << limit << ", сумма " << sum << " не является точным квадратом";
            EXPECT_EQ(diff_root * diff_root, diff)
                << "Для limit=" << limit << ", разность " << diff << " не является точным квадратом";
        }
    }
}
