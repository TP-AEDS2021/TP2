# TP 2 de Algoritmos e estruturas de dados

## Introdução

- ### [O algoritmo de permutação](#o-algoritmo-de-permutação)
- [Introdução](#introdução)
- [TP 2 de Algoritmos e estruturas de dados](#tp-2-de-algoritmos-e-estruturas-de-dados)
- [Módulos <a name="modules"></a>](#módulos-)
    - [UTILS](#utils)
      - [*Funções*](#funções)
    - [Permuta](#permuta)
      - [*Funções*](#funções-1)
- [Comando para compilar o projeto <a name="compilando-o-projeto"></a>](#comando-para-compilar-o-projeto-)
- [Compilar a documentação <a name="compilando-a-documentacao"></a>](#compilar-a-documentação-)
## Módulos <a name="modules"></a>

---
### UTILS
#### *Funções*

| Função | Tipo | Argumentos | Descrição |
|:-------|:-----:|:----------:|:----------:|
| `currentTime()` | `struct tm*` | - | Retorna a hora atual do sistema |
| `menu()` | `void` | - | Mostra o menu principal |
| `debug(int)` | `void` | `int debugindex` | Mostra uma mensagem de debug padrão na cor vermelha na ordem do índice passado |


### Permuta
#### *Funções*

| Função | Tipo | Argumentos | Descrição |
|:-------|:-----:|:----------:|:----------:|
| `nextPerm(int* , int , int)` | `int` | `int* perm, int n, int k` | Retorna o próximo elemento da permutação |


<div style="page-break-before:always">

# O algoritmo de permutação

</div>

<div style="page-break-before:always">

# O arquivo de testes

> O arquivo de teste é um arquivo de texto que contém um numero inteiro positivo N, que define a quantidade de cidades do teste.
>
> Seguido de um numero Q, que define a capacidade de carga do caminhão.
> 
> Seguido de N inteiros que definem a demanda de cada cidade .
>
> e por fim
>
>

```txt
4
5
2 3 4 5
0 1 1 
0 2 3
0 3 1
1 2 3
1 3 2
2 3 4

```

</div>

<div style="page-breake-before:always">

# O funcionamento do programa

> ### Inicia o programa

```
Opcoes:
0 - Sair
1 - Ler arquivo de testes
```
> ### ENTRADA:
>1
>  

> ### SAIDA: 

```
Opcoes:
0 - Sair
1 - Ler arquivo de testes
Digite o nome do arquivo de testes:
>>>
```
 

 > Digite o nome do arquivo a ser lido pelo programa com os valores para teste

```
Opcoes:
0 - Sair
1 - Ler arquivo de testes
Digite o nome do arquivo de testes:
>>> teste.txt
```

  > ### SAIDA:

  ```
  Opcoes:
0 - Sair
1 - Ler arquivo de testes
Digite o nome do arquivo de testes:
>> 001.txt
Arquivo lido com sucesso         (pressione enter para continuar)
```


</div>

--- 

## Comando para compilar o projeto <a name="compilando-o-projeto"></a>


  <b>Usando Makefile:</b>


```bash
make
```
---



## Compilar a documentação <a name="compilando-a-documentacao"></a>

```bash
    make doc
```

- Gera arquivo PDF com o mesmo nome do arquivo markdown (não mudar nome do aquivo .md, crie uma cópia com outro nome e compile a cópia, ou mude o nome do arquivo resultado)

```bash
      md-to-pdf readme.md
```

> - Para gerar o arquivo PDF, é necessário ter instalado o programa `md-to-pdf` , caso não tenha a ferramenta de build de documentação instalada
```bash
      pip install md-to-pdf
      --- ou ---
      npm install md-to-pdf
```