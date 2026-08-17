#include <IRremote.h>
int recvpin = 3;
int red = 11,green = 10,blue = 9;   //pins for the RGB led
int dt=250,brightval,on=0;
int brightprop = 100;   //a float value which adjusts the value of the brightval from 0 to 1
char cmd,col;
void colour(char col){
  brightval = 255*brightprop/100;    //according to the value of brightprop(0-1) sets the value of the brightval 
  switch(col){
    case('r'):{
      analogWrite(red,brightval);
      analogWrite(green,0);
      analogWrite(blue,0);
      break;
    }
    case('g'):{
      analogWrite(red,0);
      analogWrite(green,brightval);
      analogWrite(blue,0);
      break;
    }
    case('b'):{
      analogWrite(red,0);
      analogWrite(green,0);
      analogWrite(blue,brightval);
      break;
    }
    case('y'):{
      analogWrite(red,brightval);
      analogWrite(green,brightval);
      analogWrite(blue,0);
      break;
    }
    case('c'):{
      analogWrite(red,0);
      analogWrite(green,brightval);
      analogWrite(blue,brightval);
      break;
    }
    case('m'):{
      analogWrite(red,brightval);
      analogWrite(green,0);
      analogWrite(blue,brightval);
      break;
    }
    case('w'):{
      analogWrite(red,brightval);
      analogWrite(green,brightval);
      analogWrite(blue,brightval);
      break;
    }
    case('O'):{
      analogWrite(red,0);
      analogWrite(green,0);
      analogWrite(blue,0);
      break;
    }
  }
}   //function with all the colours defined
void brightness(){
  if(cmd == 'u'){
    if(brightprop >= 100){
      brightprop = 100;
    }
    else {
      brightprop += 10;
    }
  }
  else if(cmd == 'd'){
    if(brightprop <= 40){
      brightprop =40;
    }
    else{
      brightprop -= 10;
    }
  }
}  //sets the value of brightprop from 0 to 1 like 0-100%
void ledfunc(){
  button();    //gets the button pressed 
  switch(cmd){  //according to the recieved lights the led accordingly
    case('1'):{
      col = 'r';
      break;
    }
    case('2'):{
      col = 'g';
      break;
    }
    case('3'):{
      col = 'b';
      break;
    }
    case('4'):{
      col = 'y';
      break;
    }
    case('5'):{
      col = 'c';
      break;
    }
    case('6'):{
      col = 'm';
      break;
    }
    case('o'):{
      if(on){
        on=0;
        col = 'O';
      }
      else {
        on =1;
        col = 'w';
      }   //case for which the led will on/off acoording to the on flag
      break;
    }
    case('u'):{
      brightness();
      break;
    }
    case('d'):{
      brightness();
      break;
    }     //calls the function brightness which adjusts the value of the brightness 
  } 
    colour(col);
}     //function recieves the button pressed on the remote and passes the colour to light up
void buttonaddress(){
  if(IrReceiver.decode()){
    Serial.println(IrReceiver.decodedIRData.decodedRawData,HEX);
    IrReceiver.resume();
  }
}   //function for printing the button addresses in hexadecimal
void button(){
  unsigned long value = IrReceiver.decodedIRData.decodedRawData;
  if(value == 0x0){
    return;
  }
  switch(value){
      case(0xE619FF00):{
        cmd = '0';
        break;
      }
      case(0xBA45FF00):{
        cmd = '1';
        break;
      }
      case(0xB946FF00):{
        cmd = '2';
        break;
      }
      case(0xB847FF00):{
        cmd = '3';
        break;
      }
      case(0xBB44FF00):{
        cmd = '4';
        break;
      }
      case(0xBF40FF00):{
        cmd = '5';
        break;
      }
      case(0xBC43FF00):{
        cmd = '6';
        break;
      }
      case(0xF807FF00):{
        cmd = '7';
        break;
      }
      case(0xEA15FF00):{
        cmd = '8';
        break;
      }
      case(0xF609FF00):{
        cmd = '9';
        break;
      }
      case(0xE916FF00):{
        cmd = '*';
        break;
      }
      case(0xF20DFF00):{
        cmd = '#';
        break;
      }
      case(0xE718FF00):{
        cmd = 'u';
        break;
      }
      case(0xF708FF00):{
        cmd = '<';
        break;
      }
      case(0xE31CFF00):{
        cmd = 'o';
        break;
      }
      case(0xA55AFF00):{
        cmd = '>';
        break;
      }
      case(0xAD52FF00):{
        cmd = 'd';
        break;
      }
      default:{
        cmd = '_';
        break;
      }

    }
}   //function for getting that value of the actual button
void setup(){
  IrReceiver.begin(recvpin,ENABLE_LED_FEEDBACK);
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(blue,OUTPUT);
  Serial.begin(9600);
}
void loop(){
  if(IrReceiver.decode()){
    ledfunc();
    delay(dt);
    IrReceiver.resume();
  }
}
