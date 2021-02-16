#!../../bin/CaenelsFastPS

< envPaths

epicsEnvSet("PATH", "${PATH}:${TOP}/bin")
epicsEnvSet("STREAM_PROTOCOL_PATH", ".:../../protocols")
epicsEnvSet("P","$(P=caenels)")
epicsEnvSet("R1","$(R1=fastps)")
epicsEnvSet("R2","$(R2=ngps)")

cd "${TOP}"

## Register all support components
dbLoadDatabase("dbd/CaenelsFastPS.dbd",0,0)
CaenelsFastPS_registerRecordDeviceDriver(pdbbase)

## Configure device (Fast-PS)
epicsEnvSet(ASYNPORT1, "$(P)-$(R1)")
drvAsynIPPortConfigure("$(ASYNPORT1)","localhost:10001",0,0,0)

## Load record instances (Fast-PS)
dbLoadRecords("db/caenels.template", "PORT=$(ASYNPORT1),P=$(P):,R=$(R1):")
dbLoadRecords("db/fastps-faults.template", "P=$(P):,R=$(R1):")

## Configure device (NGPS)
epicsEnvSet(ASYNPORT2, "$(P)-$(R2)")
drvAsynIPPortConfigure("$(ASYNPORT2)","localhost:10001",0,0,0)

## Load record instances (NGPS)
dbLoadRecords("db/caenels.template", "PORT=$(ASYNPORT2),P=$(P):,R=$(R2):")
dbLoadRecords("db/ngps-faults.template", "P=$(P):,R=$(R2):")

cd "${TOP}/iocBoot/${IOC}"
iocInit()
