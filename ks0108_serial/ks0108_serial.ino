#define rs 8
#define rw 19
#define e 18
#define db0 17
#define db1 16
#define db2 15
#define db3 14
#define db4 6
#define db5 7
#define db6 2
#define db7 3
#define cs1 4
#define cs2 5
#define rst 9

const  byte pins [12] = {db0, db1, db2, db3, db4, db5, db6, db7,rw,rs,cs2,cs1};


void pulseE(){
    digitalWrite(e,HIGH);
    //delay(1);
    digitalWrite(e,LOW);
}

//void sendData(bool CS1, bool CS2,bool RS,bool RW,bool DB7,bool DB6,bool DB5, bool DB4,bool DB3,bool DB2,bool DB1, bool DB0){
  void sendData(int data){

  int i =0;
  int mask_bit=1;
   for (; i < 12; ++i, mask_bit<<=1) { 
    digitalWrite(pins [i],  !!(data & mask_bit));
  }

    pulseE();
}

void setupPins(){
    pinMode(rs,OUTPUT);
    pinMode(rw,OUTPUT);
    pinMode(e,OUTPUT);
    pinMode(db0,OUTPUT);
    pinMode(db1,OUTPUT);
    pinMode(db2,OUTPUT);
    pinMode(db3,OUTPUT);
    pinMode(db4,OUTPUT);
    pinMode(db5,OUTPUT);
    pinMode(db6,OUTPUT);
    pinMode(db7,OUTPUT);
    pinMode(cs1,OUTPUT);
    pinMode(cs2,OUTPUT);
    pinMode(rst,OUTPUT);


    digitalWrite(rs,LOW);
    digitalWrite(rw,LOW);
    digitalWrite(e,LOW);
    digitalWrite(db0,LOW);
    digitalWrite(db1,LOW);
    digitalWrite(db2,LOW);
    digitalWrite(db3,LOW);
    digitalWrite(db4,LOW);
    digitalWrite(db5,LOW);
    digitalWrite(db6,LOW);
    digitalWrite(db7,LOW);
    digitalWrite(cs1,LOW);
    digitalWrite(cs2,LOW);
    digitalWrite(rst,HIGH);
}



int data = 0;
void setup() {
    Serial.begin(9600);
    setupPins();
    sendData(0b110001000000);
    sendData(0b110010111000);
    sendData(0b110011000000);
    for(int j=0;j<8;j++){
      sendData(0b110010111000+j);
        for(int i=0;i<64;i++){
            sendData(0b111000000000);
        }       
    }
    sendData(0b110001000000);
    sendData(0b110010111000);
    sendData(0b110011000000);
}
void loop() {
 if(Serial.available()>0)
  {
    data = Serial.parseInt();
    sendData(data);
  }
}
