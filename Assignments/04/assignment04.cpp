/*Justin Mang 556002335 CMPT 471 SPRING 2018 Assignment 04*/


#include <string>
#include <iostream>
#include <math.h>
using namespace std;

//performs substitution on a given plaintext string
//key: a given key as an int
//addOrSub: 1 for add, 0 for subtract for a given key on a string
//str: a given string
//keyArr: the array in which the key is stored
//keyLength: the length of a key
string substitutionFunc (string str, int *keyArr, int key, int keyLength, int addOrSub);

//determines the length of a key
//base: the numerical base of the key
//key: the key as an int
int intGetLength (int key, int base);

//stores a key in an array
int* intStoreInArr (int* keyArr, int key, int keyLength);

//prints an array
void printRevArr (int* arr, int length);
void printArr (int* arr, int length);
void performFunctions(int key, string str);
void transposeFunc (int keyLength, string str, int key, int rowOrCol, int encryptDecryptNeither, int* keyArr);
void quickSort(int arr[], int arr2[], int low, int high);
int partition (int arr[], int arr2[], int low, int high);
void swap(int* a, int* b);

int main()
{
    performFunctions(94546, "this is a test MESSAGE, it uses spaces, exclaimations, and question marks!?");
    return 0;
}

void performFunctions(int key, string str)
{
    //string variables
    string encryptedStr;
    string decryptedStr;
    cout << "Plaintext: " << str << "\n";
    
    //key variables
    int keyLength = 0;
    int base = 10;
    cout << "Key: " << key << "\n";
    
    //determine length of key
    keyLength = intGetLength(key, base);
    //generate array for key
    int keyArr[keyLength];
    //store key
    intStoreInArr (keyArr, key, keyLength);
    //test print key
    printArr (keyArr, keyLength);
    
    cout << "Ciphertext: ";
    //substitution encryption method
    encryptedStr = substitutionFunc(str, keyArr, key, keyLength, 1);
    cout << encryptedStr << " \n\n";
    
    cout << "Decrypted: ";
    //substitution encryption method
    decryptedStr = substitutionFunc(encryptedStr, keyArr, key, keyLength, 0);
    cout << decryptedStr << " \n\n";
    
    transposeFunc (keyLength, str, key, 1, 1, keyArr);
    transposeFunc (keyLength, str, key, 0, 1, keyArr);
    transposeFunc (keyLength, str, key, 1, 3, keyArr);
    transposeFunc (keyLength, str, key, 0, 3, keyArr);
}

void transposeFunc (int keyLength, string str, int key, int rowOrCol, int encryptDecryptNeither, int* keyArr)
{
    int m=0;

    if(rowOrCol)
    {
        //set matrix for appropriate size (keyLength x strLength/keyLength)
        //rows x cols
        double strLength = str.length()   ;
        double n = ceil(strLength/keyLength);
        int matrixN = (int)n;
        char matrix[keyLength][matrixN]; 
        for (int i=0; i<keyLength; i++)
        {
            for(int j=0; j<matrixN; j++)
            {
                if(m<strLength)
                {
                    matrix[i][j] = str.at(m);
                }
                m++;
            }
        }
        //encrypt via key lowest to highest value first for each row
        int keyArrCopy[keyLength];
        int keyArrOrdered[keyLength];
        //copy key to temp array
        for (int i=0; i<keyLength; i++)
        {
            keyArrCopy[i] = keyArr[i];
            keyArrOrdered[i]=i;
        }
        //order array from lowest to highest
        quickSort(keyArrCopy, keyArrOrdered, 0, keyLength-1);
        if(encryptDecryptNeither==1)
        {
            m=0;
            cout << "Transposed matrix based on key(" << keyLength << "x" << matrixN << "): \n";
            for (int i=0; i<keyLength;i++)
            {
                for(int j=0; j<matrixN; j++)
                {
                    if (m==strLength)
                        break;
                    cout << matrix[keyArrOrdered[i]][j];
                    m++;
                }
                cout << "\n";
            }
            cout << "\n\n";
        }
        else
            {
            
            m=0;
            cout << "Transposed Matrix no key (" << keyLength << "x" << matrixN << "): \n";
            for (int i=0; i<keyLength; i++)
            {
                for (int j=0; j<matrixN; j++)
                {
                    if (m==strLength)
                        break;
                    cout << matrix[i][j];
                    m++;
                }
                cout << "\n";
            }
            cout << "\n\n";
        }
    }
    else
    {
        //set matrix for appropriate size (keyLength x strLength/keyLength)
        //rows x cols
        double strLength = str.length();
        double n = ceil(strLength/keyLength);
        int matrixN = (int)n;
        char matrix[matrixN][keyLength]; 
        for (int i=0; i<matrixN; i++)
        {
            for(int j=0; j<keyLength; j++)
            {
                if(m<strLength)
                {
                    matrix[i][j] = str.at(m);
                }
                m++;
            }
        }
        if(encryptDecryptNeither==1)
        {
             //encrypt via key lowest to highest value first for each row
            int keyArrCopy[keyLength];
            int keyArrOrdered[keyLength];
            //copy key to temp array
            for (int i=0; i<keyLength; i++)
            {
                keyArrCopy[i] = keyArr[i];
                keyArrOrdered[i]=i;
            }
            //order array from lowest to highest
            quickSort(keyArrCopy, keyArrOrdered, 0, keyLength-1);
    
            m=0;
            cout << "Transposed matrix based on key(" << keyLength << "x" << matrixN << "): \n";
            for (int i=0; i<matrixN;i++)
            {
                for(int j=0; j<keyLength; j++)
                {
                    if (m==strLength)
                        break;
                    cout << matrix[i][keyArrOrdered[j]];
                    m++;
                }
                cout << "\n";
            }
            cout << "\n\n";
        }
        else
        {
            m=0;
            cout << "Transposed Matrix no key (" << matrixN << "x" << keyLength << "): \n";
            for (int i=0; i<matrixN; i++)
            {
                for (int j=0; j<keyLength; j++)
                {
                    if (m==strLength)
                        break;
                    cout << matrix[i][j];
                    m++;
                }
                cout << "\n";
            }
            cout << "\n\n";
        }
    }
}

int partition (int arr[], int arr2[], int low, int high)
{
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element
 
    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot)
        {
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
            swap(&arr2[i], &arr2[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    swap(&arr2[i + 1], &arr2[high]);
    return (i + 1);
}
 
void quickSort(int arr[], int arr2[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition(arr, arr2, low, high);
 
        // Separately sort elements before
        // partition and after partition
        quickSort(arr, arr2, low, pi - 1);
        quickSort(arr, arr2, pi + 1, high);
    }
}

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

string substitutionFunc (string str, int* keyArr, int key, int keyLength, int addOrSub)
{
    int tempInt = 0;
    int tempChar = 0;
    string returnStr;
    if(addOrSub)
        for (int i=0; i<str.length(); i++ ) {
            tempChar = str.at(i) + keyArr[tempInt];
            //cout << tempChar;
            returnStr += tempChar;
            if(tempInt == keyLength)
                tempInt = 0;
            else
                tempInt++;
        }
    else
        for (int i=0; i<str.length(); i++ ) {
        
            tempChar = str.at(i) - keyArr[tempInt];
            //cout << tempChar;
            returnStr += tempChar;
            if(tempInt == keyLength)
                tempInt = 0;
            else
                tempInt++;
        }
    return returnStr;
}

int intGetLength (int key, int base) 
{
    int keyLength;
    do
    {
        keyLength++;
        key = key /= base;
    }
    while (key);
    cout << "Key Length: " << keyLength << "\n";
    return keyLength;
}

int* intStoreInArr (int* keyArr, int key, int keyLength) 
{
    for (int h = keyLength-1; h > 0; h--)
        {
            keyArr[h] = key % 10;
            key = key / 10;
        } 
        //if last digit store in array
        keyArr[0] = key;
    return keyArr;
}

void printRevArr (int* arr, int length)
{
    cout << "Print Reverse Array: \n";
    for (int i=length-1; i>=0; i--)
        cout << arr[i];
    cout << "\n\n";
}
void printArr (int* arr, int length)
{
    cout << "Print Array: \n";
    for (int i=0; i<length; i++)
        cout << arr[i];
    cout << "\n\n";
}