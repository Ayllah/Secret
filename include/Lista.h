#ifndef LISTA_H					
#define LISTA_H

#include <iostream>
#include <fstream>

//Estrutura para armazenar e tratar as chaves primarias

typedef struct ChavesP {
	std::string chavePrim; 
	int RRN;
	char MarcadorAtivo;
	struct ChavesP *prox;
}ChavesPrimarias;

class ListaRegistros{
public:
	ChavesPrimarias* Inicio;
};

//Estrutura para armazenar e tratar as chaves secundarias
//Cada no cria uma lista invertida

typedef struct ChavesS {
	std::string curso;
	unsigned referencia;
	struct ChavesS* prox;
}ChavesSecundarias;

//Estrutura para armazenar e tratar as listas invertidas
//Para cada no da lista de chaves secundarias sera criada
//uma lista invertida e será mantido os ponteiros para os
//nos da lista de chave primaria

class ListaInvertida {
public:
	ChavesSecundarias* Inicio;
};

class Lista {
	public : ChavesPrimarias *ChavPrimInicio, *ChavPrimFim;
			 ChavesSecundarias *ChavSecMATInicio, *ChavSecMATFim, *ChavSecNOMEInicio, *ChavSecNOMEFim;
			 ChavesSecundarias **vetorSecNOME, **vetorSecMATRIC;
			 ChavesPrimarias **vetorP;
			 int tamanhoVetor, tamanhoSecNOME, tamanhoSecMATRIC, tamanhoPrim;
			 char Busca = 0; // 0: Busca sem exclusao ; 1: Busca com exclusao
			 void CriaRegistro(); 
			 ChavesPrimarias* IncluirRegistroChavP(char *chavePrim, int RRN, ChavesPrimarias **Inicio, ChavesPrimarias **Fim);
			 void IncluirRegistroInvertida();
			 void ExcluirRegistro();
			 void AtualizarRegistro();
			 void Intercalacao();

};

class Arquivos{
public:
	void ArquivoPrimario();
	void InserirPrimario(ChavesPrimarias **no, std::string chave, unsigned RRN, std::ostream& indicelistaP);
	void InserirSecundario(ChavesSecundarias **no, std::string curso, unsigned RRN, std::ostream& indicelistaS);	
	void LerListaOriginal(std::istream& Lista, std::ostream& indicelistaP, std::ostream& indicelistaS, ChavesPrimarias **noP, ChavesSecundarias **noS);
};

#endif //LISTA_H