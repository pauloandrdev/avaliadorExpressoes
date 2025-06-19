# Avaliador de Expressões Matemáticas

Este projeto implementa um avaliador de expressões matemáticas em C, capaz de processar expressões na notação infixa e convertê-las para notação pós-fixa (polonesa reversa), além de calcular seus valores.

## Funcionalidades

- **Conversão de notação**: Infixa ↔ Pós-fixa
- **Cálculo de expressões**: Avaliação automática de expressões matemáticas
- **Funções matemáticas**: Suporte para funções trigonométricas e logarítmicas
- **Operadores**: +, -, *, /, %, ^ (potenciação)

### Funções Suportadas

- `sen` - Seno (ângulo em graus)
- `cos` - Cosseno (ângulo em graus)
- `tg` - Tangente (ângulo em graus)
- `log` - Logaritmo base 10
- `raiz` - Raiz quadrada

## Como Compilar

```bash
gcc expressao.c main.c -o expressao.exe -lm
```

## Como Executar

```bash
./expressao.exe
```

## Exemplos de Uso

### Expressões Simples
- `2 + 3 * 4` → Resultado: 14
- `(2 + 3) * 4` → Resultado: 20

### Expressões com Funções
- `sen 30 + cos 60` → Resultado: 0.51
- `raiz 16` → Resultado: 4
- `log 100` → Resultado: 2

## Estrutura do Projeto

- `expressao.h` - Cabeçalho com definições e protótipos
- `expressao.c` - Implementação das funções de avaliação
- `main.c` - Programa principal de exemplo
- `README.md` - Documentação do projeto

## Algoritmo

O projeto utiliza o algoritmo Shunting Yard para converter expressões infixas em pós-fixas, seguido da avaliação usando pilhas para processar os operadores e operandos na ordem correta.

## Autor

Paulo André - [GitHub](https://github.com/pauloandrdev) 