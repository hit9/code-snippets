// Copyright 2016 Chao Wang <hit9@icloud.com>

// Package idpool implements a reusable integer id pool.
//
// Example
//
//	pool := idpool.New(5,1024)
//	pool.Reserve() // 5
//	pool.Reserve() // 6
//	pool.Release(5)
//	pool.Release() // 5
//
package idpool

import (
	"math"
	"math/big"
)

// Pool is the id pool.
type Pool struct {
	table *big.Int
	high  int
	low   int
}

// New returns a new Pool for given range.
// Range [low,high) is left open and right closed.
// Setting high to 0 means high is MaxInt32.
func New(low, high int) *Pool {
	if high == 0 {
		high = math.MaxInt32
	}
	return &Pool{
		high:  high,
		low:   low,
		table: big.NewInt(0),
	}
}

// Reserve an id from the pool.
// Returns high if no id is available.
func (p *Pool) Reserve() int {
	for i := p.low; i < p.high; i++ {
		if p.table.Bit(i) == 0 {
			p.table.SetBit(p.table, i, 1)
			return i
		}
	}
	return p.high
}

// Release an id back to the pool.
// Do nothing if the id is outside of the range.
func (p *Pool) Release(id int) {
	if id >= p.low && id < p.high {
		p.table.SetBit(p.table, id, 0)
	}
}

// High returns the high.
func (p *Pool) High() int {
	return p.high
}

// Low returns the low.
func (p *Pool) Low() int {
	return p.low
}
