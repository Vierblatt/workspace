#include <iostream>
#include <vector>

void assign_element(std::vector<int>& S, int i, int e) {
    if (i >= 0 && i < S.size()) {
        S[i] = e;
    } else {
        std::cout << "索引越界！" << std::endl;
    }
}

int main() {
    std::vector<int> S = {1, 2, 3, 4, 5};
    int i = 2; // 要赋值的位置
    int e = 99; // 新值

    std::cout << "原始序列: ";
    for (int v : S) std::cout << v << " ";
    std::cout << std::endl;

    assign_element(S, i, e);

    std::cout << "赋值后序列: ";
    for (int v : S) std::cout << v << " ";
    std::cout << std::endl;
    return 0;
}
