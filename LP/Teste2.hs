v=[1..50]
v1=[1..10]
v2=[3,6,4,8,1,9,7]
nomes=["freddy mercury","antonio banderas","zorro","zebra"]
p12= ["abcdef", "aaabbbccc abc abc", "aaaa", "bbb"]
pl= [(3, 4), (2, 2), (3, 1), (7, 0)]
pl2= [(3,2),(4,5),(6,3),(8,7),(2,4)]
pk="aabbccccdeedff"
pk2="abcabcaabbcc"
m= [1, 2, 3, 4, 5]
m2= [0, 2, 6, 7]
md=  [1,2,1,1,2,1,0,1,2,1,1]



fat 0 = 1
fat x = x * fat(x-1)

doubleUs x y = x*2 + y*2

doubleMe x = x + x

doubleSmallNumber x = if x > 100 then x else x*2

doubleSmallNumber' x = (if x > 100 then x else x*2)+1

conanO'Brien = "Este sou eu, Conan O'Brien!"



del_posicao_n::[Int] -> Int -> [Int]--Exercicio 1
del_posicao_n lista n = (take (n-1)lista) ++ (drop n lista)



impares:: [Int] -> [Int] -- Exercicio 2
impares xs = quicksort ([ x | x <- xs, even (x+1)])

quicksort :: (Ord a) => [a] -> [a]
quicksort [] = []
quicksort (x:xs) =
    let menor = quicksort [a | a <- xs, a <= x]
        maior = quicksort [a | a <- xs, a > x]
    in  menor ++ [x] ++ maior


fib:: Int -> Int --Exercicio 3
fib 0 = 1
fib 1 = 1
fib x = fib(x-1)+fib(x-2)


intersec:: [Int] -> [Int] -> [Int] -- Exercicio 6
intersec x y = [xs | xs<-x, (elem xs y)]

busca_sub:: String -> [String] -> [String] --Exercicio 7

busca [] y = True
busca x y
 |(head x == head y) = busca (tail x) (tail y)
 |otherwise = False

busca_sub xs [] = []
busca_sub [] ys = []
busca_sub xs (cab:corpo)
 |(busca xs cab) = cab:(busca_sub xs corpo)
 |otherwise = busca_sub xs corpo

repete:: Int -> [Int]--Exercicio 8
repete 0 = []
repete x = take x (repeat x) ++ repete(x-1)

palindromo:: [Int] -> Bool--Exercicio 9
palindromo [_] = True
palindromo [] = True
palindromo (cab:corpo)
 | cab == (last corpo) = palindromo (init corpo)
 | otherwise = False

palindromo1 y -- Exercicio 9.2
 |y == reverse y = True
 |otherwise = False

rodaesquerda 0 y = y--Exercicio 10
rodaesquerda x [] = [] 
rodaesquerda x (cab:corpo) = rodaesquerda (x-1) (corpo ++ [cab])

inverte x = reverse x -- Exercicio 11

ocorrencias:: String -> [String] -> Int--Exercicio 12
ocorrencias x [] = 0
ocorrencias x (cab:corpo)
 |x == cab = 1 +  ocorrencias x corpo
 |otherwise = ocorrencias x corpo

limites l = limites_aux l (maxBound :: Int) 0--Exercicio 13 
limites_aux [] min max = (min, max)
limites_aux (cab:corpo) min1 max1 = limites_aux corpo (min cab min1) (max cab max1)

limites1 l = limites_aux1 l (maxBound :: Int) 0--Exercicio 13.1 
limites_aux1 [] min max = (min, max)
limites_aux1 l min max = (maximum l, minimum l)

somaQuadrados 0 = 0--Exercicio 15
somaQuadrados x = x*x + somaQuadrados (x-1)

filaInsere lista x = lista++[x]--Exercicio 16
filaRemov [] = []
filaRemov lista = tail lista
filaTam [] = 0
filaTam lista = 1 + filaTam(tail lista)

pilhaInsere lista x = [x] ++ lista--Exercicio 17
pilhaRemov [] = []
pilhaRemov lista = tail lista
pilhaTam [] = 0
pilhaTam lista = 1 + pilhaTam (tail lista)

um_poli tupla [] = [tupla] 
um_poli tupla lista
 |(snd tupla == snd(head lista)) = ( (fst tupla+fst(head lista)) , snd(head lista)):(tail lista)
 |otherwise = (head lista):um_poli tupla (tail lista)

junta_poli [] y = y -- Exercicio 19 a
junta_poli x y = junta_poli (tail x) (um_poli (head x) y)

calcula_poli x [] = 0-- b
calcula_poli x (cab:corpo) = (fst cab)*(x^ (snd cab)) + calcula_poli x corpo

somatorio li ls funct --Exercicio 21
 | (li<=ls) = funct li + somatorio (li+1) ls funct
 | otherwise = 0

merge [] y = []
merge x [] = []
merge (cab:corpo) (cab1:corpo1) -- Exercicio 22
 | (cab<=cab1) = cab:merge corpo (cab1:corpo1)
 | otherwise = cab1:merge (cab:corpo) corpo1

dic_10 = [(0, "zero"), (1, "um"), (2, "dois"), (3,"tres"), (4, "quatro"), (5,"cinco"),(6,"seis"), (7,"sete"), (8,"oito"), (9, "nove")] 

tradutor2 x dic
 | x == (fst (head dic)) = snd(head dic)
 | otherwise = tradutor2 x (tail dic)

tradutor [] dic = [] -- Exercicio 23
tradutor x dic = tradutor2 (head x) dic:tradutor (tail x) dic

classificados [] = []
classificados x 
 |length x == 1 = x
 |head x == head (tail x)  = ([head x])++(classificados (tail x))
 |otherwise = [head x]

unpack [] = []--Exercicio 25
unpack y = [classificados y]++unpack(drop(length (classificados y)) y)

applylist [] y = []--Exercicio 26
applylist (cab:corpo) y = (cab y):applylist corpo y

mydropwhile x (cab:corpo) --Exercicio 27
 |x cab = mydropwhile x corpo
 |otherwise = (cab:corpo)

ziptest1 x [] = []--Exercicio 28
ziptest1 [] y = []
ziptest1 (cab:corpo) (cab1:corpo1) = [(cab, cab1)] ++ ziptest1 corpo corpo1