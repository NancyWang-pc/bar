#include <FastLED.h> // 此示例程序需要使用FastLED库
#define NUM_LEDS 64            // LED灯珠数量
#define DATA_PIN       9  //Aduino输出控制信号引脚
#define LED_TYPE WS2812         // LED灯带型号
#define COLOR_ORDER GRB         // RGB灯珠中红色、绿色、蓝色LED的排列顺序
#define twinkleInterval  100    //  闪烁间隔时间 (毫秒)
#define twinkleChance 80        //  闪烁数量，数值越大闪烁越多（0-255） 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
CRGB leds[NUM_LEDS];            // 建立光带leds
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
uint8_t max_bright = 128;       // LED亮度控制变量，可使用数值为 0 ～ 255， 数值越大则光带亮度越高

// constants won't change. They're used here to set pin numbers:
const int sensor_a_Pin = 13;
const int sensor_b_Pin = 12;


// variables 
int count = 0;
int new_a_state = LOW;
int old_a_state = new_a_state;
int new_b_state = LOW;
int old_b_state = new_b_state;
int scene = 0;

void setup() {
  lcd.init(); // initialize the lcd 
  lcd.init(); // Print a message to the LCD.
  Serial.begin(9600);           // 启动串行通讯
  delay(1000);                  // 稳定性等待
  LEDS.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS); // 初始化光带
  FastLED.setBrightness(max_bright);                            // 设置光带亮度
  pinMode(sensor_a_Pin, INPUT);                               // initialize the first and second pushbutton pin as an input
  pinMode(sensor_b_Pin, INPUT);
}



void choose_led_pattern(){
   old_a_state = new_a_state;
   new_a_state = digitalRead(sensor_a_Pin);
 
    if (count == 0){
      lcd.backlight();
      lcd.setCursor(1,0);
      lcd.print(" >Happy  Blue   ");
      lcd.setCursor(1,1);
      lcd.print("  Angry  Calm   ");
    }
   else if (count == 1){
    lcd.backlight();
    lcd.setCursor(1,0);
    lcd.print("  Happy >Blue   ");
    lcd.setCursor(1,1);
    lcd.print("  Angry  Calm   ");
   }
   else if (count == 2){
    lcd.backlight();
    lcd.setCursor(1,0);
    lcd.print("  Happy  Blue   ");
    lcd.setCursor(1,1);
    lcd.print(" >Angry  Calm   ");
   }
   else if (count == 3){
    lcd.backlight();
    lcd.setCursor(1,0);
    lcd.print("  Happy  Blue   ");
    lcd.setCursor(1,1);
    lcd.print("  Angry >Calm   ");
   }
  // each time sensor a is pressed, count 1
  if ((new_a_state == HIGH)&&(old_a_state == LOW)){
  // in case people press sensor a many times (> 5)
    count = (count + 1)%4;
    } 
}

void light_led_belt() {
  int pos = random8(NUM_LEDS); 
       
//  EVERY_N_MILLISECONDS( twinkleInterval ) { 
//    if( random8() < twinkleChance) {
//      leds[pos] = ColorFromPalette( PartyColors_p, random8(255), 128, LINEARBLEND);
//    }   
//  }
//    EVERY_N_MILLISECONDS( 20 ) { 
//    fadeToBlackBy( leds, NUM_LEDS, 10);
//  }
    if (count == 0){
    for(int i = 0; i < NUM_LEDS; i++){
     if( random8() < twinkleChance) {
     leds[pos] = CHSV(500, 100, 100); // pink
        }    
      }
    }
    else if (count == 1){
      for(int i = 0; i < NUM_LEDS; i++){
       if( random8() < twinkleChance) {
       leds[pos] = CHSV(160, 100, 100); // blue
        }    
      }
    }
    else if (count == 2){
    for(int i = 0; i < NUM_LEDS; i++){
       if( random8() < twinkleChance) {
       leds[pos] = CHSV(283, 99, 100); // green
        }    
      }  
    }
    else if (count == 3){
      for(int i = 0; i < NUM_LEDS; i++){
       if( random8() < twinkleChance) {
       leds[pos] = CHSV(120, 100, 100); // orange
        }    
      }
    }
    EVERY_N_MILLISECONDS( 20 ) { 
    fadeToBlackBy( leds, NUM_LEDS, 10);
  }  
    FastLED.show(); 
    delay(500);
    }
       
//    for(int i = 0; i < NUM_LEDS; i++){
//       leds[i] = CHSV(230, 100, 100); // purple
//    }     
//    FastLED.show(); 
//    delay(500);    
//    for(int i = 0; i < NUM_LEDS; i++){
//       leds[i] = CHSV(650, 100, 100); //
//    }     
//    FastLED.show(); 
//    delay(500);    
//}




void loop() {
  old_b_state = new_b_state;
  new_b_state = digitalRead(sensor_b_Pin);
  if (scene == 0)
  {
    lcd.backlight();
    lcd.setCursor(1,0);
    lcd.print("    Welcome!   ");
    // once sensor b is pressed, enter the next station: light led belt in a certain pattern
    if ((new_b_state == HIGH)&&(old_b_state == LOW)){
       //next scene, visit scene for led belt display
       lcd.clear();
       lcd.print("   comfirmed!   ");
       scene = (scene+1)%4;
    }
  }
  else if(scene == 1){
     // once sensor b is pressed, enter the next station: light led belt in a certain pattern
     if ((new_b_state == HIGH)&&(old_b_state == LOW)){
        //next scene, visit scene for led belt display
        lcd.clear();
        lcd.print("   comfirmed!   ");
         scene = (scene+1)%4;
      }
     else {
        choose_led_pattern();  
      }
  } 
  else if (scene == 2) 
  {
     light_led_belt();
     if ((new_b_state == HIGH)&&(old_b_state == LOW)){
        //next scene, visit scene for led belt display
        scene = (scene+1)%4;
     }
    }
  else
  {
     for(int i = 0; i < NUM_LEDS; i++){
       leds[i] =  CRGB::Black; 
     }
     FastLED.show();
     if ((new_b_state == HIGH)&&(old_b_state == LOW)){
        //next scene, visit scene for led belt display
        scene = (scene+1)%4;
     }
   }
}
