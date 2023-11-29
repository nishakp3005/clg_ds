#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TABLE_SIZE 23

typedef struct KeyValue {
    char *key;
    char *value;
} KeyValue;

typedef struct {
    KeyValue **array;
    int size;
    float load_factor;
    int num_keys;
    int num_occupied_indices;
    int num_ops;
} HashTable;

KeyValue *createKeyValue(char *key, char *value) {
    KeyValue *newKeyValue = (KeyValue *)malloc(sizeof(KeyValue));
    if (newKeyValue != NULL) {
        newKeyValue->key = key;
        newKeyValue->value = value;
    }
    return newKeyValue;
}

HashTable *createHashTable() {
    HashTable *newTable = (HashTable *)malloc(sizeof(HashTable));
    newTable->array = (KeyValue **)malloc(TABLE_SIZE * sizeof(KeyValue *));
    for (int i = 0; i < TABLE_SIZE; i++)
        newTable->array[i] = NULL;

    newTable->size = TABLE_SIZE;
    newTable->load_factor = 0;
    newTable->num_keys = 0;
    newTable->num_occupied_indices = 0;
    newTable->num_ops = 0;
    return newTable;
}

int key_to_int(char *key) {
    int sum = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        sum += (int)key[i];
    }
    return sum;
}

int insert_key_value(HashTable *ht, char *key, char *value) {
    int index = key_to_int(key) % ht->size;
    int initial_index = index;
    int num_probes = 1;

    while (ht->array[index] != NULL) {
        if (strcmp(ht->array[index]->key, key) == 0) {
            // Key already exists, update the value
            ht->array[index]->value = value;
            return index;
        }
        // Linear probing: Move to the next index
        index = (initial_index + num_probes) % ht->size;
        num_probes++;
        ht->num_ops++;
    }

    // Insert the new key-value pair
    KeyValue *newKeyValue = createKeyValue(key, value);
    ht->array[index] = newKeyValue;
    ht->num_keys++;
    ht->num_occupied_indices++;
    ht->load_factor = (float)ht->num_keys / ht->size;
    ht->num_ops++;
    return index;
}

char *search_key(HashTable *ht, char *key) {
    int index = key_to_int(key) % ht->size;
    int initial_index = index;
    int num_probes = 1;

    while (ht->array[index] != NULL) {
        if (strcmp(ht->array[index]->key, key) == 0) {
            return ht->array[index]->value;
        }
        // Linear probing: Move to the next index
        index = (initial_index + num_probes) % ht->size;
        num_probes++;
        ht->num_ops++;
    }

    // Key not found
    return NULL;
}

int delete_key(HashTable *ht, char *key) {
    int index = key_to_int(key) % ht->size;
    int initial_index = index;
    int num_probes = 1;

    while (ht->array[index] != NULL) {
        if (strcmp(ht->array[index]->key, key) == 0) {
            // Mark the slot as deleted (you can choose your own way to handle deletions)
            free(ht->array[index]);
            ht->array[index] = NULL;
            ht->num_keys--;
            ht->num_ops++;
            return index;
        }
        // Linear probing: Move to the next index
        index = (initial_index + num_probes) % ht->size;
        num_probes++;
        ht->num_ops++;
    }

    // Key not found
    return -1;
}

int get_load_factor(HashTable *ht) {
    return (int)((float)ht->num_keys / ht->size * 100);
}

int get_avg_probes(HashTable *ht) {
    return ht->num_ops / ht->num_keys;
}

void display(HashTable *ht) {
    printf("Hash Table Contents:\n");
    for (int i = 0; i < ht->size; i++) {
        if (ht->array[i] != NULL) {
            printf("%d: Key='%s', Value='%s'\n", i, ht->array[i]->key, ht->array[i]->value);
        } else {
            printf("%d: NULL\n", i);
        }
    }
}

// int main() {
//     HashTable *ht = createHashTable();

//     // Insert key-value pairs
//     insert_key_value(ht, "first name", "Nishita");
//     insert_key_value(ht, "last name", "Panchal");
//     insert_key_value(ht, "uid", "2022300073");
//     insert_key_value(ht, "sport", "football");
//     insert_key_value(ht, "food", "banana");
//     insert_key_value(ht, "holiday", "NONE");
//     insert_key_value(ht, "role_model", "priyanka chopra");
//     insert_key_value(ht, "subject", "DSA");
//     insert_key_value(ht, "song", "The nights");
//     insert_key_value(ht, "movie", "ERAS TOUR");
//     insert_key_value(ht, "colour", "BLUE");
//     insert_key_value(ht, "book", "Childern of the time");

//     // Test the table with search and delete operations
//     char *result = search_key(ht, "sport");
//     if (result != NULL) {
//         printf("Sport: %s\n", result);
//     } else {
//         printf("Sport not found\n");
//     }

//     int delete_result = delete_key(ht, "holiday");
//     if (delete_result != -1) {
//         printf("Deleted the key 'holiday' from index %d\n", delete_result);
//     } else {
//         printf("Failed to delete the key 'holiday'\n");
//     }

//     display(ht);

//     // Cleanup
//     for (int i = 0; i < ht->size; i++) {
//         if (ht->array[i] != NULL) {
//             free(ht->array[i]);
//         }
//     }
//     free(ht->array);
//     free(ht);

//     return 0;
// }
