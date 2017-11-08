package serialUpload

import (
  "fmt"
)

// returns true each time a good header is read
func (h *Handler) RxHeader() bool {
  h.DetectInit()
  h.RxTotal(h.headerbuf[3:],0)
  //fmt.Printf("% x ",h.headerbuf)
  //fmt.Printf("%d\n",h.header.DtNum)

  // Converting from bytes to Header and verifying
  h.header.ReadBytes(&(h.headerbuf[0]))
  if !h.header.IsOk() {
    return false
  }

  // updating the last dataframe number read
  h.DtNum = h.header.DtNum

  return true
}

func (h *Hanlder) DetectInit() {
  b := h.HeaderSize[0:1]
  N := len(h.init)

  for k := 0; k < N; {
    // Read till a incomming byte
    for n := 0; n == 0 {
      n,_ = h.Rx(b)
    }

    // going to the next detection
    if b[0] == h.init[k] {
      k++
    } else if b[0] == h.init[0] {
      k = 1
    }
  }
}
