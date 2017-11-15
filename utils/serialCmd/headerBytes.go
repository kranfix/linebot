package serialUpload

import (
  "unsafe"
)

func (h *Header) ReadBytes(b *byte) {
  *h = *(*Header)(unsafe.Pointer(b))
}
