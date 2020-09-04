#ifndef __ITerminal_CPP__
#define __ITerminal_CPP__

#include "iTerminal.h"
#include "esp_log.h"

uint8_t buffDisplay[16]; // 16x8
uint8_t font8x4[16 + 1][4] = {
    { 0x00, 0x7c, 0x44, 0x7c }, // 0
    { 0x00, 0x00, 0x7c, 0x00 }, // 1
    { 0x00, 0x5c, 0x54, 0x74 }, // 2
    { 0x00, 0x54, 0x54, 0x7c }, // 3
    { 0x00, 0x70, 0x10, 0x7c }, // 4
    { 0x00, 0x74, 0x54, 0x5c }, // 5
    { 0x00, 0x7c, 0x54, 0x5c }, // 6
    { 0x00, 0x40, 0x40, 0x7c }, // 7
    { 0x00, 0x7c, 0x54, 0x7c }, // 8
    { 0x00, 0x74, 0x54, 0x7c }, // 9
    { 0x00, 0x3c, 0x50, 0x3c }, // A
    { 0x00, 0x7c, 0x54, 0x38 }, // B
    { 0x00, 0x38, 0x44, 0x44 }, // C
    { 0x00, 0x7c, 0x44, 0x38 }, // D
    { 0x00, 0x7c, 0x54, 0x54 }, // E
    { 0x00, 0x7c, 0x50, 0x50 }, // F
    { 0x00, 0x10, 0x10, 0x10 }  // -
};

iTerminal::iTerminal()
{
	polling_ms = 40;
}

void iTerminal::init(void)
{
	// Debug
	esp_log_level_set("*", ESP_LOG_VERBOSE);

	// clear error flag
	error = false;
	// clear initialized flag
	initialized = true;
}

int iTerminal::prop_count(void)
{
	// not supported
	return 0;
}

bool iTerminal::prop_name(int index, char *name)
{
	// not supported
	return false;
}

bool iTerminal::prop_unit(int index, char *unit)
{
	// not supported
	return false;
}

bool iTerminal::prop_attr(int index, char *attr)
{
	// not supported
	return false;
}

bool iTerminal::prop_read(int index, char *value)
{
	// not supported
	return false;
}

bool iTerminal::prop_write(int index, char *value)
{
	// not supported
	return false;
}
// --------------------------------------

void iTerminal::process(Driver *drv)
{

}

uint8_t* iTerminal::numberToBuffer(double n, int base, int decimal) {
	memset(buffDisplay, 0, sizeof(buffDisplay));
	char strBuff[20];
	memset(strBuff, 0, 20);
	if (base == 10) {
		sprintf(strBuff, "%f", n);
		ESP_LOGI("iTerminal", "%s", strBuff);
		while(1) {
			int n = strlen(strBuff);
			if (strBuff[n - 1] == '0') {
				strBuff[n - 1] = 0;
			} else if (strBuff[n - 1] == '.') {
				strBuff[n - 1] = 0;
				break;
			} else {
				break;
			}
		}
		ESP_LOGI("iTerminal", "%s", strBuff);
	} else if (base == 16 || base == 2 || base == 8) {
		itoa(n, strBuff, base);
	}
	
	int len = strlen(strBuff);
	int nextIndex = 0;
	bool hasDot = false;
	for (int i=0;i<len;i++) {
		if (strBuff[i] == '.') {
			hasDot = true;
			break;
		}
	}

	if (len > (hasDot ? 5 : 4)) {
		// Substring
		char newStrBuff[20];
		strcpy(newStrBuff, strBuff);
		memcpy(strBuff, &newStrBuff[len - (hasDot ? 5 : 4)], (hasDot ? 5 : 4));
	}

	if (len < (hasDot ? 5 : 4)) {
		nextIndex = (hasDot ? 5 : 4) - len;
	}
	int i = 0;
	for (;;) {
		char c = strBuff[i];
		i++;
		if (c == '.' && nextIndex > 0) {
			buffDisplay[((nextIndex - 1) * 4) + 3] |= 0x04;
			continue;
		}
		int asciiToIndex = 0;
		if (c >= '0' && c <= '9') {
			asciiToIndex = c - '0';
		} else if (c >= 'a' && c <= 'f') {
			asciiToIndex = c - 'a' + 10;
		} else if (c == '-') {
			asciiToIndex = 16; // -
		}
		memcpy(&buffDisplay[(nextIndex * 4) + 0], font8x4[asciiToIndex], 4);
		nextIndex++;
		if (nextIndex == 4) {
			break;
		}
	}
	return buffDisplay;
}

#endif