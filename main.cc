#include <iostream>
#include <fstream>

using namespace std;

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int bubbleSort(int* arr, int length) {
    int n = 0;
    bool isSorted = false;
    while (!isSorted) {
        isSorted = true;
        for (int i = 1; i<length; i++) {
            n++;
            if (arr[i-1]>arr[i]) {
                swap(arr+i-1,arr+i);
                isSorted = false;
                i--;
            }
        }
    }
    return n;
}

int insertionSort(int* arr, int length) {
    int n = 0;
    for (int i = 1; i<length; i++) {
        if (arr[i]<arr[i-1]) {
            int tmp = arr[i];
            for (int j = i-1; j>0; j--) {
                arr[j+1] = arr[j];
                n++;
                if (j==0||arr[j-1]<tmp) {
                    arr[j] = tmp;
                    break;
                }
            }
        }
    }
    return n;
}

int* create_array(int length, int range) {
    int* arr = new int[length];
    for (int i = 0; i<length; i++) {
        arr[i] = rand() % range;
    }
    return arr;
}

int* mostly_sorted_front(int length, int range) {
    int* arr = new int[length];
    int frontlen = length*0.75;
    for (int i = 0; i<frontlen; i++) {
        arr[i] = i;
    }
    int* arr2 = create_array(length-frontlen,range);
    //all added numbers will be greater than front
    for (int i = 0; i<length-frontlen; i++) {
        arr[frontlen+i] = arr2[i]+arr[frontlen-1];
    }
    delete[] arr2;
    return arr;
}

int* mostly_sorted_back(int length, int range) {
    int* arr = new int[length];
    int backlen = length*0.75;
    int* arr2 = create_array(length-backlen,range);
    for (int i = 0; i<length-backlen; i++) {
        arr[i] = arr2[i];
    }
    delete[] arr2;
    //all added numbers will be greater than front
    for (int i = length-backlen; i<length; i++) {
        arr[i] = range+i;
    }
    return arr;
}

int* interSorted(int length, int range) {
    int* arr = new int[length];
    for (int i = 0; i<length; i++) {
        int toPlace = rand()%20;
        for (int j = 0; i+j<length && j<toPlace; j++) {
            arr[i+j] = i+j;
        }
        i += toPlace;

        int toSkip = rand()%5;
        for (int j = 0; i+j<length && j<toSkip; j++) {
            arr[i+j] = rand() % (range+i);
        }
        i += toSkip;
    }
    return arr;
}

void display(int* arr, int length) {
    for (int i = 0; i<length; i++) {
        cout << arr[i] << ' ';
    }
    cout << '\n';
}

int main() {
    int cases;
    ifstream ins("input");
    ofstream outs("output.txt");
    ins >> cases;
    for (int i = 0; i<cases; i++) {
        int length,range,tests;
        ins >> length >> range >> tests;
        long long n0a,n0b,n1a,n1b,n2a,n2b,n3a,n3b;
        for (int j = 0; j<tests; j++) {
            int* arr0a = create_array(length,range);
            int* arr0b = new int[length];
            copy(arr0a,arr0a+length,arr0b);
            n0a += bubbleSort(arr0a,length);
            n0b += insertionSort(arr0b,length);
            delete[] arr0a;
            delete[] arr0b;
            cout << i << '/' << cases << '\t' << (j+1) << '/' << tests << '\n';
        }
        for (int j = 0; j<tests; j++) {
            int* arr1a = mostly_sorted_front(length,range*0.75);
            int* arr1b = new int[length];
            copy(arr1a,arr1a+length,arr1b);
            n1a += bubbleSort(arr1a,length);
            n1b += insertionSort(arr1b,length);
            delete[] arr1a;
            delete[] arr1b;
            cout << i << '/' << cases << '\t' << (j+1) << '/' << tests << '\n';
        }
        for (int j = 0; j<tests; j++) {
            int* arr2a = mostly_sorted_back(length,range*0.75);
            int* arr2b = new int[length];
            copy(arr2a,arr2a+length,arr2b);
            n2a += bubbleSort(arr2a,length);
            n2b += insertionSort(arr2b,length);
            delete[] arr2a;
            delete[] arr2b;
            cout << i << '/' << cases << '\t' << (j+1) << '/' << tests << '\n';
        }
        for (int j = 0; j<tests; j++) {
            int* arr3a = interSorted(length,range);
            int* arr3b = new int[length];
            copy(arr3a,arr3a+length,arr3b);
            n3a += bubbleSort(arr3a,length);
            n3b += insertionSort(arr3b,length);
            delete[] arr3a;
            delete[] arr3b;
            cout << i << '/' << cases << '\t' << (j+1) << '/' << tests << '\n';
        }
        outs << "Case " << i << ":\nBubble Sort random: " << (n0a/tests) << "\nInsertion Sort random: " << (n0b/tests);
        outs << "\nBubble Sort front sorted: " << (n1a/tests) << "\nInsertion Sort front sorted: " << (n1b/tests);
        outs << "\nBubble Sort back sorted: " << (n2a/tests) << "\nInsertion Sort back sorted: " << (n2b/tests);
        outs << "\nBubble Sort inter sorted: " << (n3a/tests) << "\nInsertion Sort inter sorted: " << (n3b/tests) << '\n';
        cout << (i+1) << " / " << cases << '\n';
    }
    cout << '\n';
    outs.close();
}