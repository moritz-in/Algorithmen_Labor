# Algorithmen_Labor

Java code in C++ Code verwandelt:


/******************************  TreeTools.cpp  ******************************/
/**
 * Tool-Klasse mit einigen Algorithmen fuer Baeume (C++ Version)
 */

#include <iostream>
#include <vector>
#include <stack>
#include <cmath>

using namespace std;

// Einfache Baumstruktur als Annahme
class Tree {
public:
    int val;
    Tree* leftChild;
    Tree* rightChild;

    Tree(int value) : val(value), leftChild(nullptr), rightChild(nullptr) {}

    int value() const { return val; }
    Tree* left() const { return leftChild; }
    Tree* right() const { return rightChild; }
    bool empty() const { return this == nullptr; } // kann bei nullptr geprüft werden
};

// TreeTools-ähnliche Funktionen

int treeHeight(Tree* b) {
    if (!b) return 0;
    return 1 + max(treeHeight(b->left()), treeHeight(b->right()));
}

int anzahlKnoten(Tree* b) {
    if (!b) return 0;
    return 1 + anzahlKnoten(b->left()) + anzahlKnoten(b->right());
}

void printTreeInorderWithParenthesis(Tree* b) {
    if (!b) return;
    cout << "(";
    printTreeInorderWithParenthesis(b->left());
    cout << b->value();
    printTreeInorderWithParenthesis(b->right());
    cout << ")";
}

void printTreeLevelorder(Tree* b) {
    if (!b) return;
    vector<Tree*> queue{b};
    while (!queue.empty()) {
        Tree* current = queue.front();
        queue.erase(queue.begin());
        if (current) {
            cout << current->value() << " ";
            queue.push_back(current->left());
            queue.push_back(current->right());
        }
    }
    cout << endl;
}

void tree2SortedStack(Tree* b, stack<int>& k) {
    if (!b) return;
    tree2SortedStack(b->right(), k);
    k.push(b->value());
    tree2SortedStack(b->left(), k);
}

int* searchTreeSort(const vector<int>& zahlen) {
    Tree* root = nullptr;

    // Hilfsfunktion zum Einfügen
    auto insert = [](Tree*& node, int val) {
        if (!node) node = new Tree(val);
        else if (val < node->value()) insert(node->leftChild, val);
        else insert(node->rightChild, val);
    };

    for (int num : zahlen)
        insert(root, num);

    stack<int> s;
    tree2SortedStack(root, s);

    int* result = new int[s.size()];
    for (size_t i = 0; i < s.size(); ++i) {
        result[i] = s.top();
        s.pop();
    }
    return result;
}

int spaces(int level) {
    if (level == 1) return 0;
    return 2 * spaces(level - 1) + 1;
}

void printLevel(Tree* b, int level, int spaceCount) {
    if (level == 0) {
        for (int i = 0; i < spaceCount; i++) cout << " ";
        if (b) cout << b->value();
        else cout << " ";
        for (int i = 0; i <= spaceCount; i++) cout << " ";
    } else {
        printLevel(b && b->left() ? b->left() : nullptr, level - 1, spaceCount);
        printLevel(b && b->right() ? b->right() : nullptr, level - 1, spaceCount);
    }
}

void printTree(Tree* b) {
    int height = treeHeight(b);
    for (int i = 0; i < height; i++) {
        printLevel(b, i, spaces(height - i));
        cout << "\n\n";
    }
}
