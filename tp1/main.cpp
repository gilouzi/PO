#include <iostream>
#include <vector>
#include "simplex.h"

int main() {
	int n, m;
	std::cin >> n >> m;
	//std::cout << n << " " << m << std::endl;

	std::vector< std::vector<float> > matriz (n);
	std::vector<float> c_T (n+m);
	std::vector<float> b_T (n);
	float val_obj = 0.0;
	bool aux = false;

	//o vetor de bases vai guardar na posicao i, o valor da coluna que é base com o valor 1 na linha i
	std::vector<int> bases (n);

	//o vetor colunas_bases vai guardar na posicao j se a coluna j é base ou nao, se sim, em qual linha tem o valor 1
	std::vector<int> colunas_bases (n+m);

	cria_pl(matriz, b_T, c_T, bases, colunas_bases, aux, n, m);
	
	//se aux é false, temos que as variaveis extras sao bases obvias e utilizaremos elas
	if (aux == false){

		//negativar o vetor c para podermos rodar o simplex
		std::vector<float> c_pl (c_T);
		negativa_vetor(c_pl); 

		bool simp = simplex(matriz, b_T, c_pl, bases, colunas_bases, val_obj);

		//ilimitada
		if (simp == false){
			certificado_ilimitada(matriz, b_T, c_pl, bases, colunas_bases, n, m);
			return 0;
		}

		//otima
		else{
			certificado_otima(b_T, c_pl, colunas_bases, val_obj, n, m);
			return 0;
		}

	}

	//se aux é true, vai ter que ser feito a pl auxiliar
	else{
		float val_aux = 0.0;
		std::vector<float> c_aux (m+n);

		cria_pl_aux(matriz, b_T, c_aux, bases, colunas_bases, val_aux, m, n);
		
		bool simp = simplex(matriz, b_T, c_aux, bases, colunas_bases, val_aux);

		//ilimitada
		if (simp == false){
			certificado_ilimitada(matriz, b_T, c_aux, bases, colunas_bases, n, m);
			return 0;
		}

		else{
			//se ótimo da pl auxiliar é negativo, ela é inviavel
			if (val_aux < 0){
				certificado_inviavel(c_aux, n, m);
				return 0;
			}

			//se nao, pl é viavel continua rodando o simplex
			else{
				//antes deve remover as variaveis auxiliares que estavamos utilizando
				remove_pl_aux(matriz, n);

				//pode chamar o simplex reutilizando os calculos que fizemos ate entao mas com o antigo c_T

				//negativar o vetor c para podermos rodar o simplex
				std::vector<float> c_pl (c_T);
				negativa_vetor(c_pl);

				bool simp = simplex(matriz, b_T, c_pl, bases, colunas_bases, val_obj);

				//ilimitada
				if (simp == false){
					certificado_ilimitada(matriz, b_T, c_aux, bases, colunas_bases, n, m);
					return 0;
				}
				//otima
				else{
					certificado_otima(b_T, c_pl, colunas_bases, val_obj, n, m);
					std::cout << "Hey" << std::endl;
					return 0;
				}

			}
		}


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