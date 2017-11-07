package serialUpload

import "os"

func (h *Handler) Save(name string, buf []byte) error{
  f,err := os.Create(name)
  if err != nil {
    return err
  }

  f.Write(buf)
  return nil
}
