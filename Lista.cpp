#include "Lista.hpp"
#include <iostream>

//Cria arquivos quando nao existem

void Lista :: CriaRegistro(){
	FILE *arquivo;
	arquivo = fopen("lista1.txt", "rb");
	if(!arquivo){
		arquivo = fopen("lista1.txt", "wb");
		fclose(arquivo);
	}
	arquivo = fopen("lista2.txt", "rb");
	if(!arquivo){
		arquivo = fopen("lista2.txt", "wb");
		fprintf(arquivo, "i = n");
		fclose(arquivo);
	}
}

//Insere as chaves primarias nos indices de forma ordenada.
//Caso nao houver o valor da chave primaria que se queria inserir
//a funcao ira retornar o endereco do no em que esta alocada a chave

ChavesPrimarias* Lista :: IncluirRegistroChavP(char *chavePrim, int RRN, ChavesPrimarias **Inicio, ChavesPrimarias **Fim){
	ChavesPrimarias *no, *iterador, *anterior;
	no = new(ChavesPrimarias);
	strcpy(no->chavePrim, chavePrim);
	no->RRN = RRN;
	no->MarcadorAtivo = 1;
	no->prox = NULL;

	//Verifica se a lista esta vazia
	if (!*Inicio) {
       *Inicio = no;
       *Fim = no;
   }
   else {

   		iterador = *Inicio;
   		anterior = *Inicio;

   		while (iterador) {
   			if (strcmp(iterador->chavePrim, chavePrim) == 0) {
   				return iterador;
   			}
   			if (strcmp(iterador->chavePrim, chavePrim) >= 0) {
   				break;
   			}
   			anterior = iterador;
   			iterador = iterador->prox;
   		}

   		if (iterador==NULL) {
   			(*Fim)->prox = no;
   			*Fim = no;
   		}
   		else if (iterador == anterior) {
   			no->prox = iterador;
   			*Inicio = no;
   		}
   		else {
   			anterior->prox = no;
   			no->prox = iterador;

   		}
   }
	return node;
}

