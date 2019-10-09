#include <iostream>
#include <vector>
#include "simplex.h"

int main() {
	int n, m, elem;
	std::cin >> n >> m;
	//std::cout << n << " " << m << std::endl;

	std::vector< std::vector<float> > matriz (n);
	std::vector<float> c_T (n+m);
	std::vector<float> b_T (n);
	float val_obj = 0.0;
	bool aux = false;

	//inserindo os valores do vetor de custo c_T
	for (int j = 0; j < m; j++){
			std::cin >> elem;
			c_T[j] = elem;
		}

	//inserindo os valores na matriz e em b_T
	for (int i = 0; i < n; i++){

		std::vector<float> vetor (m+m);

		//inserindo os valores lidos na linha da matriz da pl
		for (int j = 0; j < m; j++){
			std::cin >> elem;
			vetor[j] = elem;
		}

		//colocando as variaveis de folga para ficar no formato FPI
		for (int j = m; j < m+m; j++){
			if(j-m == i)
				vetor[j] = 1;
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

	//imprimindo pra testar se está inserindo certo
	std::cout << std::endl;
	imprime_matriz(matriz);

	//imprimindo os vetores c e b para testar se a insercao esta correta
	imprime_vetor(b_T);
	imprime_vetor(c_T);
	
	//se aux é false, temos que as variaveis extras sao bases obivias e utilizaremos elas
	if (aux == false){

		//negativar o vetor c para podermos rodar o simplex
		std::vector<float> c_pl (c_T);
		negativa_vetor(c_pl); 

		//vai pegar a coluna que sera pivotada
		int pivot_col = get_pivot_col(c_pl);
		std::cout << "Coluna pivot = " << pivot_col << std::endl;

		//se pivot nao for -1 ainda tem algum c negativo, logo, ainda deve rodar o simplex
		while (pivot_col != -1){

			//vai escolher qual linha dessa coluna sera a pivotada
			int pivot_lin = get_pivot_lin(matriz, b_T, pivot_col);

			//se existe uma linha para ser pivotada prossegue com o simplex
			if (pivot_lin != -1){

				//vai pivotear a matriz baseado nesse pivot encontrado
				pivoteia(matriz, b_T, c_pl, pivot_lin, pivot_col, val_obj);

				std::cout << std::endl;
				imprime_matriz(matriz);
				imprime_vetor(b_T);
				imprime_vetor(c_pl);
				std::cout << val_obj << std::endl;
				
				pivot_col = get_pivot_col(c_pl);
			}

			//se nao tem linha para ser pivotada, a pl é ilimitada
			else{
				
			}
			
		}

	}

	//se aux é true, vai ter que ser feito a pl auxiliar
	else{
		//vai criar o vetor c para a pl auxiliar ()
		// std::vector<float> c_aux (n+2m);
		// negativa_vetor(c_pl);
	}


	// constructors used in the same order as described above:
	// std::vector<int> first;                                // empty vector of ints
	// std::vector<int> second (4,100);                       // four ints with value 100
	// std::vector<int> third (second.begin(),second.end());  // iterating through second
	// std::vector<int> fourth (third);                       // a copy of third

	// the iterator constructor can also be used to construct from arrays:
	// int myints[] = {16,2,77,29};
	// std::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

	// std::cout << "The contents of fifth are:";
	// for (std::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
	// 	std::cout << ' ' << *it;
	// std::cout << '\n';

}