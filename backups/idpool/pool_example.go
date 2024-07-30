// Copyright 2016 Chao Wang <hit9@icloud.com>

// +build ignore

package main

import (
	"fmt"
	"github.com/hit9/idpool"
)

func main() {
	pool := idpool.New(5, 10)
	i1 := pool.Reserve()
	fmt.Println(i1)
	i2 := pool.Reserve()
	fmt.Println(i2)
	pool.Release(1)
	fmt.Println(pool.Reserve())
}
