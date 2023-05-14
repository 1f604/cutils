#include <stdio.h>

typedef unsigned char u8;

void print_array(
    const char* name,
    const u8* array,
    int num_elements
){
    printf("%s: [", name);
    if (num_elements == 0){
        printf("]\n");
        return;
    }
    for (int i = 0; i < num_elements-1; i++){
        printf("%u, ", array[i]);
    }
    printf("%u", array[num_elements-1]);
    printf("]\n");
}

int main(){
    u8 arr[10] = {1,2,3,4};
    print_array("arr", arr, 5);
}