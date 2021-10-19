#! /usr/bin/python3

import time
from paho.mqtt import client as mqtt_client
import ssl

broker = 'badgesvr.brucon.org'
port = 8883

certspath="/home/jg/work/brucon/0xd/backend/clicerts/"

bssid = "01:02:03:04:05:06"
mymac = "f1:f2:f3:f4:f5:f6"

subscribed={}
badges={}

#define callbacks
def on_message(client, userdata, message):
  s = str(message.payload.decode("utf-8"))
  print(message.topic+" received message =",s)
  if( "/" in s  ):
    (badge,chan) = s.split("/")
    print(badge,chan)
    if(chan not in subscribed):
      print("new chan "+chan)
      subscribed[chan]={}
      client.subscribe("/topic/"+ chan)
    if(badge not in badges):
      badges[badge]={}
      badges[badge]["ap"]=chan
  if( "|" in s ):
    (badge,stat) = s.split("|")
    if(badge not in badges):
      badges[badge]={}      
    if(stat=="C"):
      badges[badge]["stat"]=stat
      badges[badge]["ap"]=message.topic.split("/")[-1]
    if(stat=="D"):      
      badges[badge]["ap"]=None
     
  

    
def on_log(client, userdata, level, buf):
  print("log: ",buf)

def on_connect(client, userdata, flags, rc):
  print("publishing ")
  client.subscribe("/topic/CONNECT")
  #client.publish("/topic/CONNECT", mymac+"/"+bssid,                 )
  
   
client=mqtt_client.Client(client_id=mymac) 
client.on_message=on_message
client.on_log=on_log
client.on_connect=on_connect
print("connecting to broker")
client.tls_set(
    ca_certs= certspath+"ca-chain.pem",
    certfile= certspath+"out/clicert.2021-10-02-13-20-04.pem",
    keyfile=  certspath+"out/clicert.key.2021-10-02-13-20-04.pem"
#    ,    tls_version=ssl.PROTOCOL_TLSv1_2
)
client.tls_insecure_set(False)
client.connect(broker, port, 60)

client.loop_start()
#wait to allow publish and logging and exit
time.sleep(1)
client.loop_forever()
