#include "lista_dupla.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inicializarBiblioteca(Biblioteca* b) {
    b->primeiro = NULL;
    b->ultimo = NULL;
    b->totalLivros = 0;
}

int cadastrarLivro(Biblioteca* b, char* titulo, char* autor, int ano, char* isbn) {
    if (consultarLivroPorISBN(b, isbn) != NULL) return 0;

    Livro novo;
    strcpy(novo.titulo, titulo);
    strcpy(novo.autor, autor);
    novo.ano = ano;
    strcpy(novo.isbn, isbn);
    novo.status = DISPONIVEL;
    novo.usuario[0] = '\0';
    novo.dataEmprestimo[0] = '\0';

    return inserirLivroFim(b, novo);
}

int inserirLivroInicio(Biblioteca* b, Livro livro) {
    NoLivro* novo = (NoLivro*) malloc(sizeof(NoLivro));
    if (!novo) return 0;

    novo->livro = livro;
    novo->anterior = NULL;
    novo->proximo = b->primeiro;

    if (b->primeiro) {
        b->primeiro->anterior = novo;
    } else {
        b->ultimo = novo;
    }

    b->primeiro = novo;
    b->totalLivros++;
    return 1;
}

int inserirLivroFim(Biblioteca* b, Livro livro) {
    NoLivro* novo = (NoLivro*) malloc(sizeof(NoLivro));
    if (!novo) return 0;

    novo->livro = livro;
    novo->proximo = NULL;
    novo->anterior = b->ultimo;

    if (b->ultimo) {
        b->ultimo->proximo = novo;
    } else {
        b->primeiro = novo;
    }

    b->ultimo = novo;
    b->totalLivros++;
    return 1;
}

int inserirLivroNaPosicao(Biblioteca* b, Livro livro, int pos) {
    if (pos <= 0) return inserirLivroInicio(b, livro);
    if (pos >= b->totalLivros) return inserirLivroFim(b, livro);

    NoLivro* atual = b->primeiro;
    for (int i = 0; i < pos - 1; i++) {
        atual = atual->proximo;
    }

    NoLivro* novo = (NoLivro*) malloc(sizeof(NoLivro));
    if (!novo) return 0;

    novo->livro = livro;
    novo->proximo = atual->proximo;
    novo->anterior = atual;

    atual->proximo->anterior = novo;
    atual->proximo = novo;

    b->totalLivros++;
    return 1;
}

int removerLivroInicio(Biblioteca* b) {
    if (!b->primeiro) return 0;

    NoLivro* temp = b->primeiro;
    b->primeiro = temp->proximo;

    if (b->primeiro)
        b->primeiro->anterior = NULL;
    else
        b->ultimo = NULL;

    free(temp);
    b->totalLivros--;
    return 1;
}

int removerLivroFim(Biblioteca* b) {
    if (!b->ultimo) return 0;

    NoLivro* temp = b->ultimo;
    b->ultimo = temp->anterior;

    if (b->ultimo)
        b->ultimo->proximo = NULL;
    else
        b->primeiro = NULL;

    free(temp);
    b->totalLivros--;
    return 1;
}

int removerLivroNaPosicao(Biblioteca* b, int pos) {
    if (pos < 0 || pos >= b->totalLivros) return 0;

    if (pos == 0) return removerLivroInicio(b);
    if (pos == b->totalLivros - 1) return removerLivroFim(b);

    NoLivro* atual = b->primeiro;
    for (int i = 0; i < pos; i++) {
        atual = atual->proximo;
    }

    atual->anterior->proximo = atual->proximo;
    atual->proximo->anterior = atual->anterior;

    free(atual);
    b->totalLivros--;
    return 1;
}

int removerLivroPorISBN(Biblioteca* b, char* isbn) {
    NoLivro* atual = b->primeiro;
    while (atual != NULL) {
        if (strcmp(atual->livro.isbn, isbn) == 0) {
            if (atual == b->primeiro)
                return removerLivroInicio(b);
            if (atual == b->ultimo)
                return removerLivroFim(b);

            atual->anterior->proximo = atual->proximo;
            atual->proximo->anterior = atual->anterior;
            free(atual);
            b->totalLivros--;
            return 1;
        }
        atual = atual->proximo;
    }
    return 0;
}

void listarTodosLivrosFrente(Biblioteca* b) {
    NoLivro* atual = b->primeiro;
    while (atual != NULL) {
        printf("%s - %s - %d - %s [%s]\n",
               atual->livro.titulo,
               atual->livro.autor,
               atual->livro.ano,
               atual->livro.isbn,
               atual->livro.status == DISPONIVEL ? "Disponivel" : "Emprestado");
        atual = atual->proximo;
    }
}

void listarTodosLivrosTras(Biblioteca* b) {
    NoLivro* atual = b->ultimo;
    while (atual != NULL) {
        printf("%s - %s - %d - %s [%s]\n",
               atual->livro.titulo,
               atual->livro.autor,
               atual->livro.ano,
               atual->livro.isbn,
               atual->livro.status == DISPONIVEL ? "Disponivel" : "Emprestado");
        atual = atual->anterior;
    }
}

int emprestarLivro(Biblioteca* b, char* isbn, char* usuario, char* data) {
    NoLivro* no = consultarLivroPorISBN(b, isbn);
    if (no != NULL && no->livro.status == DISPONIVEL) {
        no->livro.status = EMPRESTADO;
        strcpy(no->livro.usuario, usuario);
        strcpy(no->livro.dataEmprestimo, data);
        return 1;
    }
    return 0;
}

int devolverLivro(Biblioteca* b, char* isbn) {
    NoLivro* no = consultarLivroPorISBN(b, isbn);
    if (no != NULL && no->livro.status == EMPRESTADO) {
        no->livro.status = DISPONIVEL;
        no->livro.usuario[0] = '\0';
        no->livro.dataEmprestimo[0] = '\0';
        return 1;
    }
    return 0;
}

NoLivro* consultarLivroPorISBN(Biblioteca* b, char* isbn) {
    NoLivro* atual = b->primeiro;
    while (atual != NULL) {
        if (strcmp(atual->livro.isbn, isbn) == 0) {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}

void destruirBiblioteca(Biblioteca* b) {
    NoLivro* atual = b->primeiro;
    while (atual != NULL) {
        NoLivro* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    b->primeiro = NULL;
    b->ultimo = NULL;
    b->totalLivros = 0;
}
