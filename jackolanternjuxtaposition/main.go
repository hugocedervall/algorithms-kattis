package main

import (
	"fmt"
)

func solution(a, b, c int) int {
	return a * b * c
}

func main() {
	var a, b, c int

	for {
		_, err := fmt.Scanf("%d %d %d", &a, &b, &c)
		if err != nil {
			break
		}
		fmt.Println(solution(a, b, c))
	}
}
