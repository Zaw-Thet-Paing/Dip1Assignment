#include "stdio.h"
#include "math.h"

int min(int num1, int num2){
    if(num1 > num2){
        return num2;
    }else{
        return num1;
    }
}

int JumpSearch(int arr[], int size, int key){

    int step = sqrt(size);
    int midpoint = step / 2;
    int previous = 0;

    while(arr[min(step, size)-1] < key){

        if(arr[min(step, size)-1] == key){
            return min(step, size)-1;
        }

        previous = step;
        step += sqrt(size);

        if(previous >= size){
            return -1;
        }

    }

    if(arr[previous + midpoint] > key){

        for(int j = previous; j < (previous + midpoint); j++){
            if(arr[j] == key){
                return j;
            }
        }

    }else{

        for(int j = (previous + midpoint); j < step; j++){
            if(arr[j] == key){
                return j;
            }
        }

    }

    return -1;
}

int main(){

    int arr[] = {1,2,3,4,5,6,7,8, 9,101,102,103,105,108,203};
    int size = sizeof(arr) / sizeof(arr[0]);
    int toFind = 108;

    int indexNumber = JumpSearch(arr, size, toFind);

    if(indexNumber != -1){
        printf("We found %d at index %d", toFind, indexNumber);
    }else{
        printf("Not found!");
    }

    return 0;
}