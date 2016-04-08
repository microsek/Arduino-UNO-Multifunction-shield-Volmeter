/* Define shift register pins used for seven segment display */
#define LATCH_DIO 4
#define CLK_DIO 7
#define DATA_DIO 8
 
#define Pot1 0
 
/* Segment byte maps for numbers 0 to 9 */
const byte SEGMENT_MAP[] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0X80,0X90,0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10};
/* Byte maps to select digit 1 to 4 */
const byte SEGMENT_SELECT[] = {0xF1,0xF2,0xF4,0xF8};
 
void setup ()
{
Serial.begin(9600);
/* Set DIO pins to outputs */
pinMode(LATCH_DIO,OUTPUT);
pinMode(CLK_DIO,OUTPUT);
pinMode(DATA_DIO,OUTPUT);
}
 
/* Main program */
void loop()
{
int PotValue;
float volt,temp;
PotValue = analogRead(Pot1); 
volt=PotValue*0.0048828125;
WriteNumber(volt);
  
}
/* Write a decimal number between 0 and 9999 to the display */
void WriteNumber(float Number)
{
  int vol;
  vol=int(Number*100);
  WriteNumberToSegment(0 , 0);
  WriteNumberToSegment(1 , (vol/100)+10);
 WriteNumberToSegment(2 , (vol%100)/10);
  WriteNumberToSegment(3 ,(vol%100)%10);

}
/* Write a decimal number between 0 and 9 to one of the 4 digits of the display */
void WriteNumberToSegment(byte Segment, byte Value)
{
digitalWrite(LATCH_DIO,LOW);
shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_MAP[Value]);
shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_SELECT[Segment] );
digitalWrite(LATCH_DIO,HIGH);
}
