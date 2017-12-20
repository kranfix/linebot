package main

import (
  "fmt"
  "time"
  "github.com/tarm/serial"
  "github.com/eclipse/paho.mqtt.golang"
)

var (
  broker     string = "tcp://190.90.6.43:1883"
  serialPort string = "/dev/ttyUSB0"
  baud       int    = 9600
)

func main(){
  opts := mqtt.NewClientOptions().AddBroker("tcp://190.90.6.43:1883").SetClientID("")
	opts.SetKeepAlive(2 * time.Second)
	opts.SetPingTimeout(3000 * time.Millisecond)

  mqttClient := mqtt.NewClient(opts)
	if token := mqttClient.Connect(); token.Wait() && token.Error() != nil {
		panic(token.Error())
	}

  ch := make(chan []byte)

  controlLbm := func(client mqtt.Client, msg mqtt.Message){
    ATcmd := msg.Payload()
    fmt.Printf("MQTT ATcmd: %s\n",ATcmd)
    switch string(ATcmd) {
    case "F", "B", "S", "A", "X":
      ch <- ATcmd
    }
  }

  if token := mqttClient.Subscribe("lbm2", 0, controlLbm); token.Wait() && token.Error() != nil {
		fmt.Println(token.Error())
	}

  sendCmd(ch)
}

func sendCmd(ch chan []byte) {
  c := &serial.Config{Name: serialPort, Baud: baud}
  s, err := serial.OpenPort(c)
  if err != nil {
    fmt.Println(err)
  }
  defer s.Close()
  s.Flush()

  for {
    cmd := <-ch
    fmt.Printf("Sending command: %v %s\n",cmd,cmd)
    _, err = s.Write(cmd)
    if err != nil {
      fmt.Println(err)
    }
  }
}
