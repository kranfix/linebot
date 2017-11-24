package main

import (
  "os"
  //"fmt"
  "unsafe"
  su "github.com/kranfix/linebot/utils/serialCmd"
)

type Slice struct {
  addr uintptr
  len  int
  cap  int
}

func main() {
  h := su.Header{
    Init:[...]byte{'!','@','#'},
    Src:1,
    Dst:0,
    Len:uint8(1), // Initalized in 1 to be overwrited
  }
  fin,_ := os.Open("../lbmaster/streamming.go")
  fout,_ := os.Create("out.txt")
  defer fin.Close()
  defer fout.Close()

  s := make([]byte,100)
  N := 0
  for i := uint16(0); h.Len != uint8(0); i++ {
    n,_ := fin.Read(s)
    N += n
    h.Len = uint8(n)
    h.DtNum = i + 1
    sl := Slice{uintptr(unsafe.Pointer(&h)), 8, 8}
    b := *(*[]byte)(unsafe.Pointer(&sl))
    fout.Write(b[:])
    fout.Write(s)
  }
  fin.Close()
  fout.Close()

  fin,_ = os.Open("out.txt")
  fout,_ = os.Create("test.txt")
  sl := Slice{uintptr(unsafe.Pointer(&N)), 2, 2}
  b := *(*[]byte)(unsafe.Pointer(&sl))
  fout.Write(b)
  for i,n := uint16(0),1; n != 0; i++ {
    n,_ = fin.Read(s)
    fout.Write(s)
  }
  fin.Close()
  fout.Close()
}
