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
   
   string chaveParaExcluir, linha, espaco = " ", rrn;
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

   if(chaveParaExcluir.size() < 30){
      while(chaveParaExcluir.size() < 30){
         chaveParaExcluir.push_back(espaco[0]);
      }
   }   

   ChavesPrimarias* atualP;
   while(!indicelistaP.eof()){
      getline(indicelistaP, linha);
      string chave = linha.substr(0, 30);
      if(chave.compare(chaveParaExcluir) == 0){
         contador = 31;
         while(!isspace(linha[contador])){
            rrn.push_back(linha[contador]);
            contador++;
         }
      
         RRN = stoi(rrn);
         indicelistaP.seekp(RRN/*, ios_base::beg*/);
         indicelistaP << "*                             ";

         string curso;
         curso.push_back(registro[52]);
         curso.push_back(registro[53]);
         
         while(!indicelistaS.eof()){
            string linhaS, cursoArq;
            getline(indicelistaS, linhaS);
            cursoArq = linhaS.substr(0, 2);
            string referenciaInd = linhaS.substr(3, 9);

            if(curso.compare(cursoArq) == 0){
               string referencia = linha.substr(62, 9);
               if(referencia.compare(referenciaInd) == 0){
                  indicelistaS.ignore(2, indicelistaS.eof());
                  indicelistaS << referencia << endl;
               }
            }
         }
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


void Arquivos::InserirPrimario(unsigned *indice, ChavesPrimarias **no, ChavesPrimarias *anterior, std::string chave, string RRN, std::string curso, std::ostream& indicelistaP){
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

void Arquivos::InserirSecundario(ChavesSecundarias **no, ChavesSecundarias *anterior, std::string curso, ChavesPrimarias **chavePrimaria, std::ostream& indicelistaS, string RRN){
   (*no) = new ChavesSecundarias;
   (*no)->curso = curso;
   (*no)->prox = NULL;
   (*no)->chavePrimaria = (*chavePrimaria);
   indicelistaS << curso << "|" << (*no)->chavePrimaria->RRN << std::endl;   
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

      if(linha.size() != 0){
         curso.push_back(linha[52]);
         curso.push_back(linha[53]);         

         if(chave.size() < 30){
            while(chave.size() < 30){
               chave.push_back(' ');
            }
         }
         int rrn = Lista.tellg();
         string RRN = to_string(rrn);

         if(RRN.size() < 9){
            while(RRN.size() < 9){
               RRN.push_back(' ');
            }
         }         

         InserirPrimario(&(*indice), &(*noP), anteriorP, chave, RRN, curso, indicelistaP);
         
         if((*indice) == 0 || !existeCurso(curso, listaInvertida)){
            InserirSecundario(&(*noS), anteriorS, curso, &(*noP), indicelistaS, RRN);
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

void Arquivos::OrdenaLista(string nomeArquivo){
   fstream arquivo;
   arquivo.open(nomeArquivo.c_str());
   int i=0;
   vector<string> chaves;
   string chave, RRN, linha;
   getline(arquivo, linha);
   while(!arquivo.eof() && linha.size() != 0){
      chaves.push_back(linha);
      getline(arquivo, linha);
   }
   arquivo.close();
   insertion_sort(chaves);
   arquivo.open(nomeArquivo.c_str());
   while(i != chaves.size()  ){
      arquivo << chaves[i++] << endl;
   }
   arquivo.close();
   chaves.clear();
}

void Arquivos::insertion_sort(vector<string> &vetor) {
   
    for(int i = 1; i < vetor.size(); i++) {
      string escolhido;
      escolhido = vetor[i].substr(0, vetor[1].size());
      int j = i - 1;
      
      while ((j >= 0) && (vetor[j].compare(escolhido) > 0)) {
         vetor[j + 1].swap(vetor[j]);
         j--;
      }
      
      vetor[j + 1].swap(escolhido);
      escolhido.clear();
   }
}

void Arquivos::ImprimeSecundaria(ListaInvertida* lista){
   ChavesSecundarias* atual;
   ChavesPrimarias* aux;
   unsigned indice;
   string RRN;
   std::cout << "\nCurso\t\t" << "Primeiro Registro (Referencia / PRR)" << std::endl;
   for(atual = lista->Inicio; atual != NULL; atual=atual->prox){
      indice = atual->chavePrimaria->indice;
      std::cout << atual->curso << "\t\t\t" << indice << "/" << (atual->chavePrimaria->RRN) << endl;
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

/*void Arquivos::InsereReferencia(string listaP, string listaS, string lista){
   string name = "../res/" + listaS + ".ind";
   string name2 = "../res/" + listaS + "1.ind";
   ofstream indicelista1S(name2.c_str());
   ofstream indicelistaS(name.c_str()); 
   istream indicelistaP(listaP.c_str());
   istream Lista(lista.c_str());    
   bool Primeiro = true;
   string linha;
   getline(indicelistaP, linha);  

   while(!listaP.eof() && linha.size() != 0){
      string curso = encontraCurso(linha, indicelistaP);
      indicelistaP.ignore(2);

      getline(indicelistaP, linha);  
      while(){

      }
   }
      indicelistaP.close();
      Lista.close();
      indicelista1S << "\n";
      curso.clear();
      getline(indicelistaS, curso);     
   }

   indicelistaS.close();
   indicelista1S.close();
}

string encontraCurso(string linha, ostream& Lista){
   string rrn;
   int contador = 31;
   while(!isspace(linha[contador])){
      rrn.push_back(linha[contador]);
      contador++;
   }
      
   int RRN = stoi(rrn);

   string registro;
   Lista.seekp(RRN);
   getline(Lista, registro);
   string cursoIndP;
   cursoIndP.push_back(registro[52]);
   cursoIndP.push_back(registro[53]);
   return cursoIndP;
}
*/
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


void Arquivos::Intercalar(string lista1, string lista2){
   ifstream Lista1(lista1.c_str());
   ifstream Lista2(lista2.c_str());

   string linha1;
   string linha2;
   ofstream Lista12("../res/Lista12.txt");

   cout << "\n LISTAS 1 E 2 INTERCALADAS:\n" << endl;
   while(!Lista1.eof() && !Lista2.eof()){
      getline(Lista1, linha1);
      getline(Lista2, linha2);
      if(linha1.compare(linha2) < 0){
         Lista12 << linha1 << endl;
         getline(Lista1, linha1);
         cout << linha1 << endl;
      }    
      else{
         Lista12 << linha2 << endl;
         getline(Lista2, linha2);
         cout << linha2 << endl;
      }
   }
   while(!Lista1.eof()){
      getline(Lista1, linha1);
      Lista12 << linha1 << endl;
      getline(Lista1, linha1);
      cout << linha1 << endl;
   }
   while(!Lista2.eof()){
      getline(Lista2, linha2);
      Lista12 << linha2 << endl;
      getline(Lista2, linha2);
      cout << linha2 << endl;
   }
   Lista12.close();
   Lista1.close();
   Lista2.close();
}
