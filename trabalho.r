---
title: "Trabalho: Estatística Descritiva"
subtitle: "Probabilidade e Estatística"
author: "fnaufel"
date: "(modificado em `r Sys.Date()`)"
output: 
  html_document:
    toc: true
    toc_depth: 1
    number_sections: false
---

```{r setup, include=FALSE}
knitr::opts_chunk$set(echo = TRUE)
```

---

# Apresentação

Este trabalho contém questões e tarefas de estatística descritiva.

Os itens exigem que você desenvolva e execute código em R para produzir tabelas e gráficos. 

---

# Recursos online

* Site da disciplina: http://www.professores.uff.br/fna/category/probest/

* Livro online sobre visualização de dados (inclui links para documentação de R e diversos pacotes): http://sillasgonzaga.com/material/curso_visualizacao/index.html

  As informações necessárias para você fazer este trabalho estão nos capítulos 1, 2 e 3.

* Livro online sobre Ciência de Dados: https://cdr.ibpad.com.br/index.html

* Dados sobre super-heróis: http://www.professores.uff.br/fna/superhero-set/

---

# Leitura e limpeza dos dados

---

### Carregue os pacotes `tidyverse` e `janitor`. 

Se estes pacotes não estiverem instalados no seu ambiente R, instale-os com `install.packages`.

---

### Baixe e descompacte o [arquivo de dados](http://www.professores.uff.br/fna/superhero-set/).

---

### Importe os dois arquivos para o R. 

Salve o arquivo `super_hero_powers.csv` no objeto `hero_powers` e o arquivo `heroes_information.csv` no objeto `hero_info`. Use também na função `read_csv` o argumento `na = c("", "-", "NA"))` para que linhas com traço ou vazias sejam convertidas para `NA`. Observe as colunas presentes nos *datasets* usando a função `glimpse`.

---

### Use a função `janitor::clean_names()` para limpar os nomes das colunas.

---

### No caso de `hero_info`, remova a primeira coluna.

---

### Em `hero_powers`, converta todas as colunas com exceção da primeira para o tipo `logical`.

---

### Em `hero_info`, na coluna `publisher`, observe quantas editoras diferentes existem no *dataset*. 

Substitua "Marvel Comics" por "Marvel", "DC Comics" por "DC" e todas as outras editoras pelo termo “Outros”. 

Dica: uma das possíveis maneiras de fazer isso é usando uma combinação das funções `dplyr::mutate()` e `dplyr::case_when()`.

---

# Análise exploratória

---

### Em `hero_info`, quais raças (coluna `race`) são exclusivas de cada editora?

---

### Em `hero_info`, quais cores de olhos (coluna `eye_color`) são mais comuns para cada sexo (coluna `gender`)? 

Filtre o top 3 das cores de olhos para cada sexo.

---

### Em `hero_powers`, calcule o percentual de heróis que possui cada habilidade descrita nas colunas. 

Dica: é possível calcular a soma ou percentual de um vetor lógico, pois `TRUE` equivale a 1 e `FALSE` a 0). 
  
Use a função `dplyr::summarise_if` para aplicar a função em todas as colunas cuja classe é `logical`.

---

### Repita o item anterior, usando uma abordagem mais *tidy*. 

Converta o formato do dataframe `hero_powers` para o formato *long*. Ele passará a possuir apenas 3 colunas: `hero_names`, `poder` e `possui_poder` usando a função `tidyr::gather()`. Então, calcule a média da coluna `possui_poder` agrupado pela coluna `poder`.

---

### Junte os dois *dataframes* em um só, chamado `hero`. 

A função a ser usada é `inner_join()`. Pense bem em qual será a ordem dos *dataframes* nos argumentos da função e qual será a chave usada no argumento `by` para unir as duas tabelas.

---

### No *dataframe* `hero`, calcule o percentual de heróis de cada editora que são telepatas.

---

### No *dataframe* `hero`, selecione as colunas `name`, `publisher`, `flight` e `weight`, filtre os heróis que podem voar e retorne os 10 de maior peso.

---

# Gravação dos dados modificados

---

### Salve o *dataframe* chamado `hero` no arquivo `herois_completo.csv` usando a função `readr::write_csv()`.

---

# Gráficos de dispersão (*scatterplots*)

---

### Importe o arquivo salvo `herois_completo.csv` no item anterior. Salve no objeto `herois`.

---

### Faça um gráfico de dispersão da coluna `weight` em função de `height`.

---

### Observe os *outliers* no gráfico. 

Crie um novo *dataframe* sem esses pontos. Isto é, crie um novo *dataframe* chamado `herois_limpo`, filtrando os heróis com peso e altura entre 1 a 500. Use este *dataframe* para todos os próximos items.

---

### Refaça o gráfico de dispersão, atribuindo a cor verde para os pontos.

---

### Refaça o gráfico de dispersão, mapeando a cor dos pontos à variável `publisher`.

---

### Refaça o gráfico de dispersão, mapeando a cor dos pontos à variável `gender`.

---

### Refaça o gráfico de dispersão, mapeando a cor dos pontos à variável `gender` e o formato (*shape*) dos pontos à variável `flight`.

---

### Refaça o gráfico de dispersão, mapeando a cor dos pontos à variável `gender`, o formato (*shape*) dos pontos à variável `flight` e separando o gráfico em subgráficos (*facets*) usando a variável `publisher`.

---

### Refaça o gráfico de dispersão, mapeando a cor dos pontos à variável `flight` e separando o gráfico em subgráficos (*facets*) usando as variáveis `publisher` e `gender`.

---

# Histogramas, gráficos de barras e *boxplots*

---

### Importe o arquivo salvo `herois_completo.csv`. 

Salve no objeto `herois`. Filtre os heróis que possuem peso e altura maior que 0.

---

### Crie um histograma da variável `weight`.

---

### Crie um histograma da variável `height`.

---

### Analise a distribuição da variável `weight` em função da editora dos heróis. Use *boxplots* lado a lado.

---

### Analise a distribuição da variável `height` em função da editora dos heróis. Use *boxplots* lado a lado.

---

### Crie um gráfico de barras mostrando a quantidade de heróis por editora. 

Ordene as barras em ordem descrescente. Acrescente uma camada de texto nas barras mostrando a quantidade exata.

---

### Crie um gráfico de barras mostrando a quantidade de heróis bons, maus ou neutros (variável `alignment`) por editora. 

Use tanto `geom_bar()` como `geom_col()` para isso, usando o argumento `position = position_dodge()` para separar as barras nas editoras.

---

### Repita o item anterior, trocando apenas o parâmetro `position = position_dodge()` para `position = position_fill()` para observar a proporção de personagens bons, maus ou neutros em cada editora.

---

### Use o `dplyr` e o `tidyr` para criar um *dataset* chamado `hero_agg`, que contém a quantidade de poderes agregada por editora e heroi. 

Dica: transforme as colunas de super-poderes em numéricas, converta o *dataframe* para formato tidy, agrupe os dados por editora e heroi e calcule a soma da coluna transformada de poderes.

---

### Faça um gráfico de barras mostrando os 10 heróis de cada editora que possuem mais poderes. 

Dica: use *facets* para separar os heróis de cada editora, usando `scales = "free_y"` e `drop = TRUE`. Inverta os eixos.

---

# Medidas

---

### Importe o arquivo salvo `herois_completo.csv`. 

Salve no objeto `herois`. Filtre os heróis que possuem peso e altura maior que 0.

---

### Em relação à altura dos heróis:

---

#### Qual é a média?
  
---

#### Qual é o desvio padrão?
  
---

#### Quais são os quartis?

---

### Em relação ao peso dos heróis:

---

#### Qual é a média?
  
---

#### Qual é o desvio padrão?
  
---

#### Quais são os quartis?




























