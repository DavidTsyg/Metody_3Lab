// OptimizationMethodsLab1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Functions.h"

int main()
{
	Simplex_Table table;
	Simplex_Table copy;
	table.Create_Simplex_Table_Raw();
	copy.Copy(table);
	table.Print_Problem();
	table.Print_Canonized_Problem();
	table.Print_Simplex_Table();
	table.Brute_Force();
	table.Opornoe_Solution();
	table.Simplex_Method();
	table.Tree_Solution(table);
//	table.Add_Row(3, 1, -1);
//	table.Print_Simplex_Table();
//	table.Add_Row(1, 0, -1);
//	table.Print_Simplex_Table();
	system("pause");
	return 0;

}

