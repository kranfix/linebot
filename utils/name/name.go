package name

import (
  "fmt"
  "time"
)

func Generate(lbmId, lbrId int) string {
  lb := fmt.Sprintf("%.3d:%.3d",lbmId,lbrId)
  t := time.Now()

  year, month, day := t.Date()
  date := fmt.Sprintf("%.4d-%.2d-%.2d",year,month,day)

  hour, minute, second := t.Clock()
  clk := fmt.Sprintf("%.2d:%.2d:%.2d",hour,minute,second)

  name := fmt.Sprintf("%s_%s_%s.png",lb,date,clk)
  return name
}
