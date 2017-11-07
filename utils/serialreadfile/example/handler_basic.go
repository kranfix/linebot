package main

import (
  //"fmt"
  "time"
  su "github.com/kranfix/linebot/utils/serialreadfile"
)

func main() {
  h := su.NewHandler(0)
  defer h.Close()

  h.SetSerial("/dev/ttyUSB0",38400, 2*time.Second)

  h.SetFile("test1.txt")
  buf := []byte("Hello everybody\n")
  h.File.Write(buf)

  h.SetFile("test2.txt")
  buf = []byte("Hola a todos\n")
  h.File.Write(buf)
}
