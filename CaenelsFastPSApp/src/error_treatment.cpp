#include <stdio.h>
#include <aSubRecord.h>
#include <registryFunction.h>
#include <epicsExport.h>

#include <string.h>
#include <string>
#include <map>
#include <iostream>

const std::map<int, std::string> ngps_error_table = {
    {0, "                                                              "},
    {1, "Error 1  - Unknown command"},
    {2, "Error 2  - Unknown Parameter"},
    {3, "Error 3  - Index out of range"},
    {4, "Error 4  - Not Enough Arguments"},
    {5, "Error 5  - Privilege Level Requirement not met"},
    {6, "Error 6  - Save Error on device"},
    {7, "Error 7  - Invalid password"},
    {8, "Error 8  - Module in fault"},
    {9, "Error 9  - Module already ON"},
    {10,"Error 10 - Setpoint is out of hardware limits"},
    {11,"Error 11 - Setpoint is out of software limits"},
    {12,"Error 12 - Setpoint is not a number"},
    {13,"Error 13 - Module is OFF"},
    {14,"Error 14 - Slew Rate out of limits"},
    {15,"Error 15 - Device is set in local mode"},
    {16,"Error 16 - Module is not in waveform mode"},
    {17,"Error 17 - Module is in waveform mode"},
    {18,"Error 18 - Device is set in remote mode"},
    {19,"Error 19 - Module is already in the selected loop mode"},
    {20,"Error 20 - Module is not in the selected loop mode"},
    {21,"Error 21 - Module is not in normal update mode"},
    {22,"Error 22 - Float mode is already selected"},
    {23,"Error 23 - Unknown sub-command for SFP communication"},
    {24,"Error 24 - Unknown feature or feature not available (AIN,TRIG)"},
    {25,"Error 25 - Parallel Fault"},
    {26,"Error 26 - Waveform error"},
    {27,"Error 27 - Cannot open the required file"},
    {28,"Error 28 - Module is currently inverting the polarity"},
    {29,"Error 29 - Cannot write waveform data"},
    {30,"Error 30 - Polarity switch not allowed"},
    {31,"Error 31 - Cannot set options for socket used by oscilloscope"},
    {32,"Error 32 - Cannot change settings while in parallel slave mode"},
    {33,"Error 33 - MASTER and SLAVES have different FW version"},
    {34,"Error 34 - MASTER and SLAVES are different models"},
    {35,"Error 35 - MASTER and SLAVES have different ratings"},
    {36,"Error 36 - The required feature is not available"},
    {37,"Error 37 - UDP buffer overflow"},
    {38,"Error 38 - Module is in “Wait for OFF”"},
    {39,"Error 39 - This field is read only"},
    {40,"Error 40 - Cannot parse input name for debug field"},
    {41,"Error 41 - Cannot parse input value for debug field"},
    {42,"Error 42 - Cannot parse type for debug field"},
    {43,"Error 43 - DHCP is enabled"},
    {44,"Error 44 - This command is disabled"},
    {99,"Error 99 - Unknown error"}
};

static long ngpsError(aSubRecord *prec)
{
    // Input A provides the error code
    int errcode = *(int *)prec->a;

    // Find error message in table
    std::string errmsg = (ngps_error_table.find(errcode) == ngps_error_table.end()) ?
        ngps_error_table.at(99) : ngps_error_table.at(errcode); 

    // Write to stringin record
    std::string clearbuf = ngps_error_table.at(0);
    memcpy(prec->vala, (void *)clearbuf.c_str(), clearbuf.size());
    memcpy(prec->vala, (void *)errmsg.c_str(), errmsg.size());

    return 0;
}

extern "C"
{
    epicsRegisterFunction(ngpsError);
}


