#include <stdio.h>
#include <stdlib.h>
 
#define TABLE_SIZE 11

// Structure for each element in the hash table
typedef struct {
    int key;
    int value;
} HashEntry;

// Structure for the hash table
typedef struct {
    HashEntry* table;
    int size;
} HashTable;

// Function to initialize the hash table
void initializeHashTable(HashTable* hashTable, int size) {
    hashTable->table = (HashEntry*)malloc(sizeof(HashEntry) * size);
    hashTable->size = size;

    for (int i = 0; i < size; i++) {
        hashTable->table[i].key = -1; // -1 indicates an empty slot
    }
}

// Function to calculate the hash value using modulo operation
int hash(int key, int size) {
    return key % size;
}

// Function to insert a key-value pair into the hash table
void insert(HashTable* hashTable, int key, int value) {
    int index = hash(key, hashTable->size);
    int originalIndex = index;
    int i = 1;

    while (hashTable->table[index].key != -1) {
        // Quadratic probing: incrementing by i^2
        index = (originalIndex + i * i) % hashTable->size;
        i++;
    }

    hashTable->table[index].key = key;
    hashTable->table[index].value = value;
}

// Function to search for a key in the hash table
int search(HashTable* hashTable, int key) {
    int index = hash(key, hashTable->size);
    int originalIndex = index;
    int i = 1;

    while (hashTable->table[index].key != -1) {
        if (hashTable->table[index].key == key) {
            return hashTable->table[index].value;
        }

        // Quadratic probing: incrementing by i^2
        index = (originalIndex + i * i) % hashTable->size;
        i++;
    }

    // Key not found
    return -1;
}

// Function to display the hash table
void displayHashTable(HashTable* hashTable) {
    printf("Hash Table:\n");
    for (int i = 0; i < hashTable->size; i++) {
        if (hashTable->table[i].key != -1) {
            printf("Index %d: Key=%d, Value=%d\n", i, hashTable->table[i].key, hashTable->table[i].value);
        } else {
            printf("Index %d: Empty\n", i);
        }
    }
    printf("\n");
}

// Function to free the memory allocated for the hash table
void freeHashTable(HashTable* hashTable) {
    free(hashTable->table);
}

int main() {
    HashTable myHashTable;
    initializeHashTable(&myHashTable, TABLE_SIZE);

    insert(&myHashTable, 5, 10);
    insert(&myHashTable, 15, 20);
    insert(&myHashTable, 25, 30);
    insert(&myHashTable, 35, 40);

    displayHashTable(&myHashTable);

    int searchResult = search(&myHashTable, 15);
    if (searchResult != -1) {
        printf("Key 15 found with value %d\n", searchResult);
    } else {
        printf("Key 15 not found\n");
    }

    freeHashTable(&myHashTable);

    return 0;
}
