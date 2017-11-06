package serialUpload

import (
  "os"
  "fmt"
  //"time"
  "github.com/tarm/serial"
)

type Handler struct  {
  Id byte
  Serial *serial.Port
  File *os.File
  temp  []byte // temporal buffer
}

func (h *Handler) SetSerial(port string, baud int, readTimeout) (err error){
  c := &serial.Config{
    Name: port,
    Baud: baud,
    ReadTimeout: readTimeout,
  }
  h.Serial, err = serial.OpenPort(c)
  if err != nil {
    return err
  }
  h.Serial.Flush()
  return nil
}

func (h *Handler) SetFile(name string) {
  if h.File != nil {
    h.File.Close()
  }
  h.File = os.Create(name)
}

func NewHandler(byte id) *Handler{
  return &Handler{Id:id}
}

func (h *Handler) Close() {
  h.Serial.Close()
  h.File.Close()
}
