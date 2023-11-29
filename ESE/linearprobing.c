#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

// Structure to represent a key-value pair
struct KeyValue {
    int key;
    int value;
};

// Structure to represent a hash table
struct HashTable {
    struct KeyValue *table[TABLE_SIZE];
};

// Hash function to map keys to indices
int hashFunction(int key) {
    return key % TABLE_SIZE;
}

// Function to initialize the hash table
void initializeHashTable(struct HashTable *hashTable) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable->table[i] = NULL;
    }
}

// Function to insert a key-value pair into the hash table
void insert(struct HashTable *hashTable, int key, int value) {
    int index = hashFunction(key);

    // Linear probing to handle collisions
    while (hashTable->table[index] != NULL) {
        index = (index + 1) % TABLE_SIZE;
    }

    // Create a new key-value pair
    struct KeyValue *newPair = (struct KeyValue *)malloc(sizeof(struct KeyValue));
    newPair->key = key;
    newPair->value = value;

    // Insert the pair into the table
    hashTable->table[index] = newPair;
}

// Function to search for a key in the hash table
struct KeyValue *search(struct HashTable *hashTable, int key) {
    int index = hashFunction(key);

    // Linear probing to find the key
    while (hashTable->table[index] != NULL) {
        if (hashTable->table[index]->key == key) {
            return hashTable->table[index];
        }
        index = (index + 1) % TABLE_SIZE;
    }

    // Key not found
    return NULL;
}

// Function to print the contents of the hash table
void printHashTable(struct HashTable *hashTable) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashTable->table[i] != NULL) {
            printf("Index %d: Key %d, Value %d\n", i, hashTable->table[i]->key, hashTable->table[i]->value);
        } else {
            printf("Index %d: Empty\n", i);
        }
    }
}

// Function to free memory allocated for the hash table
void freeHashTable(struct HashTable *hashTable) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        free(hashTable->table[i]);
    }
}
  
int main() {
    struct HashTable hashTable;
    initializeHashTable(&hashTable);

    // Insert some key-value pairs
    insert(&hashTable, 5, 50);
    insert(&hashTable, 1, 10);
    insert(&hashTable, 15, 150);

    // Print the initial hash table
    printf("Initial Hash Table:\n");
    printHashTable(&hashTable);

    // Search for a key
    int searchKey = 1;
    struct KeyValue *result = search(&hashTable, searchKey);

    if (result != NULL) {
        printf("Key %d found. Value: %d\n", searchKey, result->value);
    } else {
        printf("Key %d not found.\n", searchKey);
    }
  
    // Free memory
    freeHashTable(&hashTable);

    return 0;
}
