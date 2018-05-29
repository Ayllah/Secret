#include "Lista.h"
//#include "heapsort.h"

int main(int argc, char const *argv[]){
	
	// Lê arquivos e cria os arquivos de indices primarios
	Arquivos *arq;
	ListaPrimaria* listaPrimarios1 = new ListaPrimaria;
   	ListaInvertida* listaInvertida1 = new ListaInvertida;
	ListaPrimaria* listaPrimarios2 = new ListaPrimaria;
   	ListaInvertida* listaInvertida2 = new ListaInvertida; 

	arq->ArquivoPrimSec(listaPrimarios1, listaPrimarios2, listaInvertida1, listaInvertida2);

	arq->OrdenaLista("../res/listaSecundaria1.ind");
	arq->OrdenaLista("../res/listaSecundaria2.ind");

	arq->OrdenaLista("../res/indicelista2.ind");
	arq->OrdenaLista("../res/indicelista1.ind");

	arq->InsereReferencia("indicelista1", "listaSecundaria1", "../res/lista1.txt");
	arq->InsereReferencia("indicelista2", "listaSecundaria2", "../res/lista2.txt");

	//arq->Intercalar();
   	arq->Menu(arq, listaPrimarios1, listaPrimarios2, listaInvertida1, listaInvertida2);
	
	//arq->ImprimeListas(listaPrimarios1, listaPrimarios2, listaInvertida1, listaInvertida2);
	//arq->Excluir();
	
	//indicelistaP1.close();
	//indicelistaP2.close();
	return 0;
}