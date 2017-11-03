package serialUpload

import (
  "fmt"
)

type Header struct {
  Init [3]byte
  Src uint8    // source id
  Dst uint8    // destination id
  DfNum uint16 // dataframe nummber
  Len uint8    // dataframe lenght
}

func (h Header) String() string {
  str := "src: %d\n"
  str += "dst: %d\n"
  str += "Dataframe Number: %d\n"
  str += "Number of bytes: %d\n"
  return fmt.Sprintf(str,h.Src,h.Dst,h.DfNum,h.Len)
}
