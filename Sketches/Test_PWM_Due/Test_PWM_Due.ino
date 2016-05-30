#define PIN_PWM 6
#define PWM_RESOLUTION_VALUE 8
long int_parsed;

//NOTE: PWM library on Arduino Due is quite broken
// need to do modifications in variants.h to tune resolution and frequency
// see in particular the part of code:
//#define PWM_INTERFACE		PWM
//#define PWM_INTERFACE_ID	ID_PWM
//#define PWM_FREQUENCY		1000
//#define PWM_MAX_DUTY_CYCLE	255
//#define PWM_MIN_DUTY_CYCLE	0
//#define PWM_RESOLUTION		8

// to change frequency of PWM, just change #define PWM_FREQUENCY in variant.h

// to change the resolution of PWM, change both PWM_MAX_DUTY_CYCLE and PWM_RESOLUTION in variant.h
// plus use the analogWriteResolution function in the .ino program

// be careful of the mix frequency / resolution. Frequency is the frequency of a whole PWM cycle
// ie frequency 20kZ at resolution 12 bits is each pulse duration corresponding to a frequency of 81.920MHz (max)

// note: different pins on different timers?
// note: pwm ẗilde are missleading: other pins can do PWM on Due!!
// see doc:
// The Arduino Due supports analogWrite() on pins 2 through 13, plus pins DAC0 and DAC1. Unlike the PWM pins, DAC0 and DAC1 are Digital to Analog converters, and act as true analog outputs.

// 20kHz, 12 bits modifying only PWM define quantities and calling analogWriteResolution works fine on:
// pins 6, 7, 8, 9,
// do not work on pins 3, 5, 10, 11 [get only 8 bits at 1kHz]

// modifying in addition TC makes pins 5, 10, 11, work at 20kHz, at 8 bits. Did not get 12 bits on those pins

// letting PWM_RESOLUTION_VALUE in arduino .ino at 8 bits while having high resolution on variant.h lets
// the PWM work fine, but at lower resolution: exactly what is Expected

// conclusion: change variant.h and then everything works fine!! [post on Arduino formum]

void setup() {

  Serial.begin(9600);
  pinMode(PIN_PWM,OUTPUT);

}

void loop() {

  // parse the int
  if (Serial.available()>0){
      if (Serial.read()=='N'){
          int_parsed = Serial.parseInt();
          // for debuggin, print the parsed int
          //print_parsedInt(int_parsed);

          perform_pwm(int(int_parsed));
      }
  }
}

void print_parsedInt(long _int_parsed){

  Serial.println();

  Serial.print("Parsed int: ");
  Serial.println(int_parsed);

}

void perform_pwm(int _duty_cycle){

  analogWriteResolution(PWM_RESOLUTION_VALUE);
  analogWrite(PIN_PWM,_duty_cycle);

  Serial.println();

  Serial.print("PWM duty: ");
  Serial.println(_duty_cycle);

  delay(1000);

}
