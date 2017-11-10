package serialUpload

import "fmt"

func (h *Handler) LastDf() {
  offset := uint32(h.DtLen) * uint32(h.DtNum-1)
  end := offset + uint32(h.DtLen)
  fmt.Println("Offset: ",offset)
  fmt.Println("End: ",end)

  fmt.Println("\nLast read:")
  s := h.dtbuf[offset-400:end]

  for i := 0; i < 4; i++ {
    k := 100 * i
    for j := 0; j < 5; j++ {
      k += 20 * j
      fmt.Printf("% x\n",s[k:k+20])
    }
    fmt.Println()
  }
}

func (h *Handler) RxLen() uint8 {
  return h.header.Len
}
