module Basica.Ejemplo where
import Dibujo
import Interp
import Basica.Comun

type Basica = ()

ejemplo :: Dibujo Basica
-- ejemplo = Apilar 1.0 1.0 (Basica ()) (Basica ())
ejemplo = encimar (ciclar (Basica())) (Basica()) 
-- ejemplo = cuarteto (Basica()) (Basica()) (Basica()) (Basica())

interpBas :: Basica -> ImagenFlotante
interpBas () = trianguloVioleta
