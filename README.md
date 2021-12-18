# Compiladores

## Integrantes da equipe

- João Victor de Alarcão Ayalla Alcântara
- Ascânio Sávio de Araujo Neves
- Jackson Barbosa da Silva

## Instruções do makefile

Para realizar a compilação e gerar o executavel 'analyzer', basta rodar o seguinte comando:

```o
make
```

Após gerar o executavel, pode-se rodar alguns exemplos com os códigos fontes localizados na pasta 'Samples'.

- Ola mundo: `make hello`
- Fibonacci: `make fib`
- Shell Sort: `make shell`

Com os comandos acima, a saída será exibida em seu terminal. Para que seja gerado um arquivo com a saída, pode-se rodar os seguintes comandos:

- Ola mundo: `make hello-outfile`
- Fibonacci: `make fib-outfile`
- Shell Sort: `make shell-outfile`

Com isso, será criado um arquivo na pasta 'Outputs' com o nome do exemplo e a extensão '.out'.
