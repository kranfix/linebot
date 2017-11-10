package main

import (
  "fmt"
  su "github.com/kranfix/linebot/utils/serialreadfile"
)

func main() {
  h1 := su.Header{Init:[3]byte{'!','@','#'},Len:4}
  test(h1)

  h2 := su.Header{Init:[3]byte{'!','@','X'},Len:4}
  test(h2)

  h3 := su.Header{Init:[3]byte{'!','@','#'},Len:3}
  test(h3)
}

func test(h su.Header) {
  fmt.Println("-------------------------")
  fmt.Println("Is The header ok? ",h.IsOk())
  fmt.Print(h)
  fmt.Println("-------------------------")
}
