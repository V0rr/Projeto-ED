#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <cstdlib>

using namespace std;

//estrtura para armazenar o vetor de índices na página da B+
struct indice {
    unsigned tam;
    unsigned indice;
};

class Pagina {
    friend class BPlus;
    private:
    indice idx[80]; 
    Pagina* pont_tree[81]; //ponteiros usados para páginas que não são folhas
    int pont_seq[81]; //ponteiros usados nas folhas, para acesso ao sequence set
    bool ehfolha; //indica se a página é folha
    unsigned elementos; //guarda a quantidade de elementos válidos no vetor de indice
    public:
    Pagina();
};

Pagina::Pagina() {
    for (int i = 0; i < 80; i++) {
        idx[i] = {};
    }
    for (int i = 0; i < 81; i++) {
        pont_seq[i] = {};
        pont_tree[i] = NULL;
    }
    ehfolha = false;
    elementos = 0;
}

class BPlus {
    private:
    Pagina* raiz;
    public:
    BPlus();
    void Inserir (unsigned t, unsigned i);
    Pagina* Buscar (unsigned c1, unsigned c2); //retorna o endereço da página
    void Alterar (unsigned t, unsigned i);
};

BPlus::BPlus() {
    raiz = NULL;
}

//percorre a arvore e retorna a pagina folha em que o elemento deveria estar
Pagina* BPlus::Buscar(unsigned c1, unsigned c2) {
    Pagina* percorre = raiz;
    if (percorre -> ehfolha) 
        return percorre;
    
    while (percorre -> ehfolha == false ) {
        for (int i = 0; i < percorre -> elementos; i++ ) {
            if (c1 < percorre -> idx[i].tam) {
                percorre = percorre -> pont_tree[i]; //passa para pagina filha
            }

            else if (c1 == percorre -> idx[i].tam) { //caso a chave primaria for igual, compara com a chave secundaria
                if (c2 < percorre -> idx[i].indice) {
                    percorre = percorre -> pont_tree[i];
                }
            }
        }
        if (percorre -> ehfolha == false) { //caso ele seja maior que a ultima posição
            percorre = percorre -> pont_tree [percorre->elementos]; //ponteiro do ultimo elemento
        }
    }
    return percorre;
}

void BPlus::Inserir(unsigned t, unsigned i){

    if(raiz == NULL){
        raiz->idx[0].indice = i;
        raiz->idx[0].tam = t;
        raiz->ehfolha = true;
        raiz->elementos = 1;
    } else {
        Pagina* precursor = raiz;
        Pagina* parent;
        bool achou = false;

        // No loop abaixo, o precursor irá para o nó folha onde possivelmente será inserido o dado.
        while(precursor->ehfolha == false){
            parent = precursor;
            for(int i = 0; i < precursor->elementos && achou == false; i++){
                if(i == precursor->elementos - 1){
                    precursor->pont_tree[i+1];
                    achou = true;
                } else if(t < precursor->idx[i].tam){
                    precursor = precursor->pont_tree[i];
                    achou = true;
                } else if(t == precursor->idx[i].tam && i < precursor->idx[i].indice){
                    precursor = precursor->pont_tree[i];
                    achou = true;
                }
            }
        }

        if(precursor->elementos < 80){

        }

    }
}

int main(){};

