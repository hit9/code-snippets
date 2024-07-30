// Copyright 2016 Chao Wang <hit9@icloud.com>

package idpool

import (
	"math"
	"math/rand"
	"runtime"
	"testing"
)

// Must asserts the given value is True for testing.
func Must(t *testing.T, v bool) {
	if !v {
		_, fileName, line, _ := runtime.Caller(1)
		t.Errorf("\n unexcepted: %s:%d", fileName, line)
	}
}

func TestReserve(t *testing.T) {
	p := New(1, 5)
	Must(t, p.Reserve() == 1)
	Must(t, p.Reserve() == 2)
	Must(t, p.Reserve() == 3)
	Must(t, p.Reserve() == 4)
	Must(t, p.Reserve() == 5)
	Must(t, p.Reserve() == 5)
}

func TestRelease(t *testing.T) {
	p := New(1, 5)
	Must(t, p.Reserve() == 1)
	Must(t, p.Reserve() == 2)
	p.Release(2)
	Must(t, p.Reserve() == 2)
	Must(t, p.Reserve() == 3)
}

func TestLargeHigh(t *testing.T) {
	N := math.MaxUint32
	n := 1024
	p := New(1, N)
	for i := 0; i < n; i++ {
		Must(t, p.Reserve() == i+1)
	}
	id := rand.Intn(n-1) + 1
	p.Release(id)
	Must(t, p.Reserve() == id)
	Must(t, p.Reserve() == n+1)
}
