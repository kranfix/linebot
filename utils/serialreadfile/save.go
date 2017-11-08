package serialUpload

import "os"

func (h *Handler) Save(name string) error{
  f,err := os.Create(name)
  if err != nil {
    return err
  }

  f.Write(h.dtbuf)
  return nil
}
