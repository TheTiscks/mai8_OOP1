#include "closest_pair.h"
#include <cmath>

bool isPerfectSquare(int num) {
    if (num < 0) {
        return false;
    }
    if (num == 0) {
        return true;
    }
    int root = static_cast<int>(std::sqrt(num));
    return root * root == num;
}

std::pair<int, int> closest_pair_tonum(int upper_limit) {
    for (int m = upper_limit - 1; m > 0; m--) { // Ищем макс, идем от больших (и до парковки)
        for (int n = m - 1; n > 0; n--) {
            int sum = m + n;
            int diff = m - n;
            if (isPerfectSquare(sum) && isPerfectSquare(diff)) {
                return std::make_pair(m, n);
            }
        }
    }
    return std::make_pair(-1, -1); // пары нет!
}
