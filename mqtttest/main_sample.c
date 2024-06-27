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


int pub_sub = 1;  // 0:subscribe,  1: publish

volatile int toStop = 0;

extern void usage__publish();
extern int main__subscribe(int argc, char** argv);

extern void usage__subscribe();
extern int main__publish(int argc, char** argv);


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

struct opts_struct opts =
{
    (char*)"stdout-subscriber", 0, (char*)"\n", QOS1, NULL, NULL, (char*)"localhost", 1883, 0
};




void cfinish(int sig)
{
    signal(SIGINT, NULL);
    toStop = 1;
}

void usage()
{
    if(pub_sub)  usage__publish();
    else usage__subscribe();
}




void getopts(int argc, char** argv);


int main(int argc, char** argv)
{
    
    if (argc < 2) usage();
     
    getopts(argc, argv);	
    
    signal(SIGINT, cfinish);
    signal(SIGTERM, cfinish);
    
    if(pub_sub)  main__publish(argc, argv);
    else main__subscribe(argc, argv);
}




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

