#include "heapsort.h"

#define GETBIT(num,pos) (num >> pos & 1)

void swap(int *a,int *b){
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

/*void addNode(node *tmp1,node *parent, int pos){
    int dirxn = GETBIT(nodes,pos);            // 0 - go left, 1 - go right

    if(!pos){
        if(dirxn)
            tmp1->right = current;
        else
            tmp1->left = current;

        current->left = 0;
        current->right = 0;

        if(current->data > tmp1->data)
            swap(&current->data, &tmp1->data);
    }

    else
        if(dirxn)
            addNode(tmp1->right,tmp1,pos-1);
        else
            addNode(tmp1->left,tmp1,pos-1);

    if(tmp1->data > parent->data)
        swap(&parent->data,&tmp1->data);
}

void getRoot(node *tmp,int pos)
{
    int dirxn;

    if(nodes == 1)
        return ;

    while(pos)
    {
        dirxn = GETBIT(nodes,pos);

        if(dirxn)
            tmp = tmp->right;
        else
            tmp = tmp->left;
        pos--;
    }

    dirxn = GETBIT(nodes,pos);

    if(dirxn)
    {
        first->data = tmp->right->data;
        free(tmp->right);
        tmp->right = 0;
    }
    else
    {
        first->data = tmp->left->data;
        free(tmp->left);
        tmp->left = 0;
    }
}
*/
void heapSort(ChavesSecundarias *tmp){
    tmp->anterior = anterior;
    if(!tmp->anterior && !tmp->prox)
        return;

    if(!tmp->anterior){
        if(tmp->prox->referencia > tmp->referencia)
            swap(&tmp->prox->referencia, &tmp->referencia);
    }
    else{

        if(tmp->anterior->referencia > tmp->prox->referencia){
            if(tmp->anterior->referencia > tmp->referencia){
                swap(&tmp->anterior->referencia, &tmp->referencia);
                heapSort(tmp->anterior);
            }
        }           
        else{
            if(tmp->prox->referencia > tmp->referencia){
                swap(&tmp->prox->referencia, &tmp->referencia);
                heapSort(tmp->prox);
            }
        }
    }
}