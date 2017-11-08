package serialUpload

import (
  "fmt"
  "time"
  "github.com/tarm/serial"
)

type Handler struct  {
  Id byte
  header Header
  Serial *serial.Port
  headerbuf  []byte // Buffer for  header
  dtbuf []byte      // Buffer for data
  DtLen uint8
  DtNum uint16
  offset uint32
  //incompletes []byte
}

func (h *Handler) SetSerial(port string, baud int, readTimeout time.Duration) (err error){
  c := &serial.Config{
    Name: port,
    Baud: baud,
    ReadTimeout: readTimeout,
  }
  h.Serial, err = serial.OpenPort(c)
  return err
}

func NewHandler(id byte, init []byte) *Handler{
  h := &Handler{Id:id}
  h.headerbuf = make([]byte,HeaderSize)
  return h
}

func (h *Handler) Close() {
  h.Serial.Close()
}

func (h *Handler) Header() string {
  return h.header.String()
}

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
