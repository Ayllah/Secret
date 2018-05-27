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

	arq->OrdenaListaPrimaria(&listaPrimarios1, &listaInvertida1);
	arq->OrdenaListaSecundaria(listaInvertida1);

	arq->OrdenaListaPrimaria(&listaPrimarios2, &listaInvertida2);
	arq->OrdenaListaSecundaria(listaInvertida2);	

	std::cout << "\nArquivo: lista1.txt" << std::endl;
	arq->ImprimeSecundaria(listaInvertida1);
	arq->ImprimePrimaria(listaPrimarios1);
	std::cout.width(70);
	std::cout.fill( '_' );
	std::cout << "_" << std::endl;

	std::cout << "\nArquivo: lista2.txt" << std::endl;
	arq->ImprimeSecundaria(listaInvertida2);
	arq->ImprimePrimaria(listaPrimarios2);	


	return 0;
}