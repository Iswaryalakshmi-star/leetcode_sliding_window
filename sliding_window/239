#include <stdio.h>
#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    if (numsSize == 0 || k == 0) {
        *returnSize = 0;
        return NULL;
    }

    // Allocate memory for the result array
    *returnSize = numsSize - k + 1;
    int* result = (int*)malloc((*returnSize) * sizeof(int));
    
    // Allocate memory for the deque (stores indices)
    int* deque = (int*)malloc(numsSize * sizeof(int));
    int head = 0; // Front of the deque
    int tail = 0; // Back of the deque
    int resIdx = 0;

    for (int i = 0; i < numsSize; i++) {
        // 1. Remove indices that are out of the current window bounds
        if (head < tail && deque[head] < i - k + 1) {
            head++;
        }

        // 2. Remove elements smaller than the current element from the back
        while (head < tail && nums[deque[tail - 1]] <= nums[i]) {
            tail--;
        }

        // 3. Add the current element's index to the back
        deque[tail++] = i;

        // 4. Append the max element to the result once the window is fully formed
        if (i >= k - 1) {
            result[resIdx++] = nums[deque[head]];
        }
    }

    // Free the temporary deque memory
    free(deque);
    return result;
}
