/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
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


uint8_t publisz = 1;
volatile int toStop = 0;

void usage();
void getopts(int argc, char** argv);
int main__subscribe(int argc, char** argv);
int main__publish(int argc, char** argv);

void cfinish(int sig)
{
    signal(SIGINT, NULL);
    toStop = 1;
}


int main(int argc, char** argv)
{
    if (argc < 2) usage();

    getopts(argc, argv);	
    
    signal(SIGINT, cfinish);
    signal(SIGTERM, cfinish);
    
    if(publisz)  main__publish(argc, argv);
    else main__subscribe(argc, argv);
}



void usage__subscribe()
{
	printf("MQTT stdout subscriber\n");
	printf("Usage: mqtttest topicname <options>, where options are:\n");
	printf("  --host <hostname> (default is localhost)\n");
	printf("  --port <port> (default is 1883)\n");
	printf("  --qos <qos> (default is 2)\n");
	printf("  --delimiter <delim> (default is \\n)\n");
	printf("  --clientid <clientid> (default is hostname+timestamp)\n");
	printf("  --username none\n");
	printf("  --password none\n");
	printf("  --showtopics <on or off> (default is on if the topic has a wildcard, else off)\n");
	exit(-1);
}



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

void usage()
{
    if(publisz)  usage__publish();
    else usage__subscribe();
}


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
} opts =
{
    (char*)"stdout-subscriber", 0, (char*)"\n", QOS2, NULL, NULL, (char*)"localhost", 1883, 0
};


void getopts(int argc, char** argv)
{
    int count = 2;

    while (count < argc)
    {
        if (strcmp(argv[count], "--qos") == 0)
        {
            if (++count < argc)
            {
                    if (strcmp(argv[count], "0") == 0)
                            opts.qos = QOS0;
                    else if (strcmp(argv[count], "1") == 0)
                            opts.qos = QOS1;
                    else if (strcmp(argv[count], "2") == 0)
                            opts.qos = QOS2;
                    else
                            usage();
            }
            else
                    usage();
        }
        else if (strcmp(argv[count], "--host") == 0)
        {
            if (++count < argc)
                    opts.host = argv[count];
            else
                    usage__subscribe();
        }
        else if (strcmp(argv[count], "--port") == 0)
        {
            if (++count < argc)
                    opts.port = atoi(argv[count]);
            else
                    usage__subscribe();
        }
        else if (strcmp(argv[count], "--clientid") == 0)
        {
            if (++count < argc)
                    opts.clientid = argv[count];
            else
                    usage__subscribe();
        }
        else if (strcmp(argv[count], "--username") == 0)
        {
            if (++count < argc)
                    opts.username = argv[count];
            else
                    usage__subscribe();
        }
        else if (strcmp(argv[count], "--password") == 0)
        {
            if (++count < argc)
                    opts.password = argv[count];
            else
                    usage__subscribe();
        }
        else if (strcmp(argv[count], "--delimiter") == 0)
        {
            if (++count < argc)
                    opts.delimiter = argv[count];
            else
                    opts.nodelimiter = 1;
        }
        else if (strcmp(argv[count], "--showtopics") == 0)
        {
            if (++count < argc)
            {
                    if (strcmp(argv[count], "on") == 0)
                            opts.showtopics = 1;
                    else if (strcmp(argv[count], "off") == 0)
                            opts.showtopics = 0;
                    else
                            usage__subscribe();
            }
            else
                    usage__subscribe();
        }
        count++;
    }
	
}


void messageArrived(MessageData* md)
{
	MQTTMessage* message = md->message;

	if (opts.showtopics)
		printf("%.*s\t", md->topicName->lenstring.len, md->topicName->lenstring.data);
	if (opts.nodelimiter)
		printf("%.*s", (int)message->payloadlen, (char*)message->payload);
	else
		printf("%.*s%s", (int)message->payloadlen, (char*)message->payload, opts.delimiter);
	//fflush(stdout);
}





int main__subscribe(int argc, char** argv)
{
    int rc = 0;
    unsigned char buf[100];
    unsigned char readbuf[100];

    char* topic = argv[1];

    if (strchr(topic, '#') || strchr(topic, '+'))
            opts.showtopics = 1;
    if (opts.showtopics)
            printf("topic is %s\n", topic);

    Network n;
    MQTTClient c;
 
    NetworkInit(&n);
    NetworkConnect(&n, opts.host, opts.port);
    MQTTClientInit(&c, &n, 1000, buf, 100, readbuf, 100);
 
    MQTTPacket_connectData data = MQTTPacket_connectData_initializer;       
    data.willFlag = 0;
    data.MQTTVersion = 3;
    data.clientID.cstring = opts.clientid;
    data.username.cstring = opts.username;
    data.password.cstring = opts.password;

    data.keepAliveInterval = 10;
    data.cleansession = 1;
    printf("Connecting to %s %d\n", opts.host, opts.port);
	
    rc = MQTTConnect(&c, &data);
    printf("Connected %d\n", rc);

    printf("Subscribing to %s\n", topic);
    rc = MQTTSubscribe(&c, topic, opts.qos, messageArrived);
    printf("Subscribed %d\n", rc);

    while (!toStop)
    {
        MQTTYield(&c, 1000);	
    }

    printf("Stopping\n");

    MQTTDisconnect(&c);
    NetworkDisconnect(&n);

    return 0;
    
}


int main__publish(int argc, char** argv)
{
    int rc = 0;
    unsigned char buf[100];
    unsigned char readbuf[100];

    char* topic = argv[1];
    char* messagepayload = argv[2];

    Network n;
    MQTTClient c;

    NetworkInit(&n);
    NetworkConnect(&n, opts.host, opts.port);
    MQTTClientInit(&c, &n, 1000, buf, 100, readbuf, 100);
 
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



