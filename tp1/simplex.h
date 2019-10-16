#ifndef SIMPLEX_H
#define SIMPLEX_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

void imprime_matriz(std::vector< std::vector<float> > matriz);
void imprime_vetor(std::vector<float> vetor);
void imprime_vetor(std::vector<int> vetor);
void imprime_vetor(std::vector<bool> vetor);
void negativa_vetor(std::vector<float> &vetor);
int get_pivot_col(std::vector<float> vetor);
int get_pivot_lin(std::vector<std::vector<float> > &matriz, std::vector<float> &b_T, int pivot_col);
void pivoteia_matriz(std::vector< std::vector<float> > &matriz, std::vector<float> &b_T, int pivot_lin, int pivot_col);
void pivoteia_c_T(std::vector< std::vector<float> > &matriz, std::vector<float> &b_T, std::vector<float> &c_T, int pivot_lin, int pivot_col, float &val_obj);
void pivoteia_pivot(std::vector< std::vector<float> > &matriz, std::vector<float> &b_T, int pivot_lin, int pivot_col);
bool simplex(std::vector< std::vector<float> > &matriz, std::vector<float> &b_T, std::vector<float> &c_T, std::vector<int> &bases, std::vector<int> &colunas_bases, float &val_obj);
void cria_pl(std::vector< std::vector<float> > &matriz, std::vector<float> &b_T, std::vector<float> &c_T, std::vector<int> &bases, std::vector<int> &colunas_bases, bool &aux, int n, int m);
void checa_bases(std::vector< std::vector<float> > &matriz, std::vector<float> &c_T, std::vector<int> &bases, std::vector<int> &colunas_bases, int n, int m);
void cria_pl_aux(std::vector< std::vector<float> > &matriz, std::vector<float> &b_T, std::vector<float> &c_aux, std::vector<int> &bases, std::vector<int> &colunas_bases, float &val_aux, int m, int n);
void remove_pl_aux(std::vector< std::vector<float> > &matriz, std::vector<float> &c_pl, std::vector<int> &bases, std::vector<int> &colunas_bases, int n, int m);
void certificado_otima(std::vector<float> &b_T, std::vector<float> &c_pl, std::vector<int> &colunas_bases, float val_obj, int n, int m);
void certificado_inviavel(std::vector<float> &c_pl, int n, int m);
void certificado_ilimitada(std::vector< std::vector<float> > &matriz, std::vector<float> &b_T, std::vector<float> &c_pl, std::vector<int> &bases, std::vector<int> &colunas_bases, int n, int m);
void arruma_precisao(float &num);

#endif