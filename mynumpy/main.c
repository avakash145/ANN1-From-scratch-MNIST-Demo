#include<stdio.h>
#include "array.h"

int main()
{
   
size_t shape[]={3,4};
ndarray* a=create_array(2,shape,sizeof(int));
int o=10;
for(int i=0;i<3;i++)
{
    for(int j=0;j<4;j++)
    {
        size_t k[]={i,j};
        set(a,k,o);
        o+=10;
}}
size_t start[]={0,1};
size_t shape1[]={3,2};
ndarray *b=
slice(
a,
start,
shape1);
size_t idx[]={1,0};
printf("%d\n",get(a,idx)); 
printf("%d\n",get(a,idx));
    free_array(a);
}