#include "stdafx.h"
#include "Functions.h"

using namespace std;

Simplex_Table::Simplex_Table() {}
Simplex_Table::Simplex_Table(vector<vector<double>>& equations, vector<double>& conditional_values, vector<double>& function, int& number_of_equations, int& number_of_arguments)
{
	_equations = equations;
	_conditional_values = conditional_values;
	_function = function;
	_number_of_equations = number_of_equations;
	_number_of_arguments = number_of_arguments;
	vector<Simplex_Element> buffer_vector;
	for (auto i = 0; i < _number_of_equations; ++i)
	{
		buffer_vector.push_back(Simplex_Element(_conditional_values[i], _number_of_arguments + 1 + i, 0));
		for (auto j = 0; j < _equations[0].size(); ++j)
			buffer_vector.push_back(Simplex_Element(_equations[i][j], _number_of_arguments + 1 + i, j + 1));
		_simplex_table.push_back(buffer_vector);
		buffer_vector.clear();
	}
	for (auto i = 0; i < _function.size(); ++i)
		buffer_vector.push_back(Simplex_Element((_function[i])*(-1), _number_of_arguments + 1 + i, 0));
	_simplex_table.push_back(buffer_vector);
}
Simplex_Table::~Simplex_Table() {}

void Simplex_Table::Copy(Simplex_Table to_copy)
{
	_simplex_table.clear();
	for (auto i = to_copy.Give_Simplex_Table().begin(); i != to_copy.Give_Simplex_Table().end(); ++i)
	{
		_simplex_table.push_back(*i);
	}
	_equations.clear();
	for (auto i = to_copy.Give_Equations().begin(); i != to_copy.Give_Equations().end(); ++i)
	{
		_equations.push_back(*i);
	}
	_conditional_values.clear();
	for (auto i = to_copy.Give_Conditional_Values().begin(); i != to_copy.Give_Conditional_Values().end(); ++i)
	{
		_conditional_values.push_back(*i);
	}
	_function.clear();
	for (auto i = to_copy.Give_Function().begin(); i != to_copy.Give_Function().end(); ++i)
	{
		_function.push_back(*i);
	}
	_min_max = to_copy.Give_Min_Max();
	_number_of_equations = to_copy.Give_Number_Of_Equations();
	_number_of_arguments = to_copy.Give_Number_Of_Arguments();
}

const int& Simplex_Table::Give_Number_Of_Equations() { return _number_of_equations; }
const int& Simplex_Table::Give_Number_Of_Arguments() { return _number_of_arguments; }
const vector<vector<Simplex_Element>>& Simplex_Table::Give_Simplex_Table() { return _simplex_table; }
const vector<vector<double>>& Simplex_Table::Give_Equations() { return _equations; }
const vector<double>& Simplex_Table::Give_Conditional_Values() { return _conditional_values; }
const vector<double>& Simplex_Table::Give_Function() { return _function; }
const bool Simplex_Table::Give_Min_Max() { return _min_max; }

void Simplex_Table::Create_Simplex_Table()
{
	double buffer;
	vector<Simplex_Element> buffer_vector;
	cout << "min or max (for max input 1, for min input 0) : ";
	cin >> _min_max;
	cout << "Input the number of equations ( more than 0 ) : ";
	cin >> _number_of_equations;
	while (_number_of_equations == 0)
	{
		cout << "Input the number of equations ( more than 0 ) : ";
		cin >> _number_of_equations;
	}
	cout << "Input the number of arguments ( more than 0 ) : ";
	cin >> _number_of_arguments;
	while (_number_of_arguments == 0)
	{
		cout << "Input the number of arguments ( more than 0 ) : ";
		cin >> _number_of_arguments;
	}

	if (_number_of_equations > _number_of_arguments)
	{
		cout << "The number of arguments is lesss than the number of equations";
		exit(EXIT_FAILURE);
	}
	cout << "Now filling up equations" << endl;
	for (auto i = 0; i < _number_of_equations; ++i)
	{
		double buffer;
		vector<double> empty;
		_equations.push_back(empty);
		for (auto j = 0; j < _number_of_arguments; ++j)
		{
			cout << "Input the multiplier by the number : ";
			cin >> buffer;
			_equations[i].push_back(buffer);
		}
		cout << "Input the conditional value : ";
		cin >> buffer;
		_conditional_values.push_back(buffer);
	}
	cout << "Creating the function" << endl;
	cout << "Input the free value : ";
	cin >> buffer;
	_function.push_back(buffer);
	cout << "Input the funtion arguments" << endl;
	for (auto i = 0; i < _number_of_arguments; ++i)
	{
		cout << "x" << i + 1 << " : ";
		cin >> buffer;
		_function.push_back(buffer);
	}
	for (auto i = 0; i < _number_of_equations; ++i)
	{
		buffer_vector.push_back(Simplex_Element(_conditional_values[i], _number_of_arguments + 1 + i, 0));
		for (auto j = 0; j < _equations[0].size(); ++j)
			buffer_vector.push_back(Simplex_Element(_equations[i][j], _number_of_arguments + 1 + i, j + 1));
		_simplex_table.push_back(buffer_vector);
		buffer_vector.clear();
	}
	for (auto i = 0; i < _function.size(); ++i)
	{
		if (!_min_max)
		{
			if (_function[i] != 0)
				buffer_vector.push_back(Simplex_Element(_function[i], _number_of_equations + 1, i));
			else
				buffer_vector.push_back(Simplex_Element((_function[i]) * (-1), _number_of_equations + 1, i));
		}
		else
		{
			if (_function[i] != 0)
				buffer_vector.push_back(Simplex_Element(_function[i], _number_of_equations + 1, i));
			else
				buffer_vector.push_back(Simplex_Element(_function[i], _number_of_equations + 1, i));
		}
	}
	_simplex_table.push_back(buffer_vector);
	
}

void Simplex_Table::Create_Simplex_Table_Raw()
{
	_simplex_table.clear();
	double buffer;
	vector<Simplex_Element> buffer_vector;
	_min_max = 1;
	_number_of_equations = 3;
	_number_of_arguments = 3;
	double first_row[] = { 5, 4, 1, 1 };
	double second_row[] = { 7, 1, 4, 0 };
	double third_row[] = { 6, 0, 0.5, 4 };
	double fourth_row[] = { 0, 1, 5, 5 };
	vector<double> empty;
	_equations.clear();
	_equations.push_back(empty);
	for (auto j = 0; j < 3; ++j)
	{
		_equations[0].push_back(first_row[j+1]);
	}
	_equations.push_back(empty);
	for (auto j = 0; j < 3; ++j)
	{
		_equations[1].push_back(second_row[j + 1]);
	}
	_equations.push_back(empty);
	for (auto j = 0; j < 3; ++j)
	{
		_equations[2].push_back(third_row[j + 1]);
	}
	_conditional_values.clear();
	_conditional_values.push_back(first_row[0]); _conditional_values.push_back(second_row[0]); _conditional_values.push_back(third_row[0]);
	_function.clear();
	for (auto i = 0; i < 4; ++i)
	{
		_function.push_back(fourth_row[i]);
	}
	for (auto i = 0; i < _number_of_equations; ++i)
	{
		buffer_vector.push_back(Simplex_Element(_conditional_values[i], _number_of_arguments + 1 + i, 0));
		for (auto j = 0; j < _equations[0].size(); ++j)
			buffer_vector.push_back(Simplex_Element(_equations[i][j], _number_of_arguments + 1 + i, j + 1));
		_simplex_table.push_back(buffer_vector);
		buffer_vector.clear();
	}
	for (auto i = 0; i < _function.size(); ++i)
	{
		if (!_min_max)
		{
			if (_function[i] != 0)
				buffer_vector.push_back(Simplex_Element(_function[i], _number_of_equations + 1, i));
			else
				buffer_vector.push_back(Simplex_Element((_function[i]) * (-1), _number_of_equations + 1, i));
		}
		else
		{
			if (_function[i] != 0)
				buffer_vector.push_back(Simplex_Element(_function[i], _number_of_equations + 1, i));
			else
				buffer_vector.push_back(Simplex_Element(_function[i], _number_of_equations + 1, i));
		}
	}
	_simplex_table.push_back(buffer_vector);

}

void Simplex_Table::Print_Problem()
{
	// Выводим уравнение F
	vector<pair<double, unsigned int>> buffer_vector;
	for (auto i = 1; i < _function.size(); ++i)
	{
		if (_function[i] != 0)
			buffer_vector.push_back(make_pair(_function[i], i));
	}
	cout << endl;
	cout << "This is the problem" << endl;
	cout << "F = ";
	if (_function[0] != 0)
	{
		if (buffer_vector[0].first > 0)
			cout << buffer_vector[0].first << " + ";
		else
			cout << buffer_vector[0].first << " - ";
	}
	else
	{
		if (buffer_vector[0].first < 0)
			cout << buffer_vector[0].first << " - ";
	}
	for (auto i = 0; i < buffer_vector.size() - 1; ++i)
	{
		if (buffer_vector[i + 1].first > 0)
		{
			cout << buffer_vector[i].first << "*x" << buffer_vector[i].second << " + ";
		}
		else
		{
			cout << abs(buffer_vector[i].first) << "*x" << buffer_vector[i].second << " - ";
		}
	}
	cout << buffer_vector.back().first << "*x" << buffer_vector.back().second << endl;
	buffer_vector.clear();
	// Выводим неравенства
	for (auto i = 0; i < _equations.size(); ++i)
	{
		for (auto j = 0; j < _equations.size(); ++j)
		{
			if (_equations[i][j] != 0)
				buffer_vector.push_back(make_pair(_equations[i][j], j + 1));
		}
		if (buffer_vector[0].first < 0)
			cout << buffer_vector[0].first << " - ";
		for (auto j = 0; j < buffer_vector.size() - 1; ++j)
		{
			if (buffer_vector[j + 1].first > 0)
			{
				cout << buffer_vector[j].first << "*x" << buffer_vector[j].second << " + ";
			}
			else
			{
				cout << abs(buffer_vector[j].first) << "*x" << buffer_vector[j].second << " - ";
			}
		}
		cout << buffer_vector.back().first << "*x" << buffer_vector.back().second;
		cout << " <= " << _conditional_values[i] << endl;
		buffer_vector.clear();
	}
}

void Simplex_Table::Print_Canonized_Problem()
{
	// Выводим уравнение F
	vector<pair<double, unsigned int>> buffer_vector;
	for (auto i = 1; i < _function.size(); ++i)
	{
		if (_function[i] != 0)
			buffer_vector.push_back(make_pair(_function[i], i));
	}
	cout << endl;
	cout << "This is the canonized problem" << endl;
	cout << "F = - ( ";
	if (_function[0] != 0)
	{
		if (buffer_vector[0].first > 0)
			cout << _function[0] << " - ";
		else
			cout << _function[0] << " + ";
	}
	if (buffer_vector[0].first > 0)
		cout << "- ";
	for (auto i = 0; i < buffer_vector.size() - 1; ++i)
	{
		if (buffer_vector[i + 1].first > 0)
		{
			cout << buffer_vector[i].first << "*x" << buffer_vector[i].second << " - ";
		}
		else
		{
			cout << abs(buffer_vector[i].first) << "*x" << buffer_vector[i].second << " + ";
		}
	}
	cout << buffer_vector.back().first << "*x" << buffer_vector.back().second << " )" << endl;
	buffer_vector.clear();
	// Выводим равенства
	for (auto i = 0; i < _equations.size(); ++i)
	{
		for (auto j = 0; j < _equations.size(); ++j)
		{
			if (_equations[i][j] != 0)
				buffer_vector.push_back(make_pair(_equations[i][j], j + 1));
		}
		if (buffer_vector[0].first < 0)
			cout << buffer_vector[0].first << " - ";
		for (auto j = 0; j < buffer_vector.size() - 1; ++j)
		{
			if (buffer_vector[j + 1].first > 0)
			{
				cout << buffer_vector[j].first << "*x" << buffer_vector[j].second << " + ";
			}
			else
			{
				cout << abs(buffer_vector[j].first) << "*x" << buffer_vector[j].second << " - ";
			}
		}
		cout << buffer_vector.back().first << "*x" << buffer_vector.back().second;
		cout << " + x" << _equations.size() + 1 + i << " = " << _conditional_values[i] << endl;
		buffer_vector.clear();
	}
	cout << endl;
}

void Simplex_Table::Print_Simplex_Table()
{
	cout << "This is the simplex table" << endl;
	string buffer;
	cout << std::setw(8) << " ";
	cout << std::setw(8) << "Si0";
	for (auto i = 1; i < _simplex_table[0].size(); ++i)
	{
		buffer = "x";
		buffer += to_string((_simplex_table[0][i]).y);
		cout << std::setw(8) << buffer;
	}
	cout << endl;
	for (auto i = 0; i < _simplex_table.size() - 1; ++i)
	{
		buffer = "x";
		buffer += to_string(_simplex_table[i][0].x);
		cout << std::setw(8) << buffer;
		for (auto j = 0; j < _simplex_table[i].size(); ++j)
		{
			cout << std::setw(8) << defaultfloat << std::setprecision(3) << _simplex_table[i][j].value;
		}
		cout << endl;
	}
	cout << std::setw(8) << "F";
	for (auto i = 0; i < (_simplex_table.back()).size(); ++i)
	{
		cout << std::setw(8) << defaultfloat << std::setprecision(3) << ((_simplex_table.back())[i]).value;
	}
	cout << endl << endl;
}

bool Simplex_Table::Is_Solvable()
{
	int solvable = 1;
	int check_row = -1;
	
	for (auto i = 0; i < _simplex_table.size() - 1; ++i)
	{
		if (_simplex_table[i][0].value < 0)
		{
			check_row = i;
			solvable = 0;
			break;
		}
	}
	if (check_row != -1)
	{
		for (auto j = 1; j < _simplex_table.back().size(); ++j)
		{
			if (_simplex_table[check_row][j].value < 0)
			{
				solvable = 1;
			}
		}
	}
	return solvable;
}

bool Simplex_Table::Solution_Reached()
{
	bool no_negatives = 1, no_positives = 1;
	for (auto i = 0; i < _simplex_table.size() - 1; ++i)
	{
		if (_simplex_table[i][0].value < 0)
		{
			no_negatives = 0;
			break;
		}
	}
	for (auto i = 1; i < _simplex_table.back().size(); ++i)
	{
		if (_simplex_table.back()[i].value > 0)
		{
			no_positives = 0;
			break;
		}
	}
	if (no_negatives && no_positives)
		return 1;
	else
		return 0;
}

void Simplex_Table::Jordan_Exclusions(int solve_row, int solve_column, int solve_perem_column, int solve_perem_row)
{
	vector<vector<double>> buffer_vector_vector;
	vector<double> buffer_vector;
	double solve_value = _simplex_table[solve_row][solve_column].value;
	for (auto i = 0; i < _simplex_table.back().size(); ++i)
	{
		_simplex_table[solve_row][i].x = solve_perem_row;
	}
	for (auto i = 0; i < _simplex_table.size(); ++i)
	{
		_simplex_table[i][solve_column].y = solve_perem_column;
	}
	for (auto i = 0; i < _simplex_table.size(); ++i)
	{
		for (auto j = 0; j < _simplex_table.back().size(); ++j)
		{
			if (j != solve_column)
			{
				if (i == solve_row)
					buffer_vector.push_back(_simplex_table[i][j].value / solve_value);
				else
				{
					buffer_vector.push_back(_simplex_table[i][j].value - ((_simplex_table[solve_row][j].value * _simplex_table[i][solve_column].value) / solve_value));
				}
			}
			else
			{
				if (i == solve_row)
					buffer_vector.push_back(((double)1) / solve_value);
				else
					buffer_vector.push_back(0 - ((((double)1) * _simplex_table[i][solve_column].value) / solve_value));
			}
		}
		buffer_vector_vector.push_back(buffer_vector);
		buffer_vector.clear();
	}
	for (auto i = 0; i < _simplex_table.size(); ++i)
	{
		for (auto j = 0; j < _simplex_table.back().size(); ++j)
		{
			_simplex_table[i][j].value = buffer_vector_vector[i][j];
		}
	}
	buffer_vector.clear();
}

void  Simplex_Table::Opornoe_Solution()
{
	int solve_perem_column;
	int solve_perem_row;
	int solve_row;
	int solve_column;
	double solve_value;
	if (Is_Solvable())
	{
		for (auto i = 0; i < _simplex_table.size() - 1; ++i)
		{
			if (_simplex_table[i][0].value < 0)
			{
				solve_row = i;
				solve_perem_row = _simplex_table[i][0].x;
				for (auto j = 1; j < _simplex_table.back().size(); ++j)
				{
					if (_simplex_table[i][j].value < 0)
					{
						solve_column = j;
						solve_perem_column = _simplex_table[i][j].y;
						solve_value = _simplex_table[i][j].value;
						Jordan_Exclusions(solve_row, solve_column, solve_perem_row, solve_perem_column);
						cout << "Solve element is " << solve_value << " with basis perem x" << solve_perem_row << " and free perem x" << solve_perem_column << endl;
						Print_Simplex_Table();
						break;
					}
				}
			}
		}
		cout << "Base solution" << endl;
		Print_Simplex_Table();
		cout << endl;
	}
	else
	{
		Print_Simplex_Table();
		cout << "Unsolvable simplex table" << endl;
	}
}
void Simplex_Table::Simplex_Method()
{
	bool out_of_negatives = 0;
	bool out_of_positives = 0;
	double min_negative;
	double max_positive;
	double min_pos_div;
	int solve_perem_column;
	int solve_perem_row;
	int solve_row;
	int solve_column;
	double solve_value;
	vector<vector<double>> buffer_vector_vector;
	vector<double> buffer_vector;
	if (Is_Solvable())
	{
		while (!Solution_Reached())
		{
			for (auto i = 0; i < _simplex_table.size() - 1; ++i)
			{
				if (_simplex_table[i][0].value < 0)
				{
					solve_row = i;
					solve_perem_row = _simplex_table[i][0].x;
					for (auto j = 1; j < _simplex_table.back().size(); ++j)
					{
						if (_simplex_table[i][j].value < 0)
						{
							solve_column = j;
							solve_perem_column = _simplex_table[i][j].y;
							solve_value = _simplex_table[i][j].value;
							Jordan_Exclusions(solve_row, solve_column, solve_perem_row, solve_perem_column);
							cout << "Solve element is " << solve_value << " with basis perem x" << solve_perem_row << " and free perem x" << solve_perem_column << endl;
							Print_Simplex_Table();
							break;
						}
					}
				}
			}
			max_positive = 0;
			out_of_positives = 1;
			for (auto i = 1; i < _simplex_table.back().size(); ++i)
			{
				if (_simplex_table.back()[i].value > 0)
				{
					out_of_positives = 0;
					max_positive = _simplex_table.back()[i].value;
					solve_column = i;
					solve_perem_column = _simplex_table.back()[i].y;
					break;
				}

			}
			for (auto i = 1; i < _simplex_table.back().size(); ++i)
			{
				if (_simplex_table.back()[i].value > max_positive)
				{
					out_of_positives = 0;
					max_positive = _simplex_table.back()[i].value;
					solve_column = i;
					solve_perem_column = _simplex_table.back()[i].y;
				}
			}
			if (out_of_positives == 1)
				break;
			for (auto i = 0; i < _simplex_table.size() - 1; ++i)
			{
				if (_simplex_table[i][solve_column].value != 0)
				{
					if ((_simplex_table[i][0].value) / (_simplex_table[i][solve_column].value) > 0)
					{
						min_pos_div = (_simplex_table[i][0].value) / (_simplex_table[i][solve_column].value);
						solve_row = i;
						solve_perem_row = _simplex_table[i][0].x;
						break;
					}
				}
				else
					continue;
			}
			for (auto i = 0; i < _simplex_table.size() - 1; ++i)
			{
				if (_simplex_table[i][solve_column].value != 0)
				{
					if (((_simplex_table[i][0].value) / (_simplex_table[i][solve_column].value) > 0) && ((_simplex_table[i][0].value) / (_simplex_table[i][solve_column].value) < min_pos_div))
					{
						min_pos_div = (_simplex_table[i][0].value) / (_simplex_table[i][solve_column].value);
						solve_row = i;
						solve_perem_row = _simplex_table[i][0].x;
					}
				}
				else
					continue;
			}
			solve_value = _simplex_table[solve_row][solve_column].value;
			cout << "Solve element is " << solve_value << " with basis perem x" << solve_perem_row << " and free perem x" << solve_perem_column << endl;
			Jordan_Exclusions(solve_row, solve_column, solve_perem_row, solve_perem_column);
			Print_Simplex_Table();
		}
	}
	else
	{
		Print_Simplex_Table();
		cout << "Unsolvable simplex table" << endl;
	}
}

void Simplex_Table::Brute_Force()
{
	cout << "Brute force method" << endl << endl;
	double max = _simplex_table[0][0].value;
	vector<int> buf;
	vector<pair<vector<int>, double>> brute_results;
	for (auto i = 0; i < _simplex_table.size() - 1; ++i)
	{
		if (_simplex_table[i][0].value > max)
			max = _simplex_table[i][0].value;
	}
	for (int i = 0; i < max; ++i)
	{
		for (int j = 0; j < max; ++j)
		{
			for (int k = 0; k < max; ++k)
			{
				if (((_simplex_table[0][1].value * i) + (_simplex_table[0][2].value * j) + (_simplex_table[0][3].value * k) <= _simplex_table[0][0].value)
					&& ((_simplex_table[1][1].value * i) + (_simplex_table[1][2].value * j) + (_simplex_table[1][3].value * k) <= _simplex_table[1][0].value)
					&& ((_simplex_table[2][1].value * i) + (_simplex_table[2][2].value * j) + (_simplex_table[2][3].value * k) <= _simplex_table[2][0].value))
				{
					buf.clear();
					buf.push_back(i); buf.push_back(j); buf.push_back(k);
					brute_results.push_back(make_pair(buf, (i*_simplex_table.back()[1].value + j*_simplex_table.back()[2].value + k*_simplex_table.back()[3].value)));
				}

			}
		}
	}
	for (auto i = 0; i < brute_results.size(); ++i)
	{
		cout << "Solution: ";
		for (auto j = 0; j < brute_results[i].first.size(); ++j)
		{
			cout << brute_results[i].first[j] << " ";
		}
		cout << "Result: " << brute_results[i].second << endl;
	}
	max = brute_results[0].second;
	for (auto i = 0; i < brute_results.size(); ++i)
	{
		if (brute_results[i].second > max)
			max = brute_results[i].second;
	}
	cout << "-------------------------------------------" << endl;
	cout << "Best solutions:" << endl;
	for (auto i = 0; i < brute_results.size(); ++i)
	{
		if (brute_results[i].second == max)
		{
			cout << "Solution: ";
			for (auto j = 0; j < brute_results[i].first.size(); ++j)
			{
				cout << brute_results[i].first[j] << " ";
			}
			cout << "Result: " << brute_results[i].second << endl;
		}
	}
	cout << endl;
}

void Simplex_Table::Add_Row(int x, double value, int more_or_less)
{
	vector<Simplex_Element> buffer;
	for (auto i = 0; i < _simplex_table.size(); ++i)
	{
		if (_simplex_table[i][0].x == x)
		{
			if(more_or_less == -1)
				buffer.push_back(Simplex_Element(value - _simplex_table[i][0].value, _simplex_table.size() + _simplex_table[0].size() - 1, _simplex_table[i][0].y));
			else
				buffer.push_back(Simplex_Element(_simplex_table[i][0].value - value, _simplex_table.size() + _simplex_table[0].size() - 1, _simplex_table[i][0].y));
			for (auto j = 1; j < _simplex_table[i].size(); ++j)
			{
				buffer.push_back(Simplex_Element(_simplex_table[i][j].value*(more_or_less), _simplex_table.size() + _simplex_table[0].size() - 1, _simplex_table[i][j].y));
			}
		}
	}
	buffer.swap(_simplex_table.back());
	_simplex_table.push_back(buffer);
}

vector<pair<int, double>> Simplex_Table::Find_Not_Integer()
{
	vector<pair<int, double>> buf;
	for (auto i = 0; i < _simplex_table.size() - 1; ++i)
	{
		if ((_simplex_table[i][0].x == 1)||(_simplex_table[i][0].x == 2)||(_simplex_table[i][0].x == 3))
		{
			if (trunc(_simplex_table[i][0].value) != _simplex_table[i][0].value)
			{
				buf.push_back(make_pair(_simplex_table[i][0].x, _simplex_table[i][0].value));
			}
		}
	}
	if (buf.empty())
	{
		buf.push_back(make_pair(0, 0));
		return buf;
	}
	else
		return buf;
}

void Simplex_Table::Tree_Solution(Simplex_Table original)
{
	vector<pair<int ,double>> result = original.Find_Not_Integer();
	for (auto i = result.begin(); i != result.end(); ++i)
	{
		if (i->first)
		{
			unique_ptr<Simplex_Table> copy1(new Simplex_Table(original));
			copy1->Add_Row(i->first, trunc(i->second), -1);
			if (copy1->Is_Solvable())
			{
				copy1->Print_Simplex_Table();
				copy1->Simplex_Method();
				Tree_Solution(*copy1);
			}
			else
			{
				cout << "Unsolvable" << endl;
				copy1->Print_Simplex_Table();
			}
			unique_ptr<Simplex_Table> copy2(new Simplex_Table(original));
			cout << "Finally got here !!!!!!!!!!" << endl;
			copy2->Add_Row(i->first, trunc(i->second) + 1, 1);
			if (copy2->Is_Solvable())
			{
				copy2->Print_Simplex_Table();
				copy2->Simplex_Method();
				Tree_Solution(*copy2);
			}
			else
			{
				cout << "Unsolvable" << endl;
				copy2->Print_Simplex_Table();
			}
		}
		else
		{
			cout << "Done" << endl;
			original.Print_Simplex_Table();
		}
	}
}