#ifndef SMART_H
#define SMART_H


#include <iostream>
#include <fstream>
#include<string>

#include<vector>
#include<iterator>
#include <stdio.h>
#include <stdlib.h>
#include "lp_lib.h"
//

struct Edge {
	int out;
	int in;
	double cost;
	int start;
	int finish;
};

int Create(struct Edge *p, int out, int in, double cost, int start, int finish);
int IN_cur_w(struct Edge *cur_w, int wsize, struct Edge next);
float Metric(struct Edge *p, int size, struct Edge next, int time);
float Metric_2(struct Edge *p, int size, struct Edge next, int time, int dest);
int Repeat(struct Edge *p, int size, struct Edge next);
Edge Return(struct Edge *p, int size, int st, int end, int sum, int time);
void Print(struct Edge *p);
Edge Get_Max(struct Edge *p, int size);
int Copy(struct Edge p, struct Edge *m);
Edge to_destination(struct Edge *p, int size, int st, int end, int sum, int time);
Edge to_continiuos(struct Edge *p, int size, int st, int end, int sum, int time, struct Edge *w, int wsize);
std::vector<struct Edge> to_vector(struct Edge * table,int size);
std::vector<struct Edge> Search_route(struct Edge *w, struct Edge *p,struct Edge *cur_w, int size, int wsize);
std::vector<struct Edge> Delete(std::vector<struct Edge> vector_table, std::vector<struct Edge> new_vector);
Edge Return(struct Edge *p, int size, int st, int end, int sum, int time);
Edge Get_Min(std::vector<struct Edge> p, int n,struct Edge* all, int size);
struct Edge* to_arr(std::vector<struct Edge> p);
struct Edge* Arr_Flights(std::ifstream & fin,int kol_flight);
struct Edge* Change_cost(struct Edge *p, int size, struct Edge *table, int size_table, REAL *duals);
int check_forbid_route(std::vector<std::vector<struct Edge>> f, struct Edge *p, int n, int weight);



int count_neigbours(struct Edge *p, int n, struct Edge sample);
Edge Get_Min_2(std::vector<struct Edge> p, int n);
Edge find_next(struct Edge first, struct Edge *p, int size,int dest);
int check(struct Edge first, struct Edge* nodes, int m);
float cicle(struct Edge first, struct  Edge * nodes, int m, struct Edge *p, int size, int weight, int dest, std::vector<std::vector<struct Edge>> f);
float** Edge_graph_matrix(std::vector<struct Edge> p);
int Max_airport(std::vector<struct Edge> p);
std::vector<struct Edge> Low();
void Free_Low();

#endif 