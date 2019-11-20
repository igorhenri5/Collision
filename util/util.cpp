#include "util.hpp"
#include <iostream>

void util::determinarParticao(int *inicio, int *fim, int rank, int threadNum, int size, int stride){
	if(size == 0){
		*inicio = 0;
		*fim = 0;
	}
	else{
		int tamanhoParticao = (size + threadNum - 1 - stride) / threadNum;
		*inicio = stride + rank * tamanhoParticao;
		*fim = *inicio + tamanhoParticao;
		if(*fim > size)
			*fim = size;
	}
}
