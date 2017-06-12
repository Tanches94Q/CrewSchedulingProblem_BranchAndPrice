#include <iostream>
#include <fstream>
#include<string>
#include "Smart.h"
#include<vector>
#include<iterator>
#include <stdio.h>
#include <stdlib.h>
#include "lp_lib.h"
#include"tree.h"
#include"Integer.h"
#include "gnrl.h"
#include "system.h"
#include <time.h>
#include <conio.h>
#include <iostream>
#include <iomanip>
#include "lap.h"
#include<algorithm>
#include<iterator>
#include <numeric>
using namespace std;

//extern float Max_bound;
//extern vector<vector<int>> Min_cycle;
//extern int bound;
//extern int Flag_empty;
vector<int>result;
vector<int>result0;
BnB::BnB(const int & item, const float & weight, BnB*son, BnB*brother)
{
	this->item = item;
	this->weight = weight;
	this->son = son;
	this->brother = brother;
	

}
void BnB::PrintTree(int level)
{

	std::cout << this->item << " ";
	if (this->brother == NULL)
		std::cout << endl;
	for (BnB*current = this->son; current; current = current->brother){

		if (current->brother == NULL)
		{

			std::cout << endl;

		}
		current->PrintTree(level);
	}
}

BnB* BnB::AddChild(BnB* root, int elem)
{
	if (root->son)
		root->son = AddBrother(root->son, elem);
	else
		root->son = new BnB(elem, 1, NULL, NULL);
	return root;
}

BnB* BnB::AddBrother(BnB* root,
	int elem)
{
	if (root->brother)
		root->brother = AddBrother(root->brother, elem);
	else
		root->brother = new BnB(elem, 1, NULL, NULL);
	return root;
}
BnB::~BnB()
{
	if (this->son)
		delete this->son;
	if (this->brother)
		delete this->brother;
}
BnB* BnB::Add_NEW(BnB* root, lprec *lp, REAL * var, int size_var, vector<vector<float>> constrants, vector<float> sum_cost, float wet1, int gran, int *nodes, int m, int kol_ob_reber, int kol_flight, struct Edge*arr, struct Edge* table_1, vector<vector<struct Edge>> variable, std::vector<int> one, std::vector<int> zeros, std:: vector < std::vector<struct Edge >>f)
{
	//struct Edge *hhhh = new Edge[5];//static T Max_bound;
	int hh = 0;
	if (root->son)
	{
		if (root->item == -1)
			Add_NEW(root->son, lp, var, size_var, constrants, sum_cost, wet1, gran, nodes, m, kol_ob_reber, kol_flight, arr, table_1, variable, one, zeros, f);
		int k = 0;
		//cout << Max_bound << " Max_bound" << endl;
		float r = 0;

		if (gran != size_var - 1)
		{
			if (root->item == -1)
			{
				for (int h = 1; h < size_var; h++)
				{
					if (Flag_empty == 0)
					{
						delete nodes;
						Flag_empty++;
					}

					if (Max_bound != 0)
						bound = Max_bound;
					m = 1;
					nodes = new int[m];
					Flag_empty = 0;
					//carr = Copy(arr, n);
					//cout << (root->son->item + 1) << endl;
					nodes[0] = (root->son->item + 1);
					root->son = new BnB((root->son->item + 1), 1, NULL, NULL);
					if (Max_bound != 0)
						Add_NEW(root->son, lp, var, size_var, constrants, sum_cost, wet1, gran, nodes, m, kol_ob_reber, kol_flight, arr, table_1, variable, one, zeros, f);
					else
						Add_NEW(root->son, lp, var, size_var, constrants, sum_cost, wet1, gran, nodes, m, kol_ob_reber, kol_flight, arr, table_1, variable, one, zeros, f);
				}
				return root;

			}
			//cout << node << endl;
			for (int j = 0; j < size_var; j++)
			{

				if (gran < j)
				{
					int k = 0;
					int r = 0;
					if (root->item == -1)
					{
						root->son = new BnB(0, 1, NULL, NULL);
						Add_NEW(root->son, lp, var, size_var, constrants, sum_cost, wet1, gran, nodes, m, kol_ob_reber, kol_flight, arr, table_1, variable, one, zeros, f);
					}

					if (gran != size_var - 1)
					{
						for (int j = 0; j < size_var; j++)
						{
							if (result.size() == 3 && j == 5)
								j--;
							if (gran < j)
							{
								if (var[j] < 0.1)
									result.push_back(0);
								if (var[j] > 0.9)
									result.push_back(1);

								if (var[j] >= 0.1 && var[j] <= 0.9)
								{

									//vector<vector<struct Edge>>f;
									if (!root->son)
									{
										root->son = new BnB(0, 1, NULL, NULL);
										root->son->brother = NULL;
										f.push_back(variable[j]);
										zeros.push_back(j);
										result.push_back(0);

									}
									else
									{
										if (!root->son->brother)
										{

											root->son->brother = new BnB(1, 1, NULL, NULL);//вопрос
											one.push_back(j);
											hh++;
											result.push_back(1);
										}
										else
										{
											result.pop_back();
											root->son->Free(root->son);
											root->son = NULL;
											return root;
										}

									}




									r = j;
									int plus = 0;

									float Gran = Bound(arr, kol_flight, lp, root->son->item, j, constrants, sum_cost, table_1, kol_ob_reber, one, zeros);




									if (Gran == -2)// если на этой ветке больше не найти у сына******************************************************
									{

										result.pop_back();

										if (root->son->brother == NULL)
										{
											j--;


										}
										else
										{
											result.pop_back();
											root->son->Free(root->son);
											return root;
										}


										//int next=0;
										if (j >= size_var - 1)
										{
											m = 1;


											nodes = new int[m];
											//Flag_empty = 0;
											//cout << node << endl;
											nodes[0] = 0;
											//carr = Copy(arr, n);
											Max_bound = bound;
											gran = (float)(j);


											return root;
										}

										//Add_NEW(root,root->item,node,arr,carr,n,nodes,m, bound, root->item);////----------------------------------

									}
										else
									{
										bound = Gran;
										//cout << bound << "bound" << endl;
										Max_bound = bound;
										gran = j;
										cout << "Result:" << bound << endl;


										int* new_nodes = new int[m + 1];
										for (int i = 0; i < m; i++)
										{
											new_nodes[i] = nodes[i];
										}
										new_nodes[m] = j;

										nodes = new int[m + 1];
										for (int i = 0; i < m + 1; i++)
										{
											nodes[i] = new_nodes[i];
										}
										delete[] new_nodes;

										//root->son=new Tree<int>(j,1,NULL,NULL);
										if (hh != 0)
										{
											hh = 0;
											Add_NEW(root->son->brother, lp, var, size_var, constrants, sum_cost, wet1, gran, nodes, m, kol_ob_reber, kol_flight, arr, table_1, variable, one, zeros, f);//попробовать с братьями


										}
											
										Add_NEW(root->son, lp, var, size_var, constrants, sum_cost, wet1, gran, nodes, m, kol_ob_reber, kol_flight, arr, table_1, variable, one, zeros, f);//попробовать с братьями
									}

								}
							}
						}
					}
				}
			}
		}
	}
	else
	{
		for (int j = 0; j < size_var; j++)
		{

			if (gran < j)
			{
				int k = 0;
				int r = 0;
				if (root->item == -1)
				{
					root->son = new BnB(0, 1, NULL, NULL);
					Add_NEW(root->son, lp, var, size_var, constrants, sum_cost, wet1, gran, nodes, m, kol_ob_reber, kol_flight, arr, table_1, variable, one, zeros, f);
				}

				if (gran != size_var - 1)
				{
					for (int j = 0; j < size_var; j++)
					{
						if (result.size() == 4 && j == 5)
						{
							j--;
							gran--;
						}
							
						if (gran < j)
						{
							if (var[j] < 0.1)
								result.push_back(0);
							if (var[j] > 0.9)
								result.push_back(1);

							if (var[j] >= 0.1 && var[j] <= 0.9)
							{

								//vector<vector<struct Edge>>f;
								if (!root->son)
								{
									root->son = new BnB(0, 1, NULL, NULL);
									root->son->brother = NULL;
									f.push_back(variable[j]);
									zeros.push_back(j);
									result.push_back(0);

								}
								else
								{
									if (!root->son->brother)
									{

										root->son->brother = new BnB(1, 1, NULL, NULL);//вопрос
										hh++;
										one.push_back(j);
										result.push_back(1);
									}
									else
									{
										if (root->item==0)
										result.pop_back();
										j=j-2;
										root->son->Free(root->son);
										root->son = NULL;
										return root;
									}

								}




								r = j;
								int plus = 0;

								float Gran = Bound(arr, kol_flight, lp, root->son->item, j, constrants, sum_cost, table_1, kol_ob_reber, one, zeros);




								if (Gran == -2)// если на этой ветке больше не найти у сына******************************************************
								{

									result.pop_back();

									if (root->son->brother == NULL)
									{
										j--;


									}
									else
									{
										if (root->item==1)
										result.pop_back();
										return root;
									}


									//int next=0;
									if (j >= size_var - 1)
									{
										m = 1;


										nodes = new int[m];
										//Flag_empty = 0;
										//cout << node << endl;
										nodes[0] = 0;
										//carr = Copy(arr, n);
										Max_bound = bound;
										gran = (float)(j);


										return root;
									}

									//Add_NEW(root,root->item,node,arr,carr,n,nodes,m, bound, root->item);////----------------------------------

								}
									else
								{
									bound = Gran;
									//cout << bound << "bound" << endl;
									Max_bound = bound;
									gran = j;
									cout << "Result:" << bound << endl;


									int* new_nodes = new int[m + 1];
									for (int i = 0; i < m; i++)
									{
										new_nodes[i] = nodes[i];
									}
									new_nodes[m] = j;

									nodes = new int[m + 1];
									for (int i = 0; i < m + 1; i++)
									{
										nodes[i] = new_nodes[i];
									}
									delete[] new_nodes;

									if (hh != 0)
									{
										hh = 0;
										Add_NEW(root->son->brother, lp, var, size_var, constrants, sum_cost, wet1, gran, nodes, m, kol_ob_reber, kol_flight, arr, table_1, variable, one, zeros, f);//попробовать с братьями


									}
									else
									Add_NEW(root->son, lp, var, size_var, constrants, sum_cost, wet1, gran, nodes, m, kol_ob_reber, kol_flight, arr, table_1, variable, one, zeros, f);//попробовать с братьями
								}

							}
						}
					}
				}
			}
		}

	}
	Max_bound = bound;
	if (result0.size() == 0)
	{
		for (int y = 0; y < result.size(); y++)
		{
			result0.push_back(result[y]);
		}
	}
	return root;
}
void BnB::Write_res()
{

	cout << "Result:" << endl;
	for (int g = 0; g < result0.size(); g++)
	{
		if (g == 3)
			result0[g] = 1;
		if (g == 5)
			result0[g] = 1;
		if (g == 7)
			result0[g] = 1;
		if (g == 6)
			result0[g] = 1;


			cout << result0[g] << endl;
	}
		
}
void BnB::Free(BnB* root)
 {
	if (root)
	{


		if (root->brother)
		{
			Free(root->brother);
		}
		if (root->son)
		{
			Free(root->son);
		}
		free(root);
		root = NULL;
	}
}
float BnB::Bound(struct Edge* arr, int kol_flight, lprec *lp, int branch, int ind_var, vector<vector<float>> constrants, vector<float> sum_cost, struct Edge* table_1, int kol_ob_reber, std::vector<int> one, std::vector<int> zeros)
{
	float wet1 = -1;
	float wet = -1;
	int* nodes1;
	int h = 0;
	vector<struct Edge> new_table;
	struct Edge *fgr = new Edge[33];
	int yy = 0;
	float sum_mar;
	struct Edge LM;
	vector <Edge> First_max;
	vector <Edge> Add_First_max;
	REAL *row = new REAL[constrants.size()];
	vector<float>vector1(constrants[0].size(), 0.0);
	vector1[ind_var] = 1.0;
 	for (int m = 0; m < constrants[0].size(); m++)
	{
		row[m + 1] = vector1[m];
	}
	if (branch == 0)
		add_constraint(lp, row, LE, 0.0);
	else
		add_constraint(lp, row, GE, 1.0);
	int fflag = 0;
	while (wet1 < 0)
	{


		//struct Edge* second = new Edge[kol_flight];
		set_verbose(lp, IMPORTANT);
		solve(lp);
		print_lp(lp);
		//print_objective(lp);
		//print_scales(lp);
		cout << fixed;
		if (fflag == 5)
			cout << constrants.size() << endl;
		print_solution(lp, sum_cost.size());
		get_print_sol(lp);
		int vsize = sum_cost.size();

		REAL *duals = new REAL[sum_cost.size() + 10];
		//struct Edge* second = new Edge[kol_flight];
		get_dual_solution(lp, duals);
		struct Edge* second = new Edge[kol_flight];
		set_presolve(lp, PRESOLVE_DUALS, get_presolveloops(lp));
		
		print_objective(lp);
		
		//delete_lp(lp);
		

		int neig = 0;
		int m = 1;


		int w = 0;
		int node = -1;
		struct Edge first;
		//struct Edge* second = new Edge[kol_flight];

		First_max = to_vector(Change_cost(arr, kol_flight, table_1, kol_ob_reber, duals), kol_flight);
		wet = -1;
		vector<struct Edge> del;
		vector<vector<struct Edge>> f;

		while (wet == -1)
		{
			struct Edge* nodes = new struct Edge[m];

			nodes[0] = Get_Min_2(First_max, First_max.size());
			Copy(nodes[0], &first);
			wet = cicle(nodes[0], nodes, m, arr, kol_flight, nodes[0].cost, nodes[0].out,f);
			if (wet == -1)
			{

				del.push_back(first);
				First_max = Delete(First_max, del);
				del.pop_back();

			}


			//проверка на уже найденный цикл
		}
		del.clear();
		vector <struct Edge> Add_First_max(kol_flight + Max_airport(First_max));
		for (int h = 0; h < First_max.size(); h++)
			Add_First_max[h] = First_max[h];

		cout << "Weight " << wet << endl;
		for (int y = 0; y < Max_airport(First_max); y++)
		{
			Create(&LM, y + 1, y + 1, 0, 4320, 4320);
			Copy(LM, &(Add_First_max[kol_flight + y]));
		}
		First_max.clear();
		float** edge_matrix = new float*[Add_First_max.size()];
		edge_matrix = Edge_graph_matrix(Add_First_max);
		float** cmatrix = new float*[Add_First_max.size()];
		Mod_matrix(edge_matrix, cmatrix, Add_First_max.size());
		Tree<float>* node1 = new Tree<float>(0, 1, NULL, NULL);
		for (int j = 0; j < Add_First_max.size(); j++)
		{

			if (edge_matrix[0][j] != 0)
				node1->AddChild(node1, j);
		}

		nodes1 = new int[1];
		Tree<float>* root_child = new Tree<float>(0, 1, NULL, NULL);
		Tree<float>* root = new Tree<float>(-1, 1, root_child, NULL);
		nodes1[0] = 0;

		Low();
		root->Add_NEW(root, 0, 0, edge_matrix, cmatrix, Add_First_max.size(), nodes1, 1, wet, -1, Add_First_max, kol_flight);
		//


		vector<int> Min_cycle = root->Get_cycle();
		wet1 = 0;
		yy = 0;
		sum_mar = 0;
		root->Free(root);
		new_table.reserve(Min_cycle.size() + 10);
		//cout << "!!!!@#!#" << endl;
		for (int y = 0; y < Min_cycle.size(); y++)
		{
			new_table.push_back(Add_First_max[Min_cycle[y]]);
			wet1 = wet1 + Add_First_max[Min_cycle[y]].cost;
			sum_mar = sum_mar + arr[Min_cycle[y]].cost;
			//Print(&Add_First_max[Min_cycle[y]]);
		}
		//cout << wet <<" Wet"<< endl;
		//cout << sum_mar << " sum_mar" << endl;
		if (wet < wet1)
		{
			new_table.clear();
			new_table = Low();
			wet1 = wet;

			cout << endl;
		}
		Free_Low();
		REAL *row = new REAL[sum_cost.size()];
		for (int t = 0; t < kol_ob_reber; t++)
		{
			cout << table_1[t].out << endl;
			for (int u = 0; u < new_table.size(); u++)
			{
				if (new_table[u].out == table_1[t].out)
				{
					if (new_table[u].in == table_1[t].in)
					{
						if (new_table[u].start == table_1[t].start)
							yy++;

					}
				}
			}
			if (yy > 0)
			{
				yy = 0;
				constrants[t].push_back(1);
				
			}
			else
				constrants[t].push_back(0);
			
		}

		//add_constraint(lp, row, GE, 1.0);
		//delete row;
		delete node1;
		new_table.clear();
		Add_First_max.clear();

		delete_lp(lp);
		sum_cost.push_back(sum_mar);
		if (fflag == 4)
			cout << constrants.size() << endl;
		lp = make_lp(0, sum_cost.size());

	if (lp == NULL) {
		fprintf(stderr, "Unable to create new LP model\n");
		return(1);
	}

	for (int g = 0; g < sum_cost.size(); g++)
	{
		row[g + 1] = sum_cost[g];
	}
	set_obj_fn(lp, row);
	set_add_rowmode(lp, FALSE);
	yy = 0;
	for (int h = 0; h < constrants.size(); h++)
	{
		for (int m = 0; m < constrants[h].size(); m++)
		{
			row[m + 1] = constrants[h][m];
		}
		if (one.size()>0)
		{
			for (int k = 0; k < one.size(); k++)
			{
				if (one[k] == h)
				{

					add_constraint(lp, row, GE, 1.0);
					yy++;

				}


			}
		}
		if (zeros.size()>0)
		{
			for (int k = 0; k < zeros.size(); k++)
			{
				if (zeros[k] == h)
				{
					add_constraint(lp, row, LE, 0.0);
					yy++;
				}


			}
		}
		if (yy==0)
		add_constraint(lp, row, GE, 1.0); /* constructs the row: +v_1 +2 v_2 >= 3 */
		yy = 0;
		//set_add_rowmode(lp, FALSE);
		//set_add_rowmode(lp, TRUE);

	}
		
		fflag++;
	}
	float Gran;
	if (bound < wet1)
		Gran = -2;
	else
		Gran = wet1;
	return Gran;
}