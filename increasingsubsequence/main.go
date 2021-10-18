package main

import (
	"fmt"
	"math"
)

func Max(a,b int) int{
	if a < b{
		return b
	}
	return a
}

func ReverseSlice(path []int) []int{
	// reverse the order of path (since it's backwards)
	for i, j := 0, len(path)-1; i<j; i, j = i+1, j-1 {
		path[i], path[j] = path[j], path[i]
	}
	return path
}

func Solution1(a []int) []int {
	/**
	O(n^2) Solution with dynamic programming. Also finds path the path with smallest values.
	 */
	var n = len(a)
	d := make([]int, n)
	p := make([]int, n)

	// Fill with default values
	for i:=0; i < n; i++ {
		d[i] = 1
		p[i]= -1
	}

	// Build up d and p (the actual LIS algorithm)
	for i:=0; i < n; i++ {
		for j:=0; j<i; j++ {
			/* If smaller number than currently at.
			If  path is longer than already found, or if it is the same length that is already found, but the
			number is smaller than the one found before. This is done since the goal is to find the smallest longest
			subsequence. */
			if a[j] < a[i] && (d[i] < d[j] + 1 || (d[i] <= d[j] + 1 && (p[i] != -1 && a[j] < a[p[i]]))){
				d[i] = d[j] + 1
				p[i] = j
			}
		}
	}

	// Find max len
	maxLen, maxLenI := 0, -1
	for i, v := range d{
		/* If shortest length, or if same as already found, but smaller nr. This is done since
		the shortest distance with the smallest numbers were requested */
		if maxLen < v  || (maxLen <= v && a[i] < a[maxLenI]){
			maxLen = v
			maxLenI = i
		}
	}

	// Find path
	var path []int
	for maxLenI != -1{
		path = append(path, a[maxLenI])
		maxLenI = p[maxLenI]
	}

	return ReverseSlice(path)
}

func binarySearch(a []int, val int) int{
	low, high := 0, len(a)
	for low < high {
		middle := (low + high) / 2
		if val < a[middle] {
			high = middle
		} else {
			low = middle + 1
		}
	}
	return low
}


func Solution2(a []int) []int {
	/**
	O(n*log(n)) Solution with dynamic programming and binary search. Also finds the path with smallest values
	*/
	n := len(a)
	d := make([]int, n+1) // Value of element with ending sequence in index
	di := make([]int, len(d)) // Indexes of values in d from a
	p := make([]int, len(d)) // Parents

	// Fill arrays
	for i:=0; i<=n; i++{
		d[i] = math.MaxInt64
		di[i] = -1
		p[i] = -1
	}
	d[0] = -math.MaxInt64

	for i:= 0; i< n; i++ {
		/* Since array d always will be sorted, we can binary search for where to insert
		the element at a[i] */
		j := binarySearch(d, a[i])
		if d[j-1] < a[i] && a[i] < d[j]{
			d[j] = a[i]
			di[j] = i
			p[i] = di[j-1]
		}
	}

	// Find index for max length
	maxIndx := 0
	for i, v:= range d {
		if v < math.MaxInt64{
			maxIndx = di[i]
		}
	}

	// Find seq from maxIndx
	var seq []int
	parent := maxIndx
	for parent != -1 {
		seq = append(seq, a[parent])
		parent = p[parent]
	}
	return ReverseSlice(seq)
}

func main() {

	var n int
	for {
		_, err := fmt.Scanf("%d", &n)
		if err != nil{
			fmt.Println(err)
			break
		}
		if n == 0{
			return
		}

		ins := make([]int, n)
		for i:= 0; i<n; i++ {
			fmt.Scanf("%d", &ins[i])
		}
		res := Solution2(ins)
		fmt.Print(len(res), " ")
		for _, v := range res{
			fmt.Print(v, " ")
		}
		fmt.Println()
	}
}
