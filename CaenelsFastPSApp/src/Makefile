TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

# Use typed rset structure (see 3.16.1 release notes)
USR_CPPFLAGS += -DUSE_TYPED_RSET

# C++11 (std::map)
USR_CXXFLAGS += -std=c++11

# Install error_treatment.dbd into <top>/dbd
DBD += error_treatment.dbd

# Build an IOC support library
LIBRARY_IOC += CaenelsMagnetsPSSupport

# Compile and add code to the support library
CaenelsMagnetsPSSupport_SRCS += error_treatment.c
CaenelsMagnetsPSSupport_LIBS += $(EPICS_BASE_IOC_LIBS)

#=============================
# Build the IOC application

PROD_IOC = CaenelsFastPS
# CaenelsFastPS.dbd will be created and installed
DBD += CaenelsFastPS.dbd

# CaenelsFastPS.dbd will be made up from these files:
CaenelsFastPS_DBD += base.dbd

# Include dbd files from all support applications:
CaenelsFastPS_DBD += asyn.dbd
CaenelsFastPS_DBD += drvAsynIPPort.dbd
CaenelsFastPS_DBD += stream.dbd
CaenelsFastPS_DBD += error_treatment.dbd

# Add all the support libraries needed by this IOC
CaenelsFastPS_LIBS += asyn
CaenelsFastPS_LIBS += stream

# CaenelsFastPS_registerRecordDeviceDriver.cpp derives from CaenelsFastPS.dbd
CaenelsFastPS_SRCS += CaenelsFastPS_registerRecordDeviceDriver.cpp

# Build the main IOC entry point on workstation OSs.
CaenelsFastPS_SRCS_DEFAULT += CaenelsFastPSMain.cpp
CaenelsFastPS_SRCS_vxWorks += -nil-

# Link in the code from our support library
CaenelsFastPS_LIBS += CaenelsMagnetsPSSupport

# Add support from base/src/vxWorks if needed
#CaenelsFastPS_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

# Link QSRV (pvAccess Server) if available
ifdef EPICS_QSRV_MAJOR_VERSION
    CaenelsFastPS_LIBS += qsrv
    CaenelsFastPS_LIBS += $(EPICS_BASE_PVA_CORE_LIBS)
    CaenelsFastPS_DBD += PVAServerRegister.dbd
    CaenelsFastPS_DBD += qsrv.dbd
endif

# Finally link to the EPICS Base libraries
CaenelsFastPS_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

