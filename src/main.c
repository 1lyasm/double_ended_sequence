#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct DESequence {
  int extra_sp_f;
  int expansion_f;
  int n;
  int size;
  int *arr;
  int start;
  int end;
};

void build(struct DESequence *deseq, int n) {
  assert(n > 0);
  (*deseq).extra_sp_f = 3;
  (*deseq).expansion_f = 3;
  (*deseq).arr = calloc(deseq->extra_sp_f, sizeof(int));
  (*deseq).n = n;
  (*deseq).size = n * (*deseq).extra_sp_f;
  (*deseq).start = n;
  (*deseq).end = 2 * n - 1;
  return;
}

int get_at(struct DESequence *deseq, int idx) {
  assert(idx <= (*deseq).n - 1);
  assert(idx >= 0);
  return (*deseq).arr[(*deseq).start + idx];
}

void set_at(struct DESequence *deseq, int idx, int item) {
  assert(idx <= (*deseq).n - 1);
  assert(idx >= 0);
  (*deseq).arr[(*deseq).start + idx] = item;

  return;
}

void insertl(struct DESequence *deseq, int item) {
  (*deseq).n++;
  if ((*deseq).end < (*deseq).size - 1) {
    (*deseq).end++;
    (*deseq).arr[(*deseq).end] = item;
    return;
  }
  int *new_arr = calloc((*deseq).size * (*deseq).expansion_f, sizeof(int));
  for (int i = (*deseq).start; i <= (*deseq).end; i++) {
    new_arr[(*deseq).size + i] = (*deseq).arr[i];
  }
  free(deseq->arr);
  (*deseq).arr = new_arr;
  (*deseq).start += (*deseq).size;
  (*deseq).end = 2 * (*deseq).size - 1;
  (*deseq).size *= (*deseq).expansion_f;
  (*deseq).end++;
  (*deseq).arr[(*deseq).end] = item;
  return;
}

void insertf(struct DESequence *deseq, int item) {
  (*deseq).n++;
  if ((*deseq).start > 0) {
    (*deseq).start--;
    (*deseq).arr[(*deseq).start] = item;
    return;
  }
  int *new_arr = calloc((*deseq).size * (*deseq).expansion_f, sizeof(int));
  for (int i = (*deseq).start; i <= (*deseq).end; i++) {
    new_arr[(*deseq).size + i] = (*deseq).arr[i];
  }
  free(deseq->arr);
  (*deseq).arr = new_arr;
  (*deseq).start += (*deseq).size;
  (*deseq).end += (*deseq).size;
  (*deseq).size *= (*deseq).expansion_f;
  (*deseq).start--;
  (*deseq).arr[(*deseq).start] = item;
  return;
}

int deletel(struct DESequence *deseq) {
  assert((*deseq).n > 0);
  int deleted = (*deseq).arr[(*deseq).end];
  (*deseq).n--;
  (*deseq).end--;
  return deleted;
}

int deletef(struct DESequence *deseq) {
  assert((*deseq).n > 0);
  int deleted = (*deseq).arr[(*deseq).start];
  (*deseq).n--;
  (*deseq).start++;
  return deleted;
}

int size(struct DESequence *deseq) { return (*deseq).size; }

int len(struct DESequence *deseq) { return (*deseq).n; }

void print(struct DESequence *deseq) {
  printf("Sequence: ");
  for (int i = (*deseq).start; i <= (*deseq).end; i++) {
    printf("%d ", (*deseq).arr[i]);
  }
  printf("\n");
  return;
}

void dump(struct DESequence *deseq) {
  printf("Sequence dump: ");
  for (int i = 0; i < (*deseq).size; i++) {
    printf("%d ", (*deseq).arr[i]);
  }
  printf("\n");
  return;
}

int main() {
  int n = 1;
  struct DESequence deseq;
  build(&deseq, n);
  set_at(&deseq, 0, -1);
  printf("Set element at index 0 to -1\n");
  for (int i = 1; i < 10; i++) {
    insertf(&deseq, i);
    printf("Insert %d to the front\n", i);
  }
  printf("\n");
  for (int i = 1; i < 10; i++) {
    int deleted = deletel(&deseq);
    printf("Delete last element %d\n", deleted);
    printf("Sequence length: %d\n", len(&deseq));
    printf("Sequence size: %d\n", size(&deseq));
    dump(&deseq);
    print(&deseq);
    printf("\n");
  }
  free(deseq.arr);
  return 0;
}
