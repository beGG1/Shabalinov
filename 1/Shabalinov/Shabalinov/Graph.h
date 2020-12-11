#pragma once
#include <vector>
#include "KS.h"
#include "Pipe.h"
using namespace std;
class Graph
{
private:
	size_t Pipe1;
	size_t KS1;
	vector <vector <int>> Insident;
	vector <vector<int>> Smej;
public:
	void graph_create(size_t P, size_t K);
	void graph_show();
	size_t get_KS();
	size_t get_Pipe();
	void add_conection(vector<KS> KSs, vector<Pipe>Pipes, int max_id_ks, int max_id_pipe);
	void delete_conection(vector<KS> KSs, vector<Pipe>Pipes, int max_id_ks, int max_id_pipe);
	void top_sort(vector<KS> &KSs, vector<Pipe>&Pipes, int max_id_ks, int max_id_pipe, bool show_result);
	void delet_not_working(vector<KS> KSs, vector<Pipe>Pipes, int max_id_ks, int max_id_pipe);
	void max_propusk(vector<KS> KSs, vector<Pipe>Pipes, int max_id_ks, int max_id_pipe);
	void max_lenght(vector<KS> KSs, vector<Pipe>Pipes, int max_id_ks, int max_id_pipe);
	void add_pipe();
	void add_ks();
	void save(vector<KS> KSs, vector<Pipe>Pipes, string fileName);
	void load(vector<KS> KSs, vector<Pipe>Pipes, string fileName);
	void pipe_delete(int index);
	void delete_all();
	void ks_delete(int index);
};

