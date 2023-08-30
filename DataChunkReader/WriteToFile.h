#pragma once

//<summary>
// this fuction will endian swap the given unsigned short value and return it
//<summary>
//<val> = the short value you want endian swapped
unsigned short endianSwapShort(unsigned short val);

//<summary>
// ths fuction will endian swap the given unsigned long value and return it
//<summary>
//<val> = the short value you want endian swapped
unsigned long endianSwapLong(unsigned long val);

//<summary>
// ths fuction will return a random int within the range specefied
//<summary>
//<min> = the min value for the random int
//<max> = the maxa value for the random int
int getRandom(int min, int max);

//<summary>
// ths fuction will generate a random byte and takes no input
//<summary>
unsigned char getRandomByte();

//<summary>
// ths fuction will generate a random short and takes no input
//<summary>
unsigned short getRandomShort();

//<summary>
// ths fuction will generate a random long and takes no input
//<summary>
unsigned long getRandomLong();

//<summary>
// ths fuction will populate an array with random bytes
//<summary>
//<bytesP> = pointer to the beginingg of the malloced array
//<n>	   = the number of bytes that are in the array 
void generateRandomBytes(unsigned char* bytesP, int n);

//<summary>
// ths fuction will populate an array with random shorts
//<summary>
//<shortsP> = pointer to the beginingg of the malloced array
//<n>	    = the number of bytes that are in the array 
void generateRandomShorts(unsigned short* shortsP, int n);

//<summary>
// ths fuction will populate an array with random longs
//<summary>
//<longsP> = pointer to the beginingg of the malloced array
//<n>	   = the number of longs that are in the array 
void generateRandomLongs(unsigned long* longsP, int n);

//<summary>
// ths fuction will write a chunk of bytes to the output file specified
//<summary>
//<outputFile> = the file you want to write too
//<p> = a pointer the begining of the array you want to write to the output File 
//<numBytes> = the number of bytes in the array
void writeByteChunk(FILE* outputFile, unsigned char* p, int numBytes);

//<summary>
// ths fuction will write a chunk of shorts to the output file specified
//<summary>
//<outputFile> = the .dat or .bin file you want to write too
//<p> = a pointer the begining of the array you want to write to the output File 
//<numShorts> = the number of shorts in the array
void writeShortChunk(FILE* outputFile, unsigned short* p, int numShorts);

//<summary>
// ths fuction will write a chunk of longs to the output file specified
//<summary>
//<outputFile> = the .dat or .bin file you want to write too
//<p> = a pointer the begining of the array you want to write to the output File 
//<numLongs> = the number of longs in the array
void writeLongChunk(FILE* outputFile, unsigned long* p, int numLongs);

//<summary>
// ths fuction will compute the average for the number of bytes.
//<summary>
//<bytes[]> = the array of bytes that you want to coputer the average of before it has been endian swappe
//<numBytes> = the number of bytes in the bytes[] array
double computeByteAverage(unsigned char bytes[], int numBytes);

//<summary>
// ths fuction will compute the average for the number of shorts
//<summary>
//<shorts[]> = the array of shorts that you want to coputer the average of before it has been endian swappe
//<numShorts> = the number of shorts in the shorts[] array
double computeShortAverage(unsigned short shorts[], int numShorts);

//<summary>
// ths fuction will compute the average for the number of shorts
//<summary>
//<longs[]> = the array of longs that you want to coputer the average of before it has been endian swappe
//<numLongs> = the number of longs in the longs[] array
double computeLongAverage(unsigned long longs[], int numLongs);