//lab1 - program#2
unsigned long ms_runtime;
int one_ms_timer;
//DEFINE ALL TIMERS AS UNSIGNED VARIABLES
unsigned long timer1 = 0; //timer1 increments every 100ms = 0.1s
const int USER_LED_OUTPUT = 13;
const int USER_BUTTON_INPUT = 2;
void setup()
{ //initialize the digital pin as an output.
  pinMode(USER_LED_OUTPUT, OUTPUT);
  pinMode(USER_BUTTON_INPUT, INPUT);
  Serial.begin(9600);
}
void loop()
{ //run loop forever
  static int state,old_state, counter;
  timers();
  //logic for state change 
  if(state == 0)
  {    if(digitalRead(USER_BUTTON_INPUT) == 1)
  {        if(timer1 > 5)
               state = 1;
  }
   else 
     timer1 = 0;
  }
  else if(state == 1)
  {    if(digitalRead(USER_BUTTON_INPUT) == 0)
  {        if(timer1 > 5)
               state = 0;
  }
        else
          timer1 = 0;
  }
  //execute commands based on state
  if (state == 1)
      digitalWrite(USER_LED_OUTPUT, HIGH);
  else if (state == 0)
       digitalWrite(USER_LED_OUTPUT, LOW);
  //monitor and print changed of state
  if(old_state != state)
  {   counter++;
      Serial.print("counter = ");
      Serial.println(counter);
      old_state = state;
  }
}
void timers(void)
{
  int i;
  if(millis() > (ms_runtime +1))
  {   ms_runtime = ms_runtime + 1;
      one_ms_timer++;
  }
  else if( ms_runtime > millis())
       ms_runtime = millis();
  if(one_ms_timer > 99)
  {   timer1++;
      one_ms_timer = 0;
  }
}
    
