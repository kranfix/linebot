package serialUpload

import (
  "os"
  "time"
  "github.com/tarm/serial"
)

type Handler struct  {
  Id byte
  Serial *serial.Port
  File *os.File
  Buf  []byte // temporal buffer
}

func (h *Handler) SetSerial(port string, baud int, readTimeout time.Duration) (err error){
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

func (h *Handler) SetFile(name string) (err error){
  if h.File != nil {
    h.File.Close()
  }
  h.File, err = os.Create(name)
  return err
}

func NewHandler(id byte) *Handler{
  return &Handler{Id:id}
}

func (h *Handler) Close() {
  h.Serial.Close()
  h.File.Close()
}
