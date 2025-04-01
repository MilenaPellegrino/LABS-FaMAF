module Pred where

import Dibujo

type Pred a = a -> Bool

--Para la definiciones de la funciones de este modulo, no pueden utilizar
--pattern-matching, sino alto orden a traves de la funcion foldDib, mapDib 

-- Dado un predicado sobre básicas, cambiar todas las que satisfacen
-- el predicado por el resultado de llamar a la función indicada por el
-- segundo argumento con dicha figura.
-- Por ejemplo, `cambiar (== Triangulo) (\x -> Rotar (Basica x))` rota
-- todos los triángulos.
cambiar :: Pred a -> a -> Dibujo a -> Dibujo a

-- Alguna básica satisface el predicado.
anyDib :: Pred a -> Dibujo a -> Bool

-- Todas las básicas satisfacen el predicado.
allDib :: Pred a -> Dibujo a -> Bool


-- Hay 4 rotaciones seguidas.
esRot360 :: Pred (Dibujo a)
esRot360 d = fst (foldDib checkRotations resetState id id (\_ _ x y -> max x y) (\_ _ x y -> max x y) max d)
    where
        --Estado inicial: (tupla con acumulador de rotaciones consecutivas con un flag de 4 rotaciones seguidas)
        resetState = (0, False)

        --Función para actualizar el estado
        checkRotations :: a -> (Int, Bool) -> (Int, Bool)
        checkRotations _ (count, _) 
            | count >= 4 = (count, True)  -- Ya alcanzamos 4 rotaciones consecutivas
            | otherwise = (count, False) 

         -- Función para manejar rotaciones
        rotf :: (Int, Bool) -> (Int, Bool)
        rotf (count, _) = if count + 1 >= 4 then (4, True) else (count + 1, False)

        -- Función para manejar otros tipos de dibujos, que reinicia el contador
        idf :: (Int, Bool) -> (Int, Bool)
        idf _ = (0, False)

-- Hay 2 espejados seguidos.
esFlip2 :: Pred (Dibujo a)


data Superfluo = RotacionSuperflua | FlipSuperfluo

---- Chequea si el dibujo tiene una rotacion superflua
errorRotacion :: Dibujo a -> [Superfluo]

-- Chequea si el dibujo tiene un flip superfluo
errorFlip :: Dibujo a -> [Superfluo]

-- Aplica todos los chequeos y acumula todos los errores, y
-- sólo devuelve la figura si no hubo ningún error.
checkSuperfluo :: Dibujo a -> Either [Superfluo] (Dibujo a)