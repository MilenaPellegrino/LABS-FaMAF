-- http://aprendehaskell.es/content/Modulos.html Seccion: Creando nuestros propios módulos --
module Dibujo (Dibujo(..), 
              apilar, juntar, encimar, 
              rotar, r180,r270,
              (^^^),(.-.),(///),comp,
              cuarteto,encimar4,ciclar,
              foldDib,mapDib) where

-- Definir el lenguaje via constructores de tipo
data Dibujo a = Basica a 
              | Rotar (Dibujo a) 
              | Rotar45 (Dibujo a)  
              | Espejar (Dibujo a)
              | Apilar  Float Float (Dibujo a) (Dibujo a) 
              | Juntar  Float Float (Dibujo a) (Dibujo a)
              | Encimar (Dibujo a) (Dibujo a)
              deriving (Show, Eq)


-- Composición n-veces de una función con sí misma.
comp :: (a -> a) -> Int -> a -> a
comp f 0 = id
comp f n = f . comp f (n -1)

-- Funciones Auxiliares que crean elementos del tipo.
rotar :: Dibujo a -> Dibujo a
rotar x = Rotar x 

apilar :: Float -> Float -> (Dibujo a) -> (Dibujo a) -> Dibujo a
apilar size1 size2 dib1 dib2 = Apilar  size1 size2 dib1 dib2

juntar :: Float -> Float -> (Dibujo a) -> (Dibujo a) -> Dibujo a
juntar size1 size2 dib1 dib2 = Juntar  size1 size2 dib1 dib2

encimar :: (Dibujo a) -> (Dibujo a) -> Dibujo a
encimar dib1 dib2 = Encimar dib1 dib2

-- Rotaciones de múltiplos de 90.
r180 :: Dibujo a -> Dibujo a
r180 = comp rotar 2

r270 :: Dibujo a -> Dibujo a
r270 = comp rotar 3

-- Pone una figura sobre la otra, ambas ocupan el mismo espacio.
(.-.) :: Dibujo a -> Dibujo a -> Dibujo a
(.-.) = apilar 1 1

-- -- Pone una figura al lado de la otra, ambas ocupan el mismo espacio.
(///) :: Dibujo a -> Dibujo a -> Dibujo a
(///) =  juntar 1 1

-- Superpone una figura con otra.
(^^^) :: Dibujo a -> Dibujo a -> Dibujo a
(^^^) = encimar

-- Dadas cuatro dibujos las ubica en los cuatro cuadrantes.
cuarteto :: Dibujo a -> Dibujo a -> Dibujo a -> Dibujo a -> Dibujo a
cuarteto d1 d2 d3 d4 = Apilar 1 1 (Juntar 1 1 d1 d2) (Juntar 1 1 d3 d4)

-- Una dibujo repetido con las cuatro rotaciones, superpuestas.
encimar4 :: Dibujo a -> Dibujo a
encimar4 d = encimar d (encimar (rotar d) (encimar (r180 d) (r270 d)))


-- Cuadrado con la misma figura rotada i * 90, para i ∈ {0, ..., 3}.
-- No confundir con encimar4!
ciclar :: Dibujo a -> Dibujo a
ciclar d = cuarteto d (rotar d) (r180 d) (r270 d)

-- -- Transfomar un valor de tipo a como una Basica.
pureDib :: a -> Dibujo a
pureDib x = Basica x

-- -- map para nuestro lenguaje.
mapDib :: (a -> b) -> Dibujo a -> Dibujo b
mapDib f (Basica x) = Basica (f x)
mapDib f (Rotar d) = Rotar (mapDib f d)
mapDib f (Rotar45 d) = Rotar45 (mapDib f d)
mapDib f (Espejar d) = Espejar (mapDib f d)
mapDib f (Apilar s1 s2 d1 d2) = Apilar s1 s2 (mapDib f d1) (mapDib f d2)
mapDib f (Juntar s1 s2 d1 d2) = Juntar s1 s2 (mapDib f d1) (mapDib f d2)
mapDib f (Encimar d1 d2) = Encimar (mapDib f d1) (mapDib f d2)

-- -- For testing map
-- plusOne :: Int -> Int
-- plusOne x = x + 1


-- Generalizacion de fold para el tipo Dibujo. 
-- Las funciones que hagan uso de foldDib ya no tienen que definir el pattern matching para cada constructor del tipo
-- solo tienen que pasar las funciones que procesan cada constructor y foldDib se encarga de combinar los resultados
-- sin foldDib en cada funcion con estructura de fold (procesar y combinar) hay que estar definiendo el pattern matching y también
-- la combinacion de resultados.
foldDib :: (a -> b) -> (b -> b) -> (b -> b) -> (b -> b) ->
       (Float -> Float -> b -> b -> b) -> 
       (Float -> Float -> b -> b -> b) -> 
       (b -> b -> b) ->
       Dibujo a -> b
foldDib bsf rotf rot45f espf apif junf encf (Basica d) = bsf d
foldDib bsf rotf rot45f espf apif junf encf (Rotar d) = rotf (foldDib bsf rotf rot45f espf apif junf encf d)
foldDib bsf rotf rot45f espf apif junf encf (Rotar45 d) = rot45f (foldDib bsf rotf rot45f espf apif junf encf d)
foldDib bsf rotf rot45f espf apif junf encf (Espejar d) = espf (foldDib bsf rotf rot45f espf apif junf encf d)
foldDib bsf rotf rot45f espf apif junf encf (Apilar v1 v2 d1 d2) = apif v1 v2 (foldDib bsf rotf rot45f espf apif junf encf d1) (foldDib bsf rotf rot45f espf apif junf encf d2)
foldDib bsf rotf rot45f espf apif junf encf (Juntar v1 v2 d1 d2) = junf v1 v2 (foldDib bsf rotf rot45f espf apif junf encf d1) (foldDib bsf rotf rot45f espf apif junf encf d2)
foldDib bsf rotf rot45f espf apif junf encf (Encimar d1 d2) = encf (foldDib bsf rotf rot45f espf apif junf encf d1) (foldDib bsf rotf rot45f espf apif junf encf d2)

-- Ejemplo con funcion count
count_basica :: Dibujo a -> Int
count_basica = foldDib (\x -> 1) (\x -> x) (\x -> x) (\x -> x) (\w x y z -> y + z) (\w x y z -> y + z) (\x y -> x + y)

