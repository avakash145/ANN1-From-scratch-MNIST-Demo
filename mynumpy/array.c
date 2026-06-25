#include "array.h"
#include <stdio.h>
#include<stdlib.h>
size_t total_elements(const ndarray *a){
    size_t total=1;
    for(int i=0;i<a->ndim;i++)
    {
        total*=(a->shape[i]);
    }
    return total;
}
void print_shape(const ndarray* a){
    printf("Shape :(");
    for(int i=0;i<a->ndim;i++)
    {
        printf("%ld, ",a->shape[i]);
    }
    printf("\b\b)\n");
}
size_t calculate_offset(ndarray* a,size_t indices[]){
size_t offset=0;
for(int i=0;i<a->ndim;i++)
{
    if(indices[i]>=a->shape[i]){printf("Index out of bounds\n");
        exit(EXIT_FAILURE);}
offset+=indices[i]*a->strides[i];
}
return offset;
}


int get(ndarray* a, size_t indices[]){
    size_t offset=calculate_offset(a,indices);
    return *(int*)((char*)a->data+offset);
}
void set(ndarray *a,size_t indices[],int val)
{   size_t offset=calculate_offset(a,indices);
    *(int*)((char*)a->data+offset)=val;}

ndarray* slice(ndarray* a,size_t start[],size_t new_shape[]){
    ndarray *view=malloc(sizeof(ndarray));
    view->ndim=a->ndim;
view->itemsize=a->itemsize;
view->owns_data=0;
size_t offset=calculate_offset(a,start);
view->data=(char*)a->data+offset;
view->shape=malloc(a->ndim*sizeof(size_t));
for(int i=0;i<a->ndim;i++){view->shape[i]=new_shape[i];}
view->strides=malloc(a->ndim*sizeof(size_t));
for(int i=0;i<a->ndim;i++)
{view->strides[i]=a->strides[i];}
return view;
}








ndarray* create_array(int ndim,size_t shape[],size_t itemsize){
    ndarray* a=(ndarray*)malloc(sizeof(ndarray));
    a->ndim=ndim;
    a->itemsize=itemsize;
    a->shape=malloc(ndim*sizeof(size_t));
    for(int i=0;i<ndim;i++)
    {
        a->shape[i]=shape[i];
    }
    size_t total=total_elements(a);
    a->data=calloc(total,itemsize);
    calculate_strides(a);
return a;
}
void calculate_strides(ndarray* a){
    a->strides=malloc(a->ndim*sizeof(size_t));
    a->strides[a->ndim-1]=a->itemsize;
    for(int i=a->ndim-2;i>=0;i--)
    {
        a->strides[i]=(a->strides[i+1])*(a->shape[i+1]);
        }
}
void print_strides(ndarray *a)
{
    printf("(");
    for(int i=0;i<a->ndim;i++)
    {
        printf("%zu, ",a->strides[i]);
    }
    printf("\b\b)\n");
}


void free_array(ndarray *a)
{   free(a->shape);
    free(a->strides);
    if(a->owns_data)
    free(a->data);
    free(a);}

ndarray* create_view(ndarray* a){
    ndarray* view=malloc(sizeof(ndarray));
    view->ndim=a->ndim;
    view->itemsize=a->itemsize;
    view->owns_data=0;
view->data=a->data;
view->shape=malloc(view->ndim*sizeof(size_t));
for(int i=0;i<view->ndim;i++)
{
    view->shape=a->shape;
}
view->strides=malloc(view->ndim*sizeof(size_t));
for(int i=0;i<view->ndim;i++)
    view->strides[i]=a->strides[i];
    return view;
}