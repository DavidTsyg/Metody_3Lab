#include "stdafx.h"
#include "Matrix.h"
int main() {
	// полный перебор решений в пределе от 0 до 3
	bruteForce();
	// создание заполнение и решение исходной задачи ЛП
	Matrix<double> obj(ROWS, COLUMNS);
	obj.IenterElements(x, b, c);
	obj.Isimplex();
	// создание дерева и заполнение
	Tree<Matrix<double>> objTree;
	objTree.Istart(obj);
	system("pause");
	//system("cls");
	// получение корня дерева и вывод решений
	Node<Matrix<double>>* root = objTree.IgetRoot();
	objTree.IprintSolutionsRecursive(root);
	// вывод структуры дерева
	cout << "Tree:\n";
	objTree.IprintTreeStructure(root, 0);
	// вывод нужных ветвей
	objTree.IprintOptimalNode();
	cout << "\n";
	cout << "\n";
	system("pause");
	return 0;
}