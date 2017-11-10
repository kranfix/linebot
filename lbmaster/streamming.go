package main

import(
  "fmt"
  "time"
  su "github.com/kranfix/linebot/utils/serialreadfile"
)

func check(e error) {
  if e != nil {
    fmt.Println(e)
  }
}

func main() {
  h := su.NewHandler(0)
  defer h.Close()
  defer func() {
    if r := recover(); r != nil {
      fmt.Println("Recovered in f", r)
      h.LastDf()
    }
  }()

  h.SetSerial("/dev/ttyUSB0",38400, 2 * time.Millisecond)
  h.Flush()

  // Request Capture
  fmt.Print("Sending command 'C' ")
  h.Tx([]byte("C"))
  temp := make([]byte,1)
  temp[0] = 0
  for ; temp[0] != 'c'; {
    fmt.Print(".")
    h.Rx(temp[0:1])
    time.Sleep(time.Second)
  }
  fmt.Println(" ok")


  // Reading streamming
  time.Sleep(time.Second)
  fSize := h.RxMetadata()
  fmt.Println("Total size: ",fSize," bytes")


  // Request
  fmt.Print("Sending command 'T' ")
  h.Tx([]byte("T"))

  // Reading
  time.Sleep(2 * time.Millisecond)
  fSize = h.RxMetadata()
  fmt.Println("Total size: ",fSize," bytes")

  N := fSize / uint32(100)
  if fSize % uint32(100) != 0 {
    N++
  }
  fmt.Println("Waiting ",N," dataframes")

  //req := make([]byte,3)
  //req[0] = 'I'
  for i:= uint16(0); i < uint16(N); i++ {
    //j := i + uint16(1)
    //req[1] = uint8(j & 0x00FF)
    //req[2] = uint8(j >> 8)

    //h.WaitTillRxNull()
    //fmt.Print("Requesting: ",j)
    //h.Tx(req)
    //fmt.Println(" ok")

    if !h.RxHeader() {
      continue
    }

    //dt,ok :=  h.RxDataframe(0)
    _,ok :=  h.RxDataframe(0)
    if !ok {
      continue
    }

    //time.Sleep(time.Second)

  }

  fmt.Println("\nSaving data")
  h.Save("new.jpg")

}
