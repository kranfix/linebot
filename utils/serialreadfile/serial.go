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
