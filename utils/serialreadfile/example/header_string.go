package main

import (
  "fmt"
  ".."
)

func main() {
  h := serialUpload.Header{
    [3]byte{'#','!','@'}, // Init
    uint8(1),   // Src
    uint8(0),    // Dst
    uint16(35), // DfNum
    uint8(100), // Len
  }

  fmt.Print(h)
}
