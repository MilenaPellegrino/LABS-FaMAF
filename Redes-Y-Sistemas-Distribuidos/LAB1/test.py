import requests

url = "http://localhost:5000/peliculas"

# Obtener todas las películas
response = requests.get(f"{url}")
peliculas = response.json()
print("Películas existentes:")
for pelicula in peliculas:
    print(f"ID: {pelicula['id']}, Título: {pelicula['titulo']}, "
          f"Género: {pelicula['genero']}")
print()

# Agregar una nueva película
nueva_pelicula = {
    'titulo': 'Pelicula de prueba',
    'genero': 'Acción'
}
response = requests.post(f"{url}", json=nueva_pelicula)
if response.status_code == 201:
    pelicula_agregada = response.json()
    print("Película agregada:")
    print(f"ID: {pelicula_agregada['id']}, Título: {pelicula_agregada['titulo']}, "
          f"Género: {pelicula_agregada['genero']}")
else:
    print("Error al agregar la película.")
print()

# Obtener detalles de una película específica
id_pelicula = 1  # ID de la película a obtener
response = requests.get(f'{url}/{id_pelicula}')
if response.status_code == 200:
    pelicula = response.json()
    print("Detalles de la película:")
    print(f"ID: {pelicula['id']}, Título: {pelicula['titulo']}, "
          f"Género: {pelicula['genero']}")
else:
    print("Error al obtener los detalles de la película.")
print()

# Actualizar los detalles de una película
id_pelicula = 1  # ID de la película a actualizar
datos_actualizados = {
    'titulo': 'Nuevo título',
    'genero': 'Comedia'
}
response = requests.put(f'{url}/{id_pelicula}', json=datos_actualizados)
if response.status_code == 200:
    pelicula_actualizada = response.json()
    print("Película actualizada:")
    print(f"ID: {pelicula_actualizada['id']}, Título: {pelicula_actualizada['titulo']}, "
          f"Género: {pelicula_actualizada['genero']}")
else:
    print("Error al actualizar la película.")
print()

# Eliminar una película
id_pelicula = 1  # ID de la película a eliminar
response = requests.delete(f'{url}/{id_pelicula}')
if response.status_code == 200:
    print("Película eliminada correctamente.")
else:
    print("Error al eliminar la película.")


def print_pelicula(pelicula):
    """Imprime los detalles de una película."""
    print(f"ID: {pelicula['id']}, Título: {pelicula['titulo']}, "
          f"Género: {pelicula['genero']}")


# Buscar películas que contengan una subcadena en su título
subcadena = 'LoRD'
response = requests.get(f'{url}/buscar/{subcadena}')
print(f"Buscar películas que contengan la palabra {subcadena}:")
if response.status_code == 404:
    print(f"Error al buscar la película que contiene el string: '{subcadena}'")
elif len(response.json()) == 0:
    print("Ninguna película con ese string encontrada")
else:
    peliculas_nombre = response.json()
    for pelicula in peliculas_nombre:
        print_pelicula(pelicula)
print()


genero = 'Drama'
response = requests.get(f'{url}/genero/{genero}')
if response.status_code == 200:
    peliculas = response.json()
    print(f"Películas de género '{genero}':")
    for pelicula in peliculas:
        print_pelicula(pelicula)
else:
    print(f"Error al obtener películas por género: '{genero}'.")
print()

# Sugerir una película aleatoria
response = requests.get(f"{url}/aleatoria")
if response.status_code == 200:
    pelicula_sugerida = response.json()
    print("Película sugerida:")
    print_pelicula(pelicula_sugerida)
else:
    print("Error al sugerir una película aleatoria")
print()

# Sugerir una película aleatoria según un género
genero = 'Ciencia ficción'
response = requests.get(f'{url}/aleatoria/{genero}')
if response.status_code == 200:
    pelicula = response.json()
    print(f"Película de {pelicula['genero']} sugerida:")
    print(f"Título: {pelicula['titulo']}")
else:
    print(f"Error al sugerir una película aleatoria según el género {genero}")
print()


genero = 'Acción'
response = requests.get(f'{url}/holiday/{genero}')
if response.status_code == 200:
    recomendacion = response.json()
    print("Recomendación para el próximo feriado:")
    print(f"Próximo feriado: {recomendacion['dia']}/{recomendacion['mes']}")
    print(f"Película recomendada: {recomendacion['pelicula']}")
else:
    print("Error al obtener la recomendación para el feriado.")
    print()

# TESTS DE ERRORES

# Obtener una película que no existe
id_pelicula = 99999
response = requests.get(f'{url}/{id_pelicula}')
if response.status_code == 404:
    print("Película no encontrada. Al obtener una pelicula que no existe. Test Correcto")
else:
    print("Error al obtener la película. Se esperaba un 404")
print()

# Eliminar una película que no existe
id_pelicula = 99999
response = requests.delete(f'{url}/{id_pelicula}')
if response.status_code == 404:
    print("Película no encontrada. Al eliminar una pelicula que no existe. Test Correcto. ")
else:
    print("Error al eliminar la película. Se esperaba un 404")
print()

# Actualizar una película que no existe
id_pelicula = 99999
datos_actualizados = {
    'titulo': 'Titulo actualizado',
    'genero': 'Comedia'
}
response = requests.put(f'{url}/{id_pelicula}', json=datos_actualizados)
if response.status_code == 404:
    print("Película no encontrada. Al actualizar una pelicula que no existe. Test Correcto.")
else:
    print("Error al actualizar la película. Se esperaba un 404")
print()

# Agregar una pelicula sin título
nueva_pelicula = {
    'genero': 'Acción'
}
response = requests.post(f"{url}", json=nueva_pelicula)
if response.status_code == 400:
    print("Error al agregar la película sin título. Test Correcto")
else:
    print("Película agregada sin título. Test fallido. Se esperaba un 400")
print()

# Agregar una pelicula sin genero
nueva_pelicula = {
    'titulo': 'Pelicula de prueba'
}
response = requests.post(f"{url}", json=nueva_pelicula)
if response.status_code == 400:
    print("Error al agregar la película sin género. Test Correcto")
else:
    print("Película agregada sin género. Test fallido. Se esperaba un 400")
print()

# Recomendación de películas para un género que no existe
genero = 'fdasfds'
response = requests.get(f'{url}/holiday/{genero}')
if response.status_code == 404:
    print("Error al obtener la recomendación para el feriado. Test Correcto")
else:
    print("Recomendación para un genero que no existe. Test fallido. Se esperaba un 404")
print()

# Buscar una película por un string que no existe
subcadena = 'fdasfds'
response = requests.get(f'{url}/buscar/{subcadena}')
if response.status_code == 404:
    print("Error al buscar la película que contiene el string. Test Correcto")
else:
    print("Buscar películas que contengan un string que no existe. Test fallido. Se esperaba un 404")
print()
