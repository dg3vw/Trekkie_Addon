#include <NonBlockingRtttl.h>

//project's contants
#define BUZZER_PIN PC0
#define BLUE_LED_PIN PD0
const char * tetris = "tetris:d=4,o=5,b=160:e6,8b,8c6,8d6,16e6,16d6,8c6,8b,a,8a,8c6,e6,8d6,8c6,b,8b,8c6,d6,e6,c6,a,2a,8p,d6,8f6,a6,8g6,8f6,e6,8e6,8c6,e6,8d6,8c6,b,8b,8c6,d6,e6,c6,a,a";
const char * arkanoid = "Arkanoid:d=4,o=5,b=140:8g6,16p,16g.6,2a#6,32p,8a6,8g6,8f6,8a6,2g6";
const char * startrek = "Star Trek:o=5,d=16,b=63,b=63:8f.,a#,4d#6.,8d6,a#.,g.,c6.,4f6";
const char * startrekng = "StarTrekTNG:d=32,o=6,b=63:8f#.5,b.5,d#.,8c#.,a.5,g#.,4f#.,a.5,e.,f#.,g#.,e.,8d#,8c#,8b.5,d#.,b.5,2c#";
const char * mario = "mario:d=4,o=5,b=100:16e6,16e6,32p,8e6,16c6,8e6,8g6,8p,8g,8p,8c6,16p,8g,16p,8e,16p,8a,8b,16a#,8a,16g.,16e6,16g6,8a6,16f6,8g6,8e6,16c6,16d6,8b,16p,8c6,16p,8g,16p,8e,16p,8a,8b,16a#,8a,16g.,16e6,16g6,8a6,16f6,8g6,8e6,16c6,16d6,8b,8p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16g#,16a,16c6,16p,16a,16c6,16d6,8p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16c7,16p,16c7,16c7,p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16g#,16a,16c6,16p,16a,16c6,16d6,8p,16d#6,8p,16d6,8p,16c6";
const char * giveyouup = "GiveYouUp:d=4,o=5,b=200:8g,8a,8c6,8a,e6,8p,e6,8p,d.6,p,8p,8g,8a,8c6,8a,d6,8p,d6,8p,c6,8b,a.,8g,8a,8c6,8a,2c6,d6,b,a,g.,8p,g,2d6,2c.6,p,8g,8a,8c6,8a,e6,8p,e6,8p,d.6,p,8p,8g,8a,8c6,8a,2g6,b,c.6,8b,a,8g,8a,8c6,8a,2c6,d6,b,a,g.,8p,g,2d6,2c.6";
const char * pirates = "Piratesof:d=4,o=6,b=100:8a.5,8c.,8d.,8c,16a_5,8a5,16a5,8g5,16g5,f5,16p,16a5,16a.5,32p,16a5,16a5,16a5,16a5,16a5,16a5,16a5,16a5,16a5,16a5,16d.,32p,16a5,16f5,16f5,16g5,16a.5,p,16a5,16a_5,16a_5,16a_5,16g5,16g5,16g5,16a5,16a5,16a5,16f5,16f5,16f5,16g5,16g5,16g5,16g5,16a5";
const char * thegood = "Thegood,:d=4,o=6,b=63:32c,32f,32c,32f,c,8g_5,8a_5,f5,8p,32c,32f,32c,32f,c,8g_5,8a_5,d_";
const char * startrek1 = "we-rock:d=4,o=6,b=225:2b.4,4e.5,1a5,4g#.5,4e.5,4c#.5,4f#.5,2b.5,4b.5,2d#.6,";
const char * startrek2 = "StarTrek:d=4,o=5,b=80:8g,16c6,f6,16e6,16c6,16a,16d6,8g6,8p,8g,16c6,f6,16e6,16c6,16a,16d6,8g6";
const char * startrek3 = "Star Trek: d=4,o=5,b=63:8f.,16a#,d#.6,8d6,16a#.,16g.,16c.6,f6";
const char * startrek4 = "TheNextG:d=4,o=5,b=100:8f#6,16a#6,16a#6,16d#7,8c#7,16p,16g#6,16g#7,16g#7,8f#7,8p,16g#6,8f#7,16p,8d#7,16p,8d#7,16p,16d#7,16a#6,16d#7,8c#7";   
const char * startrek5 = "Communic:d=4,o=5,b=100:16g#7,8a#7,16a#7,16a#7,8f#7";

byte songIndex = 0; //which song to play when the previous one finishes

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);

  Serial.begin(115200);
  Serial.println();
  
}

void loop() {
  if ( !rtttl::isPlaying() )
  {
    if (songIndex == 0)
    {
      rtttl::begin(BUZZER_PIN, startrek5);
      songIndex++; //ready for next song
      delay(5000);

      //play for 5 sec then stop.
      //note: this is a blocking code section
      //used to demonstrate the use of stop
      /*unsigned long start = millis();
      while( millis() - start < 5000 ) 
      {
        rtttl::play();
      }
      rtttl::stop();
      */
    }
    else if (songIndex == 1)
    {
      rtttl::begin(BUZZER_PIN, startrek2 );
      songIndex++; //ready for next song
      delay(5000); //play for 5 sec then stop.
    }
    else if (songIndex == 2)
    {
      rtttl::begin(BUZZER_PIN,startrekng);
      songIndex++; //ready for next song
    }
  }
  else
  {
    rtttl::play();
  }
}