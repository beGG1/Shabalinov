#pragma once
#ifndef Header_h
#define Header_h
#include <iostream>
#include <fstream>
#include <Windows.h> // Нужно для распознания кирилицы 
#include <vector>
#include <string>
#include "Graph.h"

using namespace std;

	void print_menu();
	void save_pipe(vector<Pipe>& Pipes, string& fileName, int size);
	vector<Pipe> load_pipe(const string& fileName);
	void save_ks(vector<KS>& KS1, const string& fileName, int size);
	vector <KS> load_ks(const string& fileName);
	void edit_pipe(vector<Pipe>& Pipe);
	void edit_ks(vector<KS>& KSs);
	void deletePipe(vector <Pipe>& P, Graph &G);
	void deleteKS(vector <KS>& K,Graph &G);
	vector <Pipe> pipe_filter(vector <Pipe>& P);
	vector <KS> ks_filter_effect(vector <KS>& KS1, bool key, double number);
	vector <KS> ks_filter_name(vector <KS>& KS1, string Name);
	int find_nomer_pipe(vector<Pipe>& Pipe, size_t id);
	int find_nomer_ks(vector<KS>& KSs, size_t id);
	int findNumSort(vector<KS> KS);
	int minimal(int a, int b);
#endif