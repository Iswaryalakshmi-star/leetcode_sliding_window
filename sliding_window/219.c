#include <stdlib.h>
#include <stdbool.h>

// Structure for hash map collision chaining
typedef struct HashNode {
    int key;
    int index;
    struct HashNode* next;
} HashNode;

bool containsNearbyDuplicate(int* nums, int numsSize, int k) {
    if (numsSize <= 1 || k <= 0) {
        return false;
    }

    // Set map size proportional to input array size to minimize collisions
    int mapSize = numsSize;
    HashNode** buckets = (HashNode**)calloc(mapSize, sizeof(HashNode*));
    if (!buckets) return false;

    bool found = false;

    for (int i = 0; i < numsSize; i++) {
        // Safe hash calculation including negative numbers
        int hashIndex = nums[i] % mapSize;
        if (hashIndex < 0) {
            hashIndex += mapSize;
        }

        HashNode* curr = buckets[hashIndex];
        HashNode* prevNode = NULL;
        bool keyExists = false;

        // Traverse the chain to look for an existing duplicate key
        while (curr != NULL) {
            if (curr->key == nums[i]) {
                // If index difference condition is satisfied, mark true
                if (i - curr->index <= k) {
                    found = true;
                }
                // Always update to the absolute newest index for future checks
                curr->index = i;
                keyExists = true;
                break;
            }
            curr = curr->next;
        }

        // Fast escape if we already found our nearby duplicate matching criteria
        if (found) {
            break;
        }

        // If the key is unique to this bucket chain, add a new node at the head
        if (!keyExists) {
            HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
            if (newNode) {
                newNode->key = nums[i];
                newNode->index = i;
                newNode->next = buckets[hashIndex];
                buckets[hashIndex] = newNode;
            }
        }
    }

    // Comprehensive memory cleanup to prevent resource leaks
    for (int i = 0; i < mapSize; i++) {
        HashNode* curr = buckets[i];
        while (curr != NULL) {
            HashNode* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(buckets);

    return found;
}
