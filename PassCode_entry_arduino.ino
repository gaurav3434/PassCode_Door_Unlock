#include <avr/sleep.h>
#include <Servo.h>


Servo myservo;

bool bool_2=true;  // true if pin 7 in HIGH
int counter=0;
String main_data="";
bool bool_1=true;    // true for making buzzer sound while typing 
void setup() { 
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(7,OUTPUT);   // Display power on/off 
  digitalWrite(7,HIGH); 
  myservo.attach(9);   // Servo 
  pinMode(10,OUTPUT);  // buzzer 
  Serial.begin(9600);
  attachInterrupt(0,restart,RISING); // wake up and Restart everything 
}

void loop() {
  myservo.attach(9);
  Serial.print("t0.txt=");
  Serial.print("\"");
  Serial.print(main_data); 
  Serial.print("\"");
  Serial.write(0xff);      // mandetory to send this 3 times after sending command to object in nextion display. 
  Serial.write(0xff);
  Serial.write(0xff);  
  if (Serial.available())
    { String data="";
      if (bool_1==true)
      {digitalWrite(10,HIGH);}
      delay(30);
      while(Serial.available()){
      data+= char(Serial.read());
      } 
      Serial.println(data);
       sendData(data);
    }  
    myservo.write(0);
    digitalWrite(10,LOW);
  if (counter<2001)
    { counter++;}

  if (counter==2000)
    { digitalWrite(7,LOW);
      bool_2=false;
      sleep();
    }
}   // end of void loop

void sendData(String data)
{ if (data=="O")  
   {Serial.println("1");
    main_data+=("1");
   }
  else if (data=="TW")
   {Serial.println("2");
    main_data+=("2");
   }
  else if (data=="TH")
   {Serial.println("3");
    main_data+=("3");
   }
  else if (data=="FO") 
   {Serial.println("4");
    main_data+=("4");
   }


  else if (data=="FI") 
   {Serial.println("5");
    main_data+=("5");
   }

  else if (data=="SI") 
   {Serial.println("6");
    main_data+=("6");
   }

  else if (data=="SE") 
   {Serial.println("7");
    main_data+=("7");
   }

  else if (data=="E") 
   {Serial.println("8");
    main_data+=("8");
   }   

  else if (data=="N") 
   {Serial.println("9");
    main_data+=("9");
   }

  else if (data=="Z") 
   {Serial.println("0");
    main_data+=("0");
   }  
  
  else if (data=="B") 
   {int lastIndex = main_data.length() - 1;
    main_data.remove(lastIndex);
   } 

  else if (data=="C") 
   {main_data="";
   }  

  else if (data=="D" )
   {if (main_data=="66946796")
     {myservo.write(95);  
      digitalWrite(10,HIGH);
      delay(300);
      digitalWrite(10,LOW);
      delay(300);
      digitalWrite(10,HIGH);
      delay(300);
      digitalWrite(10,LOW);
      delay(300);
      digitalWrite(10,HIGH);
      delay(300);
      digitalWrite(10,LOW);
      delay(300);
      digitalWrite(10,HIGH);
      delay(300);
      digitalWrite(10,LOW);
      delay(300);
      digitalWrite(10,HIGH);
      delay(300);
      digitalWrite(10,LOW);
      delay(300);
      digitalWrite(10,HIGH);
      delay(300);
      digitalWrite(10,LOW);
      delay(300);
      digitalWrite(10,HIGH);
      delay(300);
      digitalWrite(10,LOW);
      delay(300);
      myservo.write(0);
      delay(1000);
       main_data="";
       bool_1=false;
       sleep();
      }
    if (main_data!="66946796")
      { main_data="";
        bool_1=false;
      }   
   }  

  else if (data=="TR" )
   {main_data="";
    bool_1=true;
   }  
}

void restart()
{ sleep_disable();
  bool_1=true;
  digitalWrite(7,LOW);
 for (int i=0; i<10; i++)
   {Serial.print("waiting ");}
  digitalWrite(7,HIGH);
  counter=0;
  main_data="";
  myservo.attach(9);
  bool_1=true; 
}

void sleep()
{ main_data="";
  bool_2=false;
  myservo.detach();
  digitalWrite(LED_BUILTIN,LOW);
  digitalWrite(7,LOW);
  sleep_enable(); 
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_cpu();
  sleep_disable();
}
