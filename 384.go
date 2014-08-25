package main

import (
	"fmt"
)

func Rudin(x int) int {
	if x == 0 {
		return 1
	} else if y := x / 2; x % 4 == 3 {
		return -Rudin(y)
	} else {
		return Rudin(y)
	}
}

func partial(x int) int {
	if x == 0 {
		return 0
	} else if x % 2 == 0 {
		return 2 * partial((x / 2 + 1) / 2)
	} else {
		return partial(x - 1) + Rudin(x - 1)
	}
}

// func pos(x, y int) int {
// 	if x == 0 {
// 		return 0
// 	} else if x % 2 == 0 {
// 		return 2 * (pos(x / 2, y / 2) + (y + 1) % 2)
// 	} else {
// 		return 0;
// 	}
// }

// func pos(x, y, hi int, rev bool) int {
	
// }

func main() {
	// for i := 1; i <= 85; i++ {
	// 	fmt.Println(i - 1, partial(i), Rudin(i))
	// }
	// for i := 1; i <= 85; i += 4 {
	// 	fmt.Printf("%d/(%d, %d, %d)\n", partial(i), partial(i + 1), partial(i + 2), partial(i + 3))
	// }
	// for i := 1; i <= 200; i += 8 {
	// 	fmt.Printf("%d/(%d, %d, %d)\n", partial(i), partial(i + 2), partial(i + 4), partial(i + 6))
	// 	// fmt.Println(partial(i))
	// }
	cnt := make([]int, 200)
	// mx := 0
	// his := make([][]int, 120)
	for i := 1; i <= 50000; i++ {
		v := partial(i)
		cnt[v]++
		// if i > 32 {
		// 	// if i - 32 >= 16 {
		// 		his[v] = append(his[v], i - 32)
		// 	// }
		// } else {
		// 	his[v] = append(his[v], i)
		// }
		// if v > mx {
		// 	mx = v
		// 	if true || mx % 2 == 1 {
		// 		fmt.Println(mx, i)
		// 	}
		// }
	}
	fmt.Println(cnt)
	// for i := 1; i <= 20; i++ {
	// 	fmt.Println(his[i])
	// }
}
