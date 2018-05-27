#ifndef LISTA_H					
#define LISTA_H

#include <iostream>
#include <fstream>
#include <string>

//Estrutura para armazenar e tratar as chaves primarias

struct ChavesPrimarias {
	std::string chave; 
	std::string curso;
	unsigned indice;
	unsigned RRN;
	char MarcadorAtivo;
	ChavesPrimarias *prox;
	ChavesPrimarias *anterior;
};

class ListaPrimaria{
public:
	ChavesPrimarias* Inicio;
};

//Estrutura para armazenar e tratar as listas invertidas
//Para cada no da lista de chaves secundarias sera criada
//uma lista invertida e será mantido os ponteiros para os
//nos da lista de chave primaria
struct ChavesSecundarias {
	std::string curso;
	ChavesPrimarias* chavePrimaria;
	ChavesSecundarias* prox;
	ChavesSecundarias* anterior;
};

//Estrutura para armazenar e tratar as listas invertidas
//Para cada no da lista de chaves secundarias sera criada
//uma lista invertida e será mantido os ponteiros para os
//nos da lista de chave primaria

class ListaInvertida {
public:
	ChavesSecundarias* Inicio;
};
/*

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
*/
class Arquivos{
public:
	int TamanhoListaPrim(ChavesPrimarias *Inicio);
	bool ExcluirRegistroP(ChavesPrimarias **no, std::string chave, std::ostream& indicelistaP);
	void Excluir(ListaPrimaria *listaPrimarios1, std::ostream& indicelistaP1);

	void ArquivoPrimSec(ListaPrimaria *listaPrimarios1, ListaPrimaria* listaPrimarios2, ListaInvertida* listaInvertida1, ListaInvertida* listaInvertida2);
	void LerListaOriginal(ListaInvertida* listaInvertida, ListaPrimaria* listaPrimaria, unsigned *indice, std::istream& Lista, std::ostream& indicelistaP, std::ostream& indicelistaS, ChavesPrimarias **noP, ChavesSecundarias **noS, ChavesSecundarias *anteriorS, ChavesPrimarias *anteriorP);
	
	void InserirPrimario(unsigned *indice, ChavesPrimarias **no, ChavesPrimarias *anterior, std::string chave, unsigned RRN, std::string curso, std::ostream& indicelistaP);
	void InserirSecundario(ChavesSecundarias **no, ChavesSecundarias *anterior, std::string curso, ChavesPrimarias **chavePrimaria, std::ostream& indicelistaS);
	bool existeCurso(std:: string curso, ListaInvertida *lista);
	void Insere_proxOrdem(ListaPrimaria* lista, ChavesPrimarias** no, std::string curso);

	void TrocaNoSec(ChavesSecundarias *atual, ChavesSecundarias *proximo);
	void OrdenaListaSecundaria(ListaInvertida *lista);
	void TrocaNoPrim(ChavesPrimarias **atual, ChavesPrimarias **proximo);
	void OrdenaListaPrimaria(ListaPrimaria **lista, ListaInvertida** invertida);

	void ImprimeSecundaria(ListaInvertida* lista);
	void ImprimePrimaria(ListaPrimaria* lista);
};

 

#endif //LISTA_H