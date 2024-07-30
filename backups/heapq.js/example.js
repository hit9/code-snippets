var heapq = require('./index');

var heap = [];

var cmp = function(x, y) {return x[0] < y[0];}

heapq.push(heap, [1, 'a'], cmp);
heapq.push(heap, [3, 'b'], cmp);
heapq.push(heap, [2, 'c'], cmp);

heapq.top(heap);  // [1, 'a']

heapq.pop(heap, cmp);  // [1, 'a']
heapq.pop(heap, cmp);  // [2, 'c']
heapq.pop(heap, cmp);  // [3, 'b']
