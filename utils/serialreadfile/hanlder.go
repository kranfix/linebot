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
  dtbuf []byte      // Buffer for dataframe
  dtNum uint8
  DtLen uint8
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
  if err != nil {
    return err
  }
  h.Serial.Flush()
  return nil
}

func NewHandler(id byte) *Handler{
  h := &Handler{Id:id}
  h.headerbuf = make([]byte,HeaderSize)
  h.dtbuf = make([]byte,256)
  //h.incompletes = make([]byte,1000)
  return h
}

func (h *Handler) Close() {
  h.Serial.Close()
}
