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

	arq->OrdenaListaPrimaria(listaPrimarios1, listaInvertida1);
	arq->OrdenaListaSecundaria(listaInvertida1);

	arq->OrdenaListaPrimaria(listaPrimarios2, listaInvertida2);
	arq->OrdenaListaSecundaria(listaInvertida2);

	arq->InsereReferencia(listaPrimarios1, listaInvertida1);
	arq->InsereReferencia(listaPrimarios2, listaInvertida2);

   	//arq->Menu(listaPrimarios1, listaPrimarios2, listaInvertida1, listaInvertida2);


	//arq->ImprimeListas(listaPrimarios1, listaPrimarios2, listaInvertida1, listaInvertida2);
	arq->Excluir(listaPrimarios1, listaInvertida1, listaPrimarios2, listaInvertida2);
	return 0;
}