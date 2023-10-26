#include <stdio.h>
#include <stdlib.h>

#define quantidade_processos_maxima 10 

typedef struct {
	int id;
	int prioridade;
	int tempo_de_execucao;
} str_processos;

void inicializa_processos(str_processos *processos);


void main() {
	int i = 0;
	str_processos* processos = (str_processos*)malloc(quantidade_processos_maxima * sizeof(str_processos));
	
	inicializa_processos(processos);
	
	for(i = 0; i < 7; i++) {
		printf("%d %d %d\n", processos[i].id, processos[i].prioridade, processos[i].tempo_de_execucao);
	}
	
	
}


void inicializa_processos(str_processos *processos) {
	processos[0].id = 1;
	processos[0].prioridade = 0;
	processos[0].tempo_de_execucao = 5;
	
	processos[1].id = 2;
	processos[1].prioridade = 1;
	processos[1].tempo_de_execucao = 10;
	
	processos[2].id = 3;
	processos[2].prioridade = 4;
	processos[2].tempo_de_execucao = 3;
	
	processos[3].id = 4;
	processos[3].prioridade = 1;
	processos[3].tempo_de_execucao = 6;
	
	processos[4].id = 5;
	processos[4].prioridade = 2;
	processos[4].tempo_de_execucao = 4;
	
	processos[5].id = 6;
	processos[5].prioridade = 3;
	processos[5].tempo_de_execucao = 12;
	
	processos[6].id = 7;
	processos[6].prioridade = 1;
	processos[6].tempo_de_execucao = 5;
	
	processos[7].id = 8;
	processos[7].prioridade = 5;
	processos[7].tempo_de_execucao = 13;
}
