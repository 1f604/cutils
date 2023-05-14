#include <stdio.h>
#include <sys/random.h>
#include <assert.h>

typedef unsigned char u8;

const unsigned char generate_byte(const unsigned char upper_bound){ // generates numbers in the range [0, upper_bound] - all inclusive!
    // This function has no dependencies.
    // I have thoroughly tested this function and informally proved that it is correct to my satisfaction.
    // this function will reject up to half of all generated numbers
    // this is a bit inefficient, but is ok when speed doesn't matter
    // you can fairly easily extend this to more than 255 by interpreting multiple bytes as 32 or 64 bit integer
    // you can also make a batch version, which would be faster
    const int n = 256; // the number of numbers in our input space
    assert(upper_bound < n); // the biggest number we can generate, given our input range
    const int range = upper_bound + 1; // the number of numbers in our output space
    //printf("range:%u\n", range);
    unsigned char array[1];
    const int nearest_multiple = (n - (n % range));
    assert(nearest_multiple >= n / 2);
    //printf("nearest multiple: %d\n", nearest_multiple);
    while (1){
        int r = getrandom(array, 1, 0); // generate one random byte
        assert(r == 1); // verify that we got one byte back
        unsigned char x = array[0];
        if (x < nearest_multiple){
            //printf("generated: %u\n", x);
            return x % range;
        }
    }
}


void choose_without_replacement( 
    // this function is limited to arrays of up to 255 elements due to generate_byte, see below
    #define ELEMENT_TYPE u8
    // the #define macro is to make this function generic, so feel free to replace u8 with some other type.
    const ELEMENT_TYPE* input_array,
    ELEMENT_TYPE* output_array, // caller must allocate this, but does not need to initialize it
    int input_array_length, // number of elements in input and output array
    int output_array_length, // number of elements in input and output array
    int elements_to_pick // number of elements to randomly pick from the input array
){
    assert(input_array_length == output_array_length);
    assert(elements_to_pick <= input_array_length);
    assert(elements_to_pick < 256); // limitation due to generate_byte
    // first, copy input array into output array
    memcpy(output_array, input_array, sizeof(ELEMENT_TYPE) * input_array_length);
    // next, pick random elements and swap them to the front of the output array
    // this is basically a Knuth shuffle
    for (int i = 0; i < elements_to_pick; i++) {
        // initially we choose between 0 and n-1
        // next we choose between 1 and n-1, and so on
        unsigned char rand_num = generate_byte(input_array_length - 1 - i); 
        int random_index = i + rand_num;
        // swap the ith element with the randomly chosen element
        ELEMENT_TYPE ith_element = output_array[i];
        output_array[i] = output_array[random_index];
        output_array[random_index] = ith_element;
    }
    return;
}


int main(){
    // demo generate_byte
    for (int i = 0; i < 5; i++){
        u8 x = generate_byte(5);
        printf("random number: %u\n", x);
    }
    // demo choose_without_replacement
    u8 input_array[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    u8 output_array[10];
    int elements_to_pick = 5;
    choose_without_replacement(input_array, output_array, 10, 10, elements_to_pick);

    printf("new array: [ ");
    for (int i = 0; i < elements_to_pick; i++){
        printf("%u ", output_array[i]);
    }
    printf("]\n");
}
