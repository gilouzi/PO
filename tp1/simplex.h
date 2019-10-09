#ifndef SIMPLEX_H
#define SIMPLEX_H

#include <iostream>
#include <string>
#include <vector>

void imprime_matriz(std::vector< std::vector<float> > matriz);
void imprime_vetor(std::vector<float> vetor);
void negativa_vetor(std::vector<float> &vetor);
int get_pivot_col(std::vector<float> vetor);
int get_pivot_lin(std::vector< std::vector<float> > matriz, std::vector<float> b_T, int pivot_col);
void pivoteia(std::vector< std::vector<float> > &matriz, std::vector<float> &b_T, std::vector<float> &c_T, int pivot_lin, int pivot_col, float &val_obj);

// class PL {
// private:
// 	int* bT;
// 	int* cT;
// 	int* cT_original;
// 	int val_obj;
// 	Matriz matriz;
// 	Matriz vero;
// 	Matriz PL_aux;
// public:
// 	PL(int n, int m);
// 	void simplex();
// };

// class Matriz {
// private:
// 	int** m;
// 	int tam_i;
// 	int tam_j;
// public:
	
// };

#endif