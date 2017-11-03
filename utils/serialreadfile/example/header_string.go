package main

import (
  "fmt"
  ".."
)

func main() {
  h := serialUpload.Header{
    [...]byte{'#','!','@'}, // Init
    uint8(100), // Len
    uint8(1),   // Src
    uint8(0),    // Dst
    uint16(1025), // DfNum
  }

  fmt.Print(h)
}
