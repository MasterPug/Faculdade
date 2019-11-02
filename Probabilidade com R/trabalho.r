---
title: "Trabalho: Estatística Descritiva"
subtitle: "Probabilidade e Estatística"
author: "Ruan"
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
```{r}
library("tidyverse")
library("janitor")
```
---

### Baixe e descompacte o [arquivo de dados](http://www.professores.uff.br/fna/superhero-set/).

---

### Importe os dois arquivos para o R. 

Salve o arquivo `super_hero_powers.csv` no objeto `hero_powers` e o arquivo `heroes_information.csv` no objeto `hero_info`. Use também na função `read_csv` o argumento `na = c("", "-", "NA"))` para que linhas com traço ou vazias sejam convertidas para `NA`. Observe as colunas presentes nos *datasets* usando a função `glimpse`.*feito*

```{r}
hero_powers <- read_csv("super_hero_powers.csv", na = c("", "-", "NA"))
hero_info <- read_csv("heroes_information.csv", na = c("", "-", "NA"))
glimpse(hero_powers)
glimpse(hero_info)
```
---
### Use a função `janitor::clean_names()` para limpar os nomes das colunas.*feito*  
```{r}
janitor::clean_names(hero_info)
janitor::clean_names(hero_powers)
```
---

### No caso de `hero_info`, remova a primeira coluna.*feito*
```{r}
hero_info$X <- NULL
hero_info
```
---

### Em `hero_powers`, converta todas as colunas com exceção da primeira para o tipo `logical`.
#já está em tipo logical

---

### Em `hero_info`, na coluna `publisher`, observe quantas editoras diferentes existem no *dataset*. 

```{r}
hero_info %>% distinct(Publisher) %>% count(Publisher) %>% filter(Publisher != "NA") %>% nrow()
```
Substitua "Marvel Comics" por "Marvel", "DC Comics" por "DC" e todas as outras editoras pelo termo “Outros”. 

```{r}
hero_info = hero_info %>% mutate(Publisher = case_when(Publisher == "Marvel Comics" ~ "Marvel", Publisher == "DC Comics" ~ "DC",TRUE ~ "Outros"))
hero_info
```
Dica: uma das possíveis maneiras de fazer isso é usando uma combinação das funções `dplyr::mutate()` e `dplyr::case_when()`.

---

# Análise exploratória

---
*Feito*
### Em `hero_info`, quais raças (coluna `race`) são exclusivas de cada editora?

```{r}
exclusive_races = hero_info %>% select(name,Race,Publisher) %>% group_by(Race) %>% filter(n_distinct(Publisher)==1)
exclusive_races
```
---

### Em `hero_info`, quais cores de olhos (coluna `eye_color`) são mais comuns para cada sexo (coluna `gender`)? 
Filtre o top 3 das cores de olhos para cada sexo.

```{r}
hero_info2 = hero_info %>% group_by(Gender , `Eye color`) %>%  count(`Eye color`) %>% filter(Gender != "NA",`Eye color` != "NA") %>% arrange(desc(n ))
male_color = hero_info2 %>% filter(Gender == "Male") %>% head(3)
female_color = hero_info2 %>%  filter(Gender == "Female") %>% head(3)
male_color
female_color
```

---

### Em `hero_powers`, calcule o percentual de heróis que possui cada habilidade descrita nas colunas. 

Dica: é possível calcular a soma ou percentual de um vetor lógico, pois `TRUE` equivale a 1 e `FALSE` a 0). 
  
Use a função `dplyr::summarise_if` para aplicar a função em todas as colunas cuja classe é `logical`.

```{r}
percentual = hero_powers %>% dplyr::summarise_if(is.logical,sum) %>% mutate_all(function(x) x/nrow(hero_powers)*100)
percentual
```
---

### Repita o item anterior, usando uma abordagem mais *tidy*. 

Converta o formato do dataframe `hero_powers` para o formato *long*. Ele passará a possuir apenas 3 colunas: `hero_names`, `poder` e `possui_poder` usando a função `tidyr::gather()`. Então, calcule a média da coluna `possui_poder` agrupado pela coluna `poder`.
*Conferir dps*
```{r}
long_powers = hero_powers %>% gather(Poder, value = "possui_poder", -hero_names) %>% group_by(Poder) %>% count(possui_poder) %>% filter(possui_poder == TRUE) %>%  mutate(novo = n/667)
long_powers
```

---
### Junte os dois *dataframes* em um só, chamado `hero`. 

A função a ser usada é `inner_join()`. Pense bem em qual será a ordem dos *dataframes* nos argumentos da função e qual será a chave usada no argumento `by` para unir as duas tabelas.

```{r}
teste <- hero_powers %>% mutate(name = hero_names)
teste$hero_names <- NULL
hero <- dplyr::inner_join(hero_info, teste, by = "name")
hero
```
---
### No *dataframe* `hero`, calcule o percentual de heróis de cada editora que são telepatas.
```{r}
marvel_heroes = hero %>% group_by(Publisher) %>% filter(Publisher == "Marvel") %>% count(Publisher)
DC_heroes = hero %>% group_by(Publisher) %>% filter(Publisher == "DC") %>% count(Publisher)
Others_heroes = hero %>% group_by(Publisher) %>% filter(Publisher == "Outros") %>% count(Publisher)
marvel_telepathy = hero %>% group_by(Publisher) %>% filter(Publisher == "Marvel") %>% count(Telepathy)
DC_telepathy = hero %>% group_by(Publisher) %>% filter(Publisher == "DC") %>% count(Telepathy)
Others_telepathy = hero %>% group_by(Publisher) %>% filter(Publisher == "Outros") %>% count(Telepathy)
DC = DC_telepathy %>% mutate(Dc = (n/DC_heroes$n)*100) %>% filter(Telepathy == TRUE)
Marvel <- marvel_telepathy %>% mutate(Marvel = (n/marvel_heroes$n) *100) %>% filter(Telepathy == TRUE)
Others <- Others_telepathy %>% mutate(Others = (n/Others_heroes$n) *100) %>% filter(Telepathy == TRUE)
DC
Marvel
Others
```
---
### No *dataframe* `hero`, selecione as colunas `name`, `publisher`, `flight` e `weight`, filtre os heróis que podem voar e retorne os 10 de maior peso.
```{r}
hero %>% select(name, Publisher, Flight, Weight) %>% filter(Flight == TRUE) %>% arrange(desc(Weight)) %>% head(10)
```
---

# Gravação dos dados modificados

---
### Salve o *dataframe* chamado `hero` no arquivo `herois_completo.csv` usando a função `readr::write_csv()`.
```{r}
readr::write_csv(hero, "herois_completo.csv")
```
---

# Gráficos de dispersão (*scatterplots*)

---
### Importe o arquivo salvo `herois_completo.csv` no item anterior. Salve no objeto `herois`.

---
*Feito*
### Faça um gráfico de dispersão da coluna `weight` em função de `height`.
```{r}
herois %>% filter(Weight != "NA", Height != "NA") %>%  ggplot(aes(x = Weight, y=Height))+geom_point()
```
---
### Observe os *outliers* no gráfico. 
Crie um novo *dataframe* sem esses pontos. Isto é, crie um novo *dataframe* chamado `herois_limpo`, filtrando os heróis com peso e altura entre 1 a 500. Use este *dataframe* para todos os próximos items.

```{r}
herois_limpo = herois %>% filter(Weight != "NA", Weight > 1, Weight < 500  , Height != "NA", Height >1, Height <500)
```
---
### Refaça o gráfico de dispersão, atribuindo a cor verde para os pontos.
```{r}
herois_limpo %>%  ggplot(aes(x = Weight, y=Height))+geom_point(color = "green")
```
---
### Refaça o gráfico de dispersão, mapeando a cor dos pontos à variável `publisher`.
```{r}
herois_limpo %>%  ggplot(aes(x = Weight, y=Height))+geom_point(aes(color = Publisher)) 
```
---
### Refaça o gráfico de dispersão, mapeando a cor dos pontos à variável `gender`.
```{r}
herois_limpo %>%  ggplot(aes(x = Weight, y=Height))+geom_point(aes(color = Gender)) 
```
---
### Refaça o gráfico de dispersão, mapeando a cor dos pontos à variável `gender` e o formato (*shape*) dos pontos à variável `flight`.
```{r}
herois_limpo %>%  ggplot(aes(x = Weight, y=Height))+geom_point(aes(color = Gender, shape=Flight)) 
```
---
### Refaça o gráfico de dispersão, mapeando a cor dos pontos à variável `gender`, o formato (*shape*) dos pontos à variável `flight` e separando o gráfico em subgráficos (*facets*) usando a variável `publisher`.
```{r}
herois_limpo %>% ggplot(aes(x = Weight, y=Height))+geom_point(aes(color = Gender, shape = Flight ))+facet_wrap(~Publisher) 
```
---
### Refaça o gráfico de dispersão, mapeando a cor dos pontos à variável `flight` e separando o gráfico em subgráficos (*facets*) usando as variáveis `publisher` e `gender`.
```{r}
herois_limpo %>% ggplot(aes(x = Weight, y=Height))+geom_point(aes(color = Gender, shape = Flight ))+facet_grid(Publisher ~ gender) 
```
---

# Histogramas, gráficos de barras e *boxplots*

---

### Importe o arquivo salvo `herois_completo.csv`. 
Salve no objeto `herois`. Filtre os heróis que possuem peso e altura maior que 0.
```{r}
herois = read_csv("herois_completo.csv")
herois = herois %>% filter(Height > 0, Weight > 0, Weight != "NA", Height != "NA" )
```
---
### Crie um histograma da variável `weight`.
```{r}
herois %>% ggplot(aes(x = Weight))+ geom_histogram()
```
---
### Crie um histograma da variável `height`.
```{r}
herois %>% ggplot(aes(x = Height))+ geom_histogram()
```
---

### Analise a distribuição da variável `weight` em função da editora dos heróis. Use *boxplots* lado a lado.
```{r}
herois %>% ggplot(aes(x = Publisher, y = Weight))+ geom_boxplot()
```
---
### Analise a distribuição da variável `height` em função da editora dos heróis. Use *boxplots* lado a lado.
```{r}
herois %>% ggplot(aes(x = Publisher, y = Height))+ geom_boxplot()
```
---
### Crie um gráfico de barras mostrando a quantidade de heróis por editora. 
Ordene as barras em ordem descrescente. Acrescente uma camada de texto nas barras mostrando a quantidade exata.
```{r}
herois %>% group_by(Publisher) %>% count(Publisher) %>% ggplot(aes(x = reorder(Publisher,-n), y = n),y = count(Publisher)) + geom_col() + geom_label(aes(label = (n)))
```
---
1/2 *Feito*
### Crie um gráfico de barras mostrando a quantidade de heróis bons, maus ou neutros (variável `alignment`) por editora. 

Use tanto `geom_bar()` como `geom_col()` para isso, usando o argumento `position = position_dodge()` para separar as barras nas editoras.
```{r}
herois %>% group_by(Publisher,Alignment) %>% count(Alignment) %>% ggplot(aes(fill = Alignment, x = Publisher, y = n)) +geom_col(position = position_dodge()) 
```

---
### Repita o item anterior, trocando apenas o parâmetro `position = position_dodge()` para `position = position_fill()` para observar a proporção de personagens bons, maus ou neutros em cada editora.
```{r}
herois %>% group_by(Publisher,Alignment) %>% count(Alignment) %>% ggplot(aes(fill = Alignment, x = Publisher, y = n)) +geom_col(position = position_fill())
```
---
### Use o `dplyr` e o `tidyr` para criar um *dataset* chamado `hero_agg`, que contém a quantidade de poderes agregada por editora e heroi. 

Dica: transforme as colunas de super-poderes em numéricas, converta o *dataframe* para formato tidy, agrupe os dados por editora e heroi e calcule a soma da coluna transformada de poderes.
```{r}
exclusive <- herois %>% select_at(vars(name,Publisher,Agility:Omniscient))
exclusive <- exclusive %>% gather(power,value = "possui_poder", -name, -Publisher)
exclusive <- exclusive %>% group_by(Publisher,name) %>% count(possui_poder) %>% filter(possui_poder == TRUE) %>% arrange(desc(n))
```
---

### Faça um gráfico de barras mostrando os 10 heróis de cada editora que possuem mais poderes. 

Dica: use *facets* para separar os heróis de cada editora, usando `scales = "free_y"` e `drop = TRUE`. Inverta os eixos.
```{r}
dez_maiores_DC = exclusive %>%  filter(Publisher == "DC") %>%  head(10)
dez_maiores_Marvel = exclusive %>%  filter(Publisher == "Marvel") %>%  head(10)
dez_maiores_Outros = exclusive %>%  filter(Publisher == "Outros") %>%  head(10)

ggplot() + geom_bar(data=dez_maiores_DC, aes(x=n, y=name),fill="black",stat="identity") + geom_bar(data=dez_maiores_Marvel, aes(x=n, y=name), fill="red",stat="identity") + geom_bar(data=dez_maiores_Outros, aes(x=n,y=name),fill="blue",stat="identity")+facet_wrap(~Publisher,drop = TRUE, scales = "free_y")
```

---

# Medidas

---

### Importe o arquivo salvo `herois_completo.csv`. 

Salve no objeto `herois`. Filtre os heróis que possuem peso e altura maior que 0.


---
### Em relação à altura dos heróis:

---

#### Qual é a média?
```{r}
media_height = mean(herois$Height)
media_height
```
---
#### Qual é o desvio padrão?
```{r}
desvio_a = sd(herois$Height)
desvio_a
```
---

#### Quais são os quartis?
```{r}
quartis = summary(herois$Height)
quartis
```
---

### Em relação ao peso dos heróis:

---

#### Qual é a média?
```{r}
media_Weight = mean(herois$Weight)
media_weight
```
--- 

#### Qual é o desvio padrão?
```{r}
desvio_p = sd(herois$Weight)
desvio_p
```
---

#### Quais são os quartis?
```{r}
quartis_p = summary(herois$Weight)
quartis_p
```



























