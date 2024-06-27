/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   sample_pub.c
 * Author: mimi
 *
 * Created on 26 czerwca 2024, 09:43
 */

#include <stdio.h>
#include <stdlib.h>
#include <memory.h> 
#include <string.h>
#include <signal.h>
#include <sys/time.h>

#include <mqtt/MQTTClient.h>

struct opts_struct
{
    char* clientid;
    int nodelimiter;
    char* delimiter;
    enum QoS qos;
    char* username;
    char* password;
    char* host;
    int port;
    int showtopics;
};

extern volatile int toStop;
extern struct opts_struct opts;


void usage__publish()
{
	printf("MQTT stdout publish\n");
	printf("Usage: mqtttest topicname message <options>, where options are:\n");
	printf("  --host <hostname> (default is localhost)\n");
	printf("  --port <port> (default is 1883)\n");
	printf("  --qos <qos> (default is 2)\n");
	printf("  --delimiter <delim> (default is \\n)\n");
	printf("  --clientid <clientid> (default is hostname+timestamp)\n");
	printf("  --username none\n");
	printf("  --password none\n"); 
	exit(-1);
}

/* MQTT */
Network mqttnet;
MQTTClient mqttclient;

char* topic;

#define SRV_BUFFER_SIZE 100 
unsigned char srvbufwr[SRV_BUFFER_SIZE];
unsigned char srvbufrd[SRV_BUFFER_SIZE];

void mqtt_service_init()
{
    NetworkInit(&mqttnet);
    MQTTClientInit(&mqttclient, &mqttnet, 1000, srvbufwr, SRV_BUFFER_SIZE, srvbufrd, SRV_BUFFER_SIZE);
}


int  mqtt_service_connect()
{
    int rc = NetworkConnect(&mqttnet, opts.host, opts.port);
    if(rc) {
        printf("Connect to %s error: %i", opts.host, rc );
        return rc;
    }
    

}

int mqtt_service_publish(char* messagepayload)
{
    
    printf("Publish to %s\n", topic);
        
    // MQTT Publish - send an MQTT publish packet and wait for all acks to complete for all QoSs
    MQTTMessage mqttmsg;
    mqttmsg.qos = QOS1;
    mqttmsg.dup = 0; 
    mqttmsg.payload = messagepayload;
    mqttmsg.payloadlen = strlen(messagepayload);
    
    int rc = MQTTPublish(&mqttclient, topic, &mqttmsg); 
    printf("Published %d\n", rc);
}


int main__publish(int argc, char** argv)
{
    int rc = 0;
    
    topic = argv[1];
    char* messagepayload = argv[2];

    mqtt_service_init();
     
    rc = mqtt_service_connect();
    printf("Network connected %d\n", rc);
    
    MQTTPacket_connectData data = MQTTPacket_connectData_initializer;       
    data.willFlag = 0;
    data.MQTTVersion = 3;
    data.clientID.cstring = opts.clientid;
    data.username.cstring = opts.username;
    data.password.cstring = opts.password;

    data.keepAliveInterval = 0;
    data.cleansession = 1;
    printf("Send mqtt connect to %s %d\n", opts.host, opts.port);
	
    rc = MQTTConnect(&mqttclient, &data);
    printf("MQTT Connected %d\n", rc);

    
    rc = mqtt_service_publish(messagepayload);
    
//    sleep(30);
//    
//    rc = mqtt_service_publish(messagepayload);
    
    sleep(2);

    printf("Stopping\n");
    MQTTDisconnect(&mqttclient);
    NetworkDisconnect(&mqttnet);

    return 0;
    
}







/*  first simple function
int main__publish(int argc, char** argv)
{
    int rc = 0;
    

    char* topic = argv[1];
    char* messagepayload = argv[2];

    Network c;
    MQTTClient n;

    NetworkInit(&n);
    MQTTClientInit(&c, &n, 1000, buf, 100, readbuf, 100);
    
    NetworkConnect(&n, opts.host, opts.port);
    
    MQTTPacket_connectData data = MQTTPacket_connectData_initializer;       
    data.willFlag = 0;
    data.MQTTVersion = 3;
    data.clientID.cstring = opts.clientid;
    data.username.cstring = opts.username;
    data.password.cstring = opts.password;

    data.keepAliveInterval = 0;
    data.cleansession = 1;
    printf("Connecting to %s %d\n", opts.host, opts.port);
	
    rc = MQTTConnect(&c, &data);
    printf("Connected %d\n", rc);

    
    printf("Publish to %s\n", topic);
    
    
    
    // MQTT Publish - send an MQTT publish packet and wait for all acks to complete for all QoSs
    MQTTMessage mqttmsg;
    mqttmsg.qos = QOS1;
    mqttmsg.dup = 0;
    mqttmsg.id  = 1;  // packetid
    mqttmsg.payload = messagepayload;
    mqttmsg.payloadlen = strlen(messagepayload);
    
    rc = MQTTPublish(&c, topic, &mqttmsg); 
    printf("Published %d\n", rc);

    sleep(2);

    printf("Stopping\n");

    MQTTDisconnect(&c);
    NetworkDisconnect(&n);

    return 0;
    
}
*/



