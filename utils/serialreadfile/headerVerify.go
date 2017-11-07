package serialUpload

var (
  HeadInit = [...]byte{'!','@','#'}
)

func (h *Header) Verify() bool {
  for i, v := range h.Init {
    if v != HeadInit[i] {
      return false
    }
  }
  if h.Len < uint8(4) {
    return false
  }
  return true
}
