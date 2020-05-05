/*!
* simple ftdi driver using the i2c data bus
* date: 04/05/2020
* Paul Kumar
* Toronto, Ontario
* BaSc Engineering Science - Biomedical Systems.
* Minor in Mechatronics and Robotics Engingeering
* Revision Hisotry:
* 0.1 20200504 - initial version


*/

/* Include required library files */

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h> 
#include <windows.h>
#include <windef.h>
#include <winnt.h>
#include <winbase.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include "ftd2xx.h"
#include "libMPSSE_i2c.h"
#include <sys/time.h>

/* Application specific macro definations */
#define I2C_DEVICE_ADDRESS_EEPROM 0x57
#define I2C_DEVICE_BUFFER_SIZE 256
#define I2C_WRITE_COMPLETION_RETRY 10
#define START_ADDRESS_EEPROM 0x00 /*read/write start address inside the EEPROM*/
#define END_ADDRESS_EEPROM 0x10
#define RETRY_COUNT_EEPROM 10 /* number of retries if read/write fails */
#define CHANNEL_TO_OPEN 1 /*0 for first available channel, 1 for next... */
#define DATA_OFFSET 1


FT_STATUS ftStatus;
DWORD numDevs;
FT_DEVICE_LIST_INFO_NODE *devInfo;
FT_HANDLE ftHandle;

uint32 channels;
ChannelConfig channelConf;
uint8 buffer[I2C_DEVICE_BUFFER_SIZE];

int CreateDeviceNumList(){
	ftStatus = FT_CreateDeviceInfoList(&numDevs);
		if (ftStatus == FT_OK) {
			printf("Number of devices is %d\n",numDevs);			
		}
	else {
	// FT_CreateDeviceInfoList failed
			printf("Failed...");			
		}
		return ftStatus;
}

int CreateDeviceInfoList(){
	if (numDevs > 0) {
// allocate storage for list based on numDevs
		devInfo = (FT_DEVICE_LIST_INFO_NODE*)malloc(sizeof(FT_DEVICE_LIST_INFO_NODE)*numDevs);
		// get the device information list
		ftStatus = FT_GetDeviceInfoList(devInfo,&numDevs);
		if (ftStatus == FT_OK) {
			for (int i = 0; i < numDevs; i++) {
				printf("Dev %d:\n",i);
				printf(" Flags=0x%x\n",devInfo[i].Flags);
				printf(" Type=0x%x\n",devInfo[i].Type);
				printf(" ID=0x%x\n",devInfo[i].ID);
				printf(" LocId=0x%x\n",devInfo[i].LocId);
				printf(" SerialNumber=%s\n",devInfo[i].SerialNumber);
				printf(" Description=%s\n",devInfo[i].Description);
				printf(" ftHandle=0x%x\n",devInfo[i].ftHandle);
			}
		}
	}
}

int OpenDevice(int deviceIndex){
	ftStatus=FT_Open(deviceIndex, &ftHandle);
	if(ftStatus == FT_OK){
		printf("Device %d open with handle 0x%x, open successfully\n", deviceIndex, ftHandle);
	}
	else{
		printf("device at index %d could not open\n", deviceIndex);
	}

}

int main(int argc, char * argv[])
{
	/*printf("peepeepoopoo\n");
	for(int i=0; i<1000; i++){
		printf("%d\n", i);
	}*/
		// create the device information list

	//on code start
	//determine list of connected devices as well as names
	int result = 0;
	result = CreateDeviceNumList();
	if(result == FT_OK){
		printf("Retrieve device list...\n");
		CreateDeviceInfoList();
	}

	OpenDevice(0);
	
	free(devInfo);
	printf("MPSSE and I2C Buss\n");
	/* define the variables for the driver */
	FT_STATUS status;
	uint8 address;
	uint8 data;
	int i,j;

	#ifdef _MSC_VER
		Init_libMPSSE();
	#endif

	channelConf.ClockRate = I2C_CLOCK_STANDARD_MODE;
	channelConf.LatencyTimer = 255;

	//check the number of i2c channels
	status = I2C_GetNumChannels(&channels);


	printf("Press Any Key to Continue\n");  
	getchar();   
}
