#include <AntoIO.h>

const char *ssid = "";
const char *pass = "";
const char *user = "";
const char *token = "";
const char *thing = "";
const char *channel = "";

// initialize AntoIO instance
AntoIO anto(user, token, thing);

int value = 0;
void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println();
  Serial.print("Anto library version: ");
  Serial.println(anto.getVersion());
  Serial.print("\nTrying to connect ");
  Serial.print(ssid);
  Serial.println("...");

  while (!anto.wifi.begin(ssid, pass));
  Serial.println("\nConnected, trying to connect to broker...");

  while (!anto.mqtt.connect(user, token, true));
  Serial.println("\nConnected");

  /* change "digital-channel" to your channel in switch type */
  anto.mqtt.sub(channel);

  //Port output
  //pinMode(D0,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(4,OUTPUT);
}

void loop() {
  anto.mqtt.loop();
  delay(10);
}

// a callback function for arriving data.
void messageReceived(String topic, String payload, char * bytes, unsigned int length){
  Serial.println("Recieved from: ");

  Serial.print("Things: ");
  unsigned int startChar = topic.indexOf(thing);
  unsigned int endChar = (unsigned)strlen(thing);
  String thingNameRecv = topic.substring(startChar,startChar+endChar);
  Serial.println(thingNameRecv);

  Serial.print("Channel: ");
  startChar = topic.indexOf(channel);
  endChar = (unsigned)strlen(channel);
  String channelNameRecv = topic.substring(startChar,startChar+endChar);
  Serial.println(channelNameRecv);

  Serial.print("Payload: ");
  Serial.println(payload);
  Serial.println("");

  //print thing name from received topic
   if(topic.indexOf(thing)>0){
    if(topic.endsWith(channel)){
      //Serial.println("check lamp");
      value = payload.toInt();
      if(value == 1){
          //digitalWrite(D0,HIGH);
          digitalWrite(2,HIGH);
          digitalWrite(4,HIGH);
      }
      else{
          //digitalWrite(D0,LOW);
          digitalWrite(2,LOW);
          digitalWrite(4,LOW);
      }
    }
  }
}
