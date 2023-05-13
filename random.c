#include <stdio.h>
#include <sys/random.h>
#include <assert.h>

typedef unsigned char u8;

const unsigned char generate_byte(const unsigned char upper_bound){ // generates numbers in the range [0, upper_bound] - all inclusive!
    // I have thoroughly tested this function and informally proved that it is correct to my satisfaction.
	// this function will reject up to half of all generated numbers
	// this is a bit inefficient, but is ok when speed doesn't matter
    // you can fairly easily extend this to more than 255 by interpreting multiple bytes as 32 or 64 bit integer
    // you can also make a batch version, which would be faster
    const int n = 256; // the number of numbers that our input range contains
    assert(upper_bound < n); // the biggest number we can generate, given our input range
    const int range = upper_bound + 1; // the number of numbers in our output range
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

int main(){
    for (int i = 0; i < 1000; i++){
        u8 x = generate_byte(2);
        printf("random number: %u\n", x);
    }
}
