#ifndef LISTA_DUPLA_H
#define LISTA_DUPLA_H

#define MAX_TITULO 100
#define MAX_AUTOR 100
#define MAX_ISBN 14
#define MAX_USUARIO 100
#define MAX_DATA 11

typedef enum {
    DISPONIVEL,
    EMPRESTADO
} StatusLivro;

typedef struct {
    char titulo[MAX_TITULO];
    char autor[MAX_AUTOR];
    int ano;
    char isbn[MAX_ISBN];
    StatusLivro status;
    char usuario[MAX_USUARIO];
    char dataEmprestimo[MAX_DATA];
} Livro;

typedef struct NoLivro {
    Livro livro;
    struct NoLivro* proximo;
    struct NoLivro* anterior;
} NoLivro;

typedef struct {
    NoLivro* primeiro;
    NoLivro* ultimo;
    int totalLivros;
} Biblioteca;

// Funções disponíveis
void inicializarBiblioteca(Biblioteca* b);
int cadastrarLivro(Biblioteca* b, char* titulo, char* autor, int ano, char* isbn);
int inserirLivroInicio(Biblioteca* b, Livro livro);
int inserirLivroFim(Biblioteca* b, Livro livro);
int inserirLivroNaPosicao(Biblioteca* b, Livro livro, int pos);
int removerLivroInicio(Biblioteca* b);
int removerLivroFim(Biblioteca* b);
int removerLivroNaPosicao(Biblioteca* b, int pos);
int removerLivroPorISBN(Biblioteca* b, char* isbn);
void listarTodosLivrosFrente(Biblioteca* b);
void listarTodosLivrosTras(Biblioteca* b);
int emprestarLivro(Biblioteca* b, char* isbn, char* usuario, char* data);
int devolverLivro(Biblioteca* b, char* isbn);
NoLivro* consultarLivroPorISBN(Biblioteca* b, char* isbn);
void destruirBiblioteca(Biblioteca* b);

#endif
