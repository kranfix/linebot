package serialUpload

func (h *Handler) RxDataframe(retries int) ([]byte,bool) {
  Len := uint32(h.header.Len)
  //fmt.Printf("%d\n",Len)

  off := uint32(h.DtLen) * uint32(h.header.DtNum-1) //offset
  end := off + Len
  s := h.dtbuf[off:end]

  return s,h.RxTotal(s,retries)
}
