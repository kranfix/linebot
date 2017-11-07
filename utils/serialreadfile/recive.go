package serialUpload

import (
  "fmt"
)

func (h *Handler) RxMetadata() {
  // Implement later. This is a temporal solution.
  temp := make([]byte,4)
  h.Rx(temp)
  fileSize := uint32(temp[0])
  fileSize += uint32(temp[1]) << 8
  fileSize += uint32(temp[2]) << 16
  fileSize += uint32(temp[3]) << 24
}

func (h *Handler) RxHeader() (n int, err error) {
  n,err = h.Rx(h.headerbuf)
  if err != nil {
    return
  } else if n != HeaderSize {
    err = fmt.Errorf("Serial Upload Header: %d/%d",n,HeaderSize)
    return
  }

  h.header.ReadBytes(&(h.headerbuf)[0])
  if !h.header.Verify() {
    err = fmt.Errorf("Serial Upload Header: %d","Not well readed")
    return
  }
  h.header.Len -= uint8(4) // substracting offset
  return
}

func (h *Handler) RxDataframe() {
  h.offset += uint32(h.DtLen) * uint32(h.dtNum)
  end := h.offset + uint32(h.h  eader.Len)

  n,err := h.Rx(h.dtbuf[h.offset:end])
  if err != nil {
    return
  } else if uint8(n) < h.header.Len {
    err = fmt.Errorf("Serial Upload Header: %d/%d",n,HeaderSize)
    return
  }
}
