#ifndef LISTA_H					
#define LISTA_H

#include <string>

//Estrutura para armazenar e tratar registros

class Registro {
    public : std :: string MATRIC;
    		 std :: string;
         
             
};

//Estrutura para armazenar e tratar as chaves primarias

class ChavesPrimarias {
	public: std :: string chavePrim; 
			int RRN;
			char MarcadorAtivo;
			ChavesPrimarias *prox;
}

//Estrutura para armazenar e tratar as listas invertidas
//Para cada no da lista de chaves secundarias sera criada
//uma lista invertida e será mantido os ponteiros para os
//nos da lista de chave primaria

class ListaInvertida {
	public : ChavesPrimarias *ptr;
			 ListaInvertida *prox;
	
}

//Estrutura para armazenar e tratar as chaves secundarias
//Cada no cria uma lista invertida

class ChavesSecundarias {
	public : std :: string chaveSec;
			 ListaInvertida *Inicio;
			 ListaInvertido *Fim;
			 ChavesSecundarias *prox;
}

class Lista {
	public : ChavesPrimarias *ChavPrimInicio, *ChavPrimFim;
			 ChavesSecundarias *ChavSecMATInicio, *ChavSecMATFim, *ChavSecNOMEInicio, *ChavSecNOMEFim;
			 ChavesSecundarias **vetorSecNOME, **vetorSecMATRIC;
			 ChavesPrimarias **vetorP;
			 int tamanhoVetor, tamanhoSecNOME, tamanhoSecMATRIC, tamanhoPrim;
			 char Busca = 0; // 0: Busca sem exclusao ; 1: Busca com exclusao
			 void CriaRegistro(); 
			 ChavesPrimarias* IncluirRegistroChavP(std :: string *chavePrim, int RRN, ChavesPrimarias **Inicio, ChavesPrimarias **Fim);
			 void IncluirRegistroInvertida(ChavesPrimarias *ptr, ListaInvertida **Inicio, ListaInvertida **Fim);
			 void IncluirRegistroChavS(std :: string *chaveSec, ChavesPrimarias *ptr, ChavesSecundarias **Inicio, ChavesSecundarias **Fim);
			 int TamanhoListaSec(ChavesSecundarias *Inicio);
			 
			 void ExcluirRegistro(ChavesPrimarias *no);
			 void AtualizarRegistro();
			 void Intercalacao();

};

 

#endif //LISTA_H