<h1>
  
  <strong> <b> AIV Workbench - C Collections | Visuals </b> </strong> 
  
  </h1>




<img width="1584" height="672" alt="C_Visuals" src="https://github.com/user-attachments/assets/f343f272-762b-450d-9e03-9ac8f223abdc" />

<br>
<br>


<p>This implementation demonstrates the classical recursive binary search algorithm.
It splits the search space in half at every recursive call, achieving logarithmic time complexity.
Recursive calls model the decision process: left subtree vs. right subtree.
The function requires a sorted array and cleanly handles all edge cases (empty interval, not found, etc.).</p>









                5
             /     \
           1 3     7 9 11
                    /  \
                  7     11 
        
         H = height (depth)        //   2
         N = number of nodes       //   6
        
         Max(N) = (2^H+1) - 1;     // 2^(2+1) - 1 = 7
         Min(H) = log2(N + 1) - 1; // log2(7 + 1) - 1 = 2
        
        #include <stdio.h>
        
        int binary_search_recursive(int array[], int start, int end, int target) { // O(LogN)
            if (start > end) return -1;  // element not found
        
            int mid = start + (end - start) / 2;
        
            if (array[mid] == target)
                return mid;  // element found
            else if (array[mid] < target)
                return binary_search_recursive(array, mid + 1, end, target);  // search the right half
            else
                return binary_search_recursive(array, start, mid - 1, target); // search the left half
        }
        
        int main() {
            int array[] = {1, 3, 5, 7, 9, 11};
            int n = sizeof(array) / sizeof(int);
            int target = 7;
        
            int index = binary_search_recursive(array, 0, n - 1, target);
            if (index != -1)
                printf("Element found at index %d\n", index);
            else
                printf("Element not found\n");
        
            return 0;
        }


<br>
<br>

<h2>
  
  <strong> <b> Core Concepts: Explained ⬇️ </b> </strong> 
  
  </h2>
  
<img width="1584" height="672" alt="C_Visuals" src="https://github.com/user-attachments/assets/aa3edff5-a020-4128-86f8-179c5251a6ba" />
<br>




```txt

🧩 Core Concepts Covered
1. Dynamic Arrays (Vector)

A dynamic array grows when capacity is exceeded using realloc().

Advantages: Fast random access (O(1)), amortized O(1) append

Trade-offs: Costly middle insertions, possible memory fragmentation

2. Linked Lists

Nodes connected via pointers, useful when insertions/deletions are frequent.

Advantages: O(1) insert/remove at known positions

Trade-offs: O(n) traversal, cache-unfriendly

3. Hash Maps

Key-value lookup through hashing and bucket-based storage.

Advantages: Average O(1) lookup/insertion

Trade-offs: Collisions degrade performance

4. Big-O Complexity

The project touches foundational algorithmic performance concepts:

O(1) – constant time

O(n) – linear growth

O(n²) – quadratic growth
understanding how operations scale helps you reason about performance-critical code.

```


<br>
<br>
<br>
<br>
<br>



<small> Project developed as part of the AIV – Accademia Italiana Videogiochi program. </small>
