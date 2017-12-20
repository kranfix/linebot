package main

import(
  "fmt"
  "time"
  "github.com/eclipse/paho.mqtt.golang"
)

var (
  broker string = "tcp://190.90.6.43:1883"
  topic string = "lbm2"
  qos byte = byte(0)
  retained bool = false
)

func main(){
  c := createMqttClient()

  var ATcmd string
  for {
    fmt.Print("Insert AT command: ")
    ReadCmd:
    fmt.Scanf("%s",&ATcmd)
    switch ATcmd {
    case "":
      goto ReadCmd
    default:
      c.Publish(topic, qos, retained, ATcmd)
    }
  }
}

func createMqttClient() mqtt.Client {
  opts := mqtt.NewClientOptions().AddBroker(broker).SetClientID("")
	opts.SetKeepAlive(2 * time.Second)
	opts.SetPingTimeout(3000 * time.Millisecond)

  mqttClient := mqtt.NewClient(opts)
	if token := mqttClient.Connect(); token.Wait() && token.Error() != nil {
		panic(token.Error())
	}

  return mqttClient
}
