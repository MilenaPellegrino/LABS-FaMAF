module Interp where
import Graphics.Gloss
import Graphics.Gloss.Data.Vector
import qualified Graphics.Gloss.Data.Point.Arithmetic as V

zero :: Point
zero = (0, 0)

-- interp_basica :: Dibujo Int -> Picture
-- interp_basica (Basica 0) = circle 100
-- interp_basica (Basica 1) = rectangleSolid 50 100


-- Gloss provee el tipo Vector y Picture.
type ImagenFlotante = Vector -> Vector -> Vector -> Picture
type Interpretacion a = a -> ImagenFlotante

mitad :: Vector -> Vector
mitad = (0.5 V.*)

-- Interpretaciones de los constructores de Dibujo

--interpreta el operador de rotacion
interp_rotar :: ImagenFlotante -> ImagenFlotante
interp_rotar f = \d w h -> f (d V.+ w) h (zero V.- w)


--interpreta el operador de espejar
interp_espejar :: ImagenFlotante -> ImagenFlotante
interp_espejar f = \d w h -> f d (zero V.- w) h

--interpreta el operador de rotacion 45
interp_rotar45 :: ImagenFlotante -> ImagenFlotante
interp_rotar45 f = \d w h -> f (d V.+ mitad (w V.+ h)) (mitad (w V.+ h)) (mitad (h V.- w))

-- --interpreta el operador de apilar
-- interp_apilar :: Int -> Int -> ImagenFlotante -> ImagenFlotante -> ImagenFlotante

-- --interpreta el operador de juntar
-- interp_juntar :: Int -> Int -> ImagenFlotante -> ImagenFlotante -> ImagenFlotante

-- --interpreta el operador de encimar
-- interp_encimar :: ImagenFlotante -> ImagenFlotante -> ImagenFlotante

-- --interpreta cualquier expresion del tipo Dibujo a
-- --utilizar foldDib 
-- interp :: Interpretacion a -> Dibujo a -> ImagenFlotante

