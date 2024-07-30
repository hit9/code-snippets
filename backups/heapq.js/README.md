heapq.js
========

Heap queue implementation for nodejs/iojs.

```
var heapq = require('heapq');

var heap = [];
var cmp = function(x, y) {return x[0] < y[0];}

heapq.push(heap, [3, 'a'], cmp);
heapq.push(heap, [4, 'b'], cmp);
heapq.push(heap, [2, 'c'], cmp);
heapq.push(heap, [1, 'd'], cmp);

heapq.pop(heap, cmp);  // [1, 'd']
heapq.pop(heap, cmp);  // [2, 'c']
```

API Refs
--------

- **heapq.push(heap, item[, cmp])**, push an item into heap. *O(log n)*
- **heapq.pop(heap[, cmp])**, pop the smallest item from heap. *O(log n)*
- **heapq.top(heap)**, get the smallest item. *O(1)*
- **heapq.pushpop(heap[, cmp])**, push an item on the heap and pop out the smallest item,
   this runs more efficiently than `heapq.push()` followed by a separate call to `heapq.pop()`. *O(log n)*
- **heapq.heapify(arr[, cmp])**, transform array `heap` into a heap (aka a heap liked array) in-place. *O(nlog n)*
- **heapq.heapsort(arr[, cmp])**, new a sorted array by heap-sort. *O(nlog n)*

Comparator
----------

Default comparator:

```
function(x, y) {return x < y;}
```

- this results a "top smallest heap".

License
--------

MIT (c) Chao Wang <hit9@icloud.com>
