#ifndef LISTA_H					
#define LISTA_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <tuple>

//Estrutura para armazenar e tratar as chaves primarias

struct ChavesPrimarias {
	std::string chave; 
	std::string curso;
	std::string RRN;
	unsigned indice;
	bool MarcadorAtivo;
	ChavesPrimarias *prox;
	ChavesPrimarias *anterior;
	ChavesPrimarias *referencia;
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
	void Menu(ListaPrimaria* listaPrimarios1, ListaPrimaria* listaPrimarios2, ListaInvertida* listaInvertida1, ListaInvertida* listaInvertida2);

	void Excluir();
	void ExcluirRegistro(std::string registro, std::fstream& Lista, std::fstream& indicelistaP, std::fstream& indicelistaP2, std::fstream& indicelistaS);

	void InserirRegistro();

	void ArquivoPrimSec(ListaPrimaria *listaPrimarios1, ListaPrimaria* listaPrimarios2, ListaInvertida* listaInvertida1, ListaInvertida* listaInvertida2);
	void LerListaOriginal(ListaInvertida* listaInvertida, ListaPrimaria* listaPrimaria, unsigned *indice, std::istream& Lista, std::ostream& indicelistaP, std::ostream& indicelistaS, ChavesPrimarias **noP, ChavesSecundarias **noS, ChavesSecundarias *anteriorS, ChavesPrimarias *anteriorP);
	
	void InserirPrimario(unsigned *indice, ChavesPrimarias **no, ChavesPrimarias *anterior, std::string chave, std::string RRN, std::string curso, std::ostream& indicelistaP);
	void InserirSecundario(ChavesSecundarias **no, ChavesSecundarias *anterior, std::string curso, ChavesPrimarias **chavePrimaria, std::ostream& indicelistaS, std::string RRN);
	bool existeCurso(std:: string curso, ListaInvertida *lista);

	void OrdenaLista(std::string nomeArquivo);
	void insertion_sort(std::vector<std::string>& vetor);

	void ImprimeSecundaria(ListaInvertida* lista);
	void ImprimePrimaria(ListaPrimaria* lista);
	void ImprimeListas(int opcao);
	void Intercalar();

	void InsereReferencia(std::string listaP, std::string listaS, std::string lista);
	std::tuple<std::string, std::string, std::string> encontraDados(std::string linha, std::istream& Lista);
	void OrganizarAquivos();

	void Atualizar();
	void AtualizarNome(std::fstream& indicelistaP, std::fstream& indicelistaP2, std::fstream& Lista, std::string registro);
	void AtualizarMatricula(std::fstream& indicelistaP, std::fstream& indicelistaP2, std::fstream& Lista, std::string registro);
	void AtualizarOpcao(std::fstream& Lista, std::string registro);
	void AtualizarTurma(std::fstream& Lista, std::string registro);
	void AtualizarCurso(std::fstream& Lista, std::fstream& listaS, std::fstream& listaP2, std::string registro, std::string nome);
};

 

#endif //LISTA_H