 #include <LiquidCrystal.h>

const int led1=0;   //red
const int led2=1;   //blue
const int led3=2;   //yellow
const int led4=3;   //green

const int bt1=8;        //red
const int bt2=9;        //blue
const int bt3=10;       //yellow
const int bt4=13;       //green

//--------------------LCD pin tanimlamalari
const int rs=12;
const int en=11;
const int d4=5;
const int d5=4;
const int d6=7;
const int d7=6;
//-------------------------------------------
#define buzzer A5
#define playBt A4


const int Re=294;
const int Do= 523;
const int La= 440;
const int Si=493;

int oyunMuzigi[]={La,Si,Do,Re};
const int maxLevel=50;                     //ulasildiginda oyunun kazanilarak sonlanacagi level
int soru[maxLevel];                        //rasgele yakilacak ledlerin tutuldugu dizi

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int speedVal=1000;                         //(milisaniye)     tur gecildiginde -=30.   delay suresi kisalir, oyun zorlugu artar
int tourNm=1;                              //her turda 1 artirilan degisken
int score=0;

void (*resetFunc)(void) = 0;               //0 adresinde bir resetleme fonksiyonu tanimladik
void muzikCal()                            //oyun basinda muzik calan fonksiyon
{
  for(int i=0; i<5; i++)
  {
    tone(buzzer, oyunMuzigi[i]);
    delay(450);
    noTone(buzzer);
    delay(50);
  }
}
void endGame()                             
{
  speedVal=1000;
  tourNm = 1;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Oyun bitti :(");
  tone(buzzer,oyunMuzigi[1]);
  delay(500);

  lcd.clear();
  noTone(buzzer);
  delay(500);

  lcd.print("Oyun bitti :(");
  tone(buzzer,oyunMuzigi[1]);
  delay(500);

  lcd.clear();
  noTone(buzzer);
  delay(500);

  lcd.print("Oyun bitti :(");
  tone(buzzer,oyunMuzigi[1]);
  delay(500);

  lcd.clear();
  noTone(buzzer);
  delay(500);
  
  
  lcd.print("skorunuz: ");
  lcd.print(String(score));
  delay(3000);
  lcd.clear();
  score=0;
  lcd.print("yeniden oynamak");
  lcd.setCursor(0,1);
  lcd.print("icin p ye basin");
 
  
  do{
   
    if(digitalRead(playBt) == HIGH)
      break;
    }while(1);
    
    resetFunc();
}

void soruUret()
{
  
  for(int i=0; i<maxLevel; i++)
  {
    soru[i] = random(0,4);
    
  }
  
  
}

void ledYak()                                 //ledleri rasgele duzende sirayla yakip sonduren fonksiyon
{
    digitalWrite(led1,LOW);                   //butun ledler sondurulur
    digitalWrite(led2,LOW);
    digitalWrite(led3,LOW);
    digitalWrite(led4,LOW);
  for( int i=0; i<tourNm; i++)                //tur sayisi kadar led yakilip sondurulur
  {
    digitalWrite(soru[i], HIGH);              //rastgele bir ledi yak  
    tone(buzzer, oyunMuzigi[soru[i]]);        //ledin indisine karsilik gelen notayi cal
    delay(speedVal);                          
    digitalWrite(soru[i], LOW);               //speedVal kadar bekle ve ledi sondur 
    noTone(buzzer);                           //buzzeri kapat
    delay(speedVal);                          //speedVal kadar bekle  
    
  }
  
}



int btOku()                           //her tur butonlari okuyup cevap dogruysa 1, yanlissa 0 degerini return eden fonksiyon                         
{
                       
  int i=0;
 
  int isAnsTrue=1;                    // fonksiyonun return edecegi degisken. =0 ise yanlis cevap, =1 ise dogru cevap
  
  int cevap[tourNm];                  //fonksiyon her cagirildiginda tourNm kadar elemani olan integer bir dizi olusturulur
  int flag=0;                         //flag degiskeninin ilk degeri 0 dir 
 
 for(int i=0;i<tourNm;i++)            //bu dongu icinde her tur yakilan led sayisinca (tourNm kadar) buton okumasi yapilir.(ancak yanlis butona basilirsa okuma sonlanir          
 {
    flag=0;

    while(flag==0)                    //flag=0 ken butonlar surekli okunur. butona basilirsa ilgili if ifadesinde dogru butona basilip basilmadigi kontrol edilir        
    {
    if(digitalRead(bt1)==HIGH)        // bt1 butonuna basilmissa yurutululecek kod dizisi    
    {
      cevap[i]=0;                     //butona karsilik gelen sayi degeri cevap[i] ye  atilir 
      flag=1;                         //butona basildisa flag=1. yani her buton okumasinda while dongusu sonlanir
     
      tone(buzzer,La);                //butona basilinca nota cal
      delay(200);
      noTone(buzzer);
      if(cevap[i] != soru[i])         
      {
        isAnsTrue=0;                  // yanlis butona basildiysa isAnsTrue 0 degerini alacak
        endGame();                    //endGame() fonksiyonunu cagir
      }
      
      
      
    }  
    if(digitalRead(bt2)==HIGH)
    {
      cevap[i]=1;
      flag=1;
      
      tone(buzzer,Si);
      delay(200);
     
      noTone(buzzer);
      
      if(cevap[i] != soru[i])
      {
        isAnsTrue=0;
        endGame();
      }
      
      
     
    }  
    if(digitalRead(bt3)==HIGH)
    {
      cevap[i]=2;
      flag=1;
     
      tone(buzzer,Do);
      delay(200);
     
      noTone(buzzer);
      
      if(cevap[i] != soru[i])
      {
        isAnsTrue=0;
        endGame();
      }
      
      
     
    }  
    if(digitalRead(bt4)==HIGH)
    {
      cevap[i]=3;
      flag=1;
      
      tone(buzzer,Re);
      delay(200);
     
      noTone(buzzer);
      
      if(cevap[i] != soru[i])
      {
        isAnsTrue=0;
        endGame();
      } 
      
      
      
    } 
     delay(150); 
    }
    
 }  
  
  return isAnsTrue;                   
  
}              
void youWon()                                   
{
                                             //oyun basariyla bitince cagirilan fonksiyon
  lcd.clear();                               //lcd deki butun karakterleri temizle
  lcd.setCursor(0,0);                        // imleci satir 0 sutun 0 konumuna al 
  lcd.print("kazandiniz!!");
  tone(buzzer,La);
  delay(500);
  tone(buzzer,Si);
  delay(500);
  tone(buzzer,La);
  delay(500);
  tone(buzzer,Si);
  delay(500);
  tone(buzzer,Do);
  delay(500);
  noTone(buzzer);
  lcd.clear();
  lcd.print("tekrar oynamak");
  lcd.setCursor(0,1);
  lcd.print("icin p ye basin");
  do{                                       //playBt butonuna basilana kadar do while doner. basildiginda ise donguden cikilir, oyun tekrar baslar
    if(digitalRead(playBt) == HIGH)
      break;
  }while(1);
  resetFunc();                                
  
}

void gameLoop()
{
     randomSeed(analogRead(A0)); 
     
     if(tourNm==1)                          // ilk turda muzik calip rastgele yakilacak led pinlerini tutan dizi olustur
     {
        muzikCal();
        soruUret();
     }
        
     lcd.clear();
     lcd.setCursor(0,0);
     
     lcd.print("tur: ");                      
     lcd.print(String(tourNm));
     lcd.setCursor(0,1);
     
     lcd.print("skor: ");
     lcd.print(String(score));
    
       
     ledYak();                            
     

     
     if(btOku()==1)                           //btOku 1 return ettiyse tur gecilir
     {
      score++;
      if(tourNm == maxLevel)                  //eger max tur sayisina ulasilmissa youWon() fonksiyonu cagirilir oyun basariyla tamamlanir
          youWon();                           
      tourNm++;                                   
      speedVal -= 30;                         //gecilen her tur icin speedVal 30 ar 30 ar eksiltilir. speedVal degeri azaldikca oyun hizi artar
     }
   
     else
        endGame();                            
     
}



void setup()
{
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);

  pinMode(bt1,INPUT);      
  pinMode(bt2,INPUT);
  pinMode(bt3,INPUT);
  pinMode(bt4,INPUT);

  pinMode(playBt, INPUT);
  pinMode(buzzer, OUTPUT);

  pinMode(buzzer, OUTPUT);
  
  lcd.begin(16, 2);
  
}


void loop()
{     
      if(tourNm == 1)                             //ilk turda playBt butununa basilmasi beklenir, butona basilinca oyun baslar
      {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("baslamak icin");
      lcd.setCursor(0,1);
      lcd.print("p ye basin");
      do{
        if(digitalRead(playBt) == HIGH)
          break;
        
      }while(1);
      }
      gameLoop();
}
  
