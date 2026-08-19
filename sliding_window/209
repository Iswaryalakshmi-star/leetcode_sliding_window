#include <stdio.h>
#include <limits.h>

int minSubArrayLen(int target, int* nums, int numsSize) {
    int left = 0;
    int current_sum = 0;
    int min_length = INT_MAX;

    // Expand the window using the right pointer
    for (int right = 0; right < numsSize; right++) {
        current_sum += nums[right];

        // Shrink the window from the left as long as the condition is met
        while (current_sum >= target) {
            int current_length = right - left + 1;
            if (current_length < min_length) {
                min_length = current_length;
            }
            
            // Remove the leftmost element and slide the pointer
            current_sum -= nums[left];
            left++;
        }
    }

    // If min_length was never updated, return 0
    return (min_length == INT_MAX) ? 0 : min_length;
}
