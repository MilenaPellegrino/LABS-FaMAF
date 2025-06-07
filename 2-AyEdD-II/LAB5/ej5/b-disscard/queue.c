#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "queue.h"

// Modifique todo el struct, cambiando first por front ya que agregue otro campo back que apunta al final de la cola 
struct s_queue {
    struct s_node *front; // Puntero al frente de la cola
    struct s_node *back;  // Puntero al final de la cola 
    queue_elem size;    // Tamano actual de la cola (me sirve para que sea de orden constante)
};


struct s_node {
    queue_elem elem;
    struct s_node *next;
};

static struct s_node *
create_node(queue_elem e) {
    struct s_node *new_node=malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->next = NULL;
    return new_node;
}

static struct s_node *
destroy_node(struct s_node *node) {
    node->next=NULL;
    free(node);
    node=NULL;
    return node;
}


static bool
invrep(queue q) {
    return q != NULL;
}

queue queue_empty(void) {
    queue q=NULL;
    q = malloc(sizeof(struct s_queue));
    q->front = NULL;
    q->back = NULL;
    q->size = 0;
    assert(invrep(q) && queue_is_empty(q));
    return q;
}


queue queue_enqueue(queue q, queue_elem e) {
    assert(invrep(q));
    struct s_node *new_node = create_node(e);
    if (q->back==NULL) {
        q->front = new_node;
    } else {
        q->back->next = new_node;
    }
    q->back = new_node;
    q->size++;
    assert(invrep(q) && !queue_is_empty(q));
    return q;
}

bool queue_is_empty(queue q) {
    assert(invrep(q));
    return q->size == 0; // Cambio la implementacin ya que agregue el campo del tamano
}

queue_elem queue_first(queue q) {
    assert(invrep(q) && !queue_is_empty(q));
    return q->front->elem;
}

unsigned int queue_size(queue q) {
    assert(invrep(q));
    unsigned int size=0;
    size = q->size;
    return size;
}

queue queue_dequeue(queue q) {
    assert(invrep(q) && !queue_is_empty(q));
    struct s_node * killme=q->front;
    q->front = q->front->next;
    killme = destroy_node(killme);
    assert(invrep(q));
    return q;

}
// Implementacion nueva
queue queue_disscard(queue q, unsigned int n) {
    assert(invrep(q) && n < q->size);
    if (n == 0) return queue_dequeue(q);
    struct s_node *current = q->front;
    for (unsigned int i = 0; i < n - 1; ++i) {
        current = current->next;
    }
    struct s_node *temp = current->next;
    current->next = temp->next;
    if (temp == q->back) {
        q->back = current;
    }
    free(temp);
    q->size--;
    return q;
}
void queue_dump(queue q, FILE *file) {
    file = file==NULL ? stdout: file;
    struct s_node *node=q->front;
    fprintf(file, "[ ");
    while(node!=NULL) {
        fprintf(file, "%d", node->elem);
        node = node->next;
        if (node != NULL) {
            fprintf(file, ", ");
        }
    }
    fprintf(file, "]\n");
}

queue queue_destroy(queue q) {
    assert(invrep(q));
    struct s_node *node=q->front;
    while (node != NULL) {
        struct s_node *killme=node;
        node = node->next;
        killme = destroy_node(killme);
    }
    free(q);
    q = NULL;
    assert(q == NULL);
    return q;
}

