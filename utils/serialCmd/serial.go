package serialUpload

func (h *Handler) Rx(buf []byte) (int,error){
  return h.Serial.Read(buf)
}

func (h *Handler) Tx(buf []byte) (int,error){
  return h.Serial.Write(buf)
}

func (h *Handler) Flush() {
  h.WaitTillRxNull()
  h.Serial.Flush()
}

func (h *Handler) WaitTillRxNull() {
  temp := make([]byte,1)
  for n := 1; n > 0; n,_ = h.Serial.Read(temp) {
    // Do nothing here
  }
}

func (h *Handler) WaitTillRxNonNull() byte {
  temp := make([]byte,1)
  for n := 0; n == 0; n,_ = h.Serial.Read(temp) {
    // Do nothing here
  }
  return temp[0]
}


/*
RxTotal reads serial port till fill a buffer
with a max tries if EOF is read.
buf: Buffer of bytes
max: maximun number of retries without reading a byte
return: true if the reading was ok
*/
func (h *Handler) RxTotal(buf []byte, max int) bool {
  var n int
  retries := 0
  N := len(buf)
  for k := 0; k < N; k += n {
    n,_ = h.Serial.Read(buf[k:])
    if n == 0 {
      retries++
      if retries >= max {
        return false
      }
    }
  }
  return true
}
