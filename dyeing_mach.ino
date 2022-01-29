  



int valveMTpin = 3;
int vmt;
int steamValvepin = 4;
int sv;
int containerValvepin = 5;
int cv;
int containerDosageValvepin = 6;
int cdv;
int drainValvepin = 7;
int dv;
float calibration_value_ph = 21.34;// this should be updated once the calibration done
int buffer_arr[10], temp;
int mainPumppin = 8;
int mp;
int winchpin = 9;
int w;
int containerMixerpin = 10;
int cm;
int alarmpin = 14;
int alarm;
int PHMeter;
int x;
int n=0;
int nextiontemp;
int nextionph;
int nextiontank;
int nextionctank;
int nextiontankinput;

int containerLevelMeter;
int tankLevelMeter;
int tank_out;
int ctank_out;


int avgval;
int tempvph;
float V;
float tempt;
float Rx;
float ph_act;

// Variables to convert voltage to resistance
float C = 79.489;
float slope = 9.24;

// Variables to convert resistance to temp
float R0 = 100.0;
float alpha = 0.00385;

int tankh;
int ctankv;
int ctankh;
int okbutton;
int int_nextion;
String string_nextion;

int int_expect() {
  if (Serial.available()) {
    int_nextion = Serial.read();
  }
}
String string_expect() {
  { if (Serial.available())
      string_nextion = Serial.read();
  }
}



int tank() {

  tankLevelMeter = analogRead(A0);
  int tankh_in = tankLevelMeter;
  int tank_out;
  tank_out = tankh_in * (5000 / 1023);
  return tank_out;


}

int ctank() {
  containerLevelMeter = analogRead(A1);
  int ctankh_in = containerLevelMeter;
  int ctank_out;
  ctank_out = ctankh_in * (500 / 1023);
  return ctank_out;
}

int nextiontankdisplay() {
  nextiontank = tank_out;
  Serial.print("n5.val=");
  Serial.print(nextionctank);
  Serial.print(0xff);
  Serial.print(0xff);
  Serial.print(0xff);

}

int nextionCtankdisplay() {
  nextionctank = ctank_out;
  Serial.print("n6.val=");
  Serial.print(nextiontank);
  Serial.print(0xff);
  Serial.print(0xff);
  Serial.print(0xff);

}
int nextiontempdisplay() {
  Serial.print("na3.val=");
  Serial.print(tempt);
  Serial.print(0xff);
  Serial.print(0xff);
  Serial.print(0xff);
  nextiontank = tempt * (255 / 120);
  Serial.print("va0.val=");
  Serial.print(nextiontemp);
  Serial.print(0xff);
  Serial.print(0xff);
  Serial.print(0xff);

}
int nextionphdisplay() {
  Serial.print("na4.val=");
  Serial.print(ph_act);
  Serial.print(0xff);
  Serial.print(0xff);
  Serial.print(0xff);
  nextiontank = ph_act * (255 / 14);
  Serial.print("va1.val=");
  Serial.print(nextionph);
  Serial.print(0xff);
  Serial.print(0xff);
  Serial.print(0xff);

}

int PT100() {
  // Bits to Voltage
  int PT100pin = analogRead(A2);
  V = (PT100pin / 1023.0) * 5.0; // (bits/2^n-1)*Vmax
  // Voltage to resistance
  Rx = V * slope + C; //y=mx+c
  // Resistance to Temperature
  tempt = (Rx / R0 - 1.0) / alpha; // from Rx = R0(1+alpha*X)
  return tempt;
}

int ph() {
  for (int i = 0; i < 10; i++)
  {

    PHMeter = analogRead(A3);
    buffer_arr[i] = PHMeter;
    delay(30);
  }
  for (int i = 0; i < 9; i++)
  {
    for (int j = i + 1; j < 10; j++)
    {
      if (buffer_arr[i] > buffer_arr[j])
      {
        tempvph = buffer_arr[i];
        buffer_arr[i] = buffer_arr[j];
        buffer_arr[j] = tempvph;
      }
    }
    for (int i = 2; i < 8; i++)
    { avgval += buffer_arr[i];
      float volt = (float)avgval * 5.0 / 1024 / 6;
      float ph_act = -5.70 * volt + calibration_value_ph;

    }
  }
  return ph_act;
}
int alarmer() {
  pinMode(alarmpin, OUTPUT);
  if (alarm == 1) {
    digitalWrite(alarmpin, HIGH);
  }
  else if (alarm == 0) {
    digitalWrite(alarmpin, LOW);
  }
}
int valveMT() {
  pinMode(valveMTpin, OUTPUT);
  if (vmt == 1) {

    digitalWrite(valveMTpin, HIGH);
  }
  else if (vmt == 0) {
    digitalWrite(valveMTpin, LOW);
  }
}
int steamValve() {
  pinMode(steamValvepin, OUTPUT);
  if (sv == 1) {
    digitalWrite(steamValvepin, HIGH);
  }
  else if (sv == 0) {
    digitalWrite(steamValvepin, LOW);
  }
}
int containerValve() {
  pinMode(containerValvepin, OUTPUT);
  if (cv == 1) {
    digitalWrite(containerValvepin, HIGH);
  }
  else if (cv == 0) {
    digitalWrite(containerValvepin, LOW);
  }
}
int containerDosageValve() {
  pinMode(containerDosageValvepin, OUTPUT);
  if (cdv == 1) {
    digitalWrite(containerDosageValvepin, HIGH);
  }
  else if (cdv == 0) {
    digitalWrite(containerDosageValvepin, LOW);
  }
}
int drainValve() {
  pinMode(drainValvepin, OUTPUT);
  if (dv == 1) {
    digitalWrite(drainValvepin, HIGH);
  }
  else if (dv == 0) {
    digitalWrite(drainValvepin, LOW);

  }
}
int mainPump() {
  pinMode(mainPumppin, OUTPUT);
  if (mp == 1) {
    digitalWrite(mainPumppin, HIGH);
  }
  else if (mp == 0) {
    digitalWrite(mainPumppin, LOW);
  }
}

int winch() {
  pinMode(winchpin, OUTPUT);
  if (w == 0) {
    digitalWrite(winchpin, LOW);
  }
  else if (w == 1) {
    digitalWrite(winchpin, HIGH);


  }
}
int containerMixer() {
  pinMode(containerMixerpin, OUTPUT);
  if (cm == 1) {
    digitalWrite(containerMixerpin, HIGH);
  }
  else if (cm == 0) {
    digitalWrite(containerMixerpin, LOW);
  }
}



void setup() {
  Serial.begin(9600);

   TIMSK2 = (TIMSK2 & B11111110) | 0x01;
   TCCR2B = (TCCR2B & B11111000) | 0x07;
}

void loop() {
  
  int_expect();
  do{
    delay(500);
  }while(int_nextion==148);

  //step one

  int vmt = 1;
  valveMT();
  while (tank() < 2800)
  {

    delay(100);
  }
  nextiontankdisplay();
  vmt = 0;
  valveMT();
  Serial.println("Step 1 is completed");
  //STEP TWO

  int mp = 1;
  mainPump();
  int w = 1;
  winch();
  int sv = 1;
  steamValve();
  if (Serial.available() > 0) {

    x = Serial.read();
  }
  cv = 1;
  containerValve();


  while (PT100() < 30 && ctank() < x) {
    delay(100);
  }
  cv = 0;
  containerValve();
  nextionCtankdisplay();
  nextiontempdisplay();


  alarm = 1;
  alarmer();
  do {
    delay(100);
    string_expect();
    if (string_nextion == "ok") {
      alarm = 0;
      alarmer();
    }
  } while (string_nextion != "ok");

  //step three

  int cdv = 1;
  containerDosageValve();

  for (int i = 0; i < 15; i++) {
    delay(60000);
  }
  cdv = 0;
  containerDosageValve();

  //step four

  for (int i = 0; i < 15; i++) {
    delay(60000);
  }


  //step five

  if (Serial.available() > 0) {

    x = Serial.read();
  }

  cv = 1;
  containerValve();
  while (PT100() < 30 && ctank() < x) {
    delay(100);
  }

  cv = 0;
  containerValve();
  nextionCtankdisplay();
  nextiontempdisplay();

  alarm = 1;
  alarmer();
  delay(5000);
  alarm = 0;
  alarmer();

  //step six

  cdv = 1;
  containerDosageValve();
  while (PT100() < 60) {
    delay(100);
  }
  for (int i = 0; i < 5; i++) {
    delay(60000);
  }
  cdv = 0;
  containerDosageValve();
  nextiontempdisplay();

  //step seven
  cv = 1;
  containerValve();
  if (Serial.available() > 0) {

    x = Serial.read();
  }
  while (ctank() < x) {
    delay(100);
  }
  cv = 0;
  containerValve();
  nextionCtankdisplay();

  //step eight

  cdv = 1;
  containerDosageValve();
  for (int i = 0; i < 30; i++)
  {
    delay(60000);
  }
  cdv = 0;
  containerDosageValve();


  //step nine

  for (int i = 0; i < 45; i++)
  {
    delay(60000);
  }

  //step ten

  alarm = 1;
  alarmer();
  do {
    delay(500);
    string_expect();
    if (string_nextion == "ok") {
      alarm = 0;
      alarmer();
    }
  } while (string_nextion != "ok");
  mp = 0;
  mainPump();
  w = 0;
  winch();
  sv = 0;
  steamValve();


  // step eleven

  dv = 1;
  drainValve();
  for (int i = 0; i < 3; i++) {
    delay(60000);
  }
  dv = 0;
  drainValve();


  //step twelve

  vmt = 1;
  valveMT();
  while (tank() < 3000) {
    delay(100);
  }
  vmt = 0;
  valveMT();
  nextiontankdisplay();

  //step thirteen

  mp = 1;
  mainPump();
  w = 1;
  winch();
  for (int i = 0; i < 10; i++) {
    delay(60000);
  }
  w = 0;
  winch();
  mp = 0;
  mainPump();


  //step fourteen

  dv = 1;
  drainValve();
  for (int i = 0; i < 3; i++) {
    delay(60000);
  }
  dv = 0;
  drainValve();

  //step fiveteen

  vmt = 1;
  valveMT();
  while (tank() < 3000) {
    delay(100);
  }
  vmt = 0;
  valveMT();
  nextiontankdisplay();


  //STEP SIXTEEN

  mp = 1;
  mainPump();
  w = 1;
  winch();
  if (Serial.available() > 0) {

    x = Serial.read();
  }
  cv = 1;
  containerValve();
  while (ctank() < x)
  {
    delay(100);
  }
  cv = 0;
  containerValve();
  nextionCtankdisplay();
  alarm = 1;
  alarmer();
  do {
    delay(100);
    string_expect();
    if (string_nextion == "ok") {
      alarm = 0;
      alarmer();
    }
  } while (string_nextion != "ok");
  //STEP SEVENTEEN

  delay(60000);
  //STEP EIGHTEEN

  ph();
  do {
    delay(100);
    string_expect();
    if (string_nextion == "ok") {
      alarm = 0;
      alarmer();
    }
  } while (string_nextion != "ok");
  nextionphdisplay();
  mp = 0;
  mainPump();
  w = 0;
  winch();
  //STEP NINETEEN

  dv = 1;
  drainValve();
  for (int i = 0; i < 3; i++)
  {
    delay(60000);
  }
  dv == 0;
  drainValve();
  //STEP TWENTY
  vmt = 1;
  valveMT();
  while (tank() < 3000)
  {
    delay(100);
  }
  vmt = 0;
  valveMT();
  //step twentyone

  mp = 1;
  mainPump();
  w = 1;
  winch();
  if (Serial.available() > 0) {

    x = Serial.read();
  }
  cv = 1;
  containerValve();
  while (ctank() < x)
  {
    delay(100);
  }
  cv = 0;
  containerValve();
  nextionCtankdisplay();
  alarm = 1;
  alarmer();
  for (int i = 0; i < 5; i++)
  {
    delay(100);
  }
  alarm = 0;
  alarmer();

  //STEP TWENTYTWO

  sv = 1;
  steamValve();
  while (PT100() < 90)
  {
    delay(300);
  }
  sv = 0;
  steamValve();
  nextiontempdisplay();

  for (int i = 0; i < 15; i++)
  {
    delay(60000);
  }
  mp = 0;
  mainPump();
  w = 0;
  winch();

  //step twentythree

  dv = 1;
  drainValve();
  for (int i = 0; i < 3; i++)
  {
    delay(60000);
  }
  dv = 0;
  drainValve();
  Serial.println("Step 23 is completed");
  //step twentyfour
  vmt = 1;
  valveMT();
  while (tank() < 3000)
  {
    delay(200);
  }
  vmt = 0;
  valveMT();
  nextiontankdisplay();
  //STEP TWENTYIVE

  mp = 1;
  w = 1;
  sv = 1;
  mainPump();
  winch();
  steamValve();

  while (PT100() < 80)
  {
    delay(100);
  }

  mp = 0;
  w = 0;
  sv = 0;
  steamValve();
  nextiontempdisplay();
  for (int i = 0; i < 10; i++)
  { delay(60000);
  }
  mainPump();
  winch();

  //STEP TWENTYSIX

  dv = 1;
  drainValve();
  for (int i = 0; i < 3; i++)
  { delay(60000);
  }
  dv = 0;
  drainValve();

  //STEP TWENTYSEVEN

  vmt = 1;
  valveMT();
  while (tank() < 3000)
  {
    delay(200);
  }
  vmt = 0;
  valveMT();
  nextiontankdisplay();

  //STEP TWENTYEIGHT

  mp = 1;
  w = 1;
  mainPump();
  winch();
  for (int i = 0; i < 5; i++)
  {
    delay(60000);
  }

  //step twentynine

  alarm = 1;
  alarmer();
  for (int i = 0; i < 5; i++)
  {

    delay(60000);// alarm 5 dk mi calacak
  }
  mp = 0;
  w = 0;
  mainPump();
  winch();

  do {
    delay(200);
    string_expect();

  } while (string_nextion != "ok");

  // STEP thirty

  dv = 1;
  drainValve();
  for (int i = 0; i < 3; i++)
  {
    delay(60000);
  }
  dv = 0;
  drainValve();

}
ISR(TIMER2_OVF_vect){
   n++;
   if(n=60){
    ph();
    PT100();
    nextionphdisplay();
    nextiontempdisplay();
    n=0;
    }
}
