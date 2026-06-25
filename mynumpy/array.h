#ifndef NDARRAY_H
#define NDARRAY_H
#include<stdlib.h>
typedef struct
{
    void *data;
    int ndim;
    size_t *shape;
    size_t *strides;
    size_t itemsize;
    //owns_data ==1 original array / owns_data=0 view of some other data
    int owns_data;
}ndarray;
typedef struct
{
size_t start;
size_t stop;
size_t step;
}Slice;








// function defination 
ndarray* create_array(int ndim,size_t shape[],size_t itemsize);
void free_array(ndarray *a);
size_t total_elements(const ndarray *a);
void calculate_strides(ndarray* a);
void print_strides(ndarray* a);
void print_shape(const ndarray* a);
size_t calculate_offset(ndarray* a,size_t indices[]);
int get(ndarray* a, size_t indices[]);
void set(ndarray* a, size_t indices[],int val);
ndarray* create_view(ndarray* a);
ndarray* slice(ndarray* a,size_t start[],size_t new_shape[]);
#endif
