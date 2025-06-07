# test.py

import pytest
from main import app

@pytest.fixture
def client():
    app.testing = True  # activa el modo de testing de Flask
    with app.test_client() as client:
        yield client

def test_obtener_peliculas(client):
    response = client.get('/peliculas')
    assert response.status_code == 200
    data = response.get_json()
    # Dependiendo del estado inicial de 'peliculas', ajustar la cantidad de elementos esperados
    assert isinstance(data, list)
    # Ejemplo: verificar que haya al menos 12 películas
    assert len(data) >= 12

def test_agregar_pelicula(client):
    nueva_pelicula = {'titulo': 'Pelicula de prueba', 'genero': 'Acción'}
    response = client.post('/peliculas', json=nueva_pelicula)
    assert response.status_code == 201
    data = response.get_json()
    assert data['titulo'] == 'Pelicula de prueba'
    assert data['id'] == 13

def test_obtener_detalle_pelicula(client):
    response = client.get('/peliculas/1')
    # Esto dependerá de que la función 'obtener_pelicula' esté implementada correctamente
    # Aquí se espera un 200 y los detalles de la película con id 1
    assert response.status_code == 200
    data = response.get_json()
    assert data['titulo'] == 'Indiana Jones'

def test_actualizar_detalle_pelicula(client):
    datos_actualizados = {'titulo': 'Nuevo título', 'genero': 'Comedia'}
    response = client.put('/peliculas/1', json=datos_actualizados)
    # Verifica el status code y los cambios realizados
    assert response.status_code == 200
    data = response.get_json()
    assert data['titulo'] == 'Nuevo título'

def test_eliminar_pelicula(client):
    response = client.delete('/peliculas/1')
    assert response.status_code == 200
    data = response.get_json()
    assert 'mensaje' in data
    response = client.get('/peliculas/1')
    assert response.status_code == 404
    response = client.delete('/peliculas/1')
    assert response.status_code == 404

def test_obtener_peliculas_por_genero(client):
    response = client.get('peliculas/Drama')
    assert response.status_code == 200
    data = response.get_json()
    assert isinstance(data, list)
    assert len(data) >= 2
    response = client.get('peliculas/Acción')
    assert response.status_code == 200
    data = response.get_json()
    assert isinstance(data, list)
    assert len(data) >= 4
    response = client.get('peliculas/Hola')
    assert response.status_code == 404 

def test_busqueda_de_peliculas(client):
    response = client.get('peliculas/buscar/in')
    assert response.status_code == 200
    data = response.get_json()
    assert isinstance(data, list)
    assert len(data) == 3 
    response = client.get('peliculas/buscar/initial')
    assert response.status_code == 404

def test_pelicula_aleatoria(client):
    response = client.get('peliculas/aleatoria')
    assert response.status_code == 200
    data = response.get_json()
    assert isinstance(data, dict)
    assert len(data) == 3
    assert data['titulo'] != ''

def test_aleatoria_genero(client):
    response = client.get('/peliculas/aleatoria/Drama')
    assert response.status_code == 200
    data = response.get_json()
    assert data['genero'] == 'Drama'
    response = client.get('/peliculas/aleatoria/Rama')
    assert response.status_code == 404

def test_recomendar_para_holiday(client):
    response = client.get('/peliculas/holiday/Acción')
    assert response.status_code == 200
    data = response.get_json()
    assert data['genero'] == 'Acción'
    response = client.get('/peliculas/holiday/Rama')
    assert response.status_code == 404
