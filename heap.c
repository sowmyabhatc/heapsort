#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "heap.h"


static void _swap_(int32_t *data1,int32_t *data2){
int32_t temp;
temp=*data1;
*data1=*data2;
*data2=temp;
}


static void _heapify_(int32_t data[],uint32_t len,uint32_t parent){  //index of the parent
assert(len>0 && len<HEAP_MAX_SIZE && parent>0);
uint32_t child=2*parent; //location of left child

while(child<=len){
    if(child+1 <=len){  //notedown the index of max child
        if(data[child+1]>data[child]){ //if value of right child >left child
            ++child;   //we increment child index to right child
        }
    }
    if(data[parent]>=data[child]){  //if value of parent is greater than data of max child
        break;
    }
    _swap_(&data[parent],&data[child]);  //else swap value
    parent=child;
    child=2*parent;
}

}

static void _test_Heap_(int32_t data[],uint32_t len){

for(uint32_t child=len; child>1; --child){
    assert(data[child]<=data[child/2]); //aserts if value of child <value of parent
}
}

Heap*  heap_test(Heap *heap){
assert(heap->size >0 && heap->size < HEAP_MAX_SIZE);
_test_Heap_(heap->data,heap->size);
return heap;

}

uint32_t heap_size(Heap *heap){
assert(heap->size >0 && heap->size < HEAP_MAX_SIZE);
return(heap->size);
}

Heap* heap_sort(Heap *heap){
assert(heap->size >0 && heap->size < HEAP_MAX_SIZE);
uint32_t idx=heap->size;
for(idx=heap->size; idx>1 ;idx--){  //idx-- bcz after every swap we are going to remove the terminal node from the next step.
    _swap_(&heap->data[idx],&heap->data[1]);
    _heapify_(heap->data,idx-1,1); // after swapping heap property will be lost only at the root node hence donot give len/2
}
return heap;
}

Heap  heap_new(int32_t data[],uint32_t len){
assert(len>0 && len<HEAP_MAX_SIZE );

Heap heap;

for(uint32_t idx=len/2;idx>0; --idx){

    _heapify_(data,len,idx);
}
heap.size=len;
memcpy(heap.data,data,(len+1)*sizeof(int32_t)); //first parameter is the destination,second para is the source,third para is the length or how many elements we want to store
_test_Heap_(heap.data,heap.size);

return heap;
}


//insert a new element into the heap
Heap*   heap_insert(Heap *heap,int32_t key){
assert(heap->size >0 && heap->size < HEAP_MAX_SIZE);
uint32_t idx=heap->size+1;
heap->data[idx]=key;
for(uint32_t i=idx/2; i>1 ;--i){
_heapify_(heap->data,idx,i);
}
++heap->size;
return heap;

}


//extract max element from the heap

int32_t heap_extract_max(Heap *heap){
assert(heap->size >0 && heap->size < HEAP_MAX_SIZE);
int32_t max=heap->data[1];
int32_t last=heap->data[heap->size];
heap->data[1]=last;
heap->size= heap->size-1;
_heapify_(heap->data,heap->size,1);




return max;

}

//get maxmimum element from the heap

int32_t heap_get_max(Heap *heap){
return (heap->data[1]);
}
