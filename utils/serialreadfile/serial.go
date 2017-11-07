package serialUpload

func (h *Handler) Rx(buf []byte) (int,error){
  return h.Serial.Read(buf)
}

func (h *Handler) Tx(buf []byte) (int,error){
  return h.Serial.Write(buf)
}
