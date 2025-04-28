#include <stdio.h>
#include <string.h>
#include "lista_dupla.h"

int main() {
    Biblioteca b;
    inicializarBiblioteca(&b);

    cadastrarLivro(&b, "Dom Quixote", "Miguel de Cervantes", 1605, "ISBN0001");
    cadastrarLivro(&b, "1984", "George Orwell", 1949, "ISBN0002");
    cadastrarLivro(&b, "A Revolucao dos Bichos", "George Orwell", 1945, "ISBN0003");
    cadastrarLivro(&b, "O Pequeno Principe", "Antoine de Saint-Exupery", 1943, "ISBN0004");
    cadastrarLivro(&b, "O Senhor dos Aneis", "J.R.R. Tolkien", 1954, "ISBN0005");

    int opcao;
    char titulo[MAX_TITULO], autor[MAX_AUTOR], isbn[MAX_ISBN], usuario[MAX_USUARIO], data[MAX_DATA];
    int ano, pos;

    do {
        printf("\n==== MENU BIBLIOTECA (Lista Duplamente Encadeada) ====\n");
        printf("1. Cadastrar livro no fim\n");
        printf("2. Inserir livro no inicio\n");
        printf("3. Inserir livro em posicao especifica\n");
        printf("4. Consultar livro por ISBN\n");
        printf("5. Emprestar livro\n");
        printf("6. Devolver livro\n");
        printf("7. Remover livro do inicio\n");
        printf("8. Remover livro do fim\n");
        printf("9. Remover livro em posicao especifica\n");
        printf("10. Remover livro por ISBN\n");
        printf("11. Listar livros da frente para tras\n");
        printf("12. Listar livros de tras para frente\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // limpar buffer

        switch(opcao) {
            case 1:
                printf("Titulo: ");
                fgets(titulo, MAX_TITULO, stdin);
                titulo[strcspn(titulo, "\n")] = 0;

                printf("Autor: ");
                fgets(autor, MAX_AUTOR, stdin);
                autor[strcspn(autor, "\n")] = 0;

                printf("Ano: ");
                scanf("%d", &ano);
                getchar();

                printf("ISBN: ");
                fgets(isbn, MAX_ISBN, stdin);
                isbn[strcspn(isbn, "\n")] = 0;

                if (cadastrarLivro(&b, titulo, autor, ano, isbn))
                    printf("Livro cadastrado com sucesso no fim!\n");
                else
                    printf("Erro ao cadastrar livro (ISBN ja existe?).\n");
                break;

            case 2:
                printf("Titulo: ");
                fgets(titulo, MAX_TITULO, stdin);
                titulo[strcspn(titulo, "\n")] = 0;

                printf("Autor: ");
                fgets(autor, MAX_AUTOR, stdin);
                autor[strcspn(autor, "\n")] = 0;

                printf("Ano: ");
                scanf("%d", &ano);
                getchar();

                printf("ISBN: ");
                fgets(isbn, MAX_ISBN, stdin);
                isbn[strcspn(isbn, "\n")] = 0;

                {
                    Livro novo;
                    strcpy(novo.titulo, titulo);
                    strcpy(novo.autor, autor);
                    novo.ano = ano;
                    strcpy(novo.isbn, isbn);
                    novo.status = DISPONIVEL;
                    novo.usuario[0] = '\0';
                    novo.dataEmprestimo[0] = '\0';

                    if (inserirLivroInicio(&b, novo))
                        printf("Livro inserido no inicio com sucesso!\n");
                    else
                        printf("Erro ao inserir livro no inicio.\n");
                }
                break;

            case 3:
                printf("Titulo: ");
                fgets(titulo, MAX_TITULO, stdin);
                titulo[strcspn(titulo, "\n")] = 0;

                printf("Autor: ");
                fgets(autor, MAX_AUTOR, stdin);
                autor[strcspn(autor, "\n")] = 0;

                printf("Ano: ");
                scanf("%d", &ano);
                getchar();

                printf("ISBN: ");
                fgets(isbn, MAX_ISBN, stdin);
                isbn[strcspn(isbn, "\n")] = 0;

                printf("Posicao (0 para inicio): ");
                scanf("%d", &pos);
                getchar();

                {
                    Livro novo;
                    strcpy(novo.titulo, titulo);
                    strcpy(novo.autor, autor);
                    novo.ano = ano;
                    strcpy(novo.isbn, isbn);
                    novo.status = DISPONIVEL;
                    novo.usuario[0] = '\0';
                    novo.dataEmprestimo[0] = '\0';

                    if (inserirLivroNaPosicao(&b, novo, pos))
                        printf("Livro inserido na posicao %d com sucesso!\n", pos);
                    else
                        printf("Erro ao inserir livro.\n");
                }
                break;

            case 4:
                printf("ISBN do livro: ");
                fgets(isbn, MAX_ISBN, stdin);
                isbn[strcspn(isbn, "\n")] = 0;

                {
                    NoLivro* no = consultarLivroPorISBN(&b, isbn);
                    if (no)
                        printf("%s | %s | %d | %s | %s\n",
                               no->livro.titulo,
                               no->livro.autor,
                               no->livro.ano,
                               no->livro.isbn,
                               no->livro.status == DISPONIVEL ? "Disponivel" : "Emprestado");
                    else
                        printf("Livro nao encontrado.\n");
                }
                break;

            case 5:
                printf("ISBN do livro: ");
                fgets(isbn, MAX_ISBN, stdin);
                isbn[strcspn(isbn, "\n")] = 0;

                printf("Usuario: ");
                fgets(usuario, MAX_USUARIO, stdin);
                usuario[strcspn(usuario, "\n")] = 0;

                printf("Data (DD/MM/AAAA): ");
                fgets(data, MAX_DATA, stdin);
                data[strcspn(data, "\n")] = 0;

                if (emprestarLivro(&b, isbn, usuario, data))
                    printf("Livro emprestado com sucesso!\n");
                else
                    printf("Nao foi possivel emprestar o livro (nao encontrado ou ja emprestado).\n");
                break;

            case 6:
                printf("ISBN do livro: ");
                fgets(isbn, MAX_ISBN, stdin);
                isbn[strcspn(isbn, "\n")] = 0;

                if (devolverLivro(&b, isbn))
                    printf("Livro devolvido com sucesso!\n");
                else
                    printf("Nao foi possível devolver o livro.\n");
                break;

            case 7:
                if (removerLivroInicio(&b))
                    printf("Livro removido do inicio com sucesso!\n");
                else
                    printf("Erro ao remover livro do inicio.\n");
                break;

            case 8:
                if (removerLivroFim(&b))
                    printf("Livro removido do fim com sucesso!\n");
                else
                    printf("Erro ao remover livro do fim.\n");
                break;

            case 9:
                printf("Posicao a remover: ");
                scanf("%d", &pos);
                getchar();

                if (removerLivroNaPosicao(&b, pos))
                    printf("Livro removido da posicao %d com sucesso!\n", pos);
                else
                    printf("Erro ao remover livro da posicao.\n");
                break;

            case 10:
                printf("ISBN do livro a remover: ");
                fgets(isbn, MAX_ISBN, stdin);
                isbn[strcspn(isbn, "\n")] = 0;

                if (removerLivroPorISBN(&b, isbn))
                    printf("Livro removido com sucesso!\n");
                else
                    printf("Erro ao remover livro por ISBN.\n");
                break;

            case 11:
                printf("\nListando livros da frente para tras:\n");
                listarTodosLivrosFrente(&b);
                break;

            case 12:
                printf("\nListando livros de tras para frente:\n");
                listarTodosLivrosTras(&b);
                break;

            case 0:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
        }

    } while (opcao != 0);

    destruirBiblioteca(&b);
    return 0;
}
