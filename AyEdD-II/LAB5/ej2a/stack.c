#include <stdlib.h>
#include <assert.h>
#include "stack.h"
 
typedef struct _s_stack {
    stack_elem e;
    stack next;
} stack_t;

stack stack_empty(){
    stack s = NULL;
    return s;
}

stack stack_push(stack s, stack_elem e){
    stack_t *stack_new = malloc(sizeof(struct _s_stack));
    stack_new->e = e;
    stack_new->next = s;
    return stack_new;
}

stack stack_pop(stack s){
      if(!stack_is_empty(s)){
      stack temp = s;
      s = temp->next;
      free(temp);
      }
      return s;
}

unsigned int stack_size(stack s){
    if(stack_is_empty(s)){
        return 0;
    }
    unsigned int lenght = 0;
    while(s->next != NULL){
        lenght++;
        s = stack_pop(s);
    }
    return lenght;
}

stack_elem stack_top(stack s){
    assert(s!=NULL);
    return s->e;
}

bool stack_is_empty(stack s){
    return s!=NULL;
}

stack_elem *stack_to_array(stack s){
    stack_elem *arr = NULL;
    if (!stack_is_empty(s)){
        arr = calloc(stack_size(s), sizeof(stack_elem));
        stack act_stack = s;
        unsigned int len = stack_size(s);
        for (int i = len - 1; i >= 0; --i){
            arr[i] = stack_top(act_stack);
            act_stack = act_stack->next;
        }
    }
    return arr;
}

stack stack_destroy(stack s) {
    while (s != NULL) {
        stack next_node = s->next;  
        free(s);  
        s = next_node; 
    }
    return NULL;  
}