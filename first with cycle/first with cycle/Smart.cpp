#include "Smart.h"
#include <iostream>
#include<malloc.h>
#include<math.h>
#include"Integer.h"
#include<vector> 
#include <fstream>
//#include"Tree.h"

using namespace std;
vector<struct Edge> Low_bound;

int Create(struct Edge *p, int out, int in, double cost, int start, int finish)
{
	p->out = out;
	p->in = in;
	p->cost = cost;
	p->start = start;
	p->finish = finish;
	
	return 1;
}

void Print(struct Edge *p)
{
	cout << "Flight" << endl;
	cout << "From:" << p->out << endl;
	cout << "Time from:" << p->start << endl;
	cout << "In:" << p->in << endl;
	cout << "Time in:" << p->finish << endl;
	cout << "Cost:" << p->cost << endl;

}
struct Edge* Arr_Flights(ifstream & fin, int kol_flight)
{
	struct Edge LM;
	struct Edge *arr = new struct Edge[kol_flight];
	int start;
	int finish;
	double y;
	int out;
	int in;
	double cost;
	int i = 0;
	int k = 0;
	while (fin >> y)
	{
		if (i < 4)
		{
			if (i == 0)
			{
				out = y;

			}
			if (i == 1)
			{
				in = y;

			}
			if (i == 2)
			{
				cost = y;

			}
			if (i == 3)
			{
				start = y;

			}

			++i;

		}
		else{
			if (i == 4)
			{
				finish = y;
				//cout << finish[0] << ':' << finish[1] << endl;
				Create(&LM, out, in, cost, start, finish);
				//Print(&LM);
				arr[k] = LM;
				//Destroy(&LM);
				i = 0;

				k++;
			}

		}



	}
	return arr;
}
vector<struct Edge> to_vector(struct Edge * table, int size)
{
	vector <Edge> vector_table(size);
	//struct Edge LM;
	for (int h = 0; h < size; h++)
	{
		//Print(&table[h]);
		Copy(table[h], &vector_table[h]);
		//vector_table.push_back(LM);

	}
	delete table;
	return vector_table;
}
int check_forbid_route(std::vector<vector<struct Edge>> f, struct Edge *p, int n,int weight)
{
	int h = 0;
	for (int t = 0; t < f.size(); t++)
	{
		if (n == f[t].size())
		{
			h++;
			for (int b = 0; b < f[t].size(); b++)
			{
				if (f[t][b].out != p[b].out)
					return weight;

			}
		}
	}
	if (h == 0)
		return weight;
	else
	return -1;
}

struct Edge* Change_cost(struct Edge *p, int size, struct Edge *table, int size_table, REAL *duals)
{
	struct Edge *pt;
	pt= new struct Edge[size];
	for (int y = 0; y < size; y++)
	{
		Copy(p[y],&pt[y]);
		for (int t = 0; t < size_table; t++)
		{
			if (p[y].out == table[t].out)
			{
				if (p[y].in == table[t].in)
				{
					if (p[y].start == table[t].start)////////////////только те рейсы, которые точно записаны как обязательные
					{
						if (p[y].finish == table[t].finish)
						{
							pt[y].cost = p[y].cost - duals[t+1];
							//cout << duals[t+1]<<" DUAL" << endl;
							cout << pt[y].cost << " new cost" << endl;
							//Print(&p[y]);
						}
						
					}
					
				}
			}
		}
		
		//cout << y << endl;

	}
	return pt;
}
struct Edge* to_arr(vector<struct Edge> p)
{
	struct Edge * arr = new struct Edge[p.size()];
	for (int t = 0; t < p.size(); t++)
	{
		arr[t] = p[t];
	}
	return arr;
}
Edge Get_Min(std::vector<struct Edge> p, int n, struct Edge* all, int size)
{
	float met = 1000;
	struct Edge l=p[0];
	for (int y = 0; y < n; y++)
	{
		if (met > Metric(all, size, p[y], p[y].start))
		{
			met = Metric(all, size,  p[y], p[y].start);
			Copy(p[y], &l);
		}
	}
	return l;
}
Edge Get_Min_2(std::vector<struct Edge> p, int n)
{
	float met = 1000;
	struct Edge l;
	for (int y = 0; y < n; y++)
	{
		if (met > Metric(to_arr(p), p.size(), p[y], p[y].start))
		{
			met = Metric(to_arr(p), p.size(), p[y], p[y].start);
			Copy(p[y], &l);
		}
	}
	return l;
}

Edge Get_Max(struct Edge *p, int size)
{
	int max = p[0].cost;
	struct Edge l;
	Create(&l, p[0].out, p[0].in, p[0].cost, p[0].start, p[0].finish);
	for (int y = 1; y < size; y++)
	{
		if (max < p[y].cost)
		{
			max = p[y].cost;
			Copy(p[y], &l);
			///l = p[y];
		}
	}
	return l;

}
float Metric(struct Edge *p, int size, struct Edge next, int time)
{
	float met = 0;
	float koeff = 0.33;
	struct Edge return_1;
	return_1 = Return(p, size, next.out, next.in, next.cost, next.finish);/////////////////////////?????????????????????????????????
	if (return_1.start == -1)// возможность вернуться назад
		return 2000;
	met = met + (koeff*(next.start - time));// учет ожидания
	met = met + (koeff*next.cost);//учет стоимости рейса
	met = met - count_neigbours(p, size, next);
	return met;
}
float Metric_2(struct Edge *p, int size, struct Edge next, int time,int dest)/////добавить dest
{
	float met = 0;
	float koeff = 0.33;
	struct Edge return_1;
	if (next.in == dest)
		Copy(next, &return_1);
	else return_1 = Return(p, size, dest, next.in, next.cost, next.finish);/////////////////////////?????????????????????????????????
	if (return_1.start == -1)// возможность вернуться назад
		return 2000;
	met = met + (koeff*(next.start - time));// учет ожидания
	met = met + (koeff*next.cost);//учет стоимости рейса
	met = met - count_neigbours(p, size, next);
	return met;
}
int count_neigbours(struct Edge *p, int n, struct Edge sample)
{
	int count = 0;

	for (int j = 0; j<n; j++)
	{
		if (p[j].out == sample.in)//проверка на продолжительность маршрута. успеет ли сегодня закончится этот рейс
			if (sample.finish<p[j].start)
				count++;

	}


	return count;
}

Edge to_destination(struct Edge *p, int size, int st, int end, int sum, int time)
{
	int start = -1;
	int finish = -1;
	
	struct Edge l;
	Create(&l, end, st, sum, start, finish);
	//Print(&l);
	int flag = 0;//
	int metrica = 0;
	for (int i = 0; i < size; i++)
	{
		//Print(&p[i]);
		if (p[i].out == end)
		{
			if (p[i].in == st)
			{
				if (p[i].start > time)/////на следующие сутки
				{
					if (metrica != 0)
					{
						if (abs(metrica) > abs(Metric(p, size, p[i], time)))
						{
							metrica = Metric(p, size, p[i], time);
							//Print(&p[i]);
							Copy(p[i], &l);
						}
					}
					else{
						metrica = Metric(p, size, p[i], time);
						//Print(&p[i]);
						Copy(p[i], &l);
					}
					
					
				}
			}
		}

	}
	//cout << l.cost << endl;
	//if (l.start - end > 60)
	//{
	//	l.cost = l.cost + l.start - end;/////////////////////////////CHANGE COST
	//	cout << "MORE THEN 60!!!!!!!!!" << endl;
	//}
	//cout << l.cost << endl;
	return l;

}
Edge Return(struct Edge *p, int size, int st, int end, int sum, int time)
{
	int start = -1;
	int finish = -1;

	struct Edge l;
	Create(&l, end, st, sum, start, finish);
	//Print(&l);
	int flag = 0;//
	int metrica = 0;
	for (int i = 0; i < size; i++)
	{
		if (p[i].out == end)
		{
			if (p[i].in == st)
			{
				if (p[i].start> time)/////на следующие сутки
				{
					
						Copy(p[i], &l);
					

				}
			}
		}

	}
	
	return l;

}
Edge to_continiuos(struct Edge *p, int size, int st, int end, int sum, int time, struct Edge *w, int wsize)// может быть несколько вариантов продолжения.. завести массив(можно из индексов)
{
	int start = -1;
	int finish = -1;
	
	struct Edge l;
	int filter=0;
	int index=-1;
	Create(&l, end, st, sum, start, finish);
	//Print(&l);
	int flag = 0;
	int metrica = 0;
	for (int i = 0; i < wsize; i++)
	{
		if (w[i].out == end)
		{
			if (w[i].in != st)
			{
				if (w[i].start > time)/////на следующие сутки
				{
					if (metrica != 0)
					{
						if (abs(metrica) > abs(Metric(p, size, w[i], time)))
						{
							metrica = Metric(p, size, w[i], time);
							//Print(&w[i]);
							Copy(w[i], &l);
							flag++;
						}
					}
					else{
						metrica = Metric(p, size, w[i], time);
						//Print(&w[i]);
						Copy(w[i], &l);
						flag++;
					}
					
					
					
				}
			}

		}

	}
	if (flag == 0)
	{
		for (int i = 0; i < size; i++)
		{
			if (p[i].out == end)
			{
				if (p[i].in != st)
				{
					if (p[i].start > time)/////на следующие сутки
					{
						if (metrica != 0)
						{
							if (abs(metrica) > abs(Metric(p, size, p[i], time)))
							{
								metrica = Metric(p, size, p[i], time);
								//Print(&p[i]);
								Copy(p[i], &l);
							}
						}
						else{
							metrica = Metric(p, size, p[i], time);
							//Print(&p[i]);
							Copy(p[i], &l);
						}


					}
				}

			}

		}
	}
	if (index>-1)
	Copy(p[index], &l);
	//cout << l.cost << endl;
	/*if (l.start - end > 60)
	{
		l.cost = l.cost + l.start - end;
		cout << "MORE THEN 60!!!!!!!!!" << endl;
	}
	cout << l.cost << endl;*/
	
	return l;
}
int Copy(struct Edge p, struct Edge *m)
{
	m->out = p.out;
	m->in = p.in;
	m->cost = p.cost;
	m->start = p.start;
	m->finish = p.finish;
	
	return 1;

}
int IN_cur_w(struct Edge *cur_w, int wsize,struct Edge next)
{
	int r = 0;
	for (int i = 0; i < wsize; i++)
	{
		if (cur_w[i].in == next.in)
		{
			if (cur_w[i].out == next.out)
				r++;
		}
	}
	if (r > 0)
		return 1;
	else
		return 0;
}
int Repeat(struct Edge *p, int size, struct Edge next)
{
	int flag = 0;
	for (int u = 0; u < size; u++)
	{
		if (p[u].out == next.out)
		{
			if (p[u].in == next.in)
			{
				flag++;
				return flag;
			}
				
		}
	}
	return flag;
}

vector<struct Edge> Search_route(struct Edge *w, struct Edge *p, struct Edge *cur_w, int size, int wsize)
{
	struct Edge* Back;
	struct Edge* Go;
	struct Edge* cycle;
	struct Edge* cur_Back;
	struct Edge* cur_Go;
	struct Edge* cur_cycle;
	int size_back = 0;
	int size_go = 0;
	int h = 0;
	int enter = 0;
	struct Edge *cur_pot_dest;
	int g = 0;
	vector<Edge> cur_W;
	cur_W.reserve(wsize+10);
	for (int m = 0; m < wsize; m++)
		cur_W.push_back(cur_w[m]);
	Edge first = Get_Max(cur_w, wsize);
	//Edge first = Get_Min(cur_W, wsize,p,size);
	cur_W.empty();
	//h++;
	struct Edge* if_recur;
	if_recur = new struct Edge[wsize];
	for (int i = 0; i < wsize; i++)
	{
		Copy(cur_w[i],&if_recur[i]);
	}
	int z = 0;
	if (wsize==0)
		cur_pot_dest = new struct Edge[wsize];
	else
	cur_pot_dest = new struct Edge[wsize-1];
	for (int i = 0; i < wsize; i++)
	{
		if (cur_w[i].out == first.out)
		{
			if (cur_w[i].in != first.in)
			{
				Copy(cur_w[i], &cur_pot_dest[z]);
				z++;

			}
		}
		else{
			Copy(cur_w[i], &cur_pot_dest[z]);
			z++;
		}
	}
	h++;
	int cur_wsize = wsize - 1;
	
	delete[]cur_w;

	cur_w = new struct Edge[cur_wsize];
	for (int i = 0; i < cur_wsize; i++)
	{
		Copy(cur_pot_dest[i],&cur_w[i]);
		
	}
	delete[]cur_pot_dest;
	//cycle = new struct Edge[1];
	Back = new struct Edge[1];
	Go = new struct Edge[1];
//	Copy(first, &cycle[0]);
	Copy(first, &Back[0]);
	Copy(first, &Go[0]);
	size_back++;
	size_go++;
	int begin = first.out;
	int not_back = 0;
	vector<struct Edge> route;
	while (h != wsize+1)
	{

		
		

		Edge next = to_destination(p, size, begin, first.in, first.cost, first.finish);

		if (next.start == -1)
		{
			if (size_back > 1)
			{
				for (int f = 0; f < size_back; f++)
					route.push_back(Back[f]);
				return route;
			}
				
			not_back++;
			
			next = to_destination(w, cur_wsize+1, begin, first.in, first.cost, first.finish);// weak place
			if (next.start == -1)
			next = to_continiuos(p, size, first.out, first.in, first.cost, first.finish, cur_w, cur_wsize);
		}
		else{
			if (IN_cur_w(w, wsize + 1, next) == 1)
			{
				h++;

			}
				
			cur_Back = new struct Edge[size_go];
			for (int i = 0; i < size_go; i++)
			{
				Copy(Go[i], &cur_Back[i]);
				
			}
			
			delete[]Back;
			size_back = size_go;
			Back = new struct Edge[size_back+1];
			for (int i = 0; i < size_back; i++)
			{
				Copy(cur_Back[i],&Back[i]);
			}
			Copy(next,&Back[size_back]);
			size_back++;
			//cout << "It is the cycle to back!" << endl;
			//for (int i = 0; i < size_back; i++)
			//{
			//	cout << "____________" << i + 1 << "--------------" << endl;
			//	//Print(&Back[i]);
			//}
			if (h == wsize + 1)
			{
				for (int f = 0; f < size_back; f++)
					route.push_back(Back[f]);
				return route;
			}
			
			
			
			next = to_continiuos(p, size, begin,first.in, first.cost, first.finish, cur_w, cur_wsize);



		}

		//Print(&next);
		if (Repeat(Go, size_go, next)>0)
		{
			if (size_back > 1)
			{
				for (int f = 0; f < size_back; f++)
					route.push_back(Back[f]);
				return route;
			}
		}
		if (next.start == -1)// и продолжение и замыкание вернули -1 и нужно вернуться
		{ // проверить весь Back на вхождение в cur_w
			if (size_back > 1)
			{
				for (int f = 0; f < size_back; f++)
					route.push_back(Back[f]);
				return route;
			}
			//cout << "Return!" << endl;
			

			return Search_route(if_recur, p, cur_w, size, cur_wsize);

		}
		else
		{
			cur_Go = new struct Edge[size_go];
			for (int i = 0; i < size_go; i++)
			{
				Copy(Go[i], &cur_Go[i]);
				
			}
			delete[]Go;

			Go = new struct Edge[size_go + 1];
			for (int i = 0; i < size_go; i++)
			{
				Copy(cur_Go[i], &Go[i]);
			}
			Copy(next, &Go[size_go]);
			size_go++;
			//cout << "The cycle is continiuos!" << endl;
			//for (int i = 0; i < size_go; i++)
			//{
			//	cout << "++++++" << i + 1 << "********" << endl;
			//	//Print(&Go[i]);
			//}
			if (next.in == begin)
			{
				cycle = new struct Edge[size_go];
				for (int y = 0; y < size_go; y++)
				{
					Copy(Go[y],&cycle[y]);

				}
				for (int f = 0; f < size_go; f++)
					route.push_back(cycle[f]);
				return route;
			}
			
			Copy(next,&first);
			enter = 0;
			for (int t = 0; t < wsize; t++)
			{
				if (w[t].out == next.out && w[t].in == next.in)
				{
					h++;
					enter++;
				}
			}
			if (enter > 0)
			{
				z = 0;
				cur_pot_dest = new struct Edge[cur_wsize - 1];
				for (int i = 0; i < cur_wsize; i++)
				{
					if (cur_w[i].out == next.out)
					{
						if (cur_w[i].in != next.in)
						{
							Copy(cur_w[i], &cur_pot_dest[z]);
							z++;

						}
					}
					else{
						Copy(cur_w[i], &cur_pot_dest[z]);
						z++;
					}
				}

				cur_wsize--;
				
				delete[]cur_w;

				cur_w = new struct Edge[cur_wsize];
				for (int i = 0; i < cur_wsize; i++)
				{
					Copy(cur_pot_dest[i], &cur_w[i]);
					
				}
				delete[]cur_pot_dest;
			}




			
		}

	}
	cycle = new struct Edge[1];
	for (int f = 0; f < 1; f++)
		route.push_back(cycle[f]);
	return route;
	
}
vector<struct Edge> Delete(vector<struct Edge> vector_table, vector<struct Edge> new_vector)
{

	for (int u = 0; u < new_vector.size(); u++)
	{
		for (int h = 0; h < vector_table.size(); h++)
		{
			if (vector_table[h].out == new_vector[u].out)
			{
				if (vector_table[h].in == new_vector[u].in)
				{
					if (vector_table[h].start == new_vector[u].start)
						vector_table.erase(vector_table.begin() + h);

				}
			}
		}
	}
	return vector_table;
}

Edge find_next(struct Edge first, struct Edge *p, int size,int dest)
{
	struct Edge next;
	int count_neigb = count_neigbours(p, size, first);
	int choice;
	int index = 0;
	float next_koef = 0;
	vector<double> koeff;
	koeff.reserve(size+10);

	if (count_neigb == 0)
		return first;
	if (count_neigb != 0)
	{
		for (int i = 0; i < size; i++)
		{
			/*while (index < count_neigb + 1)
			{*/
			if (p[i].out == first.in)
			{
				if (first.finish < p[i].start)
				{

					koeff.push_back(Metric_2(p, size, p[i], first.finish,dest));/////////////////----------------------------

				}
				else
					koeff.push_back(1000);


			}
			else
				koeff.push_back(1000);

		}

		int position;
		int cur_min = 1000;
		for (int j = 0; j < koeff.size(); j++)
		{
			if (cur_min > koeff[j])
			{
				cur_min = koeff[j];
				position = j;
			}
		}
		koeff.clear();
		if (cur_min == 1000)
			return first;
		return p[position];
	}



}

float cicle(struct Edge first, struct  Edge * nodes, int m, struct Edge *p, int size, int weight, int dest, vector<vector<struct Edge>> f)
{

	struct Edge next = find_next(first, p, size,dest);
	//int neig_first=neig_of_first(nodes[0], arr,  n,  next,neig);

	if (next.out == first.out)
	{

		//cout << "No cicle" << endl;
		//Print(&next);
		delete[] nodes;
		return -1;

	}
	if (next.in == dest)
	{
		struct Edge* new_nodes = new struct Edge[m + 1];
		for (int i = 0; i<m; i++)
		{
			new_nodes[i] = nodes[i];
		}
		new_nodes[m] = next;
		delete[] nodes;
		nodes = new struct Edge[m + 1];
		Low_bound.reserve(m);
		for (int i = 0; i<m + 1; i++)
		{
			nodes[i] = new_nodes[i];
			Low_bound.push_back(nodes[i]);
		}
		m++;
		if (f.size() != 0)
		{
			if (check_forbid_route(f, nodes, m, weight) == -1)
				return -1;
		}
		delete[] new_nodes;
		delete[] nodes;
		

		/*cout << "***********ROUTE!********" << endl;
		for (int l = 0; l < m; l++)
			Print(&nodes[l]);*/


		return next.cost + weight;

	}



	//cout << "Cicle!!!!!Not complite" << endl;
	int w = 0;
	for (int i = 0; i < m; i++)
	{
		if (i != 0)
		{
			if (nodes[i].in != next.out)
			{
				w = w + next.cost;//////////////////////////////////////////////
				//Print(&nodes[i]);
			}
			else
			{
				w = w + nodes[i].cost;//+Weight(nodes[i-1],nodes[i],arr);
				//cout<<nodes[i]<<' '<<nodes[0];
				i = m - 1;
			}
		}
		else
			Print(&nodes[i]);
		//cout<<nodes[i]<<' ';
	}


	/*cout<<endl;
	cout<<"Weight:"<<w<<endl;
	delete[] nodes;
	nodes=NULL;
	nodes=NULL;
	return w;*/
	if (check(next, nodes, m + 1) != -1)
	{
		if (check(next, nodes, m + 1) == 0)
		{
			//cout << "Cicle!!!!!" << endl;
			int w = 0;
			for (int i = 0; i<m; i++)
			{
				if (i != 0)
				{
					w = w + nodes[i].cost;
				}

				Print(&nodes[i]);
			}
			//cout<<next;
			w = w + next.cost;

			//cout << endl;
			cout << "Weight:" << w << endl;
			delete[] nodes;
			nodes = NULL;
			nodes = NULL;
			return w;


		}
		delete[] nodes;
		nodes = NULL;
		return -1;
	}
	else
	{
		struct Edge* new_nodes = new struct Edge[m + 1];
		for (int i = 0; i<m; i++)
		{
			new_nodes[i] = nodes[i];
		}
		new_nodes[m] = next;
		delete[] nodes;
		nodes = new struct Edge[m + 1];
		for (int i = 0; i<m + 1; i++)
		{
			nodes[i] = new_nodes[i];
		}
		delete[] new_nodes;
		//m++;

	}
	weight = weight + next.cost;
	first = next;
	/*int nei=neig_first;
	if(neig_first==4)
	cout<<endl;*/

	return cicle(first, nodes, m + 1, p, size, weight, dest,f);
}
void Free_Low()
{
	Low_bound.clear();
}
vector<struct Edge> Low()
{
	return Low_bound;
}

int check(struct Edge first, struct Edge* nodes, int m)
{
	for (int i = 0; i<m; i++)
	{

		if (nodes[i].in == first.in)
			if (nodes[i].out == first.out)
				return i;
	}
	return -1;
}
int Max_airport(std::vector<struct Edge> p)
{
	int max = p[0].out;
	for (int u = 0; u<p.size(); u++)
	{
		if (p[u].out > max)
			max = p[u].out;
		if (p[u].in > max)
			max = p[u].in;
	}
	return max;
}
float ** Edge_graph_matrix(std::vector<struct Edge> p)
{
	//int add_vertice = Max_airport(p);
	
	float** matrix = new float*[p.size() ];
	for (int m = 0; m < p.size(); m++)
	{
		/*if (m == 26)
			cout << endl;*/
		
		matrix[m] = new float[p.size()];
		for (int r = 0; r < p.size(); r++)
		{
			if (m != r)
			{
				if (p[m].in == p[r].out)
				{
					if (p[m].finish < p[r].start)
					{
						matrix[m][r] = (p[m].cost + p[r].cost) / 2;
						if (p[m].in == p[m].out || p[r].in == p[r].out)
							matrix[m][r] = 1;
					}
						
					else
						matrix[m][r] = 0;
					if (p[m].in==p[m].out)
						matrix[m][r] = 1;
				}
				else
					matrix[m][r] = 0;

				
			}
			else
				matrix[m][r] = 0;
			//cout << matrix[m][r] << ' ';

		}
		//cout << endl;
		//cout << endl;
	}
	return matrix;
}