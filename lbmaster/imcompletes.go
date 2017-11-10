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

  // Request
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


  // Reading
  time.Sleep(time.Second)
  fSize := h.RxMetadata()
  fmt.Println("Total size: ",fSize," bytes")

  N := fSize / uint32(100)
  if fSize % uint32(100) != 0 {
    N++
  }
  fmt.Println("Waiting ",N," dataframes")

  req := make([]byte,3)
  req[0] = 'I'
  for i:= uint16(0); i < uint16(N); i++ {
  //for i:= uint16(0); i < uint16(9); i++ {
    j := i + uint16(1)
    req[1] = uint8(j & 0x00FF)
    req[2] = uint8(j >> 8)

    request:
    h.WaitTillRxNull()
    fmt.Print("Requesting: ",j)
    n,_ := h.Tx(req[:])
    if n == 3 {
      fmt.Println(" ok")
    } else {
      fmt.Println(" error")
    }


    if !h.RxHeader() {
      goto request
    }

    //dt,ok :=  h.RxDataframe(0)
    _,ok :=  h.RxDataframe(0)
    if !ok {
      goto request
    }

    time.Sleep(time.Second)
  }


  /*temp :=  make([]byte,1)
  h.Rx(temp)
  fmt.Printf("Incomming: %s\n",temp)
  */
  h.Save("new.jpg")

  // Reading incompletes
  /*
  for {

  }
  */
}
