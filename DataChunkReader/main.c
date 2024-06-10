
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "WriteToFile.h"

typedef struct{
	int NUM_BYTES;
	int NUM_SHORTS;
	int NUM_LONGS;
} fileParametersT;


typedef struct {
	int MIN;
	int MAX;
} rangeT;

int main() {
	
	//seed the random number
	srand(time(NULL));
	
	//file setup
	FILE* inputFile;
	errno_t err = fopen_s(&inputFile, "files/input.txt", "r");
	fileParametersT inputFromFile;

	//struct setup
	rangeT byteRange;
	rangeT shortRange;
	rangeT longRange;
	int numberOfChunks = 0;
	//read parameters from the file	
	fscanf_s(inputFile, 
			"NUM_BYTES_MIN=%d\nNUM_BYTES_MAX=%d\nNUM_SHORTS_MIN=%d\nNUM_SHORTS_MAX=%d\nNUM_LONGS_MIN=%d\nNUM_LONGS_MAX=%d\nNUM_CHUNKS=%d\n", 
			&byteRange.MIN, 
			&byteRange.MAX, 
			&shortRange.MIN, 
			&shortRange.MAX, 
			&longRange.MIN, 
			&longRange.MAX,
			&numberOfChunks);

	fclose(inputFile);

	//clear stats file
	FILE* statsFile;
	errno_t errStatsFile = fopen_s(&statsFile, "files/stats.txt", "wb");
	fclose(statsFile);

	//clear  the output file
	FILE* outputFile;
	errno_t errOutput = fopen_s(&outputFile, "files/output.dat", "wb");
	fclose(outputFile);



	int toNextOffset = 0;

	for (int i = 0; i < numberOfChunks; i++) {
		inputFromFile.NUM_BYTES = getRandom(byteRange.MIN, byteRange.MAX);
		inputFromFile.NUM_SHORTS = getRandom(shortRange.MIN, shortRange.MAX);
		inputFromFile.NUM_LONGS = getRandom(longRange.MIN, longRange.MAX);
		toNextOffset = inputFromFile.NUM_BYTES + (inputFromFile.NUM_SHORTS * 2) + (inputFromFile.NUM_LONGS * 4);

		/*-----------------------
		* generate random chunks
		------------------------*/

		unsigned char* byteValuesP = (unsigned char*)malloc(inputFromFile.NUM_BYTES * sizeof(unsigned char));
		generateRandomBytes(byteValuesP, inputFromFile.NUM_BYTES);

		unsigned short* shortValuesP = (unsigned short*)malloc(inputFromFile.NUM_SHORTS * sizeof(unsigned short));
		generateRandomShorts(shortValuesP, inputFromFile.NUM_SHORTS);

		unsigned long* longValuesP = (unsigned long*)malloc(inputFromFile.NUM_LONGS * sizeof(unsigned long));
		generateRandomLongs(longValuesP, inputFromFile.NUM_LONGS);

		/*-------------------
		* write to stats file
		---------------------*/

		double avgBytes = computeByteAverage(byteValuesP, inputFromFile.NUM_BYTES);
		double avgShorts = computeShortAverage(shortValuesP, inputFromFile.NUM_SHORTS);
		double avgLongs = computeLongAverage(longValuesP, inputFromFile.NUM_LONGS);

		errno_t errStatsFile = fopen_s(&statsFile, "files/stats.txt", "a");
		
		char bytesString[50];
		char shortsString[50];
		char longsString[50];
		char sectionString[50];

		snprintf(sectionString, sizeof(sectionString), "Section %d \n", i);
		snprintf(bytesString, sizeof(bytesString), "%d bytes, average value %.2f\n", inputFromFile.NUM_BYTES, avgBytes);
		snprintf(shortsString, sizeof(shortsString), "%d shorts, average value %.2f\n", inputFromFile.NUM_SHORTS, avgShorts);
		snprintf(longsString, sizeof(longsString), "%d longs, average value %.2f\n", inputFromFile.NUM_LONGS, avgLongs);

		fprintf(statsFile, sectionString);
		fprintf(statsFile, bytesString);
		fprintf(statsFile, shortsString);
		fprintf(statsFile, longsString);

		fclose(statsFile);


		/*-----------------
		* write to the file
		------------------*/
		
		//endian swap short
		for (int i = 0; i < inputFromFile.NUM_SHORTS; i++) {
			unsigned short value = shortValuesP[i];
			unsigned short endianSwapped = endianSwapShort(value);

			shortValuesP[i] = endianSwapped;

		}

		//endian swap long
		for (int i = 0; i < inputFromFile.NUM_LONGS; i++) {
			unsigned long value = longValuesP[i];
			unsigned long endianSwapped = endianSwapLong(value);

			longValuesP[i] = endianSwapped;

		}
		

		errno_t errOutput = fopen_s(&outputFile, "files/output.dat", "ab");

		int toNextOffsetWrite = fwrite(&toNextOffset, sizeof(unsigned long), 1, outputFile);
		writeByteChunk(outputFile, byteValuesP, inputFromFile.NUM_BYTES);
		writeShortChunk(outputFile, shortValuesP, inputFromFile.NUM_SHORTS);
		writeLongChunk(outputFile, longValuesP, inputFromFile.NUM_LONGS);

		

		//frees
		free(byteValuesP);
		free(shortValuesP);
		free(longValuesP);

		fclose(outputFile);

	}
	
	
	
	return 0;
}


