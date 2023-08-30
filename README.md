# DataChunkReaderWriter
 A program to write multiple chunks of data to a binary file in c++ and then read the chunks of data in 6800k Assembly
This project involves a C program that generates a binary file containing multiple sections of data. The number of sections, N(0<N<50), is determined by user input. Each section is composed of three parts: a random number of bytes, shorts, and longs. The ranges for the number of bytes, shorts, and longs are specified in an input text file. The values for bytes, shorts, and longs are generated randomly within specified ranges.

To specify a range for the number of Byte, short, and long chunks open the file located at: "DataChunkReader\files\input.txt

The Assembly program then calculates statistics for each section, including the number of data pieces in each chunk and their average values. The results are written to an output statistics file. The expected output displays the section number, the counts, and the average values for bytes, shorts, and longs.

#Running The Program
