#include "Lista.h"

using namespace std;

void Arquivos::ExcluirRegistro(std::string registro, std::fstream& Lista, std::fstream& indicelistaP, std::fstream& indicelistaP2, std::fstream& indicelistaS){
   
   string chaveParaExcluir, linha, rrn;
   unsigned contador=0, espacos=0;
   int RRN, RRN_P;
   bool excluido = false;

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
         chaveParaExcluir.push_back(' ');
      }
   }   
   getline(indicelistaP, linha);
   while(!indicelistaP.eof()){
      string chave = linha.substr(0, 30);
      if(chave.compare(chaveParaExcluir) == 0){
         int contador = 31;
         while(!isspace(linha[contador])){
               rrn.push_back(linha[contador]);
            contador++;
         }
         string liinha;
         int RRN = stoi(rrn);
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
   }
   else if(arquivo.compare("lista2.txt") == 0){
      fstream indicelistaP("../res/indicelista2.ind");
      fstream indicelistaP2("../res/indicelista2-2.ind");
      fstream indicelistaS("../res/listaSecundaria2.ind");
      fstream Lista("../res/lista2.txt");
      ExcluirRegistro(registro, Lista, indicelistaP, indicelistaP2, indicelistaS);      
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
   std::string indiceRef, indice;
   std::cout << "\nReferencia \t\t\tChave|PRR\t\t Próxima Referencia" << std::endl;
   for(atual = lista->Inicio; atual != NULL; atual=atual->prox){
      if(atual->referencia != NULL){
         indiceRef = std::to_string(atual->referencia->indice);
         indiceRef.resize(6, ' ');
      }
      else indiceRef = "-1";

      indice = std::to_string(atual->indice);
      indice.resize(3, ' ');
      std::cout << indice << "\t\t" << atual->chave << "|" << atual->RRN << "\t\t" << indiceRef << std::endl;
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

   while(!indicelistaS.eof() && linha.size() != 0){
   
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

void Arquivos::Menu(Arquivos *arq, ListaPrimaria* listaPrimarios1, ListaPrimaria* listaPrimarios2,
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
         arq->ImprimeListas(listaPrimarios1, listaPrimarios2, listaInvertida1, listaInvertida2);
         break;
      case 2:
         break;
      case 3:
         arq->Excluir();
         break;
      case 4:
         break;
      case 5:
         arq->Intercalar();
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
      if(chave1.compare(chave2) < 0){
         RRN = stoi(rrn1);         
         Lista1.seekg(RRN);
         getline(Lista1, linha);

         Lista12 << linha << endl;
         cout << linha << endl;
         contador=31;
         rrn1.clear();
         chave1.clear();
         getline(indicelista1, linha1);
         for(int i=0; i<30; i++)
            chave1.push_back(linha1[i]);

         while(!isspace(linha1[contador]))
            rrn1.push_back(linha1[contador++]);
      } 

      else{
         RRN = stoi(rrn2);         
         Lista2.seekg(RRN);
         getline(Lista2, linha);

         Lista12 << linha << endl;
         cout << linha << endl;
         contador=31;
         rrn2.clear();
         chave2.clear();
         getline(indicelista2, linha2);
         for(int i=0; i<30; i++)
            chave2.push_back(linha2[i]);
         
         while(!isspace(linha2[contador]))
            rrn2.push_back(linha2[contador++]);    
      }
   }
   contador=31;
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
