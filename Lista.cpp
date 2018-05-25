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

//Insere os elementos na lista invertida de forma ordenada

void IncluirRegistroInvertida(ChavesPrimarias *ptr, ListaInvertida **Inicio, ListaInvertida **Fim){
	ListaInvertida *no, *iterador, *anterior;
	no = new (ListaInvertida);
	no->ptr = ptr;
	no->prox = NULL;

	//Verifica se a lista esta vazia
	if (!*Inicio) {
    	*Inicio = no;
       	*Fim = no;
    }
    else {

    	iterador = *Inicio;
    	ante = *Inicio;

    	while (iterador) {
        	if (strcmp(iterador->pk->key, pk->key)>=0) {
            	break;
        	}
        	ante = iterador;
        	iterador = iterador->prox;
    	}

    	if (iterador==NULL) {
        	(*Fim)->prox = no;
        	*Fim = no;
    	}
    	else if (iterador==ante) {
        	no->prox = iterador;
        	*Inicio = no;
    	}
    	else {
        	ante->prox = no;
        	no->prox = iterador;

    	}
 	}
}

//Insere as chaves secundarias nos indices de forma ordenada

void IncluirRegistroChavS(char *chaveSec, ChavesPrimarias *ptr, ChavesSecundarias **Inicio, ChavesSecundarias **Fim){
	ChavesSecundarias *no, *iterador, *anterior;
    no = new (ChavesSecundarias);
    strcpy(no->chaveSec, chaveSec);
    no->prox = NULL;

    no->Inicio = NULL;
    no->Fim = NULL;

    //Verifica se a lista esta vazia
    if (!*Inicio) {
       *Inicio = no;
       *Fim = no;

    	// Inserindo elementos na lista invertida
    	IncluirRegistroInvertida(ptr, &((*Inicio)->Inicio), &((*Inicio)->Fim));
   		return;
    }

    else {
    	iterador = *Incio;
    	anterior = *Inicio;

    	while (iterador) {
        	if (strcmp(iterador->chaveSec, chaveSec) == 0) {
           		free(no);

            	//Inserindo elementos na lista invertida
            	IncluirRegistroInvertida(ptr, &(iterador->Incio), &(iterador->Fim));
            	return;
        	}

        	if (strcmp(iterador->chaveSec, chaveSec) > 0) {
        		break;
       		}
        	anterior = iterador;
        	iterador = iterador->prox;
    	}

    	if (iterador == NULL) {
        	(*Fim)->prox = no;
        	*Fim = no;
    	}
    	else if (iterador == anterior) {
        	no->prox = iterador;
        	*Incio = no;
    	}
    	else {
        	anterior->prox = no;
        	no->prox = iterador;

    	}
   		//Inserindo elementos na lista invertida
    	IncluirRegistroInvertida(ptr, &(no->Incio), &(no->Fim));
 	}
}

//Retorna o tamanho da lista secundaria

int TamanhoListaSec(ChavesSecundarias *Inicio){
	int i = 0;
	ChavesSecundarias *iterador = Inicio;
	while(iterador) {
	    i++;
	    iterador = iterador->prox;
	}

	return i;
}

