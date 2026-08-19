#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

// Structure for bucket entries in our hash map
typedef struct BucketNode {
    long bucket_id;
    long value;
    struct BucketNode* next;
} BucketNode;

// Helper function to map a number to its correct bucket ID safely
long getBucketId(long num, long bucket_size) {
    // Standard integer division shifts negative values incorrectly toward zero in C.
    // Adjusting ensures numbers like -1, -2, -3 fall into bucket -1 when bucket_size is 4.
    if (num < 0) {
        return (num + 1) / bucket_size - 1;
    }
    return num / bucket_size;
}

bool containsNearbyAlmostDuplicate(int* nums, int numsSize, int indexDiff, int valueDiff) {
    if (numsSize <= 1 || indexDiff <= 0 || valueDiff < 0) {
        return false;
    }

    // Set map size proportional to indexDiff limit to minimize collisions
    int mapSize = (indexDiff < numsSize) ? indexDiff + 1 : numsSize;
    BucketNode** hashTable = (BucketNode**)calloc(mapSize, sizeof(BucketNode*));
    if (!hashTable) return false;

    // Use long type to safely prevent integer overflow during arithmetic operations
    long bucket_size = (long)valueDiff + 1;
    bool found = false;

    for (int i = 0; i < numsSize; i++) {
        long current_val = nums[i];
        long current_bucket = getBucketId(current_val, bucket_size);

        // Define target buckets to examine (Current, Previous, Next)
        long targets[3] = {current_bucket, current_bucket - 1, current_bucket + 1};

        for (int t = 0; t < 3; t++) {
            long target_id = targets[t];
            
            // Standard Hash Map Chaining lookup
            int hashIndex = labs(target_id) % mapSize;
            BucketNode* curr = hashTable[hashIndex];
            
            while (curr != NULL) {
                if (curr->bucket_id == target_id) {
                    // Rule 1: Same bucket match is always valid
                    if (t == 0) {
                        found = true;
                        break;
                    }
                    // Rule 2 & 3: Adjacent buckets must pass the valueDiff range check
                    if (labs(current_val - curr->value) <= valueDiff) {
                        found = true;
                        break;
                    }
                }
                curr = curr->next;
            }
            if (found) break;
        }

        if (found) break;

        // Insert the current value into the hash table
        int insertIndex = labs(current_bucket) % mapSize;
        BucketNode* newNode = (BucketNode*)malloc(sizeof(BucketNode));
        if (newNode) {
            newNode->bucket_id = current_bucket;
            newNode->value = current_val;
            newNode->next = hashTable[insertIndex];
            hashTable[insertIndex] = newNode;
        }

        // Maintain the sliding window size of indexDiff
        if (i >= indexDiff) {
            long old_val = nums[i - indexDiff];
            long old_bucket = getBucketId(old_val, bucket_size);
            int removeIndex = labs(old_bucket) % mapSize;

            BucketNode* curr = hashTable[removeIndex];
            BucketNode* prev = NULL;

            while (curr != NULL) {
                if (curr->bucket_id == old_bucket) {
                    if (prev == NULL) {
                        hashTable[removeIndex] = curr->next;
                    } else {
                        prev->next = curr->next;
                    }
                    free(curr);
                    break;
                }
                prev = curr;
                curr = curr->next;
            }
        }
    }

    // Free all remaining dynamic memory allocations
    for (int i = 0; i < mapSize; i++) {
        BucketNode* curr = hashTable[i];
        while (curr != NULL) {
            BucketNode* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(hashTable);

    return found;
}
