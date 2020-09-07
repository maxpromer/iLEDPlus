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

uint8_t* iTerminal::timeToBuffer(unsigned int n1, unsigned int n2, bool colon) {
	n1 = n1 % 100;
	n2 = n2 % 100;

	char n1str[5], n2str[5];

	memset(n1str, 0, 5);
	memset(n2str, 0, 5);

	itoa(n1, n1str, 10);
	itoa(n2, n2str, 10);

	if (n2 < 10) {
		n2str[1] = n2str[0];
		n2str[0] = '0';
	}

	memset(buffDisplay, 0, 16);

	if (n1 >= 10) {
		buffDisplay[0] = font8x4[n1str[0] - '0'][1];
		buffDisplay[1] = font8x4[n1str[0] - '0'][2];
		buffDisplay[2] = font8x4[n1str[0] - '0'][3];

		buffDisplay[3] = 0;
		buffDisplay[4] = font8x4[n1str[1] - '0'][1];
		buffDisplay[5] = font8x4[n1str[1] - '0'][2];
		buffDisplay[6] = font8x4[n1str[1] - '0'][3];
	} else {
		buffDisplay[4] = font8x4[n1str[0] - '0'][1];
		buffDisplay[5] = font8x4[n1str[0] - '0'][2];
		buffDisplay[6] = font8x4[n1str[0] - '0'][3];
	}

	// buffDisplay[6] = 0;
	buffDisplay[7] = colon ? 0x28 : 0;
	buffDisplay[8] = 0;

	buffDisplay[9] = font8x4[n2str[0] - '0'][1];
	buffDisplay[10] = font8x4[n2str[0] - '0'][2];
	buffDisplay[11] = font8x4[n2str[0] - '0'][3];

	buffDisplay[12] = 0;
	buffDisplay[13] = font8x4[n2str[1] - '0'][1];
	buffDisplay[14] = font8x4[n2str[1] - '0'][2];
	buffDisplay[15] = font8x4[n2str[1] - '0'][3];

	return buffDisplay;
}

uint8_t* iTerminal::splitDisplayToBuffer(unsigned int n1, unsigned int n2) {
	memset(buffDisplay, 0, 16);

	if (n1 != 9999) {
		n1 = n1 % 100;
		if (n1 >= 10) {
			buffDisplay[0] = font8x4[(n1 / 10) % 10][1];
			buffDisplay[1] = font8x4[(n1 / 10) % 10][2];
			buffDisplay[2] = font8x4[(n1 / 10) % 10][3];

			buffDisplay[3] = 0;
			buffDisplay[4] = font8x4[(n1) % 10][1];
			buffDisplay[5] = font8x4[(n1) % 10][2];
			buffDisplay[6] = font8x4[(n1) % 10][3];
		} else {
			buffDisplay[4] = font8x4[n1][1];
			buffDisplay[5] = font8x4[n1][2];
			buffDisplay[6] = font8x4[n1][3];
		}
	}

	if (n2 != 9999) {
		n2 = n2 % 100;
		if (n2 >= 10) {
			buffDisplay[9] = font8x4[(n2 / 10) % 10][1];
			buffDisplay[10] = font8x4[(n2 / 10) % 10][2];
			buffDisplay[11] = font8x4[(n2 / 10) % 10][3];

			buffDisplay[12] = 0;
			buffDisplay[13] = font8x4[(n2) % 10][1];
			buffDisplay[14] = font8x4[(n2) % 10][2];
			buffDisplay[15] = font8x4[(n2) % 10][3];
		} else {
			buffDisplay[13] = font8x4[n2][1];
			buffDisplay[14] = font8x4[n2][2];
			buffDisplay[15] = font8x4[n2][3];
		}
	}

	return buffDisplay;
}



#endif