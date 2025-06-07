# Script de pruebas para la API de películas.

# Obtener todas las películas
curl -X GET http://localhost:5000/peliculas

echo ""

# Obtener una película por ID 
curl -X GET http://localhost:5000/peliculas/6

echo ""

# Agregar una nueva película 
curl -X POST http://localhost:5000/peliculas \
-H "Content-Type: application/json" \
-d '{"titulo": "Los simuladores la pelicula", "genero": "Aventura"}'

echo ""

# Actualizar una película por ID 
curl -X PUT http://localhost:5000/peliculas/3 \
-H "Content-Type: application/json" \
-d '{"titulo": "FaAMAF: La pelicula", "genero": "Terror"}'

echo ""

# Eliminar una película por ID
curl -X DELETE http://localhost:5000/peliculas/7

echo ""

# Buscar películas por título
curl -X GET "http://localhost:5000/peliculas/buscar/Star%20Wars"

echo ""

# Obtener películas por género 
curl -X GET http://localhost:5000/peliculas/Acción

echo ""

# Obtener una película aleatoria
curl -X GET http://localhost:5000/peliculas/aleatoria
