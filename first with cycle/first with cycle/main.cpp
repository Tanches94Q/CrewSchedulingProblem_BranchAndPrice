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


int main()
{
	int kol_flight = 33;
	float wet = -1;
	float wet1 = -1;
	int fflag = 0;
	int *nodes1 = 0;
	
	struct Edge *arr = new struct Edge[kol_flight];
	ifstream fin;
	fin.open("three_schedule_in_minutes.txt");
	//fin.open("float_cost.txt");
	arr=Arr_Flights(fin, kol_flight);
	vector <Edge> First_max;

	fin.close();
	
	int kol_ob_reber = 6;
	struct Edge *table = new struct Edge[kol_ob_reber];
	struct Edge* pot_dest = new struct Edge[kol_ob_reber];
	struct Edge* table_1 = new struct Edge[kol_ob_reber];
	
	fin.open("plan_in_minutes.txt");
	table = Arr_Flights(fin,kol_ob_reber);
	for (int y = 0; y < kol_ob_reber; y++)
	{
		Copy(table[y],&pot_dest[y]);
		Copy(table[y], &table_1[y]);

	}
	
	fin.close();
	
	
	vector <vector<float>> constrants(kol_ob_reber);
	constrants.reserve(kol_ob_reber + 10);
	struct Edge LM;
	
	vector <struct Edge> vector_table;
	vector_table = to_vector(table, kol_ob_reber);

	
	vector<struct Edge> new_table;
	vector<vector<struct Edge>> variable;
	vector<float> sum_cost;
	float SUM_total=0;
	int h = 0;
	int yy = 0;
	float sum_mar;
	while (vector_table.size()!= 0)
	{
		
		if (vector_table.size() == 1)
			cout << endl;
		new_table = Search_route(table, arr, pot_dest, kol_flight, vector_table.size());// было 33
		cout << "ROUTE!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
		sum_mar = 0;
		for (int d = 0; d < new_table.size(); d++)
		{
			Print(&new_table[d]);
			sum_mar = sum_mar + new_table[d].cost;
		}
		SUM_total = SUM_total + sum_mar;
		cout << "ROUTE!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
		cout << "Cost " << sum_mar << endl;
		sum_cost.push_back(sum_mar);
		
		vector<int> cur_constr;
		for (int t = 0; t < kol_ob_reber; t++)
		{
			//cout << table_1[t].out << endl;
			for (int u = 0; u < new_table.size(); u++)
			{
				if (new_table[u].out == table_1[t].out)
				{
					if(new_table[u].in == table_1[t].in)
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
		
		
		
		vector_table=Delete(vector_table,new_table);
		table = new struct Edge[vector_table.size()];
		pot_dest = new struct Edge[vector_table.size()];
		variable.push_back(new_table);
		new_table.clear();
		for (int r = 0; r < vector_table.size(); r++)
		{
			Copy(vector_table[r],&table[r]);
			Copy(vector_table[r], &pot_dest[r]);
			
		}
}


	vector_table.clear();
	delete[] pot_dest;
	delete[] table;

	//cout << "Enter\n";
	lprec *lp;
	
	REAL *row = new REAL[constrants.size()]; 
	while (wet1 < 0)
	{
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

		for (int h = 0; h < constrants.size(); h++)
		{
			for (int m = 0; m < constrants[h].size(); m++)
			{
				row[m + 1] = constrants[h][m];
			}
			add_constraint(lp, row, GE, 1.0); /* constructs the row: +v_1 +2 v_2 >= 3 */
			//set_add_rowmode(lp, FALSE);
			//set_add_rowmode(lp, TRUE);

		}
		print_lp(lp);
		
		set_verbose(lp, IMPORTANT);
		solve(lp);
		//print_objective(lp);
		//print_scales(lp);
		cout<<fixed;
		print_solution(lp, sum_cost.size());
		get_print_sol(lp);
		int vsize = sum_cost.size();
		
		/*cout << "Variables" << endl;
		for (int t = 0; t < sum_cost.size(); t++)
		{
			cout << var[t] << endl;
		}*/
		




		//REAL *duals = new REAL[sum_cost.size()];
		REAL *duals = new REAL[sum_cost.size()+1];
		get_dual_solution(lp, duals);
		set_presolve(lp, PRESOLVE_DUALS, get_presolveloops(lp));
		print_objective(lp);
		delete_lp(lp);

		int neig = 0;
		int m = 1;

		
		int w = 0;
		int node = -1;
		struct Edge first;
		
		First_max = to_vector(Change_cost(arr, kol_flight, table_1, kol_ob_reber, duals), kol_flight);
		//delete duals;
		
		wet = -1;
		vector<struct Edge> del;
		if (fflag == 3)
			cout << endl;
		struct Edge* nodes;
		vector<vector<struct Edge>> forbird;
		while (wet == -1)
		{
			nodes = new struct Edge[m];

			nodes[0] = Get_Min_2(First_max, First_max.size());
			Copy(nodes[0], &first);
			wet = cicle(nodes[0], nodes, m, arr, kol_flight, nodes[0].cost, nodes[0].out, forbird);
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
		/*Tree<float>* node1 = new Tree<float>(0, 1, NULL, NULL);
		for (int j = 0; j < Add_First_max.size(); j++)
		{

			if (edge_matrix[0][j] != 0)
				node1->AddChild(node1, j);
		}*/
		
		nodes1 = new int[1];
		Tree<float>* root_child = new Tree<float>(0, 1, NULL, NULL);
		Tree<float>* root = new Tree<float>(-1, 1, root_child, NULL);
		nodes1[0] = 0;
		if (fflag == 3)
			cout << endl;
		Low();
		root->Add_NEW(root, 0, 0, edge_matrix, cmatrix, Add_First_max.size(), nodes1, 1, wet, -1, Add_First_max,kol_flight);
	
		for (int g = 0; g < Add_First_max.size(); g++)
		{
			delete edge_matrix[g];
			delete cmatrix[g];
		}
		delete edge_matrix;
		delete cmatrix;


		vector<int> Min_cycle = root->Get_cycle();
		wet1 = 0;
		yy = 0;
		sum_mar = 0;
		root->Free(root);
		new_table.reserve(Min_cycle.size()+10);
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
		variable.push_back(new_table);
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


		//delete nodes1;
		new_table.clear();
		Add_First_max.clear();
		
		//lprec *lp;
		sum_cost.push_back(sum_mar);
		//REAL *row = new REAL[kol_ob_reber];
		fflag++;
		//free( duals);
	}
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

	for (int h = 0; h < constrants.size(); h++)
	{
		for (int m = 0; m < constrants[h].size(); m++)
		{
			row[m + 1] = constrants[h][m];
		}
		add_constraint(lp, row, GE, 1.0); /* constructs the row: +v_1 +2 v_2 >= 3 */
		//delete[]row;
		//set_add_rowmode(lp, FALSE);
		//set_add_rowmode(lp, TRUE);

	}
	//print_lp(lp);

	set_verbose(lp, IMPORTANT);
	solve(lp);
	//print_objective(lp);
	//print_scales(lp);
	cout << fixed;
	print_solution(lp, sum_cost.size());
	//delete_lp(lp);
	REAL *var = new REAL[sum_cost.size()];
	get_variables(lp, var);
	delete_lp(lp);
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

	for (int h = 0; h < constrants.size(); h++)
	{
		for (int m = 0; m < constrants[h].size(); m++)
		{
			row[m + 1] = constrants[h][m];
		}
		add_constraint(lp, row, GE, 1.0); /* constructs the row: +v_1 +2 v_2 >= 3 */
		//set_add_rowmode(lp, FALSE);
		//set_add_rowmode(lp, TRUE);

	}
	wet = (float(1) / float(sum_cost.size() + 1));
	vector<int> one;
	vector<int> zeros;
	/*REAL *var1 = new REAL[sum_cost.size()];
	cout << "Fractional variables" << endl;*/
	for (int g = 0; g < sum_cost.size(); g++)
	{
		//cout << "__" << var[g] << endl;
		//var1[g] = var[g];
		if (var[g] == 1)
		{
			var[g] = var[g] - (0.2*wet);
		}
		else
			var[g] = var[g] + (0.3*wet);
		cout << var[g] << endl;
		if (var[g] < 0.1)
		{
			vector<float> vector1(constrants[0].size(), 0.0);
			vector1[g] = 1.0;
			for (int m = 0; m < constrants[0].size(); m++)
			{
				row[m + 1] = vector1[m];
			}
			constrants.push_back(vector1);
			add_constraint(lp, row, LE, 0.0);
			zeros.push_back(constrants.size()-1);


		}
		if (var[g] > 0.9)
		{
			vector<float> vector1(constrants[0].size(), 0.0);
			vector1[g] = 1.0;
			for (int m = 0; m < constrants[0].size(); m++)
			{
				row[m + 1] = vector1[m];
			}
			constrants.push_back(vector1);
			add_constraint(lp, row, GE, 1.0);
			one.push_back(constrants.size() - 1);


		}

		wet = wet + (float(1) / float(sum_cost.size() + 1));
	}
	
	/*cout << "Integer variables" << endl;
	for (int y = 0; y < sum_cost.size(); y++)
	{
		cout << var1[y] << endl;

	}
	cout << "Received routes" << endl;
	for (int y = 0; y < sum_cost.size(); y++)
	{
		if (var1[y] == 1)
		{
			cout << "Number of variable " << y + 1 << endl;
			for (int f = 0; f < variable[y].size(); f++)
				Print(&variable[y][f]);
			cout << endl;
			
		}

	}
	cout << "First sum" << SUM_total << endl;*/

	BnB* broot_child = new BnB(0, 1.0, NULL, NULL);
	BnB* broot = new BnB(-1, 1, broot_child, NULL);
	
	nodes1 = new int[1];
	nodes1[0] = 0;
	struct Edge *hhhh = new Edge[5];
	vector < std::vector<struct Edge >>f;


	/*for (int g = 0; g < variable[4].size(); g++)
	{
		Print(&variable[4][g]);
	}
	cout << endl;
	cout << endl;
	for (int g = 0; g < variable[9].size(); g++)
	{
		Print(&variable[9][g]);
	}*/
	broot->Add_NEW(broot, lp, var, sum_cost.size(), constrants, sum_cost, wet1, -1, nodes1, 1, kol_ob_reber, kol_flight, arr,table_1, variable,one,zeros,f);
	broot->Write_res();
	

	
	set_verbose(lp, IMPORTANT);
	print_lp(lp);
	solve(lp);
	print_objective(lp);
	system("pause\n");

	return 0;
}