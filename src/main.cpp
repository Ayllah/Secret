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

	arq->OrganizarAquivos();
   	//arq->Menu(listaPrimarios1, listaPrimarios2, listaInvertida1, listaInvertida2);

	return 0;
}