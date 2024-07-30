'use strict';

//
//                 0
//         1               2
//
//    3        4       5        6
//
// 7     8  9    10 11   12  13   14
//

var heapq = exports;

var cmplt = function(x, y) {
  return x < y;
};

// push an item into heap, O(log n)
heapq.push = function(heap, item, cmp) {
  heap.push(item);
  siftdown(heap, 0, heap.length - 1, cmp || cmplt);
};

// pop the smallest item from heap, O(log n)
heapq.pop = function(heap, cmp) {
  if (heap.length > 0) {
    var last = heap.pop();

    if (heap.length > 0) {
      var head = heap[0];
      heap[0] = last;
      siftup(heap, 0, cmp || cmplt);
      return head;
    } else {
      return last;
    }
  }
};

// get the top item, O(1)
heapq.top = function(heap) {
  if (heap.length !== 0)
    return heap[0];
};

// push an item on the heap and pop out the top item,
// this runs more efficiently than `heapq.push()` followed
// by a separate call to `heapq.pop()`, O(log n)
heapq.pushpop = function(heap, item, cmp) {
  cmp = cmp || cmplt;

  if (heap.length > 0 && cmp(heap[0], item)) {
    var temp = heap[0];
    heap[0] = item;
    item = temp;
    siftup(heap, 0, cmp);
  }
  return item;
};

// transform array `heap` into a heap in-place, O(nlog n)
heapq.heapify = function(arr, cmp) {
  cmp = cmp || cmplt;

  for (var idx = Math.floor(arr.length / 2) - 1;
       idx >= 0; --idx)
    siftup(arr, idx, cmp);
  return arr;
};

// heap sort, O(nlog n)
heapq.heapsort = function(arr, cmp) {
  var heap = [];

  for (var i = 0; i < arr.length; ++i)
    heapq.push(heap, arr[i], cmp);

  var arr_ = [];

  while (heap.length > 0)
    arr_.push(heapq.pop(heap, cmp));
  return arr_;
};

function siftdown(heap, startIdx, idx, cmp) {
  var item = heap[idx];

  while (idx > startIdx) {
    var parentIdx = (idx - 1) >> 1;
    var parentItem = heap[parentIdx];
    if (cmp(item, parentItem)) {
      heap[idx] = parentItem;
      idx = parentIdx;
      continue;
    }
    break;
  }

  heap[idx] = item;
}

function siftup(heap, idx, cmp) {
  var endIdx = heap.length;
  var startIdx = idx;
  var item = heap[idx];

  var childIdx = idx * 2 + 1;

  while (childIdx < endIdx) {
    var rightIdx = childIdx + 1;

    if (rightIdx < endIdx && (!cmp(
      heap[childIdx], heap[rightIdx]))) {
      childIdx = rightIdx;
    }
    heap[idx] = heap[childIdx];
    idx = childIdx;
    childIdx =  idx * 2 + 1;
  }

  heap[idx] = item;
  siftdown(heap, startIdx, idx, cmp);
}
