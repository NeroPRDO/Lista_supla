# Lista_Dupla

# 📚 Sistema de Gerenciamento de Biblioteca (Lista Duplamente Encadeada)

Projeto desenvolvido em linguagem C para gerenciar uma biblioteca simples, utilizando uma **lista duplamente encadeada**.

O sistema permite o cadastro de livros, consulta, empréstimo, devolução, remoções, além de exibir os livros da frente para trás e de trás para frente.

---

## 🛠️ Funcionalidades

- Cadastrar novos livros (inserção no início, no fim ou em posição específica)
- Consultar livro por ISBN
- Emprestar livro a um usuário
- Devolver livro emprestado
- Remover livro:
  - Do início
  - Do fim
  - De uma posição específica
  - Por ISBN
- Listar livros:
  - Da frente para trás
  - De trás para frente

---

## 🚀 Como Compilar e Executar

1. Abra o terminal (Prompt de Comando ou PowerShell).
2. Navegue até o diretório onde estão os arquivos `.c` e `.h`.
3. Compile o projeto usando:

gcc -o app_lista_dupla lista_dupla.c main.c

Execute o programa:

./app_lista_dupla    # Linux ou WSL

ou

app_lista_dupla.exe  # Windows (Prompt ou PowerShell)

📁 Organização dos Arquivos

lista_dupla.h — Declarações das estruturas e funções.

lista_dupla.c — Implementação das funções de manipulação da lista duplamente encadeada.

main.c — Programa principal com menu interativo para o usuário.

README.md — Documentação do projeto.

📋 Exemplo de Uso
Ao rodar o programa, será exibido um menu como:

==== MENU BIBLIOTECA (Lista Duplamente Encadeada) ====
1. Cadastrar livro no fim
2. Inserir livro no inicio
3. Inserir livro em posicao especifica
4. Consultar livro por ISBN
5. Emprestar livro
6. Devolver livro
7. Remover livro do inicio
8. Remover livro do fim
9. Remover livro em posicao especifica
10. Remover livro por ISBN
11. Listar livros da frente para tras
12. Listar livros de tras para frente
0. Sair
O usuário poderá interagir com o sistema conforme as opções disponíveis.

ℹ️ Observações
A lista é dinâmica: aloca e libera memória conforme livros são adicionados ou removidos.

Toda memória é liberada corretamente ao final do programa usando destruirBiblioteca.

O ISBN é usado como identificador único dos livros.

Validação simples impede cadastro de ISBNs repetidos.

Este projeto foi feito para fins didáticos no contexto de aprendizagem sobre listas duplamente encadeadas.

📚 Autor
Desenvolvido como parte das atividades da disciplina de Estruturas de Dados — UFPR.
