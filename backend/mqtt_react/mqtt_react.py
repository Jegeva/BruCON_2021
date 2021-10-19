#! /usr/bin/python3

import time
from paho.mqtt import client as mqtt_client
import ssl
import time
import datetime

broker = 'badgesvr.brucon.org'
port = 8883

certspath="/home/jg/work/brucon/0xd/backend/clicerts/"

bssid = "01:02:03:04:05:06"
mymac = "f1:f2:f3:f4:f5:f6"

subscribed={}
quals = {}
badges={}
AP={}
times={}


#define callbacks
def on_message(client, userdata, message):
  if message is None:
    return
  
  s = str(message.payload.decode("UTF8"))
  
  print(message.topic+" received message ="+s+" q "+str(message.qos))
  if( "/" in s  ):
    (badge,chan) = s.split("/")
    print("CONNECTION",badge,chan)
    
    if(chan not in subscribed):
      print("new chan "+chan)
      quals[chan]=0
      times[chan]=0
      subscribed[chan]={
        badge : 1
      }
      client.subscribe("/topic/"+ chan)
      
    if(badge not in badges):
      badges[badge]={}
      badges[badge]["ap"]=chan
      badges[badge]["stat"]=None
      
  if( "|" in s ):
    (badge,stat) = s.split("|")
    ap = message.topic.split("/")[-1]
 
    
    if(badge not in badges):
      badges[badge]={}
      badges[badge]["stat"]=None
      badges[badge]["ap"]=ap

    print("Stat change",badge,stat,badges[badge]["ap"],"->",ap)
      
    if(stat=="C"):      
      badges[badge]["stat"]=stat
      if badge in subscribed[ ap ]:
          del subscribed[ ap ] [badge]
      badges[badge]["ap"]=ap
      subscribed[ ap ] [badge] = 1
      print(len( subscribed[ap]))
      
    if(stat=="D"):
      if badge in badges:
        badges[badge]["stat"]=stat
      else:
        badges[badge]={}
        badges[badge]["stat"]=stat
        badges[badge]["ap"]=None
      
      if badge in subscribed[ ap ]:
          del subscribed[ ap ] [badge]
      badges[badge]["ap"]=None


    if(stat=="M"):
      return

    if(stat[0] == "R"):
      num = stat.split("@")[1]
      print( "num" , ap, num )
      quals[ap] = num
      times[ap] = time.time()
      client.publish(message.topic,"V:%d" % (int(num)),retain=True)


    # only rq a measurement every 5 min
    if( (len( subscribed[ap]) > 0)):
      if( (len( subscribed[ap])%5 == 0)):
        if( time.time() -  times[ap] > 300): 
          client.publish(message.topic,badge+"|M")
          #neutralise measurement rq for 1 min
          #so if the badge doesn't answer we re request
          #to the next %5
          times[ap] += 60
        else:
          print(ap,"too soon")
    
def on_log(client, userdata, level, buf):
  print("log: ",level,buf)

def on_connect(client, userdata, flags, rc):
  print("rc: " + str(rc))
  client.subscribe("/topic/CONNECT",1)

  
   
client=mqtt_client.Client(client_id=mymac,clean_session=True)
client.on_message=on_message
#client.on_log=on_log
client.on_connect=on_connect
print("connecting to broker")
client.tls_set(
  ca_certs= certspath+"ca-chain.pem",
  certfile= certspath+"out/clicert.2021-10-02-13-20-04.pem",
  keyfile=  certspath+"out/clicert.key.2021-10-02-13-20-04.pem",
  tls_version=ssl.PROTOCOL_TLSv1_2
)
client.tls_insecure_set(False)
client.connect(broker, port, 60)


#client.loop_start()

client.loop_forever()
#client.loop_start()
while(1):
  time.sleep(1)
