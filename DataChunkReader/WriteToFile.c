#pragma once
#include<stdio.h>
unsigned long endianSwapLong(unsigned long val) {
	return val = ((val >> 24) & 0xff) | // move byte 3 to byte 0
		((val << 8) & 0xff0000) |		// move byte 1 to byte 2
		((val >> 8) & 0xff00) |			// move byte 2 to byte 1
		((val << 24) & 0xff000000);		// byte 0 to byte 3

}


unsigned short endianSwapShort(unsigned short val) {
	return val = (val >> 8) | (val << 8);
}




unsigned char getRandomByte() {
	int min = 50;
	int max = 150;

	// Generate a random number between 0 and RAND_MAX
	int randomNum = rand();

	int range = max - min + 1;

	// Normalize the random number to the desired range
	unsigned char randomByte = (unsigned char)((randomNum % range) + min);

	return randomByte;
}

unsigned short getRandomShort() {
	int min = 1000;
	int max = 2000;

	// Generate a random number between 0 and RAND_MAX
	unsigned short randomNum = rand();

	unsigned short range = (unsigned short)(max)-(unsigned short)(min)+1;

	// Normalize the random number to the desired range
	unsigned short randomUnsignedShort = (unsigned short)((randomNum % range) + min);

	return randomUnsignedShort;
}

unsigned long getRandomLong() {
	int min = 3000;
	int max = 5000;

	unsigned long range = (unsigned long)max - (unsigned long)min + 1;

	// Generate two random unsigned integers, each representing half of the range
	unsigned long randomNum1 = (unsigned long)rand();
	unsigned long randomNum2 = (unsigned long)rand();

	// Combine the two random numbers to cover the entire range
	unsigned long randomUnsignedLong = ((randomNum1 << 32) | randomNum2) % range + min;

	return randomUnsignedLong;
}

void generateRandomBytes(unsigned char* bytesP, int n) {

	//create array of random bytes
	for (int i = 0; i < n; i++) {
		bytesP[i] = getRandomByte();
	}

}

void generateRandomShorts(unsigned short* shortsP, int n) {

	//create array of random bytes
	for (int i = 0; i < n; i++) {
		shortsP[i] = getRandomShort();
	}

}

void generateRandomLongs(unsigned long* longsP, int n) {

	//create array of random bytes
	for (int i = 0; i < n; i++) {
		longsP[i] = getRandomLong();
	}

}

void writeByteChunk(FILE* outputFile, unsigned char* p, int numBytes) {
	//write length of the byte chunk
	unsigned char buffer = 0x00;

	int byteInfoWrite = fwrite(&numBytes, sizeof(unsigned long), 1, outputFile);
	
	for (int i = 0; i < numBytes; i++) {
		int byteWrite = fwrite(&p[i], sizeof(unsigned char), 1, outputFile);
	}
	//if the number is odd
	if (numBytes % 2 == 1) {
		int writeBuffer = fwrite(&buffer, sizeof(unsigned char), 1, outputFile);
	}
}

void writeShortChunk(FILE* outputFile, unsigned short* p, int numShorts) {

	int shortInfoWrite = fwrite(&numShorts, sizeof(unsigned long), 1, outputFile);

	for (int i = 0; i < numShorts; i++) {
		int shortWrite = fwrite(&p[i], sizeof(unsigned short), 1, outputFile);

	}
}

void writeLongChunk(FILE* outputFile, unsigned long* p, int numLongs) {

	int longInfoWrite = fwrite(&numLongs, sizeof(unsigned long), 1, outputFile);

	for (int i = 0; i < numLongs; i++) {
		int longWrite = fwrite(&p[i], sizeof(unsigned long), 1, outputFile);
	}
}

double computeByteAverage(const unsigned char bytes[], int numBytes) {
	if (numBytes <= 0) {
		// To avoid division by zero, return 0.0 or handle the error as per your requirements
		return 0.0;
	}

	unsigned int sum = 0;
	for (int i = 0; i < numBytes; i++) {
		sum += bytes[i];
	}

	// Compute and return the average
	return (double)sum / numBytes;
}

double computeShortAverage(unsigned short shorts[], int numShorts) {
	if (numShorts <= 0) {
		// To avoid division by zero, return 0.0 or handle the error as per your requirements
		return 0.0;
	}

	unsigned int sum = 0;

	for (int i = 0; i < numShorts; i++) {
		sum += shorts[i];
	}

	// Compute and return the average
	return (double)sum / numShorts;
}

double computeLongAverage(unsigned long longs[], int numLongs) {
	if (numLongs <= 0) {
		// To avoid division by zero, return 0.0 or handle the error as per your requirements
		return 0.0;
	}

	unsigned int sum = 0;

	for (int i = 0; i < numLongs; i++) {
		sum += longs[i];
	}

	// Compute and return the average
	return (double)sum / numLongs;

}

int getRandom(int min, int max) {

	// Generate a random number between 0 and RAND_MAX
	int randomNum = rand();

	int range = (unsigned int)(max)-(unsigned int)(min)+1;

	// Normalize the random number to the desired range
	int randomNumInRange = ((randomNum % range) + min);

	return randomNumInRange;
}