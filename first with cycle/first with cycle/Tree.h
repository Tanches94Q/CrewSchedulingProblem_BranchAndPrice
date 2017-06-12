#ifndef TREE
#include<ctype.h>
#include "lap.h"
#include<vector>
#include<algorithm>
#include <fstream>
//#include"Smart.h"
using namespace std;
template<class T>
class Tree{
	int item;
	Tree<T>* son;
	Tree<T>* brother;
	T weight;
public:
	Tree(const int & item, const T & weight, Tree<T>*son = NULL, Tree<T>*brother = NULL);
	~Tree();
	T GetHeight();
	void  PrintTree(int level);
	Tree<T>* Add(Tree<T>* root, int first, int next, T **arr, T**carr, int n, int *nodes, int m, T bound, T gran);
	Tree<T>* Add_NEW(Tree<T>* root, int first, int node, T **arr, T**carr, int n, int *nodes, int m, T bound, T gran, vector <struct Edge> Add_First_max, int kol_flight);
	Tree<T>*  AddChild(Tree<T>* root, T elem);
	Tree<T>*  AddBrother(Tree<T>* root, T elem);
	T Bound(T** carr, int n, T bound, T** parr, vector <struct Edge> Add_First_max, int kol_flight);
	vector<vector<int>> Cycles(int n, int *to, int new_n, int first);
	vector<T> True_Cycles(vector<vector<int>> Set, int n, T bound, vector <struct Edge> Add_First_max, int kol_flight);
	T** Copy(T ** arr, int n);
	T Max_cost(vector<vector<int>>Some_flight, vector<vector<int>> Set, int n);
	vector<int> Get_cycle();
	T ** Mod_matrix(T** matrix,T** cmatrix,int size);
	void Free(Tree<T>* root);

};

//extern  int bound;
namespace
{
	float Max_bound;
	vector<vector<int>> Min_cycle;
	int bound;
	int Flag_empty;
};
template <class T>
Tree<T>::Tree(const int & item, const T & weight, Tree<T>*son = NULL, Tree<T>*brother = NULL)
{
	Tree<T>::item = item;
	Tree<T>::weight = weight;
	Tree<T>::son = son;
	Tree<T>::brother = brother;

}
template <class T>
Tree<T>* Tree<T>::Add_NEW(Tree<T>* root, int first, int node, T **arr, T**carr, int n, int *nodes, int m, T bound, T gran, vector <struct Edge> Add_First_max, int kol_flight)
{
	//static T Max_bound;
	if (root->son)
	{
		if (root->item == -1)
			Add_NEW(root->son, first, node, arr, carr, n, nodes, m, bound, gran, Add_First_max, kol_flight);
		int k = 0;
		//cout << Max_bound << " Max_bound" << endl;
		T r = 0;

		if (gran != n - 1)
		{
			if (root->item == -1)
			{
				for (int h = 1; h<n; h++)
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
					carr = Copy(arr, n);
					//cout << (root->son->item + 1) << endl;
					nodes[0] = (root->son->item + 1);
					root->son = new Tree<T>((root->son->item + 1), 1, NULL, NULL);
					if (Max_bound != 0)
						Add_NEW(root->son, (root->son->item), node, arr, carr, n, nodes, m, Max_bound, gran, Add_First_max, kol_flight);
					else
						Add_NEW(root->son, (root->son->item), node, arr, carr, n, nodes, m, bound, gran, Add_First_max, kol_flight);
				}
				return root;

			}
			//cout << node << endl;
			for (int j = 0; j<n; j++)
			{
				node = j;
				if (gran<j)
				{

					if (arr[first][j] != 0 && arr[first][j] != 1)
					{
						for (int g = 0; g<m; g++)
						{
							if (nodes[g] == j)
								k++;

						}
						if (k == 0)
						{
							root->son = new Tree<T>(j, 1, NULL, NULL);

							carr[first][j] = -100500;//исправил с 100500
							r = j;
							int plus = 0;
							/*cout << "node" << endl;
							for (int c = 0; c<m; c++)
							{
								cout << nodes[c] << " ";
							}
							cout << endl;*/
							T Gran = root->Bound(carr, n, bound, arr, Add_First_max, kol_flight);

							

								if (Gran == -1)// если в решении есть 0

								{

									carr = Copy(arr, n);

									Add_NEW(root, first, node, arr, carr, n, nodes, m, bound, r, Add_First_max, kol_flight);///----------------------------------
								}
								if (Gran == -2)// если на этой ветке больше не найти
								{

									//cout << root->item << endl;
									carr[first][j] = arr[first][j];


									Add_NEW(root, root->item, node, arr, carr, n, nodes, m, bound, (float)(j), Add_First_max, kol_flight);

								}


								if (Gran < bound)
									Add_NEW(root, first, node, arr, carr, n, nodes, m, bound, (float)(j), Add_First_max, kol_flight);///---------------------------------
								else
								{
									bound = Gran;
									cout << "Result:" << bound << endl;
								}

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


								//cout << "******************************" << endl;

								gran = -1;
								//cout << "Gran " << gran << endl;

								delete[] new_nodes;

								//root->son=new Tree<int>(j,1,NULL,NULL);
								Add_NEW(root->son, j, node, arr, carr, n, nodes, m + 1, bound, gran, Add_First_max, kol_flight);
							
						}
					}
					k = 0;



				}


			}
			/*if(first<n)
			++first;*/

		}

	}

	else
	{
		int k = 0;
		int r = 0;
		if (root->item == -1)
		{
			root->son = new Tree<T>(first, 1, NULL, NULL);
			Add_NEW(root->son, first, node, arr, carr, n, nodes, m, bound, gran, Add_First_max, kol_flight);
		}

		if (gran != n - 1)
		{
			for (int j = 0; j<n; j++)
			{
				if (gran<j)
				{

					if (arr[first][j] != 0 && arr[first][j] != 1)
					{
						for (int g = 0; g<m; g++)
						{
							if (nodes[g] == j)
								k++;

						}
						if (k == 0)
						{
							//if(!root->son)
							root->son = new Tree<T>(j, 1, NULL, NULL);
							//cout << arr[first][j] << endl;
							gran = j;
							carr[first][j] = -1000500;//// исправила с 100500
							r = j;
							int plus = 0;
							/*cout << "node" << endl;
							for (int c = 0; c<m; c++)
							{
								cout << nodes[c] << " ";
							}
							cout << endl;*/
							//cout << bound << " bound" << endl;

							T Gran = root->Bound(carr, n, bound, arr, Add_First_max, kol_flight);
							//if(j==n-1)
							//{
							//	delete nodes;
							//m=1;
							//j=0;
							//nodes=new int [m];
							//++first;
							//nodes[0]=first;
							//carr=Copy(arr,n);
							//

							//
							//root=Add(root,first,next,arr,carr,n,nodes,m, bound, -1);////последний на ряду
							//}
							

							if (Gran == -1)// если в решении есть 0

							{

								carr = Copy(arr, n);

								Add_NEW(root, first, node, arr, carr, n, nodes, m, bound, r, Add_First_max, kol_flight);///----------------------------------
							}
							if (Gran == -2)// если на этой ветке больше не найти у сына******************************************************
							{
								if (Flag_empty==0)
								{
									delete nodes;
									Flag_empty++;
								}
								carr[first][j] = arr[first][j];
								root->son->Free(root->son);
								

								//int next=0;
								if (j >= n - 1)
								{
									m = 1;


									nodes = new int[m];
									//Flag_empty = 0;
									//cout << node << endl;
									nodes[0] = node;
									carr = Copy(arr, n);
									Max_bound = bound;
									gran = (float)(first);


									return root;
								}

								//Add_NEW(root,root->item,node,arr,carr,n,nodes,m, bound, root->item);////----------------------------------

							}


							/*if (Gran>bound)
								Add_NEW(root, first, node, arr, carr, n, nodes, m, bound, (float)(j), Add_First_max, kol_flight);/*///---------------------------------
							else
							{
								bound = Gran;
								//cout << bound << "bound" << endl;
								Max_bound = bound;
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


								//cout << "******************************" << endl;

								gran = -1;
								//cout << "Gran " << gran << endl;

								delete[] new_nodes;

								//root->son=new Tree<int>(j,1,NULL,NULL);
								Add_NEW(root->son, j, node, arr, carr, n, nodes, m + 1, bound, gran, Add_First_max, kol_flight);//попробовать с братьями

								/*cout << endl;
								cout << bound << " bound" << endl;*/
								carr = Copy(arr, n);
							}
							/*if(root->item==-1)
							{
							++first;
							root->son=new Tree<int>(first,1,NULL,NULL);
							delete nodes;
							m=1;
							nodes=new int [m];
							cout<<first<<endl;
							nodes[0]=first;
							Add_NEW(root->son,j,node,arr,carr,n,nodes,m, bound,  gran);


							}*/
							/*if(j==5)
							{
							++first;
							j=0;
							}*/
						}
					}
					k = 0;
					/*if(j==n-1)
					return root;*/
					//carr=Copy(arr,n);



				}



			}
			//carr=Copy(arr,n);

		}


	}
	//return root;
	//carr=Copy(arr,n);

	//++first;
	//				j=0;
	/*cout << first << ' ' << node << ' ' << m + 1 << endl;
	cout << bound << " bound" << endl;*/
	Max_bound = bound;
	//cout << Max_bound << " Max_bound" << endl;
	return root;
	//Add_NEW(root,first+1,node,arr,carr,n,nodes,m+1, bound,  5);
}
template <class T>  void Tree<T>::Free(Tree<T>* root)
{
	if (root )
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

template <class T> T Tree<T>::Bound(T** carr, int n, T bound, T** parr, vector <struct Edge> Add_First_max, int kol_flight)
{

	int * to = new int[n];
	int * from = new int[n];
	T * u = new T[n];
	T * v = new T[n];

	T cost = lap(n, carr, to, from, u, v);
	//cout<<"Solution!"<<cost<<endl;
	int q = 0;
	int flag_2 = 0;
	int flag_0 = 0;
	for (int l = 0; l < n; ++l)
	{
		//cout << " + " << carr[l][to[l]] << ' ' << l << ' ' << to[l];
		if (carr[l][to[l]] == 1000500)
			flag_2++;
		if (carr[l][to[l]] == 0)
			flag_0++;

	}
	//cout << endl;

	//if (flag_2 > 0)
	// return -2;// or -1
	int * new_to = new int[n - flag_0];
	int first_flight = -1;
	int t = 0;
	for (int g = 0; g < n; g++)
	{
		if (carr[g][to[g]] != 0)
		{
			if (first_flight == -1)
			{
				//cout << first_flight << endl;
				first_flight = g;
				new_to[t] = to[g];
				//cout << to[g] << " to" << t << endl;
				t++;
			}
			else
			{
				new_to[t] = to[g];
				t++;

			}
		}
	}
	
	if (flag_0 == n)
		return -2;// or -1
	vector<vector<int>> Set = this->Cycles(n, to, n - flag_0, first_flight);
	vector<T> Weight = True_Cycles(Set, n, bound, Add_First_max, kol_flight);
	//vector<vector<int>> Set;
	T w = 100500;
	for (int y = 0; y < Weight.size(); y++)
	{
		if (w > Weight[y])
			w = Weight[y];

	}

	if (bound > Max_bound)
	{
		if (w > Max_bound)
			return -2;
	}
	if (w >= Max_bound)
		return -2;
	return w;


}

template<class T> T** Tree<T>::Copy(T ** arr, int n)
{
	T ** carr = new T*[n];
	for (int i = 0; i<n; i++)
	{
		carr[i] = new T[n];

		for (int j = 0; j<n; j++)
		{
			if (j != i)
			{
				if (arr[i][j] == 0)
				{
					carr[i][j] = 1000500;

				}
				else
				{
					carr[i][j] = arr[i][j];

				}


			}

			else
				carr[i][j] = arr[i][j];

			//cout<<carr[i][j]<<' ';
		}
		//cout<<endl;

	}
	return carr;
}
template <class T>
vector<vector<int>> Tree<T>::Cycles(int n, int *to, int new_n, int first)
{
	vector<vector<int>> Set;
	vector<int> cycle;
	int h = to[0];
	int count = 1;
	int m = n;

	cycle.push_back(first);

	while (new_n>1)
	{

		for (int i = 0; i < m; ++i)
		{
			if (h == i)
			{
				if (cycle.size() < new_n)
				{
					cycle.push_back(i);
					//cout<<i<<" ";
					h = to[i];
					//cout << h << "****" << endl;

					count++;
					i = 0;
					if (cycle[0] == h)
					{
						i = m - 1;
						cycle.push_back(h);
						//cout<<h<<" ";
					}

				}
				else
				{
					//cout << endl;
				}


			}

		}

		Set.push_back(cycle);
		//cout<<endl;
		cycle.clear();

		new_n -= count;
		if (new_n>1)
		{
			for (int j = 0; j<m; j++)
			{
				for (vector<vector<int>>::iterator it = Set.begin(); it != Set.end(); it++)
				{

					vector<int>::iterator p = find(it->begin(), it->end(), j);
					if (p == it->end())
					{
						cycle.push_back(j);
						h = to[j];
						j = m - 1;
					}


				}
			}
			count = 1;
		}

	}
	return Set;
}
template<class T>void Tree<T>::PrintTree(int level)
{

	cout << item << " ";
	if (brother == NULL)
		cout << endl;
	for (Tree<T>*current = son; current; current = current->brother){

		if (current->brother == NULL)
		{

			cout << endl;

		}
		current->PrintTree(level);
	}
}
template<class T>Tree<T>* Tree<T>::AddChild(Tree<T>* root,
	T elem)
{
	if (root->son)
		root->son = AddBrother(root->son, elem);
	else
		root->son = new Tree<T>(elem, 1, NULL, NULL);
	return root;
}

template<class T>Tree<T>* Tree<T>::AddBrother(Tree<T>* root,
	T elem)
{
	if (root->brother)
		root->brother = AddBrother(root->brother, elem);
	else
		root->brother = new Tree<T>(elem, 1, NULL, NULL);
	return root;
}
template <class T>
Tree<T>::~Tree()
{
	if (son)
		delete son;
	if (brother)
		delete brother;
}
template <class T> T Tree<T>::GetHeight()
{
	T max = 0;
	for (Tree<T>*current = son; current; current = current->brother){

		int curHeight = current->GetHeight();
		if (curHeight>max)
			max = curHeight;
	}
	return max + 1;
}
template <class T>vector<T> Tree<T>::True_Cycles(vector<vector<int>> Set, int n, T bound, vector <struct Edge> Add_First_max, int kol_flight)
{
	
	vector<int> airport;
	vector<vector<int>> Flights;
	for (int t = 0; t < Add_First_max.size(); t++)
	{
		airport.push_back(Add_First_max[t].out);
		airport.push_back(Add_First_max[t].in);
		Flights.push_back(airport);
		airport.clear();
		
	}
	
	vector<T> cost;
	
	for (int u = 0; u < Add_First_max.size(); u++)
	{
		
		cost.push_back(Add_First_max[u].cost);

	}
	
	int start_ver = -1;
	int last_ver = -1;

	//vector<vector<float>> Arr_cost_cycles;
	vector<T>money;
	T weight = 0;
	vector<int> cur_cycle;
	for (int u = 0; u < Set.size(); u++)
	{
		
		for (int f = 0; f < Set[u].size(); f++)
		{
			if (Set[u][f] <= kol_flight-1)
			{
				if (start_ver == -1)
				{
					start_ver = Flights[Set[u][f]][0];
					last_ver = Flights[Set[u][f]][1];
					weight = weight + cost[Set[u][f]];
					cur_cycle.push_back(Set[u][f]);

				}
				else
				{
					if (last_ver == Flights[Set[u][f]][0])
					{
						cur_cycle.push_back(Set[u][f]);
						if (start_ver == Flights[Set[u][f]][1])
						{
							weight = weight + cost[Set[u][f]];
							money.push_back(weight);

							if (weight < bound)
								Min_cycle.push_back(cur_cycle);
							if (weight == bound)
							{
								if (Min_cycle.size()==0)
									Min_cycle.push_back(cur_cycle);
							}
							cur_cycle.clear();
							weight = 0;
							start_ver = -1;
							last_ver = -1;

							/*start_ver = Flights[Set[u][f]][0];
							last_ver = Flights[Set[u][f]][1];
							weight = weight + cost[Set[u][f]];*/
						}
						else
						{
							weight = weight + cost[Set[u][f]];
							last_ver = Flights[Set[u][f]][1];
						}
					}
					else
					{
						start_ver = Flights[Set[u][f]][0];
						last_ver = Flights[Set[u][f]][1];
						weight = weight + cost[Set[u][f]];
						cur_cycle.push_back(Set[u][f]);
					}
				}

			}
			else
				f = Set[u].size() - 1;
			
			



		}




	}
	airport.clear();
	Flights.clear();
	cost.clear();
	cur_cycle.clear();
	return money;
}

template<class T>vector<int> Tree<T>::Get_cycle()
{
	vector<int> last = Min_cycle[Min_cycle.size() - 1];
	//Min_cycle.clear();

	return last;

}

template<class T>T ** Mod_matrix(T** matrix, T** cmatrix, int size)
{
	for(int i = 0; i < size; i++)
	{
		cmatrix[i] = new float[size];

		for (int j = 0; j < size; j++)
		{
			if (j != i)
			{
				if (matrix[i][j] == 0)
				{
					cmatrix[i][j] = 100500;//исправила с 100500

				}
				else
				{
					cmatrix[i][j] = matrix[i][j];

				}

			}
			else
				cmatrix[i][j] = matrix[i][j];
			//cout << cmatrix[i][j] << ' ';
		}
		//cout << endl;
	}
	//cout << endl;
	return cmatrix;
}




#endif