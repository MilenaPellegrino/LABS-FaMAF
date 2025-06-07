#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "abb.h"

struct _s_abb {
    abb_elem elem;
    struct _s_abb *left;
    struct _s_abb *right;
};

static bool elem_eq(abb_elem a, abb_elem b) {
    return a == b;
}

static bool elem_less(abb_elem a, abb_elem b) {
    return a < b;
}

static bool invrep(abb tree) {
    // Check:
    // - Todos los elementos en la parte izquierda del subarbol son menores que la raiz
    // - Todos los elementos en la parte derecha del subarte son mayores que a raiz
    if (tree == NULL) {
        return true;
    }
    return (tree->left == NULL || elem_less(tree->left->elem, tree->elem)) &&
           (tree->right == NULL || elem_less(tree->elem, tree->right->elem)) &&
           invrep(tree->left) && invrep(tree->right);
}

abb abb_empty(void) {
    abb tree;
    tree = NULL;  // Un árbol vacío está representado por un puntero NULL
    assert(invrep(tree) && abb_is_empty(tree));
    return tree;
}

abb abb_add(abb tree, abb_elem e) {
    assert(invrep(tree));

    if (abb_is_empty(tree)) {
        // Creamos un nuevo nodo para el elemento 
        tree = malloc(sizeof(struct _s_abb));
        tree->elem = e;
        tree->left = NULL;
        tree->right = NULL;
    } else if (elem_less(e, tree->elem)) {  
        // Si el elemento es menor, anadimos el elemento recursivamente en la parte izquierda

        tree->left = abb_add(tree->left, e);
    } else if (elem_less(tree->elem, e)) {
        // Si el elemento es mayor, anadimos el elemento recursivamente en la parte izquierda
        tree->right = abb_add(tree->right, e);
    }

    assert(invrep(tree) && abb_exists(tree, e));
    return tree;
}

bool abb_is_empty(abb tree) {
    bool is_empty=false;
    assert(invrep(tree));
    is_empty = tree == NULL;
    return is_empty;
}

bool abb_exists(abb tree, abb_elem e) {
    assert(invrep(tree));

    if (abb_is_empty(tree)) {
        // En un arbol vacio ps no esta el elemento, ya que obviamente no hay elementos
        return false;
    } else if (elem_eq(e, tree->elem)) {
        // Encontramos el elemento en el nodo actual
        return true;
    } else if (elem_less(e, tree->elem)) {
        // Buscamos el elementos en la parte izquierda 
        return abb_exists(tree->left, e);
    } else {
        // Buscamos el elementos en la parte derecha
        return abb_exists(tree->right, e);
    }
    
}


unsigned int abb_length(abb tree) {
    unsigned int length=0;
    assert(invrep(tree));
    if(abb_is_empty(tree))
    {
        return length;
    }
    length = 1 + abb_length(tree->right) + abb_length(tree->left);
    assert(invrep(tree) && (abb_is_empty(tree) || length > 0));
    return length;
}

abb abb_remove(abb tree, abb_elem e) {
  assert(invrep(tree));

  // SI el arbol esta vacio no eliminamos nada
  if (abb_is_empty(tree)) {
    return tree;
  }

  // Eliminación recursiva en el subárbol izquierdo o derecho
  else if (elem_less(e, tree->elem)) {
    // Elimina el elemento 'e' del subárbol izquierdo
    tree->left = abb_remove(tree->left, e);
  } else if (elem_less(tree->elem, e)) {
    // Elimina el elemento 'e' del subárbol derecho
    tree->right = abb_remove(tree->right, e);
  } else {  // Elemento encontrado: eliminación del nodo actual

    // Maneja los tres casos de eliminación del nodo actual
    if (tree->left == NULL) {
      // Nodo hoja (sin hijos o solo hijo derecho)
      abb temp = tree;
      tree = tree->right;
      free(temp);
    } else if (tree->right == NULL) {
      // Nodo con un hijo (solo hijo izquierdo)
      abb temp = tree;
      tree = tree->left;
      free(temp);
    } else {
      // Nodo con dos hijos: encuentra el sucesor en orden y reemplaza el nodo
      abb temp = tree->right;
      while (temp->left != NULL) {
        temp = temp->left;
      }
      tree->elem = temp->elem;
      tree->right = abb_remove(tree->right, temp->elem);
    }
  }
  assert(invrep(tree));
  return tree;
}

abb_elem abb_root(abb tree) {
    abb_elem root;
    assert(invrep(tree) && !abb_is_empty(tree));
    root = tree->elem;
    assert(abb_exists(tree, root));
    return root;
}

abb_elem abb_max(abb tree) {
    abb_elem max_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    // El elemento máximo se encuentra en el subárbol más a la derecha
    if (abb_is_empty(tree->right)) {
        // Si el hijo derecho está vacío, el nodo actual es el máximo
        max_e = abb_root(tree);
        return max_e;
    } else {
        // De lo contrario buscamos recursivamente el elemento máximo en el subárbol derecho
        max_e = abb_max(tree->right);
        assert(invrep(tree) && abb_exists(tree, max_e)); 
    }

    return max_e;
}

// HAcemos lo mismo que en el anterior solo que en la parte izquierda, donde estan los menores 
abb_elem abb_min(abb tree) {
    abb_elem min_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    if (abb_is_empty(tree->left))
    {
        min_e = abb_root(tree);
    }else{
        min_e = abb_min(tree->left);
    }
    assert(invrep(tree) && abb_exists(tree, min_e));
    return min_e;
}

// MODIFIQUE LA FUNCION PARA QUE SOLO LO IMPRIMA ENTONCES LA PUEDO USAR EN EL MAIN 
void abb_dump(abb tree) {
    assert(invrep(tree));
    /*
     * c) Needs implementation: use the dump order indicated by `ord`
     *
     */

    // Implementing in-order as default
    if (tree != NULL) {
        abb_dump(tree->left);
        printf("%d ", tree->elem);
        abb_dump(tree->right);
    }
}

abb abb_destroy(abb tree) {
    assert(invrep(tree));
    if (abb_is_empty(tree))
    {
        free(tree);
        tree = NULL;
        return tree;
    }
    tree->right = abb_destroy(tree->right);
    tree->left = abb_destroy(tree->left);
    free(tree);
    tree = NULL;
    assert(tree == NULL);
    return tree;
}

