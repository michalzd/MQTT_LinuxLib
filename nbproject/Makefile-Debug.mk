#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/MQTT/Client/MQTTClient.o \
	${OBJECTDIR}/MQTT/Client/MQTTLinux.o \
	${OBJECTDIR}/MQTT/Packet/MQTTConnectClient.o \
	${OBJECTDIR}/MQTT/Packet/MQTTConnectServer.o \
	${OBJECTDIR}/MQTT/Packet/MQTTDeserializePublish.o \
	${OBJECTDIR}/MQTT/Packet/MQTTFormat.o \
	${OBJECTDIR}/MQTT/Packet/MQTTPacket.o \
	${OBJECTDIR}/MQTT/Packet/MQTTSerializePublish.o \
	${OBJECTDIR}/MQTT/Packet/MQTTSubscribeClient.o \
	${OBJECTDIR}/MQTT/Packet/MQTTSubscribeServer.o \
	${OBJECTDIR}/MQTT/Packet/MQTTUnsubscribeClient.o \
	${OBJECTDIR}/MQTT/Packet/MQTTUnsubscribeServer.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libmqtt.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libmqtt.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libmqtt.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/MQTT/Client/MQTTClient.o: MQTT/Client/MQTTClient.c
	${MKDIR} -p ${OBJECTDIR}/MQTT/Client
	${RM} "$@.d"
	$(COMPILE.c) -g -IMQTT/Packet -IMQTT/Client -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MQTT/Client/MQTTClient.o MQTT/Client/MQTTClient.c

${OBJECTDIR}/MQTT/Client/MQTTLinux.o: MQTT/Client/MQTTLinux.c
	${MKDIR} -p ${OBJECTDIR}/MQTT/Client
	${RM} "$@.d"
	$(COMPILE.c) -g -IMQTT/Packet -IMQTT/Client -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MQTT/Client/MQTTLinux.o MQTT/Client/MQTTLinux.c

${OBJECTDIR}/MQTT/Packet/MQTTConnectClient.o: MQTT/Packet/MQTTConnectClient.c
	${MKDIR} -p ${OBJECTDIR}/MQTT/Packet
	${RM} "$@.d"
	$(COMPILE.c) -g -IMQTT/Packet -IMQTT/Client -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MQTT/Packet/MQTTConnectClient.o MQTT/Packet/MQTTConnectClient.c

${OBJECTDIR}/MQTT/Packet/MQTTConnectServer.o: MQTT/Packet/MQTTConnectServer.c
	${MKDIR} -p ${OBJECTDIR}/MQTT/Packet
	${RM} "$@.d"
	$(COMPILE.c) -g -IMQTT/Packet -IMQTT/Client -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MQTT/Packet/MQTTConnectServer.o MQTT/Packet/MQTTConnectServer.c

${OBJECTDIR}/MQTT/Packet/MQTTDeserializePublish.o: MQTT/Packet/MQTTDeserializePublish.c
	${MKDIR} -p ${OBJECTDIR}/MQTT/Packet
	${RM} "$@.d"
	$(COMPILE.c) -g -IMQTT/Packet -IMQTT/Client -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MQTT/Packet/MQTTDeserializePublish.o MQTT/Packet/MQTTDeserializePublish.c

${OBJECTDIR}/MQTT/Packet/MQTTFormat.o: MQTT/Packet/MQTTFormat.c
	${MKDIR} -p ${OBJECTDIR}/MQTT/Packet
	${RM} "$@.d"
	$(COMPILE.c) -g -IMQTT/Packet -IMQTT/Client -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MQTT/Packet/MQTTFormat.o MQTT/Packet/MQTTFormat.c

${OBJECTDIR}/MQTT/Packet/MQTTPacket.o: MQTT/Packet/MQTTPacket.c
	${MKDIR} -p ${OBJECTDIR}/MQTT/Packet
	${RM} "$@.d"
	$(COMPILE.c) -g -IMQTT/Packet -IMQTT/Client -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MQTT/Packet/MQTTPacket.o MQTT/Packet/MQTTPacket.c

${OBJECTDIR}/MQTT/Packet/MQTTSerializePublish.o: MQTT/Packet/MQTTSerializePublish.c
	${MKDIR} -p ${OBJECTDIR}/MQTT/Packet
	${RM} "$@.d"
	$(COMPILE.c) -g -IMQTT/Packet -IMQTT/Client -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MQTT/Packet/MQTTSerializePublish.o MQTT/Packet/MQTTSerializePublish.c

${OBJECTDIR}/MQTT/Packet/MQTTSubscribeClient.o: MQTT/Packet/MQTTSubscribeClient.c
	${MKDIR} -p ${OBJECTDIR}/MQTT/Packet
	${RM} "$@.d"
	$(COMPILE.c) -g -IMQTT/Packet -IMQTT/Client -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MQTT/Packet/MQTTSubscribeClient.o MQTT/Packet/MQTTSubscribeClient.c

${OBJECTDIR}/MQTT/Packet/MQTTSubscribeServer.o: MQTT/Packet/MQTTSubscribeServer.c
	${MKDIR} -p ${OBJECTDIR}/MQTT/Packet
	${RM} "$@.d"
	$(COMPILE.c) -g -IMQTT/Packet -IMQTT/Client -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MQTT/Packet/MQTTSubscribeServer.o MQTT/Packet/MQTTSubscribeServer.c

${OBJECTDIR}/MQTT/Packet/MQTTUnsubscribeClient.o: MQTT/Packet/MQTTUnsubscribeClient.c
	${MKDIR} -p ${OBJECTDIR}/MQTT/Packet
	${RM} "$@.d"
	$(COMPILE.c) -g -IMQTT/Packet -IMQTT/Client -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MQTT/Packet/MQTTUnsubscribeClient.o MQTT/Packet/MQTTUnsubscribeClient.c

${OBJECTDIR}/MQTT/Packet/MQTTUnsubscribeServer.o: MQTT/Packet/MQTTUnsubscribeServer.c
	${MKDIR} -p ${OBJECTDIR}/MQTT/Packet
	${RM} "$@.d"
	$(COMPILE.c) -g -IMQTT/Packet -IMQTT/Client -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MQTT/Packet/MQTTUnsubscribeServer.o MQTT/Packet/MQTTUnsubscribeServer.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
