#include <iostream>
#include <random>

struct LinkedTree {
    char value;
    LinkedTree *left;
    LinkedTree *right;

    LinkedTree(char val) : value(val), left(nullptr), right(nullptr) {
    }

    LinkedTree(LinkedTree *left, char val, LinkedTree *right): value(val), left(left), right(right) {
    };
};

class TreeTools {
public:
    /**
    * Ermittelt die Hoehe eines Baumes
    * @param b der zu uebergebende Baum
    * @return Hoehe des Baumes
    */
    static int treeHeight(LinkedTree *b) {
        if (b == nullptr) return 0;
        return 1 + std::max(treeHeight(b->left), treeHeight(b->right));
        //Rekursive Addition der Höhe des Linken oder Rechten Baumteiles
    }

    /**
    * Ermittelt die Anzahl der Knoten eines Baumes
    * @param b der zu uebergebende Baum
    * @return Anzahl der Knoten des Baumes
    */
    static int anzahlKnoten(LinkedTree *b) {
        if (b == nullptr) return 0;
        return 1 + anzahlKnoten(b->left) + anzahlKnoten(b->right);
        //Rekursive Addition der anzahl der Knoten des Linken und Rechten Baumteiles
    }

    static void printTreeInorder(LinkedTree *b) {
        if (b == nullptr) return;
        printTreeInorder(b->left);
        std::cout << b->value;
        printTreeInorder(b->right);
    }

    /**
    * gibt den übergebenen Baum in Inorder-Traversierung mit Klammerung aus
    * @param b der zu uebergebende Baum
    */

    static void printTreeInorderWithParenthesis(LinkedTree *b) {
        if (b == nullptr) return;
        std::cout << "(";
        printTreeInorderWithParenthesis(b->left);
        std::cout << b->value;
        printTreeInorderWithParenthesis(b->right);
        std::cout << ")";
    }


    /**
    * gibt den übergebenen Baum in Levelorder-Traversierung aus
    * @param b der zu uebergebende Baum
    */
    static void printTreeLevelorder(LinkedTree *b) {
        for (int i = 0; i < treeHeight(b); i++) {
            printLevel(b, i, 0 );
        }
    }

    /**
    * Sortiert gegebene Zahlenfolge per Suchbaum
    * @param zahlen zu sortierende Zahlenfolge
    * @return sortierte Folge
    */
    static int* searchTreeSort(int* zahlen, int size) {
        LinkedTree* root = nullptr;
        for (int i = 0; i < size; ++i)
            root = insert(root, zahlen[i]);

        std::stack<int> k;
        tree2SortedStack(root, k);          // jetzt korrekt befüllt

        int* res = new int[size];
        for (int i = size - 1; i >= 0; --i) { // weil größter oben liegt
            res[i] = k.top();
            k.pop();
        }

        deleteTree(root);                    // <<< Speicher wieder frei
        return res;
    }
    /**
    * Helfermethode zum sortieren von Elementen im SearchTree
    * @param b SearchTree mit zu sortierendem Inhalt
    * @param k Stack in den der SearchTree Inhalt sortiert werden soll
    */

    static void tree2SortedStack(LinkedTree* b, std::stack<int>& k) {
        if (!b) return;
        tree2SortedStack(b->left,  k);   // kleiner
        k.push(b->value);                // Wurzel
        tree2SortedStack(b->right, k);   // größer
    }

    /**
    * Druckt einen Baum auf der Konsole ebenenweise aus.
    * Nutzt treeHeight(Tree), printLevel(Tree,int,int) und spaces(int).
    * @param b der zu druckende Baum
    */
    static void printTree(LinkedTree *b) {
        // Berechne die Hoehe des Baumes
        int resthoehe = treeHeight(b);

        //Gehe die Ebenen des Baumes durch
        for (int i = 0; i < resthoehe; i++) {
            //Drucke die Ebene, beruecksichtige Anzahl der Leerzeichen
            //fuer korrekte Einrueckung
            printLevel(b, i, spaces(resthoehe - i));
            std::cout << std::endl;
            std::cout << std::endl;
        }
    }

    /**
    * Druckt eine Ebene eines Baumes aehnlich der Breitensuche.
    * 0 ist dabei die Wurzel. Vor und nach jedem Element werden Leerzeichen
    * eingefuegt.
    * @param b der auszugebende Baum
    * @param ebene die gewuenschte Ebene beginnend bei 0
    * @param spaces Anzahl von Leerzeichen vor und nach jedem Element
    */
    static void printLevel(LinkedTree *b, int level, int spaces) {
        // Wenn 0 erreicht, drucke Element mit Leerzeichen
        if (level == 0) {
            for (int i = 0; i < spaces; i++) std::cout << " ";
            if (b != nullptr) {
                std::cout << b->value;
            } else {
                // Wenn Nullzeiger uebergeben wurde, ein Leerzeichen drucken
                std::cout << " ";
            }
            for (int i = 0; i <= spaces; i++)
                std::cout << " ";
        } else {
            // Steige rekursiv ab, betrachte Soehne als Teilbaeume und verringere
            // dabei die zu druckende Ebene. In endende Aeste wird mit dem Nullzeiger
            // gelaufen.
            if (b != nullptr && b->left != nullptr) {
                printLevel(b->left, level - 1, spaces);
            } else {
                printLevel(nullptr, level - 1, spaces);
            }

            if (b != nullptr && b->right != nullptr) {
                printLevel(b->right, level - 1, spaces);
            } else {
                printLevel(nullptr, level - 1, spaces);
            }
        }
    }

    /**
    * Berechnet die Anzahl an benoetigten Leerzeichen fuer
    * eine korrekte Einrueckung, also 0.5 * (2^(level) - 2).
    * @param level die Ebene, Blaetter sind Ebene 1, darueber aufsteigend
    * @return Anzahl der Leerzeichen zur Elementtrennung
    */
    static int spaces(int level) {
        if (level == 1) {
            return 0;
        } else {
            // verdoppele die Leerzeichen gegenueber der Ebene darunter
            // und fuege ein weiteres Leerzeichen hinzu
            return 2 * spaces(level - 1) + 1;
        }
    }

    static LinkedTree* insert(LinkedTree* node, int val) {
        if (node == nullptr) return new LinkedTree(val);
        if (val < node->value) node->left = insert(node->left, val);
        else node->right = insert(node->right, val);
        return node;
    }

    static void deleteTree(LinkedTree* root) {
        if (root == nullptr) return;
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }

    static LinkedTree* createRandomSearchTree(int n) {
        std::vector<int> values(n);
        for (int i = 0; i < n; ++i) values[i] = i + 1;

        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(values.begin(), values.end(), g);

        LinkedTree* root = nullptr;
        for (int val : values) {
            root = insert(root, val);
        }
        return root;
    }
};

