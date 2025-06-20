module Interp where
import Graphics.Gloss
import Graphics.Gloss.Data.Vector
import qualified Graphics.Gloss.Data.Point.Arithmetic as V
import Dibujo

zero :: Point
zero = (0, 0)

-- Gloss provee el tipo Vector y Picture.
type ImagenFlotante = Vector -> Vector -> Vector -> Picture
type Interpretacion a = a -> ImagenFlotante

mitad :: Vector -> Vector
mitad = (0.5 V.*)

-- Interpretaciones de los constructores de Dibujo

--interpreta el operador de rotacion
interp_rotar :: ImagenFlotante -> ImagenFlotante
interp_rotar f = \d w h -> f (d V.+ w) h (V.negate w)

--interpreta el operador de espejar
interp_espejar :: ImagenFlotante -> ImagenFlotante
interp_espejar f = \d w h -> f (d V.+ w) (V.negate w) h

--interpreta el operador de rotacion 45
interp_rotar45 :: ImagenFlotante -> ImagenFlotante
interp_rotar45 f = \d w h -> f (d V.+ mitad (w V.+ h)) (mitad (w V.+ h)) (mitad (h V.- w))

--interpreta el operador de encimar
interp_encimar :: ImagenFlotante -> ImagenFlotante -> ImagenFlotante
interp_encimar f g d w h = pictures [f d w h, g d w h]

--interpreta el operador de apilar
-- Veri si esta bien porque me da error porque no tengo la de encimar implementada
interp_apilar :: Float -> Float -> ImagenFlotante -> ImagenFlotante -> ImagenFlotante
interp_apilar m n f g d w h = 
    let 
        rp = n/(m+n)
        r = m/(m+n)
        hp = rp V.* h
    in
        pictures [f (d V.+ hp) w (r V.*h), g d w hp]

-- --interpreta el operador de juntar
interp_juntar :: Float -> Float -> ImagenFlotante -> ImagenFlotante -> ImagenFlotante
interp_juntar m n f g d w h = 
        let 
        rp = n/(m+n)
        r = m/(m+n)
        wp = r V.* w
    in
        pictures [f d wp h, g (d V.+ wp) (rp V.* w) h]

-- --interpreta cualquier expresion del tipo Dibujo a
-- --utilizar foldDib 
interp :: Interpretacion a -> Dibujo a -> ImagenFlotante
interp interp_basica dib = foldDib (interp_basica)
                                   (interp_rotar) 
                                   (interp_rotar45) 
                                   (interp_espejar) 
                                   (interp_apilar) 
                                   (interp_juntar) 
                                   (interp_encimar)
                                   dib
