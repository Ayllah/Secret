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
//Retorna o tamanho da lista primaria
int TamanhoListaPrim(ChavesPrimarias *Inicio) {
    int i = 0;
    ChavesPrimarias *iterador = Inicio;
    while (iterador) {
        if (iterador->MarcadorAtivo) {
          i++;
        }
        iterador = iterador->prox;
   }
    return i;
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
//Percorre o arquivo com base no RRN e adiciona uma marca
//de exclusao (*) e desetiva o respectivo no
void ExcluirRegistro(ChavesPrimarias *no){
  no->MarcadorAtivo = 0;
  FILE *arquivo;
  arquivo = fopen("lista1.txt", "r+b");
  fseek(arquivo, no->RRN, SEEK_SET);
  fputc('*', arquivo);
  fclose(arquivo);
}
//Cria um vetor a partir de uma lista ligada e a percorre.
ChavesSecundarias** ListaParaVetorSec(ChavesSecundarias *Incio) {
    int i, n;
    ChavesSecundarias **elementos;
    n = TamanhoListaSec(Incio);
    elementos = new(ChavesSecundarias);
    for (i = 0; i < n; i++) {
        elementos[i] = Incio;
        Incio = Incio->prox;
    }
    tamanhoVetor = n;
    return elementos;
}
//Cria um vetor a partir de uma lista ligada e a percorre.
ChavesPrimarias** ListaParaVetorPrim(ChavesPrimarias *Inicio) {
    int i, n;
    ChavesPrimarias **elementos;
    n = TamanhoListaPrim(Inicio);
    elementos = new(ChavesPrimarias);
    for (i = 0; i < n; i++) {
        while (!(Inicio->MarcadorAtivo)) {
          Inicio = Inicio->prox;
        }
        elementos[i] = Inicio;
        Inicio = Inicio->prox;
    }
    tamanhoVetor = n;
    return elementos;
}
//Atualiza o tamanho dos indices e recria os vetores
void AtualizarRegistro(){
  free(vetorSecNOME);
  free(vetorSecMATRIC);
  free(vetorP);
  vetorP = ListaParaVetorPrim(ChavPrimInicio);
  tamanhoPrim = tamanhoVetor;
  vetorSecNOME = ListaParaVetorSec(ChavSecMATInicio);
  tamanhoSecNOME = tamanhoVetor;
  vetorSecMATRIC = ListaParaVetorSec(ChavSecNOMEInicio);
  tamanhoSecMATRIC = tamanhoVetor;
}
*/
void Arquivos::ArquivoPrimario(){
   std::ifstream Lista1("../res/lista1.txt");
   std::ifstream Lista2("../res/lista2.txt");
   std::ofstream indicelistaP1("../res/indicelista1.ind");
   std::ofstream indicelistaP2("../res/indicelista2.ind");

   std::ofstream indicelistaS1("../res/listaSecundaria1.ind");
   std::ofstream indicelistaS2("../res/listaSecundaria2.ind"); 

   // Ler Lista1 e cria indicelista1
   ListaPrimaria *listaPrimarios1 = new ListaPrimaria;
   ListaInvertida* listaInvertida1 = new ListaInvertida;
   LerListaOriginal(Lista1, indicelistaP1, indicelistaS1, &listaPrimarios1->Inicio, &listaInvertida1->Inicio);

   // Ler Lista 2 e cria arquivo de indices primarios: indicelista2
   ListaPrimaria *listaPrimarios2 = new ListaPrimaria;
   ListaInvertida* listaInvertida2 = new ListaInvertida;
   LerListaOriginal(Lista2, indicelistaP2, indicelistaS2, &listaPrimarios2->Inicio, &listaInvertida2->Inicio);
   
   Lista1.close();
   Lista2.close();
   indicelistaP1.close();
   indicelistaP2.close();
   indicelistaS1.close();
   indicelistaS2.close(); 
}

void Arquivos::InserirSecundario(ChavesSecundarias **no, std::string curso, unsigned RRN, std::ostream& indicelistaS){
   (*no) = new ChavesSecundarias;
   (*no)->curso = curso;
   (*no)->prox = NULL;
   (*no)->referencia = RRN;
   indicelistaS << curso << " " << (*no)->referencia << std::endl;   
}

void Arquivos::InserirPrimario(ChavesPrimarias **no, std::string chave, unsigned RRN, std::ostream& indicelistaP){
   (*no) = new ChavesPrimarias;
   (*no)->chavePrim = chave;
   (*no)->RRN = RRN;
   (*no)->MarcadorAtivo = 1;
   (*no)->prox = NULL;
   indicelistaP << chave << "|" << (*no)->RRN << std::endl; 
}

void Arquivos::LerListaOriginal(std::istream& Lista, std::ostream& indicelistaP, std::ostream& indicelistaS,
                              ChavesPrimarias **noP, ChavesSecundarias **noS){
   if(!Lista.eof()){
      std::string linha, chave, curso;
      getline(Lista, linha);

      unsigned contador=0, espacos=0;

      while( (chave.size() < 30) && (espacos <= 4) ){
         if( !isspace(linha[contador]) ){
            chave.push_back(linha[contador]);
         }
         else espacos++;
         contador++;
      }

      
      
      std::string espaco = " ";
      if(linha.size() != 0){
         curso.push_back(linha[52]);
         curso.push_back(linha[53]);         

         if(chave.size() < 30){
            while(chave.size() < 30){
               chave.push_back(espaco[0]);
            }
         }
         unsigned RRN = 2*indicelistaP.tellp();
         InserirPrimario(&(*noP), chave, RRN, indicelistaP);
         InserirSecundario(&(*noS), curso, RRN, indicelistaS);
         std::cout << chave << std::endl;

         Arquivos::LerListaOriginal(Lista, indicelistaP, indicelistaS, &((*noP)->prox), &((*noS)->prox));
      }
   }
}