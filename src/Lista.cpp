#include "Lista.h"

//Cria arquivos quando nao existem
/*
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
}
*/
void Arquivos::ArquivoPrimario(){
   std::ifstream Lista1("Lista1.txt");
   std::ifstream Lista2("Lista2.txt");
   std::ofstream indicelista1("indicelista1.ind");
   std::ofstream indicelista2("indicelista2.ind");

   // Ler Lista1 e cria indicelista1
   ChavesPrimarias *no;
   LerListaOriginal(Lista1, indicelista1, &no);

   Lista1.close();
   Lista2.close();
   indicelista1.close();
   indicelista2.close();
}

void Arquivos::LerListaOriginal( std::istream& Lista, std::ostream& indicelista, ChavesPrimarias **no){
   (*no) = new(ChavesPrimarias);
   std::string linha;
   std::string chave;
   getline(Lista, linha);

   unsigned contador=0;

   while(chave.size() <= 30){
      if( !isspace(linha[contador]) ){
         chave.push_back(linha[contador++]);
      }
      else continue;
   }

   (*no)->chavePrim = chave;
   (*no)->RRN = indicelista.tellp();
   (*no)->MarcadorAtivo = 1;
   (*no)->prox = NULL;

   indicelista << chave << " " << (*no)->RRN << std::endl;
   std::cout << linha << std::endl;

   Arquivos::LerListaOriginal(Lista, indicelista, &((*no)->prox));
}
