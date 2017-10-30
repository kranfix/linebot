package main

import (
  "fmt"
  Name "github.com/kranfix/linebot/utils/name"
)

func main() {
  lbmId := 0
  lbrId := 1
  name := Name.Generate(lbmId,lbrId)
  fmt.Println(name)
  //fmt.Println(t.Format("2006-01-02-15:04:05"))
}
