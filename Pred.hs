module Pred where

import Dibujo (Dibujo(..), foldDib, mapDib)


type Pred a = a -> Bool

--- EJEMPLOS PARA TESTS 

-- data Figura = Triangulo Float Float
--             | Rectangulo Float Float
--             | Circulo Float
--             deriving (Eq,Show)


-- esGrande :: Pred Figura
-- esGrande (Triangulo base altura) = (base * altura / 2) > 100
-- esGrande (Rectangulo base altura) = (base * altura) > 100
-- esGrande (Circulo radio) = (pi * radio^2) > 100

-- esTriangulo :: Pred Figura
-- esTriangulo (Triangulo _ _) = True
-- esTriangulo _ = False

-- ghci> let dib1 = Basica (Rectangulo 10 5)
-- ghci> anyDib esGrande dib1
-- False
--- FIN EJEMPLOS PARA TESTS

--Para la definiciones de la funciones de este modulo, no pueden utilizar
--pattern-matching, sino alto orden a traves de la funcion foldDib, mapDib 

-- Dado un predicado sobre básicas, cambiar todas las que satisfacen
-- el predicado por el resultado de llamar a la función indicada por el
-- segundo argumento con dicha figura.
-- Por ejemplo, `cambiar (== Triangulo) (\x -> Rotar (Basica x))` rota
-- todos los triángulos.
-- cambiar :: Pred a -> a -> Dibujo a -> Dibujo a -> Dibujo a
-- cambiar pred f dib = mapDib (\x -> if pred x then f x else dib) dib

--cambiar :: Pred a -> (a -> Dibujo a) -> Dibujo a -> Dibujo a
--cambiar pred f = mapDib (\x -> if pred x then f x else  x)


--Alguna básica satisface el predicado.
anyDib :: Pred a -> Dibujo a -> Bool
anyDib pred = foldDib pred id id id (\_ _ a b -> (a||b)) (\_ _ a b -> (a||b)) (||) 

-- Todas las básicas satisfacen el predicado.
allDib :: Pred a -> Dibujo a -> Bool
allDib pred = foldDib pred id id id (\_ _ a b -> (a&&b)) (\_ _ a b -> (a&&b)) (&&)

-- Hay 4 rotaciones seguidas.
esRot360 :: Pred (Dibujo a)
esRot360 d = snd (foldDib contarBasica contarRotar contarRotar45 contarEspejar contarApilar contarJuntar contarEncimar d)
    where
        --Funciones auxiliares
        --"Caso base"
        contarBasica _ = (0.0, False)

        --Rotar suma 1 a nuestro contador
        contarRotar (n, encontrado) = let nuevoN = n + 1.0 
                                      in (nuevoN, encontrado || nuevoN >= 4.0)

        --Rotar45 cuenta como medio rotar
        contarRotar45 (n, encontrado) = let nuevoN = n + 0.5 
                                        in (nuevoN, encontrado || nuevoN >= 4.0)

        --Espejar reinicia el contador
        contarEspejar _ = (0.0, False)

        --En Apilar y Juntar miramos adentro de ambos hijos
        contarApilar _ _ (_, e1) (_, e2) = (0, e1 || e2)
        contarJuntar _ _ (_, e1) (_, e2) = (0, e1 || e2)

        --En Encimar pasa lo mismo
        contarEncimar (_, e1) (_, e2) = (0, e1 || e2)

--Hay 2 espejados seguidos. La idea es similar a la función anterior
esFlip2 :: Pred (Dibujo a)
esFlip2 d = snd (foldDib contarBasica contarRotar contarRotar45 contarEspejar contarApilar contarJuntar contarEncimar d)
    where
        --Funciones auxiliares
        --"Caso base"
        contarBasica _ = (0.0, False)

        --Rotar me reinicia el contador
        contarRotar _ = (0.0, False)

        --Rotar45 me reinicia el contador
        contarRotar45 _ = (0.0, False)

        -- Espejar suma 1 al contador
        contarEspejar prev = let (n, encontrado) = prev  -- Desempaquetamos la tupla recibida
                                 nuevoN = n + 1 
                             in (nuevoN, encontrado || nuevoN >= 2)

        --En Apilar y Juntar miramos adentro de ambos hijos
        contarApilar _ _ (_, e1) (_, e2) = (0, e1 || e2)
        contarJuntar _ _ (_, e1) (_, e2) = (0, e1 || e2)

        --En Encimar pasa lo mismo
        contarEncimar (_, e1) (_, e2) = (0, e1 || e2)

data Superfluo = RotacionSuperflua | FlipSuperfluo deriving (Show, Eq)

---- Chequea si el dibujo tiene una rotacion superflua
errorRotacion :: Dibujo a -> [Superfluo]
errorRotacion d = if (esRot360 d) then [RotacionSuperflua] else []

-- Chequea si el dibujo tiene un flip superfluo
errorFlip :: Dibujo a -> [Superfluo]
errorFlip d = if (esFlip2 d) then [FlipSuperfluo] else []

-- Aplica todos los chequeos y acumula todos los errores, y
-- sólo devuelve la figura si no hubo ningún error.
checkSuperfluo :: Dibujo a -> Either [Superfluo] (Dibujo a)
checkSuperfluo d = 
    let errores = errorRotacion d ++ errorFlip d
    in if (errores == [])
        then Right d
        else Left errores
