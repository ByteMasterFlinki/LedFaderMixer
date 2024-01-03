/*
This is the code for a four fader LED controller.
You have to adjust the Pins for your input and output devices.
As an output I used a normal 5V LED Strip with commond Vcc (5V).
For input I used fader how they are used in music mixer equipment.
This code was designt for an Esp32-PICO-D4.

Designed by ByteMasterFlinki and his coworker SironLudwig 
*/

#define DEBUG_OUTPUT true
#define DEBUG_OUTPUT_SERIAL if(DEBUG_OUTPUT)Serial
  // by changing 'true' to 'false' you can disable/enable serial output

#define BrightnesFader 25
#define RedFader       26
#define GreenFader     32
#define BlueFader      33
  // define the input pins for your different faders/potentiometers

#define RedLed   12
#define GreenLed 13
#define BlueLed  15
  // define the output pins for the connected LEDs

int Brightnes  = 0;
int RedValue   = 0; 
int GreenValue = 0;
int BlueValue  = 0; 
  // make variables for the value that get send to the output pins

   
void setup() {

  Serial.begin(9600);
    // start the serial communication

  while (!Serial);
    // wait until Serial ist started
    
  pinMode(RedLed  , OUTPUT);
  pinMode(GreenLed, OUTPUT);
  pinMode(BlueLed , OUTPUT);
    // set the pinmode to output
}


void loop() {

  Brightnes  = map(analogRead(BrightnesFader)  , -25, 4070, 0, 100);
  RedValue   = (map(analogRead(RedFader)       , -25, 4070, 0, 255) * (-1 * Brightnes)) / 100 + 255;
  GreenValue = (map(analogRead(GreenFader)     , -25, 4070, 0, 255) * (-1 * Brightnes)) / 100 + 255 ;
  BlueValue  = (map(analogRead(BlueFader)      , -25, 4070, 0, 255) * (-1 * Brightnes)) / 100 + 255;
    // calculating the output values depends on analog readings from the potentiometers.
    // first the input from the input pins is calculatet to a number between zeroooo and 255.
    // than the brightnes is also calculated in the variable

  analogWrite(RedLed  , RedValue);
  analogWrite(GreenLed, GreenValue);
  analogWrite(BlueLed , BlueValue);
    // write the determined values to the LEDs

  DEBUG_OUTPUT_SERIAL.print(RedValue);
  DEBUG_OUTPUT_SERIAL.print(" ---- ");
  DEBUG_OUTPUT_SERIAL.print(GreenValue);
  DEBUG_OUTPUT_SERIAL.print(" ---- ");
  DEBUG_OUTPUT_SERIAL.print(BlueValue);
  DEBUG_OUTPUT_SERIAL.print(" ---- ");
  DEBUG_OUTPUT_SERIAL.println(Brightnes);
    // serial output for debuging (disable/enablen with #define DEBUG_OUTPUT 'true' or 'false')
  
 delay(50);
  // let the program wait for 50 milliseconds

}
