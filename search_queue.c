#include "search_queue.h"
#include "bstree.h"
#include "stdlib.h"

struct _SearchQueue {
  BSTree *data;
};

SearchQueue *search_queue_new(P_ele_print print_ele, P_ele_cmp cmp_ele) {

  SearchQueue *q = NULL;

  if (!print_ele || !cmp_ele)
    return NULL;

  if (!(q = (SearchQueue *)malloc(sizeof(SearchQueue))))
    return NULL;

  if (!(q->data = tree_init(print_ele, cmp_ele))) {
    free(q);
    return NULL;
  }

  return q;
}

void search_queue_free(SearchQueue *q) {
  if (!q)
    return;

  if (q->data) tree_destroy(q->data);

  free(q);
  return;
}

Bool search_queue_isEmpty(const SearchQueue *q) {
  if (!q)
    return TRUE;

  return tree_isEmpty(q->data);
}

Status search_queue_push(SearchQueue *q, void *ele) {
  if (!q || !ele)
    return ERROR;

  if (tree_insert(q->data, ele) == ERROR)
    return ERROR;

  return OK;
}

void *search_queue_pop(SearchQueue *q){
  void *aux = NULL;
  
  if (!q || search_queue_isEmpty(q)) return NULL;
  
  aux = tree_find_min(q->data);

  tree_remove(q->data, tree_find_min(q->data));

  return aux;
}

void *search_queue_getFront(const SearchQueue *q){
  if (!q || search_queue_isEmpty(q)) return NULL;

  return tree_find_min(q->data);
}

void *search_queue_getBack(const SearchQueue *q){
  if (!q || search_queue_isEmpty(q)) return NULL;

  return tree_find_max(q->data);
}

size_t search_queue_size(const SearchQueue *q){
  if (!q)
    return 0;

  return tree_size(q->data);
}

BSTree *search_queue_get_tree (const SearchQueue *q){
  if (!q) return NULL;

  return q->data;
}

int search_queue_print(FILE *fp, const SearchQueue *q){
  if (!fp || !q)
    return -1;

  return tree_inOrder(fp, q->data);
}
