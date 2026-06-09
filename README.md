# Atividade Somativa: Sistema de Manutenção de Contas (PIF)

**Estudante:** Matheus Larré  
**Curso:** Análise e Desenvolvimento de Sistemas (ADS) - CESAR School  
**Disciplina:** Programação Imperativa e Funcional  
**Professor:** Renan Costa Alencar

---

## Sobre a Atividade

Este programa foi desenvolvido como parte de uma das atividades somativas da disciplina de PIF. O objetivo principal é colocar em prática os conceitos de manipulação de arquivos em C, utilizando registros de tamanho fixo em um arquivo binário (`contas.bin`).

## Explicação da Implementação

Para atender aos requisitos do Professor Renan, foquei em utilizar as funções da biblioteca padrão para gerenciar os dados de forma eficiente:

*   **Acesso Aleatório com `fseek`:** No cadastro de clientes, utilizei o `fseek` para calcular a posição exata onde o registro deve ser gravado. Isso permite inserir um cliente em qualquer "índice" do arquivo sem precisar ler tudo antes.
*   **Manipulação do Ponteiro com `rewind`:** Implementei uma função específica para restaurar a leitura (opção 6). Usei o `rewind` para garantir que o ponteiro do arquivo volte ao início, permitindo que a listagem de clientes seja reiniciada corretamente.
*   **Exclusão Lógica:** Na remoção de contas, em vez de deletar o dado fisicamente (o que exigiria reestruturar o arquivo), utilizei uma flag `ativo` dentro da struct. Assim, apenas marcamos a conta como desativada.
*   **Atualização de Dados:** Para atualizar o saldo, o programa localiza o registro, usa o `ftell` para saber onde ele está e o `fseek` para voltar o tamanho de um registro e sobrescrever apenas aquele saldo com `fwrite`.

## Como Executar

O projeto foi configurado para ser executado diretamente pelo terminal, mantendo o diretório limpo e focado no código-fonte.

1.  **Compilação:**
    ```bash
    gcc main.c -o sistema_contas
    ```
2.  **Execução:**
    ```bash
    ./sistema_contas
    ```

---
*Desenvolvido para fins acadêmicos.*
