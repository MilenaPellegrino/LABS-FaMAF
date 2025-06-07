
-- PROYECTO 2 
-- LABORATORIO 

-- EJERCICIO 1 

--A)
data Carrera = Matematica | Fisica | Computacion | Astronomia deriving (Eq, Show)

--B)
titulo ::  Carrera -> String
titulo Matematica = "Licenciatura en Matematica"
titulo Fisica = "Licenciatura en Fisica"
titulo Computacion = "Licenciatura en Ciencias de la Computacion"
titulo Astronomia = "Licenciatura en Astronomia"

{-
EJEMPLOS: 
ghci> titulo Matematica 
"Licenciatura en Matematica"

ghci> titulo Computacion 
"Licenciatura en Ciencias de la Computacion"

ghci> titulo Fisica
"Licenciatura en Fisica"
-}

--C)
data NotaBasica = Do | Re | Mi | Fa | Sol | La | Si  deriving (Eq, Ord, Bounded, Show)

--D) 
cifradoAmericano :: NotaBasica -> Char

cifradoAmericano Do = 'C'
cifradoAmericano Re = 'D'
cifradoAmericano Mi = 'E'
cifradoAmericano Fa = 'F'
cifradoAmericano Sol = 'G'
cifradoAmericano La = 'A'
cifradoAmericano Si = 'B'

{-
EJEMPLOS
ghci> cifradoAmericano Do
'C'

ghci> cifradoAmericano Sol
'G'

ghci> cifradoAmericano  Si
'B'
-}

-- EJERCICIO 2 
-- A) 
-- Hecho en el ejercicio c 

{-
EJEMPLOS
ghci> Do < Re
True

ghci> Re < Do
False

ghci> Si == La
False

-}

-- EJERCICIO 3 

-- A) 
minimoElemento :: Ord a => [a] -> a
minimoElemento [x] = x
minimoElemento (x:xs) = min x (minimoElemento xs)

{-
EJEMPLOS
ghci> minimoElemento [1, 2, 3, 4] 
1

ghci> minimoElemento [20, 30, 5, 40, 50] 
5

ghci> minimoElemento [10, 30, 50, 90, -89]
-89

-}

-- Tambien lo podria hacer por guardas pero la forma es un poco mas confusa: 
{-
minimoElemento :: Ord a => [a] -> a
minimoElemento [a] = a
minimoElemento (x:xs) | x <= (head xs) = minimo(x:(tail xs))
              | otherwise = minimo xs
-}


-- B) 
minimoElemento' :: (Ord a, Bounded a) => [a] -> a
minimoElemento' [] = minBound -- Ya que es la cota inferior 
minimoElemento' [x] = x
minimoElemento' (x:xs) = min x (minimoElemento' xs)

{-
EJEMPLOS
ghci> minimoElemento' ([10, 30, 5, -9]::[Int])
-9

ghci> minimoElemento' ([10, 20, 30]::[Int])
10

ghci> minimoElemento' []
()
-}
-- C)
-- Funcion generalizada para cualquier lista de nota, te devuelve la nota mas grave
notaMasGrave :: [NotaBasica] -> NotaBasica
notaMasGrave xs = minimoElemento xs

{-
EJEMPLOS 
ghci> notaMasGrave [Fa, La, Sol, Re, Fa]
Re

ghci> notaMasGrave [Sol, La, Si]
Sol

ghci> notaMasGrave [Do, Re, Mi]
Do
-}

-- EJERCICIO 4

type Altura = Int 
type NumCamiseta = Int 

data Zona = Arco | Defensa | Mediocampo | Delantera deriving (Eq, Show)
data TipoReves = DosManos | UnaMano deriving Show
data Modalidad = Carretera | Pista | Monte | BMX deriving Show
data PiernaHabil = Izquierda | Derecha deriving Show

type ManoHabil = PiernaHabil 

data Deportista = Ajedrecista | Ciclista Modalidad | Velocista Altura | Tenista TipoReves ManoHabil Altura | Futbolista Zona NumCamiseta PiernaHabil Altura  deriving Show -- Lo necesito para el ejercicio 7 para poder ejecutar la funcion, por eso tambien lo tiene los tipos de arriba

-- B)
-- El tipo del constructor ciclista: Ciclista :: Modalidad -> Deportista 

-- C)
contar_velocistas :: [Deportista] -> Int
contar_velocistas [] = 0
contar_velocistas (Velocista al : xs) = 1 + contar_velocistas xs
contar_velocistas (x:xs) = contar_velocistas xs

{-
EJEMPLOS
ghci> contar_velocistas [Ajedrecista, Velocista 120, Ciclista Monte, Velocista 150]
2

ghci> contar_velocistas [Velocista 180, Velocista 190, Velocista 170]
3

ghci> contar_velocistas [Ajedrecista, Ciclista BMX, Ciclista  Carretera, Ajedrecista]
0
-}

-- D)
-- Funcion auxiliar para el ejercicio mismaZona
-- Dada una zona y un futbolista con la zona te devuelve True o False si la zona coincide con la zona del futbolista

mismaZona :: Zona -> Deportista -> Bool
mismaZona Delantera (Futbolista Delantera _ _ _) = True
mismaZona Mediocampo (Futbolista Mediocampo _ _ _) = True
mismaZona Arco (Futbolista Arco _ _ _) = True
mismaZona Defensa (Futbolista Defensa _ _ _) = True
mismaZona _ _ = False

{-
EJEMPLOS DE USO DE LA FUNCION AUXILIAR
ghci> mismaZona Delantera (Futbolista Delantera 10 Izquierda 200)
True

ghci> mismaZona Arco (Futbolista Mediocampo 5 Derecha 180)
False
-}

contar_futbolistas :: [Deportista] -> Zona -> Int
contar_futbolistas [] z = 0
contar_futbolistas (x:xs) z  |(mismaZona z x) = 1 + contar_futbolistas xs z
                             | otherwise = contar_futbolistas xs z
{-
EJEMPLOS
ghci> contar_futbolistas [(Futbolista Mediocampo 3 Derecha 150), (Futbolista Arco 1 Izquierda 140), Ajedrecista, Ciclista BMX] Mediocampo 
1

ghci> contar_futbolistas [(Futbolista Mediocampo 3 Derecha 150), (Futbolista Arco 1 Izquierda 140), (Futbolista Delantera 10 Izquierda 160), (Futbolista Arco 23 Derecha 180)] Arco 
2

ghci> contar_futbolistas [(Futbolista Mediocampo 3 Derecha 150), (Futbolista Arco 1 Izquierda 140), Ajedrecista, Ciclista BMX] Delantera  
0
-}

-- E)
contar_futbolistas' :: [Deportista] -> Zona -> Int
contar_futbolistas' xs zon = length (filter (mismaZona zon) xs)

{-
EJEMPLOS 
ghci> contar_futbolistas' [(Futbolista Mediocampo 3 Derecha 150), (Futbolista Arco 1 Izquierda 140), Ajedrecista, Ciclista BMX] Mediocampo 
1

ghci> contar_futbolistas' [(Futbolista Mediocampo 3 Derecha 150), (Futbolista Arco 1 Izquierda 140), (Futbolista Delantera 10 Izquierda 160), (Futbolista Arco 23 Derecha 180)] Arco 
2

ghci> contar_futbolistas' [(Futbolista Mediocampo 3 Derecha 150), (Futbolista Arco 1 Izquierda 140), Ajedrecista, Ciclista BMX] Delantera  
0
-}

-- EJERCICIO 5 
--A)
sonidoNatural :: NotaBasica -> Int
sonidoNatural Do = 0
sonidoNatural Re = 2
sonidoNatural Mi = 4
sonidoNatural Fa = 5
sonidoNatural Sol = 7
sonidoNatural La = 9
sonidoNatural Si = 11

{-
EJEMPLOS
ghci> sonidoNatural Do
0

ghci> sonidoNatural Re
2

ghci> sonidoNatural La
9
-}

-- B)
data Alteracion = Bemol | Natural | Sostenido 

-- C)
data NotaMusical = Nota NotaBasica Alteracion 

-- D)

-- Funcion auxiliar dada una nota basica y una alteracion me devuelve el sonido 
alteracion :: NotaBasica -> Alteracion -> Int
alteracion n Bemol = sonidoNatural (n) - 1
alteracion n Sostenido = sonidoNatural (n) + 1
alteracion n Natural = sonidoNatural n 

sonidoCromatico :: NotaMusical -> Int
sonidoCromatico (Nota nb a) = (alteracion nb a)

{-
EJEMPLOS
ghci> sonidoCromatico (Nota Do Sostenido)
1

ghci> sonidoCromatico (Nota Re Bemol)
1

ghci> sonidoCromatico (Nota La Bemol )
8
-}

-- E) 
instance Eq NotaMusical where
    nota == nota2 = sonidoCromatico nota == sonidoCromatico nota2

-- F) 
instance Ord NotaMusical where
    nota <= nota2 = sonidoCromatico nota <= sonidoCromatico nota2

-- EJERCICIO 6 
-- A) 
primerElemento' :: [a] -> Maybe a 
primerElemento' [] = Nothing
primerElemento' xs = Just (head xs)

{-
EJEMPLOS
ghci> primerElemento' [1, 2, 3, 4]
Just 1

ghci> primerElemento' [-9, 34, 56]
Just (-9)

ghci> primerElemento' []
Nothing
-}

-- EJERCICIO 7 
data Cola = VaciaC | Encolada Deportista Cola deriving Show

-- A) 1) 
atender :: Cola -> Maybe Cola
atender VaciaC  = Nothing
atender (Encolada d c) = Just c 

{-
EJEMPLOS
ghci> atender VaciaC
Nothing

ghci> atender (Encolada Ajedrecista (Encolada (Ciclista BMX) (VaciaC)))
Just (Encolada (Ciclista BMX) VaciaC)
-}

-- A) 2)
encolar :: Deportista -> Cola -> Cola
encolar depor VaciaC = Encolada depor VaciaC
encolar depor (Encolada dep c) = Encolada dep (encolar depor c)

{-
EJEMPLOS
ghci> encolar Ajedrecista (Encolada(Ciclista BMX)(Encolada (Ciclista Carretera )VaciaC))
Encolada (Ciclista BMX) (Encolada (Ciclista Carretera) (Encolada Ajedrecista VaciaC))

ghci> encolar Ajedrecista VaciaC
Encolada Ajedrecista VaciaC

-}
-- A) 3) 
busca :: Cola -> Zona -> Maybe Deportista
busca VaciaC _ = Nothing
busca (Encolada (Futbolista z a b c ) col) zon | z == zon = Just (Futbolista z a b c)
                                               | otherwise = busca col zon
busca (Encolada deport c) zon = busca c zon

{-
EJEMPLOS
ghci> busca VaciaC Arco
Nothing

ghci> busca (Encolada (Futbolista Arco 10 Izquierda 150) (Encolada (Futbolista Delantera 11 Derecha 190) (Encolada (Futbolista Delantera 9 Derecha 185) (VaciaC)))) Delantera 
Just (Futbolista Delantera 11 Derecha 190)

-}

-- B) 
-- El tipo cola se parece a la funcion recursiva de las listas

-- EJERCICIOS 8 
data ListaAsoc a b = Vacia | Nodo a b ( ListaAsoc a b ) deriving Show

-- A) 
-- Dado un nombre (String) te dice el numero de telefono (Int)
type GuiaTelefonica = ListaAsoc String Int

-- B) 1) 
la_long :: ListaAsoc a b -> Int
la_long Vacia = 0 
la_long (Nodo a b (lista)) = 1 + la_long lista

{-
EJEMPLOS
ghci> la_long Vacia
0

ghci> la_long (Nodo "estudia" "en" (Nodo "famaf" "si te recibes" (Nodo "en 20" "anios" Vacia)))
3

ghci> la_long (Nodo 1 2 (Nodo 3 4 (Nodo 5 6 Vacia)))
3
-}

-- B) 2) 
la_concat :: ListaAsoc a b -> ListaAsoc a b -> ListaAsoc a b
la_concat Vacia lista2 = lista2
la_concat lista Vacia = lista
la_concat (Nodo a b (lista)) lista2 = Nodo a b (la_concat lista lista2)

{-
EJEMPLOS
ghci> la_concat (Nodo 1 "UNC" (Nodo 2 "FaMAF" (Nodo 3 "FCEFyN" Vacia))) Vacia
Nodo 1 "UNC" (Nodo 2 "FaMAF" (Nodo 3 "FCEFyN" Vacia))

ghci> la_concat (Nodo 1 "UNC" (Nodo 2 "FaMAF" (Nodo 3 "FCEFyN" Vacia))) (Nodo 4 "Estudia!" Vacia)
Nodo 1 "UNC" (Nodo 2 "FaMAF" (Nodo 3 "FCEFyN" (Nodo 4 "Estudia!" Vacia)))

-}

-- B) 3) 
la_agregar :: Eq a => ListaAsoc a b -> a -> b -> ListaAsoc a b
la_agregar Vacia valor valor2 = Nodo valor valor2 Vacia
la_agregar (Nodo a b (lista)) valor valor2 = la_concat (Nodo a b (lista)) (Nodo valor valor2(Vacia))

{-
EJEMPLOS
ghci> la_agregar (Nodo 7 9 Vacia) 11 13
Nodo 7 9 (Nodo 11 13 Vacia)
-}
-- B) 4)

la_pares :: ListaAsoc a b -> [(a,b)]
la_pares Vacia = [] 
la_pares (Nodo a b (lista)) = (a, b) : la_pares (lista) 

{-
EJEMPLOS
ghci> la_pares (Nodo 1 1 (Nodo 2 3 (Nodo 5 8 Vacia)))
[(1,1),(2,3),(5,8)]

ghci> la_pares Vacia
[]
-}
-- B) 5)

la_busca :: Eq a => ListaAsoc a b -> a -> Maybe  b
la_busca Vacia _  = Nothing
la_busca (Nodo a b lista) clave | a == clave = Just b 
                                | otherwise = la_busca lista clave
{-
EJEMPLOS
ghci> la_busca (Nodo 5 "FAMAF"  (Nodo 3 "FCM"  (Nodo 1 "UNC"  Vacia))) 1
Just "UNC"

ghci> la_busca (Nodo 5 4 (Nodo 3 2 (Nodo 1 0 Vacia))) 3
Just 2

-}
-- B) 6)

la_borrar :: Eq a => a -> ListaAsoc a b -> ListaAsoc a b
la_borrar _ Vacia = Vacia
la_borrar clave (Nodo a b lista) | clave == a = lista
                                 | otherwise = (Nodo a b (la_borrar clave lista))
{-
EJEMPLOS
ghci> la_borrar 1 (Nodo 1 "UNC" (Nodo 3 "FaMAF" Vacia))
Nodo 3 "FaMAF" Vacia

ghci> la_borrar 4 (Nodo 2 3 (Nodo 4 5 (Nodo 6 7 Vacia)))
Nodo 2 3 (Nodo 6 7 Vacia)
-}

