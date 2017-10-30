package name

import (
  "fmt"
  "time"
)

func generate(lbmId, lmrId int) string {
  lb := fmt.Sprintf("%.3d:%.3d",lbmId,blrId)
  t := time.Now()

  year, month, day := t.Date()
  date := fmt.Sprintf("%.4d-%.2d-%.2d",year,month,day)

  hour, minute, second := t.Clock()
  clk := fmt.Sprintf("%.2d:%.2d:%.2d",hour,minute,second)

  name := fmt.Sprintf("%s_%s_%s.png",lb,date,clk)
}
