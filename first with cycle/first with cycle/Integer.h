#ifndef INTEGER_H
#define INTEGER_H
#include<ctype.h>
#include "lap.h"
#include<vector>
#include<algorithm>
#include <fstream>
//#include"Smart.cpp"
using namespace std;

class BnB{
	int item;
	BnB* son;
	BnB* brother;
	float weight;
public:
	BnB(const int & item, const float & weight, BnB*son, BnB*brother);
	~BnB();
	
	void  PrintTree(int level);
	void Write_res();
	BnB* Add(BnB* root, int first, int next, float **arr, float**carr, int n, int *nodes, int m, float bound, int gran);
	BnB* Add_NEW(BnB* root, lprec *lp, REAL * var, int size_var, vector<vector<float>> constrants, vector<float> sum_cost, float wet1, int gran, int *nodes, int m, int kol_ob_reber, int kol_flight, struct Edge*arr, struct Edge*table_1, vector<vector<struct Edge>> variable, std::vector<int> one, std::vector<int> zeros, std::vector < std::vector<struct Edge >>f);
	BnB*  AddChild(BnB* root, int elem);
	BnB*  AddBrother(BnB* root, int elem);
	float Bound(struct Edge* arr, int kol_flight, lprec *lp, int branch, int ind_var, vector<vector<float>> constrants, vector<float> sum_cost, struct Edge* table_1, int kol_ob_reber, std::vector<int> one, std::vector<int> zeros);
	vector<vector<int>> Cycles(int n, int *to, int new_n, int first);
	vector<float> True_Cycles(vector<vector<int>> Set, int n, float bound, vector <struct Edge> Add_First_max, int kol_flight);
	//T** Copy(T ** arr, int n);
	/*T Max_cost(vector<vector<int>>Some_flight, vector<vector<int>> Set, int n);
	vector<int> Get_cycle();
	T ** Mod_matrix(T** matrix, T** cmatrix, int size);*/
	void Free(BnB* root);
};
//float Max_bound;
//vector<vector<int>> Min_cycle;
//#include"Integer.cpp"
#endif

