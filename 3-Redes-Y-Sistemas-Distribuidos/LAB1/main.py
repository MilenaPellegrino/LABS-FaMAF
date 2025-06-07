from flask import Flask, jsonify, request
import random
from proximo_feriado import NextHoliday, day_of_week

from urllib.parse import unquote

app = Flask(__name__)
peliculas = [{
    'id': 1,
    'titulo': 'Indiana Jones',
    'genero': 'Acción'
}, {
    'id': 2,
    'titulo': 'Star Wars',
    'genero': 'Acción'
}, {
    'id': 3,
    'titulo': 'Interstellar',
    'genero': 'Ciencia ficción'
}, {
    'id': 4,
    'titulo': 'Jurassic Park',
    'genero': 'Aventura'
}, {
    'id': 5,
    'titulo': 'The Avengers',
    'genero': 'Acción'
}, {
    'id': 6,
    'titulo': 'Back to the Future',
    'genero': 'Ciencia ficción'
}, {
    'id': 7,
    'titulo': 'The Lord of the Rings',
    'genero': 'Fantasía'
}, {
    'id': 8,
    'titulo': 'The Dark Knight',
    'genero': 'Acción'
}, {
    'id': 9,
    'titulo': 'Inception',
    'genero': 'Ciencia ficción'
}, {
    'id': 10,
    'titulo': 'The Shawshank Redemption',
    'genero': 'Drama'
}, {
    'id': 11,
    'titulo': 'Pulp Fiction',
    'genero': 'Crimen'
}, {
    'id': 12,
    'titulo': 'Fight Club',
    'genero': 'Drama'
}]


id_disponible: list[int] = []


def obtener_peliculas():
    """Devuelve la lista de todas las películas."""
    return jsonify(peliculas)


def buscar_pelicula_id(id: int) -> dict | None:
    """Busca una película por su ID y la devuelve si existe."""
    for pelicula in peliculas:
        if pelicula['id'] == id:
            return pelicula
    return None


def obtener_pelicula(id: int) -> int:
    """Devuelve una película por su ID."""
    pelicula_encontrada = buscar_pelicula_id(id)
    if pelicula_encontrada is None:
        return jsonify({'mensaje': 'Película no encontrada'}), 404
    return jsonify(pelicula_encontrada), 200


def obtener_nuevo_id():
    """Genera un nuevo ID para una película."""
    if len(peliculas) > 0:
        if len(id_disponible) > 0:
            return id_disponible.pop()
        else:
            ultimo_id = peliculas[-1]['id']
            return ultimo_id + 1
    else:
        return 1


def agregar_pelicula():
    """Añade una nueva película."""
    datos = request.json
    if 'titulo' not in datos or 'genero' not in datos:
        return jsonify({'error': 'Faltan datos'}), 400
    nueva_pelicula = {
        'id': obtener_nuevo_id(),
        'titulo': request.json['titulo'],
        'genero': request.json['genero']
    }
    peliculas.append(nueva_pelicula)
    print(peliculas)
    return jsonify(nueva_pelicula), 201


def actualizar_pelicula(id: int):
    """Actualiza una película existente."""
    pelicula = buscar_pelicula_id(id)
    if pelicula is None:
        return jsonify({'error': 'Película no encontrada'}), 404
    pelicula['titulo'] = request.json['titulo']
    pelicula['genero'] = request.json['genero']
    return jsonify(pelicula), 200


def eliminar_pelicula(id: int):
    """Elimina una película por su ID."""
    pelicula = buscar_pelicula_id(id)
    if pelicula is None:
        return jsonify({'error': 'Película no encontrada'}), 404
    id_disponible.append(id)
    peliculas.remove(pelicula)
    return jsonify({'mensaje': (f'Película con el ID {id} '
                                'eliminada correctamente')}), 200


def obtener_peliculas_por_genero(genero: str):
    """Devuelve las películas de un género específico."""
    peliculas_por_genero = []
    for pelicula in peliculas:
        if pelicula['genero'].lower() == genero.lower():
            peliculas_por_genero.append(pelicula)
    if not peliculas_por_genero:
        return jsonify({'mensaje': ('No se encontraron películas '
                                    'con ese género')}), 404
    return jsonify(peliculas_por_genero), 200


def busqueda_de_peliculas(titulo: str):
    """Busca películas por una subcadena de su título."""
    titulo = unquote(titulo)
    peliculas_encontradas = []
    for pelicula in peliculas:
        if titulo.lower() in pelicula['titulo'].lower():
            peliculas_encontradas.append(pelicula)
    if not peliculas_encontradas:
        return jsonify({'mensaje': ('No se encontraron '
                                    'películas con ese título')}), 404
    return jsonify(peliculas_encontradas)


def pelicula_aleatoria():
    """Devuelve una película aleatoria."""
    if not peliculas:
        return jsonify({'mensaje': 'La lista esta vacia'}), 404
    pelicula_aleatoria = random.choice(peliculas)
    return jsonify(pelicula_aleatoria), 200


def pelicula_aleatoria_por_genero(genero: str):
    """Devuelve una película aleatoria de un género específico."""
    peliculas_por_genero = obtener_peliculas_por_genero(genero)
    if (isinstance(peliculas_por_genero, tuple)
            and peliculas_por_genero[1] == 404):
        return jsonify({'mensaje': 'No hay películas de ese género'}), 404
    peliculas_por_genero = peliculas_por_genero[0].json
    pelicula_aleatoria = random.choice(peliculas_por_genero)
    return jsonify(pelicula_aleatoria), 200


def recomendar_para_holiday(genero: str):
    """Recomienda una película según el género para el próximo feriado."""
    holiday = NextHoliday()
    holiday.fetch_holidays()
    nextholiday = holiday.holiday
    peli = pelicula_aleatoria_por_genero(genero)
    if isinstance(peli, tuple) and peli[1] == 404:
        return jsonify({'mensaje': 'No hay películas de ese género'}), 404
    peli = peli[0].json
    res = {
        'dia': str(day_of_week(
            nextholiday['dia'],
            nextholiday['mes'],
            holiday.year
        )) + ' ' + str(nextholiday['dia']),
        'mes': nextholiday['mes'],
        'motivo': str(nextholiday['motivo']),
        'pelicula': str(peli['titulo']),
        'genero': str(peli['genero'])
    }
    return jsonify(res), 200


app.add_url_rule('/peliculas',
                 'obtener_peliculas',
                 obtener_peliculas,
                 methods=['GET'])
app.add_url_rule('/peliculas/<int:id>',
                 'obtener_pelicula',
                 obtener_pelicula,
                 methods=['GET'])
app.add_url_rule('/peliculas',
                 'agregar_pelicula',
                 agregar_pelicula,
                 methods=['POST'])
app.add_url_rule('/peliculas/<int:id>',
                 'actualizar_pelicula',
                 actualizar_pelicula,
                 methods=['PUT'])
app.add_url_rule('/peliculas/<int:id>',
                 'eliminar_pelicula',
                 eliminar_pelicula,
                 methods=['DELETE'])

app.add_url_rule('/peliculas/buscar/<titulo>',
                 'busqueda_de_peliculas',
                 busqueda_de_peliculas,
                 methods=['GET'])
app.add_url_rule('/peliculas/<genero>',
                 'obtener_peliculas_por_genero',
                 obtener_peliculas_por_genero,
                 methods=['GET'])
app.add_url_rule('/peliculas/aleatoria',
                 'pelicula_aleatoria',
                 pelicula_aleatoria,
                 methods=['GET'])
app.add_url_rule('/peliculas/aleatoria/<genero>',
                 'pelicula_aleatoria_por_genero',
                 pelicula_aleatoria_por_genero,
                 methods=['GET'])
app.add_url_rule('/peliculas/holiday/<genero>',
                 'recomendar_para_holiday',
                 recomendar_para_holiday,
                 methods=['GET'])

if __name__ == '__main__':
    app.run(host='0.0.0.0')
