*-----------------------------------------------------------
* Title      : Binary chunk reader
* Written by :  Enzo Sorano
* Date       : 7/25/2023
* Description: this program takes in a custom made binary file made by the included c file called chunkWriter. when you run this program you will be prompted to enter what chunk 
* you want to look at, you can then check if it is correct by looking at the stats file that is created by the c program.
*-----------------------------------------------------------

*--------------------------------Structure------------------------------
* |(offset to next offset) -(info stored in chunk)|number of bytes|bytes.
* ..........|number of shorts| shorts....................................
* ......................................................................
* ................................|number of longs| longs................
* ...............|(offset to next offset) - (info stored in chunk length)
*-----------------------------------------------------------------------

*----------TRAP_CODES------
TRAP_STRING_WOCRLF                  EQU     14
TRAP_STRING_WCRLF                   EQU     13
TRAP_DISPLAY_STRING_NUMBER          EQU     17   
TRAP_DISPLAY_NUMBER                 EQU     15
TRAP_READ_NUMBER                    EQU     4
TRAP_DISPLAY_ASCII                  EQU     6
TRAP_DISPLAY_FRACTION               EQU     3
*----------CONSTANTS---------
LINE_FEED                           EQU     10
CARRIAGE_RETURN                     EQU     13
BASETEN                             EQU     10 
DECIMAL_PERCISION                   EQU     100
CHUNK_INFO_LENGTH                   EQU     12
*----LOCAL VARAIBLES--------
AVG_OF_ELEMENTS                     EQU     8
NUMBER_OF_ELEMENTS                  EQU     4
SIZE_OF_PARAMS_PRINT_DECIMAL        EQU     8
*--------REGISTERS----------
REGISTERS_ALL                       REG     D0-D7


                    org   $2000
*-------------------------------------------------*
*------------------MAIN PROGRAM-------------------*
*-------------------------------------------------*
START:                  

    *prompt the user
    move.l #TRAP_STRING_WCRLF, d0
    lea promptString, a1
    trap #15
   
    *get the inputed Number
    move.l #TRAP_READ_NUMBER, d0
    trap #15
    
    *get the chunk info
    clr.l d0
    lea chunkFile, a1
    jsr getChunkInfo  
    
    *print the info to the screen      
    jsr displayChunkInfo
    
    SIMHALT
                
*-------------------------------------------------*
*------------------FUNCTIONS----------------------*
*-------------------------------------------------*

*<summary>
*this function will get the information from the desired chunk and
*store it in the correct variables
*<summary>
*<variable 1 = start of chunk file>
getChunkInfo

    move.l (a1)+, d7                ;put the offset to the next offset into d7
    
    *endian swap the offset
    movem.l d1, -(sp)               ;save off d1(chunk we want to get too)
    move.l d7, d1           
    jsr endianSwapLong              ;endian swap it
    move.l d1, d7
    movem.l (sp)+, d1               ;restore d1 and the stack pointer
   
    addi.l #CHUNK_INFO_LENGTH, d7   ;add the length of all of the byte, short, and long information to the offset
    
    *check if the number of bytes was odd
    movem.l d1, -(sp)               ;save off d1(chunk we want to get too)       
    move.l (a1), d1                 ;put the number of bytes into d1         
    jsr endianSwapLong              ;endian swap it
    and #1, d1                      ;if the number is odd the last binary digit will be a 1              
    BEQ SKIPADDONE                  ;if it isn't odd dont add one
    add.l #1, d7

SKIPADDONE:     
    movem.l (sp)+, d1               ;if is isn't restore the stack and do nothing to d7
    
    *check if we are at the correct chunk            
    cmp d0, d1               
    BEQ STARTCHUNKREAD        
    add.l d7, a1                    ;if not, then add the offset calculated in d7 to get the next chunks
    addi.l #1, d0                   ;increment the counter 
    bra getChunkInfo                ;continue untill you find the correct chunk
       
STARTCHUNKREAD: 
    jsr FC_CLEAR_REGISTERS
    
    *get the number of bytes
    move.l (a1)+, d1            
    jsr endianSwapLong              ;put the number of bytes into d1
    move.l d1, (numBytes)           ;store off the number of bytes
    
    *check if the number of bytes is even
    move.l d1, d3
    and #1, d3                      ;will be zero if even
    BNE SKIPSUB
    subi.l #1, d1                   ;sub to account for offset change
SKIPSUB: 
    move.b (a1)+, d2                ;get the first byte
    move.l d2, d3                   ;put the byte into the sum(d3)
    
GETBYTESUM:

    *iterate through the bites
    move.b (a1)+, d2                ;put the next byte into d2
    add.l  d2, d3                   ;add the byte to the sum
                                                            
    sub.l #1, d1                    ;decrement the number of bytes
    BNE GETBYTESUM                  ;if we are not done, keep getting the sum
    
GETBYTEAVG:
    
    *get the average
    move.l (numBytes), d2
    divu.w d2, d3                   ;divide the sum by the total number of elements
    move.l d3, (byteAvg)            ;store off the quoitent and remainder
    
    jsr FC_CLEAR_REGISTERS
       
    *get the number of shorts
    move.l (a1)+, d1            
    jsr endianSwapLong              ;put the number of shorts into d1
    
    move.l d1, (numShorts)          ;store off the number of bytes
    sub.l #1, d1                    ;decrement the counter one so we don't go to far
    
    move.w (a1)+, d2                ;get the first word
    move.l d2, d3                   ;put the word into the sum(d3)

   
GETSHORTSUM:
    *iterate through the shorts
    move.w (a1)+, d2                ;put the next short into d2
    add.l  d2, d3                   ;add the short to the sum
                                                            
    sub.l #1, d1                    ;decrement the number of shorts
    BNE GETSHORTSUM                 ;if we are not done, keep getting the sum
        
GETSHORTAVG:
    
    move.l (numShorts), d2
    divu.w d2, d3                   ;divide the sum by the number of shorts
    move.l d3, (shortAvg)           ;store of the quoitent  
 
    jsr FC_CLEAR_REGISTERS 
    
    move.l (a1)+, d1                ;get the number of longs in the chunk
    jsr endianSwapLong
    
    move.l d1, (numLongs)
    sub #1, d1                      ;sub 1 from the number of longs
    
    move.l (a1)+,d2                 ;get the first long
    move.l d2, d3                   ;put the first long into the sum

GETLONGSUM:
    *iterate through the longs
    move.l (a1)+, d2                ;put the next long into d2
    add.l  d2, d3                   ;add the long to the sum
                                                            
    sub.l #1, d1                    ;decrement the number of longs
    BNE GETLONGSUM                  ;if we are not done, keep getting the sum
    
GETLONGAVG:
    move.l (numLongs), d2       
    divu.w d2, d3                   ;divide the sum by the number of shorts
    move.l d3, (longAvg)            ;store of the quoitent 
    
    rts
    
*<summary>
*this function will display the chunk info that the program
*returned from running the getChunkInfo function
*<summary>
*<NO VARAIBLES>
displayChunkInfo:
    *-------------------------------------------    
    *--------print the byte info----------------
    *-------------------------------------------
    movem.l REGISTERS_ALL, -(sp)
    
    *pass praameters through stack
    move.l (ByteAvg), -(sp)
    move.l (numBytes), -(sp)
    lea bytesString, a1
    
    jsr printNumberOfElements
    
    add.l #SIZE_OF_PARAMS_PRINT_DECIMAL, sp
    movem.l (sp)+, REGISTERS_ALL  
 
    *-------------------------------------------
    movem.l REGISTERS_ALL, -(sp)
    
    *pass parameters through stack
    move.l (ByteAvg), -(sp)
    move.l (numBytes), -(sp)                 
    
    jsr printDecimal
    
    add.l #SIZE_OF_PARAMS_PRINT_DECIMAL, sp
    movem.l (sp)+, REGISTERS_ALL
    
    jsr newLine
    
    *-------------------------------------------    
    *--------print the short info---------------
    *-------------------------------------------
    movem.l REGISTERS_ALL, -(sp)
    
    *pass parameters through the stack
    move.l (ShortAvg), -(sp)
    move.l (numShorts), -(sp)
    lea shortsString, a1
    
    jsr printNumberOfElements
    
    add.l #SIZE_OF_PARAMS_PRINT_DECIMAL, sp
    movem.l (sp)+, REGISTERS_ALL   
    
    *-------------------------------------------
    movem.l REGISTERS_ALL, -(sp)
    
    *pass parameters through the stack  
    move.l (shortAvg), -(sp)
    move.l (numShorts), -(sp)                 
    
    jsr printDecimal
    
    add.l #SIZE_OF_PARAMS_PRINT_DECIMAL, sp
    movem.l (sp)+, REGISTERS_ALL   
    
    jsr newLine
    
    *-------------------------------------------    
    *--------print the long info---------------
    *-------------------------------------------    
    movem.l REGISTERS_ALL, -(sp)
     
    *pass parameters through the stack
    move.l (LongAvg), -(sp)
    move.l (numlongs), -(sp)
    lea longsString, a1
    
    jsr printNumberOfElements
    
    add.l #SIZE_OF_PARAMS_PRINT_DECIMAL, sp
    movem.l (sp)+, REGISTERS_ALL
    
    *-------------------------------------------        
    movem.l REGISTERS_ALL, -(sp)
    
    *pass parameters through the stack  
    move.l (longAvg), -(sp)
    move.l (numLongs), -(sp)                 
    
    jsr printDecimal
    
    add.l #SIZE_OF_PARAMS_PRINT_DECIMAL, sp
    movem.l (sp)+, REGISTERS_ALL  
    
    rts
    
*<summary>
*this function will display the decimal part of the avg
*and it is called by the display avg
*<summary>
*<varaible 1 = the average number of elements>
*<varaible 2 = the total number of elements>
printDecimal:
                   
    move.l #TRAP_STRING_WOCRLF, d0
    lea decimalPoint, a1
    trap #15
    
    clr.l d0
    move.l AVG_OF_ELEMENTS(sp), d0           
    clr.w d0
    swap d0
    
    mulu #DECIMAL_PERCISION,d0 
    
    *round the decimal part
    move.l  NUMBER_OF_ELEMENTS(sp), d1
    move.l  d1,d2
    lsr     #1,d2
    add.l   d2,d0
    divu    d1,d0
    ext.l   d0
    
    
    cmp.l #10, d0       
    bge SKIPDISPLAYZERO                 ;check if the number is preceeded by a zero
    
    movem.l d0, -(sp)
    
    move.l #0, d1
    move.l #BASETEN, d2                  
    move.l #TRAP_DISPLAY_NUMBER, d0
    trap #15
    
    movem.l (sp)+, d0
    
SKIPDISPLAYZERO:
    move.l d0, d1
    move.l #TRAP_DISPLAY_FRACTION, d0
    trap #15
    
    
    rts
    
*<summary>
*this function will display the number of elements and
*the average number of elements passed in 
*<summary>
*<varaible 1 = the average number of elements>
*<varaible 2 = the total number of elements> 
*<a1 = string we want read in    
printNumberOfElements:
    move.l #TRAP_DISPLAY_NUMBER, d0
    move.l NUMBER_OF_ELEMENTS(sp), d1
    move.l #BASETEN, d2
    trap    #15
    
    move.l #TRAP_STRING_WOCRLF, d0
    trap #15
    
    clr.l d1                            
    move.l AVG_OF_ELEMENTS(sp), d1    
    swap d1                             
    clr.w d1                
    swap d1                 
    
    move.l #TRAP_DISPLAY_NUMBER, d0
    move.b #BASETEN, d2
    trap #15
    
    rts

    
FC_CLEAR_REGISTERS:
    clr.l d0
    clr.l d1
    clr.l d2
    clr.l d4 
    
    rts
    
endianSwapLong:
    ror.w #$8, d1
    swap d1
    ror.w #$8, d1
    
    rts
    
newLine:
    move.l #TRAP_DISPLAY_ASCII, d0
    move.l #LINE_FEED, d1
    trap #15
    
    move.l #CARRIAGE_RETURN, d1
    trap #15
    
    rts
    

promptString     dc.b     'please enter the chunk you want to see stats for: ',0
bytesString      dc.b     ' bytes, average value ',0
shortsString     dc.b     ' shorts, average value ',0
longsString      dc.b     ' longs, average value ',0
decimalPoint     dc.b     '.',0
line             dc.b     ' ',0
byteAvg          ds.l     1
shortAvg         ds.l     1
longAvg          ds.l     1
numBytes         ds.l     1
numShorts        ds.l     1
numLongs         ds.l     1
chunkInput       ds.b     1
    ORG        $3000         
chunkFile        INCBIN  'files\output.dat' 

    END    START        ; last line of source









*~Font name~Courier New~
*~Font size~12~
*~Tab type~1~
*~Tab size~4~
