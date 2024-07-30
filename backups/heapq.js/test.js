'use strict';

var assert = require('assert');
var should = require('should');
var heapq = require('./index');

var cmp = function(x, y) {return x[0] < y[0];}

describe('heapq', function() {
  it('heapq.push', function() {
    var heap = [];
    heapq.push(heap, [1, 'a'], cmp);
    heapq.push(heap, [2, 'b'], cmp);
    should(heapq.top(heap)).eql([1, 'a']);
    should(heapq.pop(heap, cmp)).eql([1, 'a']);
    should(heapq.pop(heap, cmp)).eql([2, 'b']);
  });

  it('heapq.pop', function() {
    var heap = [];
    heapq.push(heap, [3, 'a'], cmp);
    heapq.push(heap, [4, 'b'], cmp);
    heapq.push(heap, [2, 'c'], cmp);
    should(heapq.pop(heap, cmp)).eql([2, 'c']);
    should(heapq.pop(heap, cmp)).eql([3, 'a']);
    should(heapq.pop(heap, cmp)).eql([4, 'b']);
  });

  it('heapq.top', function() {
    var heap = [];
    heapq.push(heap, 2);
    heapq.push(heap, 3);
    should(heapq.top(heap)).eql(2);
  });

  it('heapq.pushpop', function() {
    var heap = [];
    heapq.push(heap, 2);
    heapq.push(heap, 3);
    should(heapq.pushpop(heap, 4)).eql(2);
  });

  it('heapq.heapify', function() {
    var heap = heapq.heapify([3, 4, 5, 2]);
    should(heapq.top(heap)).eql(2);
  });

  it('heap.heapsort', function() {
    should(heapq.heapsort([3, 4, 5, 0, 2, 1]))
    .eql([0, 1, 2, 3, 4, 5]);
  });

  it('heap greater on the top', function() {
    var cmp = function(x, y) {return x > y};
    var heap = [];
    heapq.push(heap, 1, cmp);
    heapq.push(heap, 2, cmp);
    heapq.push(heap, 3, cmp);
    should(heapq.top(heap)).eql(3);
  });
});
