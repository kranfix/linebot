package serialUpload

import (
  "time"
  "github.com/tarm/serial"
)

type Handler struct  {
  Serial *serial.Port
  File *os.File
  temp  []byte // temporal buffer
}

func New(port string, baud int) *Hander {
  c := &serial.Config{Name: "/dev/ttyUSB0", Baud: 38400}
  s, err := serial.OpenPort(c)
  if err != nil {
    fmt.Println(err)
  }
  s.Flush()
}

func (h *Handler) Close() {
  h.Serial.Close()
  h.File.Close()
}
