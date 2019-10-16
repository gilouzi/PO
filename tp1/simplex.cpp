#include <iomanip>

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
        std::cout << std::setprecision(7) << vetor[j] << " "; 
	std::cout << std::endl;
}

void imprime_vetor(std::vector<int> vetor){
	for (int j = 0; j < vetor.size(); j++) 
        std::cout << vetor[j] << " "; 
	std::cout << std::endl;
}

void imprime_vetor(std::vector<bool> vetor){
	for (int j = 0; j < vetor.size(); j++) 
        std::cout << vetor[j] << " "; 
	std::cout << std::endl;
}

void negativa_vetor(std::vector<float> &vetor){
	for (int i = 0; i < vetor.size(); i++){
		if(vetor[i] != 0){
			vetor[i] = (-1) * vetor[i];
		}
	}
		
}

int get_pivot_col(std::vector<float> vetor){
	int pos = -1;

	for (int i = 0; i < vetor.size(); i++){
		if (vetor[i] < 0){
			pos = i;
			return pos;
		}
	}

	return pos;
}

int get_pivot_lin(std::vector<std::vector<float> > &matriz, std::vector<float> &b_T, int pivot_col){
	float menor_valor;
	int pos = -1;

	//vai salvar o primeiro possivel valor de col do pivot
    for (int j = 0; j < matriz.size(); j++){
		if (matriz[j][pivot_col] > 0){
			menor_valor = b_T[j]/matriz[j][pivot_col];
			arruma_precisao(menor_valor);
			pos = j;
			break;
		}
	}

	//vai testar se tem outros valores possiveis que sejam mais adequados p/ ser pivot
	if (pos != -1){
		for (int j = pos; j < matriz.size(); j++){
			if (matriz[j][pivot_col] > 0){
				if (b_T[j]/matriz[j][pivot_col] < menor_valor){
					menor_valor = b_T[j]/matriz[j][pivot_col];
					arruma_precisao(menor_valor);
					pos = j;
				}
			}
		}
	}
    return pos; 
}

void pivoteia_matriz(std::vector< std::vector<float> > &matriz, std::vector<float> &b_T, int pivot_lin, int pivot_col){

	//pivoteia matriz
	for (int i = 0; i < matriz.size(); i++) {
		if (i != pivot_lin){
			float fator_mult = matriz[i][pivot_col]/matriz[pivot_lin][pivot_col];
			for (int j = 0; j < matriz[i].size(); j++){
				matriz[i][j] = matriz[i][j] - (fator_mult*matriz[pivot_lin][j]);
				arruma_precisao(matriz[i][j]);
			}
			//atualiza tambem o b da mesma linha com esse fator encontrado
			b_T[i] = b_T[i] - (fator_mult*b_T[pivot_lin]);
			arruma_precisao(b_T[i]);
		}     
    } 
}

void pivoteia_c_T(std::vector< std::vector<float> > &matriz, std::vector<float> &b_T, std::vector<float> &c_T, int pivot_lin, int pivot_col, float &val_obj){
	//pivoteia c_t
	float fator_mult = c_T[pivot_col]/matriz[pivot_lin][pivot_col];
	for (int j = 0; j < c_T.size(); j++){
		c_T[j] = c_T[j] - (fator_mult*matriz[pivot_lin][j]);
		arruma_precisao(c_T[j]);

	}

	//atualiza val obj com base no fator calculado em c
	val_obj = val_obj - (fator_mult*b_T[pivot_lin]);
	arruma_precisao(val_obj);

}

void pivoteia_pivot(std::vector< std::vector<float> > &matriz, std::vector<float> &b_T, int pivot_lin, int pivot_col){
	float div = matriz[pivot_lin][pivot_col];
	for (int j = 0; j < matriz[pivot_lin].size(); j++){
		matriz[pivot_lin][j] = matriz[pivot_lin][j]/div;
		arruma_precisao(matriz[pivot_lin][j]);
	}
	b_T[pivot_lin] = b_T[pivot_lin]/div;
	arruma_precisao(b_T[pivot_lin]);

}

bool simplex(std::vector< std::vector<float> > &matriz, std::vector<float> &b_T, std::vector<float> &c_T, std::vector<int> &bases, std::vector<int> &colunas_bases, float &val_obj){
	//vai pegar a coluna que sera pivotada
	int pivot_col = get_pivot_col(c_T);
	//std::cout << "Coluna pivot = " << pivot_col << std::endl;

	//se pivot nao for -1 ainda tem algum c negativo, logo, ainda deve rodar o simplex
	while (pivot_col != -1){

		// std::cout << std::endl;
		// std::cout << "Matriz:" << std::endl;
		// imprime_matriz(matriz);
		// std::cout << "b:" << std::endl;
		// imprime_vetor(b_T);
		// std::cout << "C:" << std::endl;
		// imprime_vetor(c_T);
		// std::cout << "val_obj:" << std::endl;
		// std::cout << val_obj << std::endl;

		//vai escolher qual linha dessa coluna sera a pivotada
		int pivot_lin = get_pivot_lin(matriz, b_T, pivot_col);
		//std::cout << "Linha pivot = " << pivot_lin << std::endl;

		//se existe uma linha para ser pivotada prossegue com o simplex
		if (pivot_lin != -1){

			//vai pivotear a matriz baseado nesse pivot encontrado
			pivoteia_matriz(matriz, b_T, pivot_lin, pivot_col);
			pivoteia_pivot(matriz, b_T, pivot_lin, pivot_col);
			pivoteia_c_T(matriz, b_T, c_T, pivot_lin, pivot_col, val_obj);

			//vai atualizar as bases
			//removendo a base antiga do conjunto de bases
			int ex_base = bases[pivot_lin];
			colunas_bases[ex_base] = -1;

			//colocando a nova base no conjunto de bases
			bases[pivot_lin] = pivot_col;
			colunas_bases[pivot_col] = pivot_lin;

			// imprime_vetor(bases);
			// imprime_vetor(colunas_bases);
			
			pivot_col = get_pivot_col(c_T);
		}

		//se nao tem linha para ser pivotada, a pl é ilimitada
		else{
			return false;
		}
	}

	return true;
}

void checa_bases(std::vector< std::vector<float> > &matriz, std::vector<float> &c_T, std::vector<int> &bases, std::vector<int> &colunas_bases, int n, int m){
	//vai procurar se tem outra base obvia diferente da atual
	bool base = true;

	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			if (matriz[i][j] == 1 && c_T[j] == 0){
				for (int k = 0; k < n; k++){
					if(k != i && matriz[k][j] != 0){
						base = false;
						k = n;
					}
				}
				if (base == true){
					//removendo a base antiga do conjunto de bases
					int ex_base = bases[i];
					colunas_bases[ex_base] = -1;

					//colocando a nova base no conjunto de bases
					bases[i] = j;
					colunas_bases[j] = i;
				}
				base = true;
			}
		}
	}
}

void cria_pl(std::vector< std::vector<float> > &matriz, std::vector<float> &b_T, std::vector<float> &c_T, std::vector<int> &bases, std::vector<int> &colunas_bases, bool &aux, int n, int m){
	int elem;
	//inserindo os valores do vetor de custo c_T
	for (int j = 0; j < m; j++){
			std::cin >> elem;
			c_T[j] = elem;
			colunas_bases[j] = -1;
		}

	//inserindo os valores na matriz e em b_T
	for (int i = 0; i < n; i++){

		std::vector<float> vetor (m+n);

		//inserindo os valores lidos na linha da matriz da pl
		for (int j = 0; j < m; j++){
			std::cin >> elem;
			vetor[j] = elem;
		}

		//colocando as variaveis de folga para ficar no formato FPI
		for (int j = m; j < m+n; j++){
			if(j-m == i){
				vetor[j] = 1;
				bases[i] = j;
				colunas_bases[j] = i; 
			}
			else
				vetor[j] = 0;
			c_T[j] = 0;
		}

		std::cin >> elem;

		//se b for negativo nao teremos mais as variaveis extras como base obvias, vai ter que fazer pl auxiliar
		if (elem < 0){
			negativa_vetor(vetor);
			b_T[i] = (-1) * elem;
			aux = true;
		}

		else{
			b_T[i] = elem;
		}

		matriz[i] = vetor;
	}

	checa_bases(matriz, c_T, bases, colunas_bases, n, m);
	// //imprimindo pra testar se está inserindo certo
	// std::cout << std::endl;
	// imprime_matriz(matriz);

	// //imprimindo os vetores c e b para testar se a insercao esta correta
	// imprime_vetor(b_T);
	// imprime_vetor(c_T);
	// imprime_vetor(bases);
	// imprime_vetor(colunas_bases);
}

void cria_pl_aux(std::vector< std::vector<float> > &matriz, std::vector<float> &b_T, std::vector<float> &c_aux, std::vector<int> &bases, std::vector<int> &colunas_bases, float &val_aux, int m, int n) {
	//inicializando o vetor c auxiliar como 0 para as variaveis da matriz
	for (int i = 0; i < m+n; i ++){
		c_aux[i] = 0;
		colunas_bases[i] = -1;
	}

	//acrescentando as colunas extras na matriz e em c para formar a pl auxiliar
	for (int i = 0; i < n; i++){
		for (int j = m+n; j < (2*n)+m; j ++){
			if(j-(m+n) == i){
				c_aux.insert(c_aux.end(), 1);
				matriz[i].insert(matriz[i].end(),1);
				colunas_bases.insert(colunas_bases.end(), i); 
				bases[i] = j;
			}
			else
				matriz[i].insert(matriz[i].end(),0);
		}
	}

	//faz com que as colunas auxiliares acrescentadas tornem-se base
	for (int i = 0; i < n; i++){
		for (int j = m+n; j < (2*n)+m; j ++){
			if(j-(m+n) == i){
				pivoteia_c_T(matriz, b_T, c_aux, i, j, val_aux);
			}
		}
	}

	// std::cout << std::endl;
	// imprime_matriz(matriz);
	// imprime_vetor(b_T);
	// std::cout << "Imprimindo o c da pl aux:" << std::endl;
	// imprime_vetor(c_aux);
	// std::cout << val_aux << std::endl;
}

void remove_pl_aux(std::vector< std::vector<float> > &matriz, std::vector<float> &c_pl, std::vector<int> &bases, std::vector<int> &colunas_bases, int n, int m){

	checa_bases(matriz, c_pl, bases, colunas_bases, n, m);
	// removendo as n colunas extras da matriz 
	for (int i = 0; i < n; i++)
		matriz[i].erase(matriz[i].end()-n, matriz[i].end());
		
}

void certificado_otima(std::vector<float> &b_T, std::vector<float> &c_pl, std::vector<int> &colunas_bases, float val_obj, int n, int m){
	std::cout << "otima" << std::endl;
	std::cout << val_obj << std::endl;

	for(int i = 0; i < m; i++){
		if(colunas_bases[i] != -1){
			std::cout << b_T[colunas_bases[i]] << " ";
		}
		else{
			std::cout << "0 ";
		}
	}
	std::cout << std::endl;

	for(int i = m; i < n+m; i++){
		std::cout << c_pl[i] << " ";
	}
	std::cout << std::endl;
}

void certificado_inviavel(std::vector<float> &c_pl, int n, int m){
	std::cout << "inviavel" << std::endl;

	for(int i = m; i < n+m; i++){
		std::cout << c_pl[i] << " ";
	}
	std::cout << std::endl;

}

void certificado_ilimitada(std::vector< std::vector<float> > &matriz, std::vector<float> &b_T, std::vector<float> &c_pl, std::vector<int> &bases, std::vector<int> &colunas_bases, int n, int m){
	std::cout << "ilimitada" << std::endl;

	for(int i = 0; i < m; i++){
		if(colunas_bases[i] != -1){
			std::cout << b_T[colunas_bases[i]] << " ";
		}
		else{
			std::cout << "0 ";
		}
	}
	std::cout << std::endl;

	int pivot_col = get_pivot_col(c_pl);

	for(int i = 0; i < m; i++){
		if(pivot_col == i){
			std::cout << 1 << " ";
		}
		else if(colunas_bases[i] == -1){
			std::cout << 0 << " ";
		}
		else{
			int pos_1 = colunas_bases[i];
			if(matriz[pos_1][pivot_col] != 0){
				std::cout << (-1) * matriz[pos_1][pivot_col] << " ";
			}
			else{
				std::cout << 0 << " ";
			}
			
		}
	}

	std::cout << std::endl;
}

void arruma_precisao(float &num){
	if (std::abs(num) < 1e-5) num = 0;
}