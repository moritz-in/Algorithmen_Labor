#include <iostream>
#include "Tree_Tools.cpp"

int main() {

    // Erzeuge einen Test-Baum
    LinkedTree* a = new LinkedTree('A');
    LinkedTree* b = new LinkedTree('B');
    LinkedTree* m = new LinkedTree(a, '*', b);
    LinkedTree* f = new LinkedTree('F');
    LinkedTree* p = new LinkedTree(f, '+', m);
    LinkedTree* x = new LinkedTree('X');
    LinkedTree* y = new LinkedTree('Y');
    LinkedTree* n = new LinkedTree(x, '-', y);
    LinkedTree* d = new LinkedTree(p, '/', n);


    // Testet treeHeight(), anzahlKnoten(),
    // printTreeInorderWithParenthesis(), printTreeLevelorder()

        TreeTools::printTree(d);
    //
       std::cout << "Baumhoehe laut Methode (sollte 4 sein): "
                << TreeTools::treeHeight(d) << std::endl;
    //
    std::cout << "Anzahl Knoten laut Methode (sollte 9 sein): "
                  << TreeTools::anzahlKnoten(d) << std::endl;
    TreeTools::printTreeInorder(d);
    std::cout <<std::endl;
    //
        std::cout << "Ausdruck mit Klammerung: ";
        TreeTools::printTreeInorderWithParenthesis(d);
        std::cout << std::endl;
    //
    std::cout << "Baum ebenenweise: ";
    TreeTools::printTreeLevelorder(d);
    std::cout << std::endl;


    // Testet searchTreeSort()

    std::cout << "Sortiere  6194283" << std::endl;
    int z[] = {6,1,9,4,2,8,3};
    int* sorted = TreeTools::searchTreeSort(z, sizeof(z));
    std::cout << "Ergebnis (sollte 1234689 sein): ";
    for(int i = 0; i < sizeof(a)/sizeof(int); i++)
    std::cout << sorted[i];

    std::cout << std::endl;


    return 0;
}
