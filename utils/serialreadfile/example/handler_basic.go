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
}
