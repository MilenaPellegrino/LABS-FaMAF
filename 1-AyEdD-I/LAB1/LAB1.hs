
{- PROYECTO DE LABORATORIO 1 

Programacion con haskell 
Creacion de funciones

Ejercicio 1
A) 
-}
esCero :: Int -> Bool 
esCero x = x == 0

{-
EJEMPLOS
ghci> esCero 3
False

ghci> esCero 0 
True 

-}

-- B) 
esPositivo :: Int -> Bool
esPositivo x = x > 0

{-
EJEMPLOS
ghci> esPositivo 560
True

ghci> esPositivo 0 
False

ghci> esPositivo (-32)
False
-}

-- C) 
esVocal :: Char -> Bool
esVocal c =  (c == 'a') || (c == 'e') || (c == 'i') || (c == 'o') || (c == 'u') 

{-
EJEMPLOS
ghci> esVocal 'x'
False

ghci> esVocal 'A'
False

ghci> esVocal 'e'
True
-}

-- D)  
valorAbsoluto :: Int -> Int
valorAbsoluto x | x>=0 = x 
                | otherwise = x * (-1)

{-
EJEMPLOS
ghci> valorAbsoluto 3
3

ghci> valorAbsoluto (-352)
352

ghci> valorAbsoluto 0
0
-}

-- EJERCICIO 2 

-- A)        
paraTodo :: [Bool] -> Bool 
paraTodo [] = True
paraTodo (x:xs) = x == True && paraTodo xs

{-
EJEMPLOS
ghci> paraTodo [True, False, True, False]
False

ghci> paraTodo [True, True, True]
True

ghci> paraTodo [False, False, False]
False
-}

-- B) 
sumatoria :: [Int] -> Int
sumatoria [] = 0 
sumatoria (x:xs) = x + sumatoria xs

{-
EJEMPLOS
ghci> sumatoria [1, 2, 3, 5]
11

ghci> sumatoria [5, -8, -10, 10, 3]
0

ghci> sumatoria [-9, 8, -4, 5, -7]
-7
-}

-- C)
productoria :: [Int] -> Int
productoria [] = 1 
productoria (x:xs) = x * productoria xs

{-
EJEMPLOS
ghci> productoria [1, 2, 3, 4, 5]
120

ghci> productoria [2, 4, 1]
8
-}

-- D) 
factorial :: Int -> Int
factorial 0 = 1 
factorial n = n * factorial (n - 1)

{-
EJEMPLOS
ghci> factorial 5
120

ghci> factorial 10
3628800

ghci> factorial 0
1
-}

-- E) 
promedio :: [Int] -> Int
promedio xs =  (sumatoria xs) `div` (length (xs)) 

{-
EJEMPLOS
ghci> promedio [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
5

ghci> promedio [10, 56, -49, 90, 10]
23

ghci> promedio [10, 20, 30, 40, 50]
30
-}

-- EJERCICIO 3 

pertenece :: Int -> [Int] -> Bool
pertenece n [] = False
pertenece n (x:xs) = n == x || pertenece n xs

{-
EJEMPLOS
ghci> pertenece 5 [1, 2, 3, 4, 5] 
True

ghci> pertenece  709 [100, 200, 300, 400]
False
-}

-- EJERCICIO 4 

-- A) 
paraTodo' :: [a] -> (a -> Bool) -> Bool
paraTodo' [] t = True
paraTodo' (x:xs) t = t x && paraTodo' xs t 

{-
EJEMPLOS
ghci> paraTodo' [1, 2, 3, 4] esCero
False

ghci> paraTodo' "FaMAF" esVocal
False

ghci> paraTodo' [1, 2, 3, 4, 5] esPositivo 
True
-}

--B)  
existe' :: [a] -> (a -> Bool) -> Bool
existe' [] t = False
existe' (x:xs) t = t x || existe' xs t 

{-
EJEMPLOS
ghci> existe' [0, 1, 2, 3, 4, 5] esCero
True

ghci> existe' "Estudia en FaMAFF" esVocal
True

ghci> existe' [-1, -8, -9, -10] esPositivo
False
-}

-- C) 
sumatoria' :: [a] -> (a -> Int) -> Int  
sumatoria'[] t = 0 
sumatoria'(x:xs) t = t x + sumatoria' xs t 

{-
EJEMPLOS
ghci> sumatoria' [-2, -1, 0, 1, 2] valorAbsoluto 
6

ghci> sumatoria' [[10, 20, 30], [100, 200, 300], [1, 2, 3, 4, 5]] promedio 
223

ghci> sumatoria' [[10, 20, 30], [1, 2, 3, 4], [90, 1000, 0]] productoria
6024
-}

-- D)  
productoria' :: [a] -> (a -> Int) -> Int
productoria' [] t = 1 
productoria' (x:xs) t = t x * productoria' xs t 

{-
EJEMPLOS
ghci> productoria' [1, 2, 3, -4, -5, -6] valorAbsoluto 
720

ghci> productoria' [[10, 20, 30], [1, 2, 3, 4, 5]] promedio
60

ghci> productoria' [[1, 2, 3], [10, 20, 30], [1, -1, 0]] sumatoria
0
-}

paraTodo3 :: [Bool] -> Bool
paraTodo3 xs = paraTodo' xs (==True)

{-
EJEMPLOS 
ghci> paraTodo3 [True, False, True] 
False

ghci> paraTodo3 [False, False, False] 
False

ghci> paraTodo3 [True, True, True] 
True

-}

-- EJERCICIO 6

-- Funcion auxiliar ejercicio 6. a) 
-- Verifica si un numero es par. 

esPar :: Int -> Bool
esPar x = (mod x 2) == 0

{-
EJEMPLOS
ghci> esPar 10
True

ghci> esPar 3
False

ghci> esPar 19
False

-}
-- A) 
todosPares :: [Int] -> Bool
todosPares xs = paraTodo' xs (esPar)

{-
ACLARACION: En vez de crear la funcion esPar, haskell ya tiene una funcion
que verifica si un numero es par que es "even". Con lo cual tambien
lo podriamos haber usado y ahorrarnos el paso de crear una funcion auxiliar.
-}

{-
EJEMPLOS
ghci> todosPares [2, 4, 6, 8]
True

ghci> todosPares [1, 2, 3, 4, 5]
False 

ghci> todosPares [1, 3, 5, 7, 9]
False

-}

-- Funcion auxiliar ejercicio 6. b)
-- Verifica si un numero es multiplo de otro 

esMultiplo :: Int -> Int -> Bool 
esMultiplo x y = (mod x y) == 0 

{-
EJEMPLOS
ghci> esMultiplo  10 2
True

ghci> esMultiplo 2 10
False
 
ghci> esMultiplo 9 3
True

-}

-- B) 
hayMultiplo :: Int -> [Int] -> Bool
hayMultiplo x xs = existe' xs (esMultiplo x)

{-

EJEMPLOS
ghci> hayMultiplo 3 [1, 2, 3, 4, 5, 6, 7, 8, 9]
True

ghci> hayMultiplo 10 [3, 4, 6, 7] 
False

ghci> hayMultiplo 2 [3, 4, 5, 6]
False

-}

-- C)
sumaCuadrados :: Int -> Int 
sumaCuadrados x = sumatoria' [0..(x-1)] (^2)

-- Es x-1 ya que en el ejercicio dice menos estricto
{-
EJEMPLOS
ghci> sumaCuadrados 10
285

ghci> sumaCuadrados 4
14

ghci> sumaCuadrados 7
91
-}

-- Funcion adicional ejercicio 6. d) 
-- Verifica si un numero es divisor del otro 

-- D)
divide :: Int -> Int -> Bool
divide x y = (mod x y) == 0 

{-
EJEMPLOS

ghci> divide 2 10
False 

ghci> divide 10 2
True

ghci> divide 3 9
False

-}
existeDivisor :: Int -> [Int] -> Bool 
existeDivisor x xs = existe' xs (divide x)

{-
EJEMPLOS
ghci> existeDivisor 2 [11, 3, 9, 7, 10] 
True

ghci> existeDivisor 2 [11, 7, 9]
False

ghci> existeDivisor 3 [3, 5, 9, 9, 10]
True
-}

-- E)
esPrimo :: Int -> Bool
esPrimo n = n> 1 && not (existeDivisor n [2..n-1])

{-
EJEMPLOS
ghci> esPrimo 10
False
 
ghci> esPrimo 997
True

ghci> esPrimo 2
True
 
-}

-- F) 
factorial' :: Int -> Int
factorial' 0 = 1 
factorial' x = productoria' [1..x] id

{-
EJEMPLOS
ghci> factorial' 10
3628800

ghci> factorial' 5
120

ghci> factorial'1
1

-}

-- G) 
-- Funcion auxiliar ejercicio 6. G) 
-- Filtra todos los numeros primos de una lista 

filtrarPrimos :: [Int] -> [Int]
filtrarPrimos [] = []
filtrarPrimos (x:xs) | esPrimo x = x : filtrarPrimos xs
                     | otherwise = filtrarPrimos xs
{-
EJEMPLOS
ghci> filtrarPrimos [2, 3, 4, 5, 6]
[2,3,5]

ghci> filtrarPrimos [10, 20, 30, 40]
[]

ghci> filtrarPrimos [67, 87, 97, 107] 
[67,97,107]

-}

multiplicaPrimos :: [Int] -> Int
multiplicaPrimos xs = productoria' (filtrarPrimos xs) id

{-
EJEMPLOS
ghci> multiplicaPrimos [1, 2, 3, 4, 5] 
30

ghci> multiplicaPrimos [1, 3, 5, 7, 9]
105

ghci> multiplicaPrimos [87, 69, 40, 23, 33, 1, 2]
46

-}

{-
Funcion auxiliar ejercicio 6. H)
Dado un entero n me devuelve el numero que se encuentra 
en la posicion de la sucesion de fibonacci
-}

fib :: Int -> Int
fib n | n == 0 = 0
      | n == 1 = 1 
      | otherwise = fib (n-1) + fib (n-2)

{-
EJEMPLOS
ghci> fib 4
3

ghci> fib 5
5

ghci> fib 10
55

-}
-- H) 
esFib :: Int -> Bool
esFib n = existe' [1..(n+1)] ((n==).(fib))

{-
EJEMPLOS
ghci> esFib 10
False

ghci> esFib 3
True

ghci> esFib 55
True

-}

-- I)
todosFib :: [Int] -> Bool
todosFib xs = paraTodo' xs esFib

{-
EJEMPLOS

ghci> todosFib [1, 2, 3, 4, 5]
False

ghci> todosFib [2, 5, 3]
True

-}


-- EJERCICIO 7
{-
Indaga en Hoogle sobre las funciones map y filter. 

¿Que hacen estas funciones?
      La funcion map sirve para aplicar una funcion a cada elemento de una lista, 
      y se genera una nueva lista con los nuevos elementos. 

      La funcion filter sirve para seleccionar elementos de una lista, 
      pero que estos elementos cumplan con una condicion dada. 

Tipo de datos: 

map :: (a -> b) -> [a] -> [b]

filter :: (a -> Bool) -> [a] -> [a]

¿A que equivale la expresion map succ [1, -4, 6, 2, -8], donde succ n = n+1?
[2,-3,7,3,-7]

¿Y la expresion filter esPositivo [1, -4, 6, 2, -8]?
[1, 6, 2]

-}

-- EJERCICIO 8
-- Recursion:
doble :: [Int] -> [Int]
doble [] = []
doble (x:xs) = x*2 : doble xs

{-
EJEMPLOS
ghci> doble [10, 20, 30, 40] 
[20,40,60,80]

ghci> doble [1, 2, 3, 4, 5]
[2,4,6,8,10]

ghci> doble [100, 200, 300] 
[200,400,600]

-}

dob :: Int -> Int
dob x = 2 * x

-- Usando la funcion map
doble' :: [Int] -> [Int]
doble' xs = map dob xs

{-
EJEMPLOS
ghci> doble' [10, 20, 30, 40] 
[20,40,60,80]

ghci> doble' [1, 2, 3, 4, 5]
[2,4,6,8,10]

ghci> doble' [100, 200, 300] 
[200,400,600]

-}

-- EJERCICIO 9

-- Recursion (A)
filterPrimos :: [Int] -> [Int]
filterPrimos [] = []
filterPrimos (x:xs) | esPrimo x = x : filtrarPrimos xs
                     | otherwise = filtrarPrimos xs
{-
EJEMPLOS
ghci> filterPrimos [1, 2, 3, 4, 5, 6]
[2,3,5]

ghci> filterPrimos [7, 8, 9, 10, 11, 12]
[7,11]

ghci> filterPrimos [20, 21, 22, 23]
[20,21,22,23]

-}

-- B) Utilizando filter

filterPrimos' :: [Int] -> [Int]
filterPrimos' xs = filter esPrimo xs

{-
EJEMPLOS
ghci> filterPrimos' [1, 2, 3, 4, 5, 6]
[2,3,5]

ghci> filterPrimos' [7, 8, 9, 10, 11, 12]
[7,11]

ghci> filterPrimos' [20, 21, 22, 23]
[20,21,22,23]

-}

-- C)
multiplicaPrimos' :: [Int] -> Int
multiplicaPrimos' xs =  productoria (filterPrimos' xs)

{-
EJEMPLOS
ghci> multiplicaPrimos' [1, 2, 3, 4, 5, 6, 7, 8] 
210

ghci> multiplicaPrimos' [10, 11, 12, 13, 14, 15, 16] 
143

ghci> multiplicaPrimos' [20, 21, 22, 23, 24, 25]
23

-}

-- EJERCICIO 10

-- A) Por recursion: 
primIgualesA ::  Eq a => a -> [a] -> [a] 
primIgualesA _ [] = []
primIgualesA n (x:xs) | n == x = x : primIgualesA n xs
                      | otherwise = []

{-
EJEMPLOS
ghci> primIgualesA 5 [5, 5, 5, 5, 6, 7] 
[5,5,5,5]

ghci> primIgualesA 5 [5, 4, 5, 6]
[5]

ghci> primIgualesA 4 [5, 6, 7, 4, 4]
[]


-}
-- B) Usando takewhile 
primIgualesA' :: Eq a => a -> [a] -> [a]   
primIgualesA' n xs = takeWhile (==n) xs 

{-
EJEMPLOS
ghci> primIgualesA' 5 [5, 5, 5, 5, 6, 7] 
[5,5,5,5]

ghci> primIgualesA' 5 [5, 4, 5, 6]
[5]

ghci> primIgualesA' 4 [5, 6, 7, 4, 4]
[]

-}

-- EJERCICIO 11 

-- A) Recursivo

primIguales [] = []
primIguales [x] = [x]
primIguales (x:xs) |  x== (head xs) = x : primIguales xs 
                   | otherwise = [x]

{-

EJEMPLOS 
ghci> primIguales [4, 4, 4, 3, 1]
[4,4,4]

ghci> primIguales [3, 3, 4, 1]
[3,3]

ghci> primIguales "adaad"
"a"

-}

-- B) No recursiva
primIguales' :: Eq a => [a] -> [a] 
primIguales' (x:xs) = x : primIgualesA x xs

{-

EJEMPLOS 
ghci> primIguales' [4, 4, 4, 3, 1]
[4,4,4]

ghci> primIguales' [3, 3, 4, 1]
[3,3]

ghci> primIguales' "adaad"
"a"

-}

-- EJERCICIO 12 
cuantGen :: (b -> b -> b) -> b -> [a] -> (a -> b) -> b
cuantGen op neu [] t = neu
cuantGen op neu (x:xs) t = t x `op` (cuantGen op neu xs t )

{-

-}

-- EJERCICIO 13
distanciaEdicion :: [Char]->[Char]-> Int 
distanciaEdicion [] ys = length ys 
distanciaEdicion xs [] = length xs
distanciaEdicion (x:xs) (y:ys) | x == y = distanciaEdicion xs ys 
                               | x /= y = 1 + distanciaEdicion xs ys 

{- 
ghci> distanciaEdicion "estudia" "computacion"
10

ghci> distanciaEdicion " " "messi" 
5

ghci> distanciaEdicion "famaf" "famaf" 
0
 -}
-- EJERCICIO 14 
primQueCumplen :: [a] -> (a->Bool) -> [a]
primQueCumplen [] p = []
primQueCumplen [x] p = [x]
primQueCumplen (x:xs) p | p x == p (head xs) = x : primQueCumplen xs p
                        | otherwise = [x]

{- 

EJEMPLOS:
ghci> primQueCumplen ['a', 'e', 'i', 'c', 'm'] esVocal
['a', 'e', 'i'] 

ghci> primQueCumplen [1, 3, 90, -8, 3] esPositivo 
[1,3,90]

ghci> primQueCumplen [0, 0, 0, 3, 4, 1] esCero
[0,0,0]

ghci> primQueCumplen [2, 6, 8, 16, 3, 5] esPar
[2,6,8,16] 

-}

-- EJERCICIO 15 
{- 
a) f :: (a, b) -> ...
f (x , y) = ...
TIPADO: Bien
TIPO DE LA SUBEXPRESION: 2-Tupla
CUBRE TODOS LOS CASOS.

b) f :: [(a, b)] -> ...
f (a , b) = ...
TIPADO: Mal
Para que tipe seria: 
f ((a, b) : xs ) y asi, 
TIPO DE LA SUBEXPRESION: Lista de 2-tuplas
NO CUBRE TODOS LOS CASOS.

c) f :: [(a, b)] -> ...
f (x:xs) = ...
TIPADO: Mal
Para que tipe seria: 
f ((x, y):xs) y asi,
TIPO DE LA SUBEXPRESION: Lista de 2-tupla
NO CUBRE TODOS LOS CASOS. 

d) f :: [(a, b)] -> ...
f ((x, y) : ((a, b) : xs)) = ...
TIPADO: Bien
TIPO DE LA SUBEXPRESION: Lista de 2-tupla
NO CUBRE TODOS LOS CASOS.

e) f :: [(Int, a)] -> ...
f [(0, a)] = ...
TIPADO: Bien
TIPO DE LA SUBEXPRESION: Lista de 2-tuplas con el primer elemento de la tupla de tipo int
NO CUBRE TODOS LOS CASOS.

f ) f :: [(Int, a)] -> ...
f ((x, 1) : xs) = ...
NO CUBRE TODOS LOS CASOS.
TIPADO: 
g ) f :: (Int -> Int) -> Int -> ...
f a b = ...
h) f :: (Int -> Int) -> Int -> ...
f a 3 = ...
i) f :: (Int -> Int) -> Int -> ...
f 0 1 2 = ... -}


-- EJERCICIO 16 

{- 

a) f :: (a, b) -> b
- f (x, y) = y
- f (x * y, z) = z

b) f :: (a, b) -> c
- f (x, y) = z
- f (x+5, y*5) = a

c) f :: (a -> b) -> a -> b
- f (x, y) x = y
- f (a+1, b+2) (a+1) = b+2

d) f :: (a -> b) -> [a] -> [b] 
- f (x, y) [x] = [y]
- f (x*2, y+4) [(x*2)] = [y+4]

-}