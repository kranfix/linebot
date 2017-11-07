package serialUpload

import (
  "fmt"
)

var HeaderSize = 8

type Header struct {
  Init [3]byte
  Len uint8    // dataframe lenght
  Src uint8    // source id
  Dst uint8    // destination id
  DfNum uint16 // dataframe nummber
}

func (h Header) String() string {
  str := "Lenght: %d\n"
  str += "src: %d\n"
  str += "dst: %d\n"
  str += "Dataframe Number: %d\n"
  return fmt.Sprintf(str,h.Len,h.Src,h.Dst,h.DfNum)
}
