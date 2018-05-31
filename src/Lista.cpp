#include "Lista.h"

using namespace std;

void Arquivos::ExcluirRegistro(std::string registro, std::fstream& Lista, std::fstream& indicelistaP, std::fstream& indicelistaP2, std::fstream& indicelistaS){
   
   string chaveParaExcluir, linha, rrn;
   unsigned contador=0, espacos=0;
   int RRN, RRN_P;
   bool excluido = false;

   // Cria chave: Concatena o registro: matricula + nome
   while( (chaveParaExcluir.size() < 30) && (espacos <= 5) ){
      if( !isspace(registro[contador]) ){
         chaveParaExcluir.push_back(registro[contador]);
      }
      else espacos++;
      contador++;
   }

   if(chaveParaExcluir.size() < 30){ // fixa tamanho da chave a ser comparada
      while(chaveParaExcluir.size() < 30){
         chaveParaExcluir.push_back(' ');
      }
   }   
   getline(indicelistaP, linha);

   // Verifica as chaves do Arq de Indices Primarios
   // Quando encontrar, calcula PRR para entao excluir no Arq Orignal
   while(!indicelistaP.eof()){
      string chave = linha.substr(0, 30);
      if(chave.compare(chaveParaExcluir) == 0){
         int contador = 31;
         while(!isspace(linha[contador]))
               rrn.push_back(linha[contador++]); // calcula PRR
         
         int RRN = stoi(rrn);
         // Sobrescreve Arq sinalizando a exclusão com um *
         Lista.seekp(RRN);
         Lista << "*                                                 ";
         Lista << "            ";

         RRN_P = indicelistaP.tellg();
         indicelistaP.seekp(RRN_P - 41);
         indicelistaP << "*                             ";
         excluido = true;

         string curso;
         curso.push_back(registro[52]);
         curso.push_back(registro[53]);
         // Verifica se o curso do registro excluido corresponde ao
         // primeiro da lista de secundarios
         // Se for o primeiro, atualiza o curso sobrescrevendo o
         // curso proximo da lista (informação dada pelo arq da lista Invertida)
         while(!indicelistaS.eof()){
            string linhaS, linhaSS, cursoSec, referenciaInd;
            getline(indicelistaS, linhaS);
            linhaSS.replace(0, linhaS.size(), linhaS);
            cursoSec = linhaS.substr(0, 2);
            for(int i=3; i<12; i++) referenciaInd.push_back(linhaS[i]);

            if(curso.compare(cursoSec) == 0){
               string referencia = linha.substr(31, 9);
               
               if(referencia.compare(referenciaInd) == 0){
                  int posicao = indicelistaP.tellg();
                  indicelistaP2.seekg(posicao+1);
                  string novoRRN;
                  getline(indicelistaP2, novoRRN);
                  
                  posicao = indicelistaS.tellg();
                  indicelistaS.seekg(posicao - 10);
                  indicelistaS << novoRRN;
               }              
            }
         }
         RRN_P = indicelistaP.tellg();
         indicelistaP2.seekg(RRN_P - 30);
         indicelistaP2 << "*                             ";          
         break;
      }
      getline(indicelistaP, linha);  
   }
   if(!excluido) 
      cout << "\n Não existe esse registo!\n" << endl;
}

void Arquivos::Excluir(){
   cout << "\nInsira o Registro que queira excluir (conforme modelo de entrada), exemplo:" << endl;
   cout << "031147 Anderson Silva Bezerra                   34  EC       B\n" << endl;
   string registro;
   getline(cin, registro);
   cout << "\nQual o nome do arquivo o qual obtem esse registro (lista1.txt ou lista2.txt)?" << endl;
   string arquivo;
   getline(cin, arquivo);

   if(arquivo.compare("lista1.txt") == 0){
      fstream indicelistaP("../res/indicelista1.ind");
      fstream indicelistaP2("../res/indicelista1-2.ind");
      fstream indicelistaS("../res/listaSecundaria1.ind");
      fstream Lista("../res/lista1.txt");
      ExcluirRegistro(registro, Lista, indicelistaP, indicelistaP2, indicelistaS);
      indicelistaP.close();
      indicelistaP2.close();
      indicelistaS.close();
      Lista.close();
      ImprimeListas(1);
   }
   else if(arquivo.compare("lista2.txt") == 0){
      fstream indicelistaP("../res/indicelista2.ind");
      fstream indicelistaP2("../res/indicelista2-2.ind");
      fstream indicelistaS("../res/listaSecundaria2.ind");
      fstream Lista("../res/lista2.txt");
      ExcluirRegistro(registro, Lista, indicelistaP, indicelistaP2, indicelistaS);
      indicelistaP.close();
      indicelistaP2.close();
      indicelistaS.close();
      Lista.close();  
      ImprimeListas(2);
   }
   else
      cout << "Não foi digitado arquivo válido!" << endl; 
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
   indicelistaS << curso << std::endl;   
}

void Arquivos::LerListaOriginal(ListaInvertida* listaInvertida, ListaPrimaria* listaPrimaria, unsigned *indice, 
   std::istream& Lista, std::ostream& indicelistaP, 
   std::ostream& indicelistaS, ChavesPrimarias **noP, 
   ChavesSecundarias **noS, ChavesSecundarias *anteriorS, 
   ChavesPrimarias *anteriorP){
   
   if(!Lista.eof()){
      std::string linha, chave, curso;
      int rrn = Lista.tellg();
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

void Arquivos::InsereReferencia(string listaP, string listaS, string lista){
   string nameS = "../res/" + listaS + ".ind";
   string nameP11 = "../res/" + listaP + "-2.ind";
   string nameP = "../res/" + listaP + ".ind";
   ofstream indicelista11(nameP11.c_str());
   fstream indicelistaS(nameS.c_str()); 
   fstream indicelistaP;
   ifstream Lista(lista.c_str());    
   bool temProx = false;
   string linha, curso;
   vector<string> indSec;
   string ultimoDaLista;
   string curso2, RRN2, chave2;
   string cursoPrimario, RRN, chave;

   getline(indicelistaS, linha);  

   while(!indicelistaS.eof() && linha.size() != 0){ // Para cada curso no arq de indices secundarios, encontra 
   
      curso = linha.substr(0, 2);
      indicelistaP.open(nameP.c_str());

      getline(indicelistaP, linha); 

      while(!indicelistaP.eof() && linha.size() != 0){
         tuple<string, string> reg;
         tie(cursoPrimario, RRN, chave) = encontraDados(linha, Lista);
         ultimoDaLista = linha.substr(0, linha.size());

         if(curso.compare(cursoPrimario) == 0){
            string linha2;
            getline(indicelistaP, linha2);

            while(!indicelistaP.eof() && linha2.size() != 0){
               tuple<string, string, string> reg2;
               tie(curso2, RRN2, chave2) = encontraDados(linha2, Lista);
               temProx = false;

               if(curso.compare(curso2) == 0){
                  indicelista11 << chave << "|" << RRN2 << endl;
                  temProx = true;
                  linha.swap(linha2);
                  chave.swap(chave2);
               }
               ultimoDaLista = linha2.substr(0, linha2.size());
               getline(indicelistaP, linha2);
            }
            string secundario = curso + "|" + RRN;
            indSec.push_back(secundario);

            if(!temProx)
            indicelista11 << chave << "|-1       " << endl;                
            break;
         }
         getline(indicelistaP, linha);
      }    
      indicelistaP.close();
      getline(indicelistaS, linha);
   }
   tie(curso2, RRN2, chave2) = encontraDados(ultimoDaLista, Lista);
   indicelista11 << chave2 << "|-1       " << endl;

   int i=0;
   indicelistaS.close();
   indicelistaS.open(nameS.c_str());
   while(i < indSec.size()){
      indicelistaS << indSec[i] << endl;
      i++;

   }

   indicelistaS.close();
   indicelista11.close();
   Lista.close();
   OrdenaLista(nameP11);
}

tuple<string, string, string> Arquivos::encontraDados(string linha, istream& Lista){
   string rrn, chave;
   for(int i=0; i<30; i++){
      chave.push_back(linha[i]);
   }
   int contador = 31;
   while(!isspace(linha[contador])){
      rrn.push_back(linha[contador]);
      contador++;
   }
      
   int RRN = stoi(rrn);

   string registro;
   Lista.seekg(RRN);
   getline(Lista, registro);
   string cursoIndP;
   cursoIndP.push_back(registro[52]);
   cursoIndP.push_back(registro[53]);

   while(rrn.size() != 9){
      rrn.push_back(' ');
   }
   return make_tuple(cursoIndP, rrn, chave);
}

void Arquivos::ImprimeListas(int opcao){
   string linha;
   ifstream indicelistaP, indicelistaP2, indicelistaS, Lista;
   // Verifica qual arquivo .txt será manipulado, assim como suas listas de indices
    if(opcao == 1){
      indicelistaP.open("../res/indicelista1.ind");
      indicelistaP2.open("../res/indicelista1-2.ind");
      indicelistaS.open("../res/listaSecundaria1.ind");
      Lista.open("../res/lista1.txt");
   }
   else if(opcao == 2){
      indicelistaP.open("../res/indicelista2.ind");
      indicelistaP2.open("../res/indicelista2-2.ind");
      indicelistaS.open("../res/listaSecundaria2.ind");
      Lista.open("../res/lista2.txt");
   }

   cout << "LISTA DE INDICES PRIMARIOS" << endl;
   cout << "Chave\t\t\t\tPRR do registro" << endl;
   while(!indicelistaP.eof()){
      getline(indicelistaP, linha);
      cout << linha << endl;
   }

   cout << "\nLISTA INVERTIDA" << endl;
   cout << "Chave\t\t\t\tPRR (proximo registro de mesmo curso)" << endl;
   while(!indicelistaP2.eof()){
      getline(indicelistaP2, linha);
      cout << linha << endl;
   }

   cout << "\nLISTA DE INDICES SECUNDARIOS" << endl;
   cout << "Curso|PRR (primeiro chave que contém o curso)" << endl;
   while(!indicelistaS.eof()){
      getline(indicelistaS, linha);
      cout << linha << endl;
   }

   cout << "\nlista1.txt" << endl;
   while(!Lista.eof()){
      getline(Lista, linha);
      cout << linha << endl;
   }            

   indicelistaP.close();
   indicelistaP2.close();
   indicelistaS.close();
   Lista.close();   
}

void Arquivos::Menu(ListaPrimaria* listaPrimarios1, ListaPrimaria* listaPrimarios2,
   ListaInvertida* listaInvertida1, ListaInvertida* listaInvertida2){
   string opcao;
   int op;
   while(true){
      cout <<endl<<endl;
      cout <<"\t\t**************************************************"<<endl;
      cout <<"\t\t"<<"*"<<setw(17)<<""<<setw(13)<<"MENU INDICES"<<setw(18)<<""<<"*"<<endl;
      cout <<"\t\t**************************************************"<<endl;
      cout <<"\t\t"<<"*"<<"\t"<<"OPÇÃO:"<<"\t\t"<<"DESCRIÇÃO:"<<"\t\t"<<" *"<<endl;
      cout <<"\t\t"<<"*""------------------------------------------------"<<"*"<<endl;
      cout <<"\t\t"<<"*"<<"\t"<<"[1]"<<"\t"<<"Mostrar LISTAS"<<"\t\t\t"<<" *"<<endl;
      cout <<"\t\t"<<"*"<<"\t"<<"[2]"<<"\t"<<"Incluir REGRISTRO"<<"\t\t"<<" *"<<endl;
      cout <<"\t\t"<<"*"<<"\t"<<"[3]"<<"\t"<<"Excluir REGISTRO"<<"\t\t"<<" *"<<endl;
      cout <<"\t\t"<<"*"<<"\t"<<"[4]"<<"\t"<<"Atualizar REGISTRO"<<"\t\t"<<" *"<<endl;
      cout <<"\t\t"<<"*"<<"\t"<<"[5]"<<"\t"<<"Intercalar INDICES"<<"\t\t"<<" *"<<endl;
      cout <<"\t\t"<<"*"<<"\t"<<"[0]"<<"\t"<<"SAIR"<<"\t\t\t\t"<<" *"<<endl;
      cout <<"\t\t**************************************************"<<endl;
      cout <<"\t\t"<<setw(10)<<"Digite sua opção---> ";
      getline(cin, opcao);
      op = stoi(opcao);
    switch(op){
      case 1: 
         this->ImprimeListas(1);
         this->ImprimeListas(2);
         break;
      case 2:
         this->InserirRegistro();
         break;
      case 3:
         this->Excluir();
         break;
      case 4:
         this->Atualizar();
         break;
      case 5:
         this->Intercalar();
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

// Algoritmo semelhante ao MergeSort, modificado para comparar strings
// O Merge é calculado usando os Arq de Indice Primarios
// Escolhida a string, é calculado o PRR do registro correspondente
// Posiciona Arq Original no registro, lê e escreve no novo Arquivo
void Arquivos::Intercalar(){ 
   ifstream Lista1("../res/lista1.txt");
   ifstream Lista2("../res/lista2.txt");
   ifstream indicelista1("../res/indicelista1.ind");
   ifstream indicelista2("../res/indicelista2.ind");
   ofstream Lista12("../res/Lista12.txt");

   string linha1, linha2, rrn, rrn1, rrn2, linha, chave1, chave2;
   int RRN, contador=31;;

   cout << "\n LISTAS 1 E 2 INTERCALADAS:\n" << endl;
   getline(indicelista1, linha1);
   getline(indicelista2, linha2);  
   for(int i=0; i<30; i++){
      chave1.push_back(linha1[i]);
   }
   for(int i=0; i<30; i++){
      chave2.push_back(linha2[i]);
   }   
   while(!isspace(linha[contador])){
      rrn1.push_back(linha1[contador]);
      contador++;
   }
   contador=31;
   while(!isspace(linha[contador])){
      rrn2.push_back(linha2[contador]);
      contador++;
   }   

   while(!indicelista1.eof() && !indicelista2.eof()){
      if(chave1.compare(chave2) < 0){ // compara chaves
         RRN = stoi(rrn1); // calcula PRR do registro no Arq Original
         Lista1.seekg(RRN); // posiciona no registro correspondente
         getline(Lista1, linha); // captura (lê) registro

         Lista12 << linha << endl; // escreve no novo arquivo
         cout << linha << endl;
         // reatuliza auxiliares para ficarem prontos a serem usados novamente
         contador=31;
         rrn1.clear();
         chave1.clear();
         getline(indicelista1, linha1);
         for(int i=0; i<30; i++)
            chave1.push_back(linha1[i]); // captura nova chave

         while(!isspace(linha1[contador]))
            rrn1.push_back(linha1[contador++]); // captura novo PRR
      } 

      else{
         RRN = stoi(rrn2); // calcula PRR do registro no Arq Original
         Lista2.seekg(RRN); // posiciona no registro correspondente
         getline(Lista2, linha); // captura (lê) registro

         Lista12 << linha << endl; // escreve no novo arquivo
         cout << linha << endl;
         // reatuliza auxiliares para ficarem prontos a serem usados novamente
         contador=31;
         rrn2.clear();
         chave2.clear();
         getline(indicelista2, linha2);
         for(int i=0; i<30; i++)
            chave2.push_back(linha2[i]); // captura nova chave
         
         while(!isspace(linha2[contador]))
            rrn2.push_back(linha2[contador++]); // captura novo PRR
      }
   }
   contador=31;
   // Escreve em sequencia as chaves que sobraram
   // Seguindo a mesma logica anterior de pegar o PRR
   // Le registro correspondente a chave e escrevendo no novo Arquivo
   while(!indicelista1.eof()){
      
      while(!isspace(linha1[contador])){
            rrn.push_back(linha1[contador]);
            contador++;
         }
      int RRN = stoi(rrn);         
      Lista1.seekg(RRN);
      getline(Lista1, linha); 

      Lista12 << linha << endl;
      cout << linha << endl;
      contador=31;
      rrn.clear();
      getline(indicelista1, linha1);
   }
   while(!indicelista2.eof()){

      while(!isspace(linha2[contador])){
         rrn.push_back(linha2[contador]);
         contador++;
      }
      int RRN = stoi(rrn);         
      Lista2.seekg(RRN);
      getline(Lista2, linha);      
      
      Lista12 << linha << endl;
      cout << linha << endl;
      contador=31;
      rrn.clear();      
      getline(indicelista2, linha2);
   }
   Lista1.close();
   Lista2.close();
   Lista12.close();
   indicelista1.close();
   indicelista2.close();
}

void Arquivos::Atualizar(){
   cout << "\nInsira o Registro que queira atualizar (conforme modelo de entrada), exemplo:" << endl;
   cout << "031147 Anderson Silva Bezerra                   34  EC       B\n" << endl;
   string registro, opcao, nome;
   int opcaoImp;
   getline(cin, registro);
   cout << "\nQual o nome do arquivo o qual obtem esse registro (lista1.txt ou lista2.txt)?" << endl;
   string arquivo;
   getline(cin, arquivo);

   fstream indicelistaP, indicelistaP2, indicelistaS, Lista;   

   // Verifica para qual arquivo.txt foi requerido e abre os arquivos de indices correspondentes
   if(arquivo.compare("lista1.txt") == 0){
      indicelistaP.open("../res/indicelista1.ind");
      indicelistaP2.open("../res/indicelista1-2.ind");
      indicelistaS.open("../res/listaSecundaria1.ind");
      Lista.open("../res/lista1.txt");
      nome = "listaSecundaria1";
      opcaoImp = 1;
   }
   else if(arquivo.compare("lista2.txt") == 0){
      indicelistaP.open("../res/indicelista2.ind");
      indicelistaP2.open("../res/indicelista2-2.ind");
      indicelistaS.open("../res/listaSecundaria2.ind");
      Lista.open("../res/lista2.txt");
      nome = "listaSecundaria2";
      opcaoImp = 2;
   }
   else{
      cout << "Não foi digitado arquivo válido!" << endl;
      exit(0);
   }
   cout << "Digite a opção que queira atualizar:" << endl;
   cout << "1 - Matricula\n2 - Nome\n3 - Opção\n4 - Curso\n5 - Turma\n" << endl;
   getline(cin, opcao);

   switch(stoi(opcao)){ // Atualiza o dado requerido
      case(1):
         this->AtualizarMatricula(indicelistaP, indicelistaP2, Lista, registro);
         this->ImprimeListas(opcaoImp);
         break;
      case(2):
         this->AtualizarNome(indicelistaP, indicelistaP2, Lista, registro);
         this->ImprimeListas(opcaoImp);
         break;
      case(3):
         this->AtualizarOpcao(Lista, registro);
         this->ImprimeListas(opcaoImp);
         break;
      case(4):
         this->AtualizarCurso(Lista, indicelistaS, indicelistaP2, registro, nome);
         this->ImprimeListas(opcaoImp);
         break;
      case(5):
         this->AtualizarTurma(Lista, registro);
         this->ImprimeListas(opcaoImp);
         break;
      default:
         cout << "Opcao invalida";
         break;
   }

   indicelistaP.close();
   indicelistaP2.close();
   indicelistaS.close();
   Lista.close(); 

   this->OrganizarAquivos(); // Ordena e Organiza PRR
}

void Arquivos::AtualizarNome(fstream& indicelistaP, fstream& indicelistaP2, fstream& Lista, string registro){
   string novoNome, nome, novoNomeP, chave, chaveP, rrn, linha;
   int espacos=0, contador=0, RRN;
   cout << "Digite o novo nome:    ";
   getline(cin, novoNome);

   // Concatena nome do registro, para futura verificação com o arquivo de indices primarios
   for(int i=7; espacos < 5; i++){
      if( !isspace(registro[i]) ){
         nome.push_back(registro[i]);
      }
      else espacos++;
   }

   if(nome.size() < 24) while(nome.size() < 24) nome.push_back(' '); //fixa tamanho do nome
   
   // Enquanto arquivo não acabar, verifica se o nome da chave do arquivo de indices primarios
   // é igual ao nome do registro requerido, para entao fazer a mudança
   getline(indicelistaP, linha);
   while(!indicelistaP.eof() && linha.size() != 0){
      string nomeP = linha.substr(6, 24); // pega somente o nome da chave para comparação

      if(nome.compare(nomeP) == 0){
         contador = 31;
         while(!isspace(linha[contador])){ // Estrai o RNN do qual a chave se refere no arquivo original
               rrn.push_back(linha[contador]);
            contador++;
         }
         RRN = stoi(rrn);
         Lista.seekp(RRN + 7); //posiciona o seek na posição em que o novo nome sera escrito
        
         while(novoNome.size() < 41) novoNome.push_back(' ');
         Lista << novoNome; // sobrescreve o arquivo com o novo nome
         
         int posicao = indicelistaP.tellg();
         indicelistaP.seekp(posicao - 35);
         novoNomeP.clear();
         contador=0;
         // concatena novo nome e fixa o tamanho para sobrescrever os arquivos de indices primarios
         while(contador < novoNome.size() && novoNomeP.size() < 24){
            if(!isspace(novoNome[contador]))
               novoNomeP.push_back(novoNome[contador]);
            contador++;
         }
         if(novoNomeP.size() < 24) while(novoNomeP.size() < 24) novoNomeP.push_back(' ');
         indicelistaP << novoNomeP;

         indicelistaP2.seekp(posicao - 35);
         indicelistaP2 << novoNomeP;
         break;
      }
      getline(indicelistaP, linha);
   }
}

void Arquivos::AtualizarMatricula(fstream& indicelistaP, fstream& indicelistaP2, fstream& Lista, string registro){
   string matricula = registro.substr(0, 6);
   string novaMatricula, matriculaP, linha, rrn;
   int contador=31, RRN;

   cout << "Digite a nova matricula (apenas 6 caracteres):   ";
   getline(cin, novaMatricula);

   getline(indicelistaP, linha);
   // Enquanto Arq de Indices Primarios nao acabar
   // compara matricula da chave com a matricula do registro a ser atualizado
   // quando encontrar, sobrescreve os Arq de Indice Primarios com a nova matricula
   while(!indicelistaP.eof() && linha.size() != 0){
      matriculaP = linha.substr(0, 6);
      
      if(matricula.compare(matriculaP) == 0){
         int posicao = indicelistaP.tellg();
         indicelistaP.seekp(posicao - 41);
         indicelistaP << novaMatricula;
         indicelistaP2.seekp(posicao - 41);
         indicelistaP2 << novaMatricula;

         while(!isspace(linha[contador])){
            rrn.push_back(linha[contador]);
            contador++;
         }
         RRN = stoi(rrn); // Obtem a posição relativa do registro no arquivo original a qual a chave se refere
         Lista.seekp(RRN);
         Lista << novaMatricula; // Atualiza Arquivo original
         break;         
      }
      getline(indicelistaP, linha);
   }
}

void Arquivos::AtualizarOpcao(fstream& Lista, string registro){
   string linha, novaOpcao, Registro;
   cout << "Digite a nova opção:    ";
   getline(cin, novaOpcao);
   getline(Lista, linha);

   // Enquanto arquivo não acabar, procura registro a ser atualizado,
   // posiciona seek e sobrescreve a nova opção de curso
   while(!Lista.eof() && linha.size() != 0){
      Registro = linha.substr(0, 62);
      if(Registro.compare(registro) == 0){
         
         int posicao = Lista.tellg();
         Lista.seekp(posicao - 16);
         Lista << novaOpcao;
         break;
      }
      getline(Lista, linha);
   }
}

void Arquivos::AtualizarTurma(fstream& Lista, string registro){
   string linha, novaOpcao, Registro;
   cout << "Digite a nova turma:  ";
   getline(cin, novaOpcao);
   getline(Lista, linha);

   // Enquanto arquivo não acabar, procura registro a ser atualizado,
   // posiciona seek e sobrescreve a nova turma
   while(!Lista.eof() && linha.size() != 0){
      Registro = linha.substr(0, 62);
      if(Registro.compare(registro) == 0){
         
         int posicao = Lista.tellg();
         Lista.seekp(posicao - 3);
         Lista << novaOpcao;
         break;
      }
      getline(Lista, linha);
   }
}

void Arquivos::AtualizarCurso(fstream& Lista, fstream& listaS, fstream& listaP2, string registro, string nome){
   string linha, novoCurso, inserirCurso, cursoS, cursoReg, RRN_Reg, Registro;
   int posicao;
   bool encontrou = false;
   cursoReg = registro.substr(52, 2);

   cout << "Digite o novo curso:  ";
   getline(cin, novoCurso);
   inserirCurso = novoCurso;

   getline(Lista, linha);
   while(!Lista.eof() && linha.size() != 0){ // procura registro a ser atualizado e sobrescreve novo curso
      Registro = linha.substr(0, 62);
      if(Registro.compare(registro) == 0){
         
         posicao = Lista.tellg();
         Lista.seekp(posicao - 12);
         Lista << novoCurso;

         posicao = Lista.tellg();
         posicao = posicao - 54;
         break;
      }
      getline(Lista, linha);
   }
   // Procura curso no Arq de Indices Secundarios
   // Se não encontrar, insere novo curso na lista
   listaS.seekg(0);
   getline(listaS, linha);
   while(!listaS.eof() && linha.size() != 0){
      cursoS = linha.substr(0, 2);
      if(cursoS.compare(novoCurso) == 0){
         encontrou = true;
         break;
      }
      getline(listaS, linha);
   }
   listaS.close();
   string nomeArq = "../res/" + nome + ".ind";
   listaS.open(nomeArq.c_str(), ios::app);
   if(!encontrou){
      string RRN_Reg = to_string(posicao); // Calcula a PRR do registro atualizado
      if(RRN_Reg.size() < 9){
         while(RRN_Reg.size() < 9){
            RRN_Reg.push_back(' ');
         }
      }
      listaS << novoCurso << "|" << RRN_Reg << endl; // Insere novo curso
   }
   listaS.close();
   listaS.open(nomeArq);
}

// Ordena Arquivos de Indices Primarios e Secundarios
// Cria Lista Invertida: indicelista1-2.ind ou indicelista2-2.ind
// Que contém as chaves, seguidas dos PRR da proxima chave que contem o 
// mesmo curso (de forma ordenada). 
void Arquivos::OrganizarAquivos(){
   this->OrdenaLista("../res/listaSecundaria1.ind");
   this->OrdenaLista("../res/listaSecundaria2.ind");

   this->OrdenaLista("../res/indicelista2.ind");
   this->OrdenaLista("../res/indicelista1.ind");

   this->InsereReferencia("indicelista1", "listaSecundaria1", "../res/lista1.txt");
   this->InsereReferencia("indicelista2", "listaSecundaria2", "../res/lista2.txt");
}

void Arquivos::InserirRegistro(){
   string arquivo, registro, chave, RRN, nomeLista, nomeIndice;
   string nomeSec, linha, curso, cursoS;
   int i=0, rrn, posicao, contador=0, opcao;
   bool temEspaco = false, existeCurso = false;
   fstream Lista, indicelistaP, listaSecundaria;
   cout << "Digite os registro que queira excluir (como no modelo)" << endl;
   getline(cin, registro);
   cout << "\nDigite o nome do arquivo em que deseja incluir" << endl;
   getline(cin, arquivo);
   
   if(arquivo.compare("lista1.txt") == 0){
      nomeLista = "../res/lista1.txt";
      nomeIndice = "../res/indicelista1.ind";
      nomeSec = "../res/listaSecundaria1.ind";
      opcao = 1;
   }
   if(arquivo.compare("lista2.txt") == 0){
      nomeLista = "../res/lista2.txt";
      nomeIndice = "../res/indicelista2.ind";
      nomeSec = "../res/listaSecundaria2.ind";
      opcao = 2;
   }   

   indicelistaP.open(nomeIndice.c_str());
   Lista.open(nomeLista.c_str());
   // Cria chave do registro
   while(chave.size() < 30 && contador < registro.size()){
      if(!isspace(registro[i])) chave.push_back(registro[i]);
      i++;
      contador++;
   }
   // Captura curso correspondente
   if(chave.size() < 30) while(chave.size() < 30) chave.push_back(' ');
   curso.push_back(registro[52]);
   curso.push_back(registro[53]);

   getline(indicelistaP, linha);
   // Se linha conter * (espaço disponivel), insere nova chave no lugar
   // Insere no Arquivo Original no lugar correspondente
   while(!indicelistaP.eof() && linha.size()!=0){
      if(linha[0] == '*'){
         posicao = indicelistaP.tellg();
         indicelistaP.seekp(posicao-41);

         indicelistaP << chave;
         cout << chave << "*" << endl;
         temEspaco = true;
         RRN = linha.substr(31, 9);

         int pos = stoi(RRN);
         Lista.seekp(pos);
         Lista << registro;
         break;
      }
      getline(indicelistaP, linha);
   }
   indicelistaP.close();
   Lista.close();
   // Caso não tenha espaço disponivel, insere no fim dos arquivos
   if(!temEspaco){
      indicelistaP.open(nomeIndice.c_str(), ios::app);
      Lista.open(nomeLista.c_str(), ios::app);
      rrn = Lista.tellg();
      rrn = rrn - 64;
      
      RRN = to_string(rrn);
      while(RRN.size() < 9)  RRN.push_back(' ');
      indicelistaP << chave << "|" << RRN << endl;
      Lista << registro << endl;
      indicelistaP.close();
      Lista.close(); 
   }

   // Verifica se curso existe na lista Secundaria. Se nao existir, insere na lista
   listaSecundaria.open(nomeSec.c_str());
   getline(listaSecundaria, linha);

   while(!listaSecundaria.eof() && linha.size() != 0){
      cursoS = linha.substr(0, 2);
      if(cursoS.compare(curso) == 0){
         existeCurso = true;
         break;
      }
      getline(listaSecundaria, linha);
   }
   listaSecundaria.close();
   listaSecundaria.open(nomeSec.c_str(), ios::app);
   if(!existeCurso){
      listaSecundaria << curso << "|" << RRN << endl;
   }
   listaSecundaria.close();

   // Organiza novamente os arquivos (Ordenando e Organziando a Lista Invertida)
   OrganizarAquivos();
   ImprimeListas(opcao);
}