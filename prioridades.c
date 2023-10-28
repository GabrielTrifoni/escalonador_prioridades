#include <stdio.h>
#include <stdlib.h>

#define QUANT_PROCESSOS 5


typedef struct {
	int id;
	int prioridade;
	int tempo_de_execucao;
	int tempo_de_chegada;
	enum enum_status { executando, pronto, bloqueado } status;
} str_processos;

void inicializa_processos(str_processos *processos);

void executa_processos(str_processos *processos);

void print_processos(str_processos *processos);

void swap_processos(str_processos *lista_de_prontos, int i);

int is_lista_vazia(str_processos *lista_de_prontos, int cont);


void main() {
	int i = 0;
	str_processos* processos = (str_processos*)malloc(QUANT_PROCESSOS * sizeof(str_processos) * sizeof(int));
	
	inicializa_processos(processos);
	
	print_processos(processos);
	
	executa_processos(processos);
}


void inicializa_processos(str_processos *processos) {
	int i;
	for(i = 0; i < QUANT_PROCESSOS; i++) {
		processos[i].id = i + 1;
		processos[i].prioridade = rand() % 10;
		processos[i].tempo_de_execucao = 1 + rand() % 20;
		if(i == 0) {
			processos[i].tempo_de_chegada = 0;
		} else {
			processos[i].tempo_de_chegada = (processos[i - 1].tempo_de_chegada) + rand() % 10;	
		}
		processos[i].status = bloqueado;
	}
}

void executa_processos(str_processos *processos) {
	str_processos* lista_de_prontos = (str_processos*)malloc(QUANT_PROCESSOS * sizeof(str_processos) * sizeof(int));
	int i, cont = 0;
	int tempo = 0;

	/* WHILE que simula o tempo passando */
	while(1) {
		printf("tempo: %d\n", tempo);
		/* Verifica se eh preciso adicionar novos processos na lista de pronto */
		for(i = cont; i < QUANT_PROCESSOS; i++) {
			if (processos[i].tempo_de_chegada <= tempo) {
				lista_de_prontos[cont].id = processos[i].id;
				lista_de_prontos[cont].prioridade = processos[i].prioridade;
				lista_de_prontos[cont].tempo_de_execucao = processos[i].tempo_de_execucao;
				lista_de_prontos[cont].tempo_de_chegada = processos[i].tempo_de_chegada;
				cont++;
			}
		}
		
		/* Verifica qual eh o processo com mais prioridade e coloca no inicio da lista */
		for(i = 1; i < cont; i++) {
			if(lista_de_prontos[i].prioridade < lista_de_prontos[0].prioridade) { // se condicao = true, entao lista[0] vira o processo com maior prioridade
				swap_processos(lista_de_prontos, i); // swap lista[i] <-> lista[0]
			}
		}
		
		if(lista_de_prontos[0].status != executando) {
			printf("Processador ocioso, sem processos executando no momento");	
		} else {
			printf("Executando processo: %d\ttempo restante: %d\tprioridade: %d", lista_de_prontos[0].id, lista_de_prontos[0].tempo_de_execucao, lista_de_prontos[0].prioridade);
			/* Decrementa tempo da execucao do processo e diminui a sua prioridade */
			lista_de_prontos[0].tempo_de_execucao--;
			lista_de_prontos[0].prioridade++;
		}
		
		if(lista_de_prontos[0].tempo_de_execucao == 0){ // Indica que o processo terminou
			/* Remove processo da lista */
			lista_de_prontos[0].status = 2;
			lista_de_prontos[0].prioridade = 1024;
		}
		
		/* Sai do while se: lista possuir apenas processos bloqueado e o tamanho da lista_de_prontos for igual a quantidade de processos total */
		if(is_lista_vazia(lista_de_prontos, cont) == 1 && cont == QUANT_PROCESSOS) {
			break;
		}
		
		printf("\n\n");
		tempo++;
	}
	
	printf("\n\nOs processos acabaram!\n");
}

void print_processos(str_processos *processos) {
	int i;
	
	printf("\nLista de processos:\n");
	for(i = 0; i < QUANT_PROCESSOS; i++) {
		printf("id: %d \tPrioridade: %d \tTempoExec: %d \tTempoChegada: %d\tStatus: %d\n", processos[i].id, processos[i].prioridade, processos[i].tempo_de_execucao, processos[i].tempo_de_chegada, processos[i].status);
	}
	printf("------------------------------------------------------------\n");
	
}

void swap_processos(str_processos *lista_de_prontos, int i) {
	str_processos buffer_str_processos;
	
	buffer_str_processos.id = lista_de_prontos[0].id;
	buffer_str_processos.prioridade = lista_de_prontos[0].prioridade;
	buffer_str_processos.tempo_de_chegada = lista_de_prontos[0].tempo_de_chegada;
	buffer_str_processos.tempo_de_execucao = lista_de_prontos[0].tempo_de_execucao;
	
	lista_de_prontos[0].id = lista_de_prontos[i].id;
	lista_de_prontos[0].prioridade = lista_de_prontos[i].prioridade;
	lista_de_prontos[0].tempo_de_chegada = lista_de_prontos[i].tempo_de_chegada;
	lista_de_prontos[0].tempo_de_execucao = lista_de_prontos[i].tempo_de_execucao;
	lista_de_prontos[0].status = executando;
	
	lista_de_prontos[i].id = buffer_str_processos.id;
	lista_de_prontos[i].prioridade = buffer_str_processos.prioridade;
	lista_de_prontos[i].tempo_de_chegada = buffer_str_processos.tempo_de_chegada;
	lista_de_prontos[i].tempo_de_execucao = buffer_str_processos.tempo_de_execucao;
	if(lista_de_prontos[i].prioridade != 1024)
		lista_de_prontos[i].status = pronto;
	else
		lista_de_prontos[i].status = bloqueado;
}

int is_lista_vazia(str_processos *lista_de_prontos, int cont) {
	int i;
	for(i = 0; i < cont; i++) {
		if(lista_de_prontos[i].status != bloqueado) { // retorna falso caso encontrar algum processo que nao esteja bloqueado (ou seja encontrou processo ativo na lista)
			return 0;
		}
	}
	
	return 1; // se lista estiver sem processos prontos ou executando
}
