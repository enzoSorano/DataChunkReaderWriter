# DataChunkReaderWriter
The C program creates a binary file which will contain N(0 < N < 50) sections of data, where N is specified by the user (ie. How many sections of data the user wants?). Each section will consist of three chunks of data. The first chunk will be a random (100 < NUM_BYTES < 500) number of bytes, followed by a random (100 < NUM_SHORTS < 500) number of shorts, followed by a random (100 < NUM_LONGS < 500) number of longs. The byte values themselves will be unsigned and random (50 < BYTEVAL<150) . The short values will also be random (1000 < SHORTVAL < 2000). The long values will also be random (3000 < LONGVAL < 5000). **The range of NUM_BYTES, NUM_SHORTS and NUM_LONGS is provided in an input text file that the C program reads.** 

The assembly program will then be run and ask the user for a section number to use in its computations. The assembly program will then read the bianry file and find the averages for the three chunks in the section specified by the user. The values should match the text output given by the C program.

## To Run the program
 1. Open "DataChunkReaderWriter\DataChunkReader\files\input.txt" and specify the size range of the bytes, shorts, and longs blocks
 2. Open the "DataChunkWriter.sln" using Visual Studio 2019
 3. Run the program using visual studio
 4. Open the "DataChunkReaderWriter\DataChunkReader\files\stats.txt" in a window.
 5. Now open the assembly file "DataChunkReader\ChunkReader.X68" and run it. Details about how to run the assembly program are mentioned below.
 6. Now you can compare the number of pieces in each data chunk and its average value with the data present in "stats.txt" which you had previously opened.

## To run the assembly program 
 1. Please download the Easy68k Assembler/Editor/Simulator from "http://www.easy68k.com" (it is an assembler for 68000).
 2. Open "ChunkReader.X68" (it must open in Easy 68k).
 3. Hit play button, which is on the right side of the Menu bar (shortcut key: F9).
 4. Hit Execute button
 5. Hit Play button again, this time it is the second button from left on the Menu bar.
 
