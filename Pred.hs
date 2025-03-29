import Dibujo (Dibujo(..), foldDib, mapDib)


type Pred a = a -> Bool

--- EJEMPLOS PARA TESTS 

data Figura = Triangulo Float Float
            | Rectangulo Float Float
            | Circulo Float
            deriving (Eq,Show)


esGrande :: Pred Figura
esGrande (Triangulo base altura) = (base * altura / 2) > 100
esGrande (Rectangulo base altura) = (base * altura) > 100
esGrande (Circulo radio) = (pi * radio^2) > 100

esTriangulo :: Pred Figura
esTriangulo (Triangulo _ _) = True
esTriangulo _ = False

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

-- -- Hay 4 rotaciones seguidas.
-- esRot360 :: Pred (Dibujo a)


-- -- Hay 2 espejados seguidos.
-- esFlip2 :: Pred (Dibujo a)

-- data Superfluo = RotacionSuperflua | FlipSuperfluo

-- ---- Chequea si el dibujo tiene una rotacion superflua
-- errorRotacion :: Dibujo a -> [Superfluo]

-- -- Chequea si el dibujo tiene un flip superfluo
-- errorFlip :: Dibujo a -> [Superfluo]

-- -- Aplica todos los chequeos y acumula todos los errores, y
-- -- sólo devuelve la figura si no hubo ningún error.
-- checkSuperfluo :: Dibujo a -> Either [Superfluo] (Dibujo a)


