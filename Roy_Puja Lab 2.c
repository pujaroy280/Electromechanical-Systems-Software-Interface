/* LAB 2 BY Puja Roy  */
//GLOBAL VARIABLES

#include <EEPROM.h>
unsigned long ms_runtime;
int one_ms_timer;

//DEFINE ALL TIMERS AS UNSIGNED LONG
// These timers are incremented every 100ms = 0.1s
unsigned long timer1;    //timer1 is used for blinking USER_LED_Pin
unsigned long button_dbnc_tmr = 0; //button_dbnc_tmr for debouncing input
const int User_Button = 2;
const int USER_LED_Pin = 13;
bool allow_change = 0;
int counter = 0;
int state; //possible values 0 -> 1 -> 2 -> 3 -> 0
void read_state_from_memory (void);
void write_state_from_memory (void);
void turnoff(void);
void flash_1s(void);
void flash_2s(void);
void flash_3s(void);

void setup()
{
  read_state_from_memory();  //Reads the location in the memory register
  pinMode(USER_LED_Pin, OUTPUT);
  Serial.begin(9600);   //initialize uart
}
void loop()
{
  timers();
  if(digitalRead(User_Button) == 1)  //Reads the button input digitally
  {
    if(allow_change == 1)
    {
      counter++;
      if(button_dbnc_tmr > 10)
      {
        state++;
        Serial.println(counter);
        Serial.println(state);
        allow_change = 0;
        if(state > 3)
          state = 0;
        write_state_to_memory();
      }
    }
  }
  else
  {   counter = 0;
      allow_change = 1;
      button_dbnc_tmr = 0;
  }
  switch(state)  //Reads the cases in the function body(case 0,1,2,3 etc)
  {
    case 0:
    turnoff();
    break;
    case 1:
    flash_1s();
    break;
    case 2:
    flash_2s();
    break;
    case 3:
    flash_3s();
    break;
  }
}
void turnoff()
{//TURN OFF OUTPUT
  //TO BE COMPLETED BY STUDENT
  digitalWrite(LED1, LOW); //Turns off the LED in pin 13
}
void flash_1s()
{//flash output every one second
  //TO BE COMPLETED BY STUDENT
  if(timer1<10)
    digitalWrite(LED1, HIGH); //Turns the LED on
  else
  {
    digitalWrite(LED1, LOW); //Turns the LED off
    if(timer1>10)
      timer1 = 0;
  }
}
void flash_2s()
{//flash output every two seconds
  //TO BE COMPLETED BY STUDENT
  if(timer>=10 && timer1<20)
    digitalWrite(LED1, HIGH); //Turn the LED on
  else
  {
    digitalWrite(LED1, LOW);  //Turn the LED off
    if(timer1>20)
      timer1 = 0;
  }
}
void flash_3s()
{//flash output every three seconds
  //TO BE COMPLETED BY STUDENT
  if(timer1>=20 && timer1<30)
    digitalWrite(LED1, HIGH);  //Turn the LED on
  else
  {
    digitalWrite(LED1, LOW);  //Turn the LED off
    if(timer1>30)
      timer1 = 0;
  }
}
void timers(void)
{
  static unsigned long ms_runtime;
  static int one_ms_timer;
  
  if(millis() > (ms_runtime + 1))
  {   ms_runtime = ms_runtime + 1;
      one_ms_timer++;
  }
  else if( ms_runtime > millis())x
      ms_runtime = millis();
    
  if(one_ms_timer > 99) // every 100 ms
  { one_ms_timer = 0;
    button_dbnc_tmr++;
    timer1++;
  }
}
void read_state_from_memory ()
{
  //TO BE COMPLETED BY STUDENT
  val = EEPROM.read(mem);  //Read value stored in the memory and wakes up to the old state
  Serial.println(mem);
  Serial.print("\n");
  Serial.print(val);
  Serial.println();
  
  mem = mem + 1;
  
  if (mem == 255)
  {
    mem = 0;
  }
}
void write_state_to_memory()
{
  //TO BE COMPLETED BY STUDENT
  EEPROM.update(mem,val);
  
  //This part of the code is to obtain the new values based on counts of the LED flashing 
  //Saves value in memory
}

// Logic of the Program:
// This program is based on the concept of global variables. 
// Once you have your Arduino circuit constructed with the assigned components, the program starts.
// Then, the timers for each blinking pin functions once the location in the memory register is read.
// Once the program starts, the timers read the button inputs which turns on the switch to read the cases (1, 2 and 3).
// When the program is turned off, the LED flashes within 3 seconds.
// Then, the values of the program are stored in the memory based on how many times the LED flashes which saves the value in the memory of the program. 


// Sentence description of each program functions: 
// 1. setup() - This function reads the modes and output from the memory.
// 2. read_memory() - This function reads the location in the memory register.
// 3. loop() - This function represents a loop which starts a counter to register inputs and print the button pins which are pressed.
// 4. timers() - This function triggers the timer for the operations.
// 5. update_memory()- This function updates the registers in the memory.
// 6. switch(state) - This function reads the cases in the function body(case 0,1,2,3 etc). 
// 7. turnoff() - This function is used to turn off the LED blinking/output.
// 8. flash_1s(), 2s(), 3s() - This fucntion defines the timer for LED blinking which are 1s, 2s nd 3s.
// 9. digitalRead(buttonPIN) - This function reads the button input digitally.
// 10. digitalWrite(LED1, HIGH/LOW) - This function writes the output digitally if the LED is ON = HIGH or the LED is OFF = LOW.
// 11. millis() - This reads the time in milliseconds.
// 12. timers(void) - This means that there is no argument passed to the timers function.
// 13. update_memory() - This function saves the value based on counts of the LED flashing to the memory.
