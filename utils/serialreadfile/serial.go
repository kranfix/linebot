package serialUpload

func (h *Handler) Rx(buf []byte) (int,error){
  return h.Serial.Read(buf)
}

func (h *Handler) Tx(buf []byte) (int,error){
  return h.Serial.Write(buf)
}

func (h *Handler) Flush() {
  h.Serial.Flush()

  temp := make([]byte,1)
  n := 1 // initial value different to 0
  for n > 0{
    n,_ = h.Serial.Read(temp)
  }
}

/*
RxTotal reads serial port till fill a buffer
with a max tries if EOF is read.
buf: Buffer of bytes
max: maximun number of tries without reading a byte
return: true if the reading was ok
*/
func (h *Handler) RxTotal(buf []byte, max int) bool {
  tries := 0
  N := len(buf)
  for k := 0; k < N; k += n {
    n,_ = h.Serial.Read(buf[k:])
    if n == 0 {
      tries++
      if tries == max {
        return false
      }
    }
  }
  return true
}
