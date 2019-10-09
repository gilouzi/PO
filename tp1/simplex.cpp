#include "simplex.h"

void imprime_matriz(std::vector< std::vector<float> > matriz){
	for (int i = 0; i < matriz.size(); i++) { 
        for (int j = 0; j < matriz[i].size(); j++) 
            std::cout << matriz[i][j] << " "; 
        std::cout << std::endl; 
    } 
	std::cout << std::endl;
}

void imprime_vetor(std::vector<float> vetor){
	for (int j = 0; j < vetor.size(); j++) 
        std::cout << vetor[j] << " "; 
	std::cout << std::endl;
}

void negativa_vetor(std::vector<float> &vetor){
	for (int i = 0; i < vetor.size(); i++)
		vetor[i] = (-1) * vetor[i];
}

int get_pivot_col(std::vector<float> vetor){
	int menor_valor = 0;
	int pos = -1;
	for (int i = 0; i < vetor.size(); i++){
		if (vetor[i] < menor_valor){
			pos = i;
			menor_valor = vetor[i];
		}
	}
	return pos;
}

int get_pivot_lin(std::vector< std::vector<float> > matriz, std::vector<float> b_T, int pivot_col){
	float menor_valor;
	int pos = -1;

    for (int j = 0; j < matriz.size(); j++){
		if (matriz[pivot_col][j] > 0){
			menor_valor = b_T[j]/matriz[j][pivot_col];
			pos = j;
			break;
		}
	}

	if (pos != -1){
		for (int j = pos; j < matriz.size(); j++){
			if (matriz[j][pivot_col] > 0){
				if (b_T[j]/matriz[j][pivot_col] < menor_valor){
					menor_valor = b_T[j]/matriz[j][pivot_col];
					pos = j;
				}
			}
		}
	}
    return pos; 
}

void pivoteia(std::vector< std::vector<float> > &matriz, std::vector<float> &b_T, std::vector<float> &c_T, int pivot_lin, int pivot_col, float &val_obj){
	//pivoteia matriz
	for (int i = 0; i < matriz.size(); i++) {
		if (i != pivot_lin){
			float fator_mult = matriz[i][pivot_col]/matriz[pivot_lin][pivot_col];
			for (int j = 0; j < matriz[i].size(); j++){
				matriz[i][j] = matriz[i][j] - (fator_mult*matriz[pivot_lin][j]);
			}
			//atualiza tambem o b da mesma linha com esse fator encontrado
			b_T[i] = b_T[i] - (fator_mult*b_T[pivot_lin]);
		}     
    } 

	//pivoteia c_t
	float fator_mult = c_T[pivot_col]/matriz[pivot_lin][pivot_col];
	for (int j = 0; j < c_T.size(); j++){
		c_T[j] = c_T[j] - (fator_mult*matriz[pivot_lin][j]);
	}

	//atualiza val obj com base no fator calculado em c
	val_obj = val_obj - (fator_mult*b_T[pivot_lin]);
}



// PL::PL() { //definindo metodo virus da classe virus (classe eh o q vem primeiro)
// 	_nome = nome;
// 	_forca = forca;
// 	_num_pacientes = 0;
// 	//this->nome = nome; //ponteiro para o metodo, referencia para si msm
// } //boas praticas: todos atributos tem que ser inicializados no construtor

// void PL::incrementa_infectados() {
// 	_num_pacientes++;
// }