// Copyright 2022 NNTU-CS
#include <algorithm>
#include <cstdint>
#include <vector>

#include "tree.h"

Node::Node(char val) : value(val) {}

Node::~Node() {
    for (Node* child : children) {
        delete child;
    }
}

void PMTree::buildTree(Node* node, std::vector<char> remaining) {
    if (remaining.empty()) return;

    for (size_t i = 0; i < remaining.size(); ++i) {
        Node* child = new Node(remaining[i]);
        node->children.push_back(child);

        std::vector<char> next_remaining = remaining;
        next_remaining.erase(next_remaining.begin() + i);

        buildTree(child, next_remaining);
    }
}

PMTree::PMTree(const std::vector<char>& in) {
    std::vector<char> sorted_in = in;
    std::sort(sorted_in.begin(), sorted_in.end());
    size = static_cast<int>(sorted_in.size());

    root = new Node('\0');
    buildTree(root, sorted_in);
}

PMTree::~PMTree() {
    delete root;
}

void dfs_all(Node* node, std::vector<char>& current,
             std::vector<std::vector<char>>& result) {
    if (node->value != '\0') {
        current.push_back(node->value);
    }

    if (node->children.empty() && node->value != '\0') {
        result.push_back(current);
    } else {
        for (Node* child : node->children) {
            dfs_all(child, current, result);
        }
    }

    if (node->value != '\0') {
        current.pop_back();
    }
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
    std::vector<std::vector<char>> result;
    std::vector<char> current;
    if (tree.root) {
        dfs_all(tree.root, current, result);
    }
    return result;
}

void dfs_kth(Node* node, std::vector<char>& current, int& k,
             std::vector<char>& result) {
    if (!result.empty()) return;

    if (node->value != '\0') {
        current.push_back(node->value);
    }

    if (node->children.empty() && node->value != '\0') {
        k--;
        if (k == 0) {
            result = current;
        }
    } else {
        for (Node* child : node->children) {
            dfs_kth(child, current, k, result);
        }
    }

    if (node->value != '\0') {
        current.pop_back();
    }
}

std::vector<char> getPerm1(PMTree& tree, int num) {
    std::vector<char> result;
    std::vector<char> current;
    int k = num;
    if (tree.root) {
        dfs_kth(tree.root, current, k, result);
    }
    return result;
}

int64_t factorial(int n) {
    int64_t f = 1;
    for (int i = 2; i <= n; ++i) f *= i;
    return f;
}

std::vector<char> getPerm2(PMTree& tree, int num) {
    std::vector<char> result;
    if (tree.size == 0) return result;

    int64_t total_perms = factorial(tree.size);
    if (num < 1 || num > total_perms) return result;

    Node* current = tree.root;
    int n = tree.size;
    int k = num - 1;

    while (!current->children.empty()) {
        int64_t perms_per_branch = factorial(n - 1);
        int index = k / static_cast<int>(perms_per_branch);
        k = k % static_cast<int>(perms_per_branch);

        current = current->children[index];
        result.push_back(current->value);
        n--;
    }
    return result;
}
