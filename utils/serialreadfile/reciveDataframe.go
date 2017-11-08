package serialUpload

func (h *Handler) RxDataframe(tries int) bool {
  Len := uint32(h.header.Len)
  //fmt.Printf("%d\n",Len)

  off := uint32(h.DtLen) * uint32(h.header.DtNum-1) //offset
  end := h.offset + Len
  s := h.dtbuf[off:end]

  return h.RxTotal(s,tries)
}
