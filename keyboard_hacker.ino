/* Arduino USB HID Keyboard Demo
 * Random Key/Random Delay
 */
 
/* Include this to allow us to store the large strings in the flash memory and save RAM for the program to run */
 #include <avr/pgmspace.h>  
 
 #define KEY_LEFT_SHIFT 0x02
 #define MAX_MESSAGE_LENGTH 50
 
uint8_t buf[8] = { 0 }; 	/* Keyboard report buffer */

// PROGMEM stores the strings into FLASH memory to save space on the RAM to run the program
//prog_char string1[] PROGMEM = {"  LOOK OUT BEHIND YOU!!!  "};
//prog_char string2[] PROGMEM = {" poop "};
//prog_char string3[] PROGMEM = {"the the the "};
//prog_char string4[] PROGMEM = {" *insert toilet joke here* "};
//prog_char string5[] PROGMEM = {"aaaaAAAAaaaa"};
//prog_char string6[] PROGMEM = {"qwertyuiop"};
//prog_char string7[] PROGMEM = {" \n,___,\n[O.o]\n/)__)\n-\"--\"-\nWhat a hoot.\n "};
//prog_char string8[] PROGMEM = {" :D "};
//prog_char string9[] PROGMEM = {" :P Happy April Fools ;P "};
const char string1[] PROGMEM = {"  LOOK OUT BEHIND YOU!!!  "};
const char string2[] PROGMEM = {" poop "};
const char string3[] PROGMEM = {"the the the "};
const char string4[] PROGMEM = {" *insert toilet joke here* "};
const char string5[] PROGMEM = {"aaaaAAAAaaaa"};
const char string6[] PROGMEM = {"qwertyuiop"};
const char string7[] PROGMEM = {" \n,___,\n[O.o]\n/)__)\n-\"--\"-\nWhat a hoot.\n "};
const char string8[] PROGMEM = {" :D "};
const char string9[] PROGMEM = {" :P Happy April Fools ;P "};
char stringBuffer[MAX_MESSAGE_LENGTH];  //make sure this buffer is as big or bigger than the longest string above 

//PROGMEM const char *stringTable[] =   //commented 30/3/2016 to try get working again
const char* const stringTable[] PROGMEM =
{
 string1, string2, string3, string4, string5, string6, string7,
 string8, string9 };
 
void setup() 
{
  Serial.begin(9600);
  randomSeed(analogRead(0));
  delay(200);
}
 
void loop() 
{
  int randomString = random(1, 9); //choose a random message between 1 and 9
  long randomDelay = random(60000, 600000); //1 minute to 10 minutes
 
  delay(randomDelay);
  
  // because strings are stored in FLASH memory, need to use special command to retieve it
  // see more at http://www.arduino.cc/en/Reference/PROGMEM
  strcpy_P(stringBuffer, (char*)pgm_read_word(&(stringTable[randomString])));
  
  // NB: note that sendKeyStrokes is looking for a pointer (&) to the string
  //http://arduino.cc/en/Reference/Pointer
  sendKeyStrokes(stringBuffer);
  
}
 
void releaseKey() 
{
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8);	// Release key  
}

/*****************************************
*  Function sends input message keystroke by keystroke at a rate of 20 keys per second
*****************************************/
void sendKeyStrokes(char *inputMessage)
{
  char *chp = inputMessage;

  while(*chp){
    ASCIIToHID(*chp);
    Serial.write(buf,8);
    delay(25);
    releaseKey();
    delay(25);
    
    chp++;
  }
}

/*****************************************
*  Function converts single char letter into HID code
*****************************************/
void ASCIIToHID(char ASCIIIn){
  // This section is based on http://hunt.net.nz/users/darran/weblog/b3029/Arduino_UNO_Keyboard_HID_version_03.html
  // and code values from http://www.freebsddiary.org/APC/usb_hid_usages.php
  
  if ((ASCIIIn >= 'a') && (ASCIIIn <= 'z')){
    //lowercase letter
    buf[0] = 0;
    buf[2] = ASCIIIn - 'a' +4;
  }else if ((ASCIIIn >= 'A') && (ASCIIIn <= 'Z')){
    //Uppercase letter (need shift key)
    buf[0] = KEY_LEFT_SHIFT;
    buf[2] = ASCIIIn - 'A' + 4;
  }else if ((ASCIIIn >= '0') && (ASCIIIn <= '9')){
    //number
    buf[0] = 0;
    buf[2] = ASCIIIn - '0' + 30;
  }else {
    switch (ASCIIIn) {
      case char(10):
        buf[0] = 0;
        buf[2] = 0x28;  break;// ENTER
      case char(9):
        buf[0] = 0;
        buf[2] = 0x2B;  break;// Tab
      case ' ':
        buf[0] = 0;
        buf[2] = 0x2C;  break;// Space
      case '!':
        buf[0] = KEY_LEFT_SHIFT;
        buf[2] = 0x1E;  break;// !
      case '@':
        buf[0] = KEY_LEFT_SHIFT;
        buf[2] = 0x1F;  break;// @
      case '#':
        buf[0] = KEY_LEFT_SHIFT;
        buf[2] = 0x20; break;
      case '$':
        buf[0] = KEY_LEFT_SHIFT;
        buf[2] = 0x21; break;
      case '%':
        buf[0] = KEY_LEFT_SHIFT;
        buf[2] = 0x22;  break;
      case '^':
        buf[0] = KEY_LEFT_SHIFT;
        buf[2] = 0x23;  break;
      case '&':
        buf[0] = KEY_LEFT_SHIFT;
        buf[2] = 0x24;  break;
      case '*':
        buf[0] = KEY_LEFT_SHIFT;
        buf[2] = 0x25;  break;
      case '(':
        buf[0] = KEY_LEFT_SHIFT;
        buf[2] = 0x26;  break;
      case ')':
        buf[0] = KEY_LEFT_SHIFT;
        buf[2] = 0x27; break;
      case '-':
        buf[0] = 0;
        buf[2] = 0x2D; break;
      case '_':
        buf[0] = KEY_LEFT_SHIFT;
        buf[2] = 0x2D; break;
      case '=':
        buf[0] = 0;
        buf[2] = 0x2E; break;
      case '+':
        buf[0] = KEY_LEFT_SHIFT;
        buf[2] = 0x2E; break;
      case '[':
        buf[0] = 0;
        buf[2] = 0x2F; break;
      case '{':
        buf[0] = KEY_LEFT_SHIFT;
        buf[2] = 0x2F; break;
      case ']':
        buf[0] = 0;
        buf[2] = 0x30; break;
      case '}':
        buf[0] = KEY_LEFT_SHIFT;
        buf[2] = 0x30; break;
      case char(92):  //NB: 92 is the ASCII decimal code for \
        buf[0] = 0;
        buf[2] = 0x31; break;
      case '|':
        buf[0] = KEY_LEFT_SHIFT;
        buf[2] = 0x31; break;
      case ';':
        buf[0] = 0;
        buf[2] = 0x33; break;
      case ':':
        buf[0] = KEY_LEFT_SHIFT;
        buf[2] = 0x33; break;
      case char(39):  //NB: 39 is the ASCII decimal code for '
        buf[0] = 0;
        buf[2] = 0x34; break;
      case '"':
        buf[0] = KEY_LEFT_SHIFT;
        buf[2] = 0x34; break;
      case '~':
        buf[0] = KEY_LEFT_SHIFT;
        buf[2] = 0x35; break;
      case '`':
        buf[0] = 0;
        buf[2] = 0x35; break;
      case ',':
        buf[0] = 0;
        buf[2] = 0x36; break;
      case '<':
        buf[0] = KEY_LEFT_SHIFT;
        buf[2] = 0x36; break;
      case '.':
        buf[0] = 0;
        buf[2] = 0x37; break;
      case '>':
        buf[0] = KEY_LEFT_SHIFT;
        buf[2] = 0x37; break;
      case '/':
        buf[0] = 0;
        buf[2] = 0x38; break;
      case '?':
        buf[0] = KEY_LEFT_SHIFT;
        buf[2] = 0x38; break;
      default: //could not process ASCII character send back '?'
        buf[0] = KEY_LEFT_SHIFT;
        buf[2] = 0x38; break; //'?'
      }
  }
}
