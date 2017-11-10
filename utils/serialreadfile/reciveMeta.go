package serialUpload

import (
  "fmt"
  "unsafe"
)

var buf = make([]byte,4)

func (h *Handler) RxMetadata() uint32 {
  // Implement later. This is a temporal solution.
  h.Rx(buf)
  fileSize := *(*uint32)(unsafe.Pointer(&buf[0]))

  h.DtLen = 100
  //h.DtLen = h.header.DtLen
  h.dtbuf = make([]byte,fileSize)
  fmt.Println("Creating file buffer")
  fmt.Println("Capacity: ",cap(h.dtbuf))
  fmt.Println("Lenght: ",len(h.dtbuf))

  //fmt.Printf("% x\n",buf)
  return fileSize
}
