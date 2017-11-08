package serialUpload

import (
  "fmt"
)

func (h *Handler) RxDataframe() {
  Len := uint32(h.header.Len)
  //fmt.Printf("%d\n",Len)

  h.offset = uint32(h.DtLen) * uint32(h.header.DtNum-1)
  end := h.offset + Len
  s := h.dtbuf[h.offset:end]

  var n int
  for N := uint32(0); N < Len; N += uint32(n) {
    n,_ = h.Rx(s[N:])
  }
  return
}
