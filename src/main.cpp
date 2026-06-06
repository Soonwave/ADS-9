// Copyright 2022 NNTU-CS
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include "tree.h"

void printPerm(const std::vector<char>& v) {
    for (char c : v) std::cout << c;
    std::cout << "\n";
}

int main() {
    std::vector<char> in = { '1', '2', '3' };
    PMTree tree(in);
    std::vector<std::vector<char>> perms = getAllPerms(tree);

    for (const auto& p : perms) {
        printPerm(p);
    }

    std::vector<char> in4 = { '1', '3', '5', '7' };
    PMTree tree4(in4);

    printPerm(getPerm1(tree4, 2));
    printPerm(getPerm2(tree4, 2));
    std::random_device rd;
    std::mt19937 gen(rd());

    for (int n = 3; n <= 9; ++n) {
        std::vector<char> test_in;
        for (int i = 0; i < n; ++i) {
            test_in.push_back(static_cast<char>('A' + i));
        }

        PMTree expTree(test_in);

        long long total_perms = 1;
        for (int i = 2; i <= n; ++i) {
            total_perms *= i;
        }

        std::uniform_int_distribution<long long> dist(1, total_perms);
        long long random_num = dist(gen);

        auto start = std::chrono::high_resolution_clock::now();
        getAllPerms(expTree);
        auto stop = std::chrono::high_resolution_clock::now();
        auto t_all = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();

        start = std::chrono::high_resolution_clock::now();
        getPerm1(expTree, static_cast<int>(random_num));
        stop = std::chrono::high_resolution_clock::now();
        auto t_p1 = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();

        start = std::chrono::high_resolution_clock::now();
        getPerm2(expTree, static_cast<int>(random_num));
        stop = std::chrono::high_resolution_clock::now();
        auto t_p2 = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();

        std::cout << "N=" << n
            << " | getAll=" << t_all
            << " | getPerm1=" << t_p1
            << " | getPerm2=" << t_p2 << "\n";
    }

    return 0;
}
