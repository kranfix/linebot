package serialUpload

import (
  "os"
  "sync"
  "time"
  "github.com/tarm/serial"
)

type Handler struct  {
  Id          byte
  header      Header
  File       *os.File
  Serial     *serial.Port
  headerbuf []byte  // Buffer for  header
  dtbuf     []byte  // Buffer for data
  DtLen       uint8
  DtNum       uint16
  //incompletes []byte
  //cond *sync.Cond
  locked bool
  mutex *sync.Mutex
}

func NewHandler(id byte) *Handler{
  h := &Handler{Id:id}
  h.headerbuf = make([]byte,HeaderSize)
  h.dtbuf = make([]byte,256)

  //mutex := &sync.Mutex{}
  //h.cond = NewCond(mutex)

  return h
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

func (h *Handler) SetFile(name string) (err error) {
  h.File,err = os.Create(name)
  if err != nil {
    return
  }

  err = h.File.Sync()
  return
}

func (h *Handler) Close() {
  h.Serial.Close()
  h.File.Close()
}

func (h *Handler) Header() string {
  return h.header.String()
}
