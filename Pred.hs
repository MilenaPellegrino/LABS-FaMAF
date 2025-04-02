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
{- cambiar :: Pred a -> a -> Dibujo a -> Dibujo a

-- Alguna básica satisface el predicado.
anyDib :: Pred a -> Dibujo a -> Bool

-- Todas las básicas satisfacen el predicado.
allDib :: Pred a -> Dibujo a -> Bool -}


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

{- -- Hay 2 espejados seguidos.
esFlip2 :: Pred (Dibujo a)




data Superfluo = RotacionSuperflua | FlipSuperfluo

---- Chequea si el dibujo tiene una rotacion superflua
errorRotacion :: Dibujo a -> [Superfluo]

-- Chequea si el dibujo tiene un flip superfluo
errorFlip :: Dibujo a -> [Superfluo]

-- Aplica todos los chequeos y acumula todos los errores, y
-- sólo devuelve la figura si no hubo ningún error.
checkSuperfluo :: Dibujo a -> Either [Superfluo] (Dibujo a) -}