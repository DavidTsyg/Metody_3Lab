#pragma once
#include "Elements.h" 
#include <iostream> 
#include <math.h> 
#include <limits> 
#include <vector> 
#include <string> 
#include <algorithm> 
#include <iomanip> 

#define MAX_INT_X_VAR 4 
using namespace std;

// ����� ����� 
template <class Matrix>
struct Node {
	Matrix simplexMatrix; // �������, ������� � ����� 

	Node<Matrix>* leftNode; // ��������� �� ������� � �������������� ������������ (� ������� �������) 
	Node<Matrix>* rightNode; // ��������� �� ������� � �������������� ������������ (� ������� �������) 

	vector<int> extra; // ������ �������� �������������� ����������� 
	vector<unsigned int> xPos; // ������ �������� ���������� ��� ������������ 

							   // ������������ 
	Node(Matrix& key);
	Node(Node<Matrix>* &node, int x, unsigned int pos, bool leftOrRight);

	int error; // ������� �� ������� 
};

// ����� ������ 
template <class Matrix>
class Tree {
	Node<Matrix>* _root; // ������ ������ 
	void _recursiveFill(Node<Matrix>*& node); // ����������� ��������� �� ������� �������� 
	void _recursiveFill(Node<Matrix>*& next, double x, unsigned int pos); // ��������������� ����� ���������� 
	vector<double> _resF; // ��� �������� F ��� ������������� ������ 
public:
	Tree(); // ����������� 
	void Istart(Matrix &obj); // ������ ���������� 
	void IprintSolutionsRecursive(Node<Matrix>*& node); // ����� ������� ������� �� ������������ ������ 
	void IprintTreeStructure(Node<Matrix>*& node, unsigned int level); // ����� ��������� ������ (������) 
	void IprintOptimalNode(); // ����� ���������� �������� F � ����� ����� 

	Node<Matrix>* IgetRoot(); // ������ ����� 

};

// ����� ������� 
template <typename T>
class Matrix {
private:
	bool _isMax; // ��������� �� ������� ������� � ��������� 
	bool _isDual; // ������������ �� ������ 

	unsigned int _rows; // ���������� ����� 
	unsigned int _columns; // ���������� �������� 

	T**_array; // ��������� ������ 

	vector<unsigned int> _varFree; // ������ ������� ��������� ���������� 
	vector<unsigned int> _varBase; // ������ ������� �������� ���������� 

								   // ���� ��������� 
	void _toDual(); // ���������� ������ � ������������ 
	int _stepFirst(); // ����� �������� ������� 
	int _stepSecond(); // ����� ������������ ������� 
	int _wrongCi(unsigned int tempPos, int step); // �������, ���������� ���  
	void _jordanProcess(Matrix &temp, unsigned int acRow, unsigned int acColumn); // ��������� ���������� 

	void _printCanon(); // ����� ������������� ���� 
	void _printSolution(bool optimal); // ����� ������� 
	void _checkSolution(double x[][COLUMNS - 1], double freeB[], double objFunc[]); // �������� ������� 

public:

	//������������ 
	Matrix();
	Matrix(unsigned int rows, unsigned int columns);
	Matrix(const Matrix& get);
	~Matrix();

	void IenterElements(double varX[][COLUMNS - 1], double freeB[], double objFunc[]); // ���������� ��������� 
	int IfirstStep(); // ������ ��� 
	int IsecondStep(); // ������ ��� 
	void Isimplex(); // ����� ������� �������� ������ 
	void Iprint(); // ����� 
	void IprintSol(bool error); // ����� ������� 
	void IprintCanon(); // ����� ������������� ���� 
	void IcheckSolutions(); // �������� ������� 

	void setDual(bool set); // ��������� ������������ ������ 

	vector<unsigned int> getVarBase(); // ������ �������� �������� ���������� 
	vector<unsigned int> getVarFree(); // ������ �������� ��������� ���������� 
	void setBaseFree(vector<unsigned int> vb, vector<unsigned int> vf); // ��������� �������� 

	void IsetElementsManual(); // ������ ���� 

	T IgetElement(unsigned int row, unsigned int column); // ��������� ����������� �������� �� ������� 
	void IsetElement(unsigned int row, unsigned int column, T key); // ��������� �������� 

	T** getArray(); // ������ ������� 

	unsigned int getRows(); // ������ ���������� ����� 
	unsigned int getColumns(); // ���-�� �������� 

	Matrix<T>& operator= (const Matrix& right);
	bool operator==(const Matrix& right) const;
};

void bruteForce(); // ������ ������� 