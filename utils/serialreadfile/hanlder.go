package serialUpload

import (
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

func NewHandler(id byte) *Handler{
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
