#include "Lista.h"

using namespace std;

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

//Retorna o tamanho da lista primaria
int Arquivos::TamanhoListaPrim(ChavesPrimarias *Inicio) {
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

void Arquivos::ExcluirRegistro(ListaPrimaria* listaP, ListaInvertida* listaI, std::string registro, 
   std::fstream& indicelistaP, std::fstream& indicelistaS){
   
   string chaveParaExcluir, linha, rrn;
   unsigned contador=0, espacos=0;
   int RRN;

   // Concatena o registro: matricula + nome
   while( (chaveParaExcluir.size() < 30) && (espacos <= 5) ){
      if( !isspace(registro[contador]) ){
         chaveParaExcluir.push_back(registro[contador]);
      }
      else espacos++;
      contador++;
   }

   ChavesPrimarias* atualP;
   while(!indicelistaP.eof()){
      getline(indicelistaP, linha);
      string chave = linha.substr(0, 29);

      if(chave.compare(chaveParaExcluir) == 0){

         for(int i = 31; !isspace(linha[i]); i++)
            rrn.push_back(linha[i]);
      cout << rrn << endl;
      std::string::size_type sz;
      RRN = stoi(rrn);
      cout << RRN << endl;
      break;
      }
         
   }
   

   //cout << RRN << endl;
}

void Arquivos::Excluir(ListaPrimaria* listaP1, ListaInvertida* listaI1, ListaPrimaria* listaP2, ListaInvertida* listaI2){
   cout << "\nInsira o Registro que queira excluir (conforme modelo de entrada)" << endl;
   string registro;
   getline(cin, registro);
   cout << "\nQual o nome do arquivo o qual obtem esse registro (lista1.txt ou lista2.txt)?" << endl;
   string arquivo;
   getline(cin, arquivo);

   if(arquivo.compare("lista1.txt") == 0){
      fstream indicelistaP("../res/indicelista1.ind");
      fstream indicelistaS("../res/listaSecundaria1.ind");
      ExcluirRegistro(listaP1, listaI1, registro, indicelistaP, indicelistaS);
   }
   else if(arquivo.compare("lista2.txt") == 0){
      fstream indicelistaP("../res/indicelista2.ind");
      fstream indicelistaS("../res/listaSecundaria2.ind");
      ExcluirRegistro(listaP1, listaI1, registro, indicelistaP, indicelistaS);      
   }
}

void Arquivos::ArquivoPrimSec(ListaPrimaria *listaPrimarios1, ListaPrimaria* listaPrimarios2, ListaInvertida* listaInvertida1, ListaInvertida* listaInvertida2){
   std::ifstream Lista1("../res/lista1.txt");
   std::ifstream Lista2("../res/lista2.txt");
   std::ofstream indicelistaP1("../res/indicelista1.ind");
   std::ofstream indicelistaP2("../res/indicelista2.ind");

   std::ofstream indicelistaS1("../res/listaSecundaria1.ind");
   std::ofstream indicelistaS2("../res/listaSecundaria2.ind"); 

   // Ler Lista1 e cria indicelista1
   unsigned indice = 0;
   LerListaOriginal(listaInvertida1, listaPrimarios1, &indice, Lista1, indicelistaP1, indicelistaS1, &listaPrimarios1->Inicio, &listaInvertida1->Inicio, NULL, NULL);

   // Ler Lista 2 e cria arquivo de indices primarios: indicelista2
   indice = 0;
   LerListaOriginal(listaInvertida2, listaPrimarios2, &indice, Lista2, indicelistaP2, indicelistaS2, &listaPrimarios2->Inicio, &listaInvertida2->Inicio, NULL, NULL);
   
   Lista1.close();
   Lista2.close();
   indicelistaP1.close();
   indicelistaP2.close();
   indicelistaS1.close();
   indicelistaS2.close(); 
}


void Arquivos::InserirPrimario(unsigned *indice, ChavesPrimarias **no, ChavesPrimarias *anterior, std::string chave, unsigned RRN, std::string curso, std::ostream& indicelistaP){
   (*no) = new ChavesPrimarias;
   (*no)->chave = chave;
   (*no)->RRN = RRN;
   (*no)->MarcadorAtivo = 1;
   (*no)->prox = NULL;
   (*no)->indice = (*indice);
   (*no)->anterior = anterior;
   (*no)->curso = curso;
  
   indicelistaP << chave << "|" << (*no)->RRN << std::endl; 
}

void Arquivos::InserirSecundario(ChavesSecundarias **no, ChavesSecundarias *anterior, std::string curso, ChavesPrimarias **chavePrimaria, std::ostream& indicelistaS){
   (*no) = new ChavesSecundarias;
   (*no)->curso = curso;
   (*no)->prox = NULL;
   (*no)->chavePrimaria = (*chavePrimaria);
   indicelistaS << curso << " " << (*no)->chavePrimaria->indice << std::endl;   
}

void Arquivos::LerListaOriginal(ListaInvertida* listaInvertida, ListaPrimaria* listaPrimaria, unsigned *indice, 
   std::istream& Lista, std::ostream& indicelistaP, 
   std::ostream& indicelistaS, ChavesPrimarias **noP, 
   ChavesSecundarias **noS, ChavesSecundarias *anteriorS, 
   ChavesPrimarias *anteriorP){
   
   if(!Lista.eof()){
      std::string linha, chave, curso;
      getline(Lista, linha);

      unsigned contador=0, espacos=0;

      while( (chave.size() < 30) && (espacos <= 5) ){
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

         InserirPrimario(&(*indice), &(*noP), anteriorP, chave, RRN, curso, indicelistaP);
         
         if((*indice) == 0 || !existeCurso(curso, listaInvertida)){
            InserirSecundario(&(*noS), anteriorS, curso, &(*noP), indicelistaS);
            (*indice)++;
            Arquivos::LerListaOriginal(listaInvertida, listaPrimaria, &(*indice), Lista, indicelistaP, indicelistaS, &((*noP)->prox), &((*noS)->prox), *noS, *noP);
         }
         else{
            (*indice)++;
            Arquivos::LerListaOriginal(listaInvertida, listaPrimaria, &(*indice), Lista, indicelistaP, indicelistaS, &((*noP)->prox), &(*noS), *noS, *noP);
         }
      }
   } 
}

bool Arquivos::existeCurso(std::string curso, ListaInvertida* lista){

   ChavesSecundarias *atual;
   bool existe = false;
   
   for(atual = lista->Inicio; atual != NULL; atual=atual->prox){
      if( (atual->curso).compare(curso) == 0 ) 
         existe = true;
   }
   return existe;
}

void Arquivos::TrocaNoSec(ChavesSecundarias *atual, ChavesSecundarias *proximo){
   ChavesSecundarias *tmpProx;
   tmpProx = proximo->prox;
   proximo->prox = atual->prox;
   atual->prox = tmpProx;

   ChavesSecundarias *tmpAnterior;
   tmpAnterior = proximo->anterior;
   proximo->anterior = atual->anterior;
   atual->anterior = proximo->anterior;
}

void Arquivos::OrdenaListaSecundaria(ListaInvertida *lista){
   ChavesSecundarias *atual;
   bool trocou = true;

   while(!trocou){
      trocou = false;
      for(atual = lista->Inicio; atual != NULL; atual=atual->prox){
         if( (atual->curso).compare(atual->prox->curso) > 0 ){
            TrocaNoSec(atual, atual->prox);
            trocou = true;
         }
      }
   }
}
 
void Arquivos::TrocaNoPrim(ChavesPrimarias **atual, ChavesPrimarias **proximo){
   ( (*atual)->chave ).swap( (*proximo)->chave );
   ( (*atual)->curso ).swap( (*proximo)->curso );

   unsigned tmp;
   tmp = (*atual)->indice;
   (*atual)->indice = (*proximo)->indice;
   (*proximo)->indice = tmp;

   tmp = (*atual)->RRN;
   (*atual)->RRN = (*proximo)->RRN;
   (*proximo)->RRN = tmp; 

   bool tmpB = (*atual)->MarcadorAtivo;
   (*atual)->MarcadorAtivo = (*proximo)->MarcadorAtivo;
   (*proximo)->MarcadorAtivo = tmpB;

   ChavesPrimarias *aux = (*atual)->referencia;
   (*atual)->referencia = (*proximo)->referencia;
   (*proximo)->referencia = aux;
   
   /*
   ChavesPrimarias* tmpProx;
   if((*proximo)->prox == NULL) {
      (*proximo)->prox =  (*atual)->prox;
      (*atual)->prox = NULL;
   }
   else {
      tmpProx = (*proximo)->prox;
      (*proximo)->prox = (*atual)->prox;
      (*atual)->prox = (*proximo)->prox;
   }

   ChavesPrimarias* tmpAnterior;
   if((*atual)->anterior == NULL) {
      (*atual)->anterior =  (*proximo)->anterior;
      (*proximo)->anterior = NULL;
   }
   else {
      tmpAnterior = (*proximo)->anterior;
      (*proximo)->anterior = (*atual)->anterior;
      (*atual)->anterior = (*proximo)->anterior;
   }
   */
}

void Arquivos::OrdenaListaPrimaria(ListaPrimaria *lista, ListaInvertida *invertida){
   ChavesPrimarias *atual;
   ChavesSecundarias *aux;
   atual = lista->Inicio;
   ChavesPrimarias *teste;
   bool trocou = true;

   while(trocou){
      trocou = false;
      for(atual = lista->Inicio; atual->prox != NULL; atual=atual->prox){
         if( (atual->chave).compare(atual->prox->chave) > 0 ){
            TrocaNoPrim(&atual, &atual->prox);
            trocou = true;
         }
      }
   }

   /*(*aux) = (*invertida)->Inicio;
   while((*aux) != NULL){
      for((*atual) = lista->Inicio; (*atual)->curso != (*aux)->curso; (*atual)=(*atual)->prox);
      (*aux)->chavePrimaria = (*atual);
      (*aux) = (*aux)->prox;  
   }
   */
}

void Arquivos::ImprimeSecundaria(ListaInvertida* lista){
   ChavesSecundarias* atual;
   ChavesPrimarias* aux;
   unsigned RRN, indice;
   std::cout << "\nCurso\t\t" << "Primeiro Registro (Referencia / PRR)" << std::endl;
   for(atual = lista->Inicio; atual != NULL; atual=atual->prox){
      indice = atual->chavePrimaria->indice;
      RRN = atual->chavePrimaria->RRN;
      std::cout << atual->curso << "\t\t\t" << indice << "/" << RRN << endl;
   }
}

void Arquivos::ImprimePrimaria(ListaPrimaria* lista){
   ChavesPrimarias* atual;
   std::string indiceRef, indice, espaco = " ";
   std::cout << "\nReferencia \t\t\tChave|PRR\t\t Próxima Referencia" << std::endl;
   for(atual = lista->Inicio; atual != NULL; atual=atual->prox){
      if(atual->referencia != NULL){
         indiceRef = std::to_string(atual->referencia->indice);
         indiceRef.resize(6, espaco[0]);
      }
      else indiceRef = "-1";

      indice = std::to_string(atual->indice);
      indice.resize(3, espaco[0]);
      std::cout << indice << "\t\t" << atual->chave << "|" << atual->RRN << "\t\t" << indiceRef << std::endl;
   }
}

void Arquivos::InsereReferencia(ListaPrimaria *listaP, ListaInvertida *listaS){
   ChavesSecundarias *noS = listaS->Inicio;
   while(noS != NULL){
      ChavesPrimarias *noP, *auxP;
      for(noP = listaP->Inicio; noP != NULL; noP = noP->prox){
         if( (noP->curso).compare(noS->curso) == 0){
            auxP = noP;
            break;
         }
      }
      for(noP = auxP; noP != NULL; noP = noP->prox){
         if( (noP->curso).compare(noS->curso) == 0){
            auxP->referencia = noP;
            noP->referencia = NULL;
            auxP = noP;
         }
      }
      noS = noS->prox;
   }
}

void Arquivos::ImprimeListas(ListaPrimaria* listaPrimarios1, ListaPrimaria* listaPrimarios2,
   ListaInvertida* listaInvertida1, ListaInvertida* listaInvertida2){
   ImprimeSecundaria(listaInvertida1);
   ImprimePrimaria(listaPrimarios1);
   std::cout.width(70);
   std::cout.fill( '_' );
   std::cout << "_" << std::endl;

   std::cout << "\nArquivo: lista2.txt" << std::endl;
   ImprimeSecundaria(listaInvertida2);
   ImprimePrimaria(listaPrimarios2);   
}

void Arquivos::Menu(ListaPrimaria* listaPrimarios1, ListaPrimaria* listaPrimarios2,
   ListaInvertida* listaInvertida1, ListaInvertida* listaInvertida2){
   int opcao;
   while(true){
      cout <<endl<<endl;
      cout <<"\t\t**************************************************"<<endl;
      cout <<"\t\t"<<"*"<<setw(17)<<""<<setw(13)<<"MENU INDICES"<<setw(18)<<""<<"*"<<endl;
      cout <<"\t\t**************************************************"<<endl;
      cout <<"\t\t"<<"*"<<"\t"<<"OPÇÃO:"<<"\t\t"<<"DESCRIÇÃO:"<<"\t\t"<<" *"<<endl;
      cout <<"\t\t"<<"*""------------------------------------------------"<<"*"<<endl;
      cout <<"\t\t"<<"*"<<"\t"<<"[1]"<<"\t"<<"Mostrar INDICES"<<"\t\t\t"<<" *"<<endl;
      cout <<"\t\t"<<"*"<<"\t"<<"[2]"<<"\t"<<"Incluir REGRISTRO"<<"\t\t"<<" *"<<endl;
      cout <<"\t\t"<<"*"<<"\t"<<"[3]"<<"\t"<<"Excluir REGISTRO"<<"\t\t"<<" *"<<endl;
      cout <<"\t\t"<<"*"<<"\t"<<"[4]"<<"\t"<<"Atualizar REGISTRO"<<"\t\t"<<" *"<<endl;
      cout <<"\t\t"<<"*"<<"\t"<<"[5]"<<"\t"<<"Intercalar INDICES"<<"\t\t"<<" *"<<endl;
      cout <<"\t\t"<<"*"<<"\t"<<"[0]"<<"\t"<<"SAIR"<<"\t\t\t\t"<<" *"<<endl;
      cout <<"\t\t**************************************************"<<endl;
      cout <<"\t\t"<<setw(10)<<"Digite sua opção---> ";
    cin >> opcao;
    switch(opcao){
      case 1: 
           ImprimeListas(listaPrimarios1, listaPrimarios2, listaInvertida1, listaInvertida2);
           break;
      case 2:
         break;
      case 3:
         break;
      case 4:
         break;
      case 5:
         break;
      case 0: 
         cout <<"\n\tVocê saiu do programa!\n";
         exit(0);
         break;
      default:
         cout <<"\n\tDigite uma opção válida!\n";
    }
  }
}