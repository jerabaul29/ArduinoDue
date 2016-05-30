#define pin_read_ADC A0
#define number_readings 100000

int sensor_value = 0;
unsigned long time1;
unsigned long time2;
unsigned long time_elapsed;

// notes about Arduino Due
// theory: ADC: 16 x 12 bits, 1MHz
// real worls because of Arduino wrappers: I get around 232 000 Hz
// NOTE: this is fast enough to do some over sampling and reduce noise

void setup() {

  // open serial port on native USB; baud rate must be the same as in Python
  Serial.begin(115200);

  // change the resolution to 12 bits and read A0 (12 bits ADC on Arduino Due)
  analogReadResolution(12);

  // prepare for reading
  pinMode(pin_read_ADC,INPUT);

}

void loop() {

  // do the test when receive a char on serial
  if (Serial.available()>0){
    Serial.read();

    // test reading on pin_read_ADC
    int readings = 0;
    time1 = micros();

    // do a number of readings
    while(readings < number_readings){
      sensor_value = analogRead(ADC0);
      readings += 1;
    }

    time2 = micros();

    // output stats
    print_time_elapsed(time1,time2,number_readings);
    Serial.print("Last reading: ");
    Serial.println(sensor_value);

  }

}

void print_time_elapsed(unsigned long _time1, unsigned long _time2, int number_of_events){
  // compute and print on screen some informations about frequency corresponding to two microsecond time stamps

  unsigned long _time_elapsed = _time2 - _time1;

  Serial.println();

  Serial.print("Time elapsed (micro s): ");
  Serial.println(_time_elapsed);

  int _frequency = pow(10.,6.) / _time_elapsed * number_of_events;

  Serial.print("Frequency (Hz): ");
  Serial.println(_frequency);

}
