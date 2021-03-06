package main

import (
  "fmt"
  "github.com/kranfix/linebot/utils/serialCmd"
)

func main() {
  var h serialUpload.Header

  // from byte array
  b := [...]byte{'!','@','#',5,1,0,50,1}
  fmt.Printf("array: % d\n",b)
  h.ReadBytes(&b[0])
  fmt.Println("From byte array to Header:")
  fmt.Println(h)

  // from byte slice
  s := []byte{'!','@','#',45,2,1,38,2}
  fmt.Printf("slice: % d\n",s)
  h.ReadBytes(&s[0])
  fmt.Println("From byte slice to Header:")
  fmt.Println(h)
}
