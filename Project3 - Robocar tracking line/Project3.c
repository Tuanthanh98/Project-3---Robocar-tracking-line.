#include <Project3.h>
#include <def_877a.h>
#DEFINE     TRIGGER      PIN_b3     //          dinh nghia chan tao xung      
#DEFINE     ECHO         PIN_b2     //          chan tin hieu

#define     trg         pin_a4         // trai ngoai
#define     trt         pin_a3         // trai trong
#define     giua        pin_a2         // giua
#define     pht         pin_a1         //Phai trong
#define     phg         pin_a0         //phai ngoai

signed int32    PWM_DUTY;     // chay 0 - 1000
//CAC HAM CHO DK DONG CO DC BANG PWM
//================================
#DEFINE  MOTOR_ENA0   PIN_c0
#DEFINE  MOTOR_ENA1   PIN_d1

FLOAT KCSA, KCSB;                   // vi doc vao gia tri thuc
UNSIGNED INT8  GT_TRAN;        // c�c khai bao can thiet

signed int16 kc;

#int_timer1                         // ngat de do khoang cach li�n tuc
void interrupt_timer1()
{
   GT_TRAN++;                       //bao tran
}

INT1 DCMOTOR_TN;        // tn thuan nghich
//CAC HAM CHO DK DONG CO DC BANG PWM
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID DC_MOTOR_KTAO_CCP1_THUAN()
{     
      SETUP_CCP2(CCP_OFF);      
      SETUP_CCP1(CCP_PWM);
      OUTPUT_LOW(PIN_C1);      
}
VOID DC_MOTOR_KTAO_CCP2_NGHICH()
{            
      SETUP_CCP1(CCP_OFF);      
      SETUP_CCP2(CCP_PWM);
      OUTPUT_LOW(PIN_C2);
}
VOID DC_MOTOR_KTAO_CCPX_KTAO()
{         
     IF (DCMOTOR_TN==1)    DC_MOTOR_KTAO_CCP1_THUAN();
     ELSE                  DC_MOTOR_KTAO_CCP2_NGHICH();            
}
VOID DC_MOTOR_PWW_SETUP_DUTY()
{     
     IF (DCMOTOR_TN==1)    SET_PWM1_DUTY(PWM_DUTY);
     ELSE                  SET_PWM2_DUTY(PWM_DUTY);     
} 
VOID DC_MOTOR_PWM_CCP1_CCP2_STOP()
{         
//!      PWM_DUTY=0;            
      SETUP_CCP1(CCP_OFF);
      SETUP_CCP2(CCP_OFF);
      DC_MOTOR_KTAO_CCPX_KTAO();
//!      DC_MOTOR_PWW_SETUP_DUTY();
}

VOID TAO_XUNG_TRIGGER()       // tao xung de day tin hieu ra ngoai
{
   DELAY_MS(30);              //tao tre
   OUTPUT_HIGH(TRIGGER);      // kich muc cao truoc
   DELAY_MS(1);               // cho 1 ti de tao xung
   OUTPUT_LOW(TRIGGER);       // kich muc thap thi tao duoc 1 xung
   
   SET_TIMER1(0);                // chuong trinh ngat reset ve 0
   WHILE(!(INPUT(ECHO)));        // ktra chan echo ==1
   SETUP_TIMER_1(T1_INTERNAL);   // cho phep dem xung timer
   
   WHILE(INPUT(ECHO)==1);           //het du lieu echo = 0
   KCSA = GET_TIMER1();          // doc gia tri timer
   SETUP_TIMER_1(T1_DISABLED);   // khong cho doc gia tri timer
}

VOID DOC_KHOANG_CACH()
{
   GT_TRAN=0;              //bao gia tri tran
   TAO_XUNG_TRIGGER();     // khi tran thi doc gia tri
   KCSB = KCSA +GT_TRAN*65536;         // c�ch tinh l� c�ng tong cac gia tri lai
   
   KCSB = KCSB/5;             //  chuyen sang thoi gian uS
   KCSB = (KCSB/58);          // chia  de chuyen sang don vi cm
   kc=kcsb;
}

void chay_line()
{
   if((input(trg)==0)&&(input(trt)==0)&&(input(giua)==1)&&(input(pht)==0)&&(input(phg)==0))                 // 00100
   {
       PWM_DUTY=500;
       OUTPUT_high(MOTOR_ENA0);        // bat 2 dong  co
       OUTPUT_high(MOTOR_ENA1);
       DCMOTOR_TN=0;                   // = 1 quay thuan
       DC_MOTOR_KTAO_CCPX_KTAO();      // khoi tao quay 
       DC_MOTOR_PWW_SETUP_DUTY();      // khoi tao toc do quay
   }
   else if((input(trg)==0)&&(input(trt)==1)&&(input(giua)==1)&&(input(pht)==0)&&(input(phg)==0))         // 01100
   {
       PWM_DUTY=400;
       OUTPUT_high(MOTOR_ENA0);        // bat 2 dong  co
       OUTPUT_high(MOTOR_ENA1);
       DCMOTOR_TN=0;                   // = 1 quay thuan
       DC_MOTOR_KTAO_CCPX_KTAO();      // khoi tao quay 
       DC_MOTOR_PWW_SETUP_DUTY();      // khoi tao toc do quay
   }
   else if((input(trg)==0)&&(input(trt)==0)&&(input(giua)==1)&&(input(pht)==1)&&(input(phg)==0))      //  00110
   {
       PWM_DUTY=400;
       OUTPUT_high(MOTOR_ENA0);        // bat 2 dong  co
       OUTPUT_high(MOTOR_ENA1);
       DCMOTOR_TN=0;                   // = 1 quay thuan
       DC_MOTOR_KTAO_CCPX_KTAO();      // khoi tao quay 
       DC_MOTOR_PWW_SETUP_DUTY();      // khoi tao toc do quay
   }
   else if((input(trg)==0)&&(input(trt)==1)&&(input(giua)==1)&&(input(pht)==1)&&(input(phg)==0))         //01110
   {
       PWM_DUTY=400;
       OUTPUT_high(MOTOR_ENA0);        // bat 2 dong  co
       OUTPUT_high(MOTOR_ENA1);
       DCMOTOR_TN=0;                   // = 1 quay thuan
       DC_MOTOR_KTAO_CCPX_KTAO();      // khoi tao quay 
       DC_MOTOR_PWW_SETUP_DUTY();      // khoi tao toc do quay
   }
   else if((input(trg)==0)&&(input(trt)==1)&&(input(giua)==0)&&(input(pht)==0)&&(input(phg)==0))         //01000
   {
       PWM_DUTY=400;
       OUTPUT_low(MOTOR_ENA0);        // phai
       OUTPUT_high(MOTOR_ENA1);        // trai
       DCMOTOR_TN=0;                   // = 1 quay thuan
       DC_MOTOR_KTAO_CCPX_KTAO();      // khoi tao quay 
       DC_MOTOR_PWW_SETUP_DUTY();      // khoi tao toc do quay
   }
   else if((input(trg)==0)&&(input(trt)==0)&&(input(giua)==0)&&(input(pht)==1)&&(input(phg)==0))         //00010
   {
       PWM_DUTY=400;
       OUTPUT_high(MOTOR_ENA0);        // bat 2 dong  co
       OUTPUT_low(MOTOR_ENA1);
       DCMOTOR_TN=0;                   // = 1 quay thuan
       DC_MOTOR_KTAO_CCPX_KTAO();      // khoi tao quay 
       DC_MOTOR_PWW_SETUP_DUTY();      // khoi tao toc do quay
   }
   else if((input(trg)==1)&&(input(trt)==1)&&(input(giua)==0)&&(input(pht)==0)&&(input(phg)==0))         //11000
   {
       PWM_DUTY=400;
       OUTPUT_low(MOTOR_ENA0);        // bat 2 dong  co
       OUTPUT_high(MOTOR_ENA1);
       DCMOTOR_TN=0;                   // = 1 quay thuan
       DC_MOTOR_KTAO_CCPX_KTAO();      // khoi tao quay 
       DC_MOTOR_PWW_SETUP_DUTY();      // khoi tao toc do quay
   }
   else if((input(trg)==0)&&(input(trt)==0)&&(input(giua)==0)&&(input(pht)==1)&&(input(phg)==1))         //00011
   {
       PWM_DUTY=400;
       OUTPUT_high(MOTOR_ENA0);        // bat 2 dong  co
       OUTPUT_low(MOTOR_ENA1);
       DCMOTOR_TN=0;                   // = 1 quay thuan
       DC_MOTOR_KTAO_CCPX_KTAO();      // khoi tao quay 
       DC_MOTOR_PWW_SETUP_DUTY();      // khoi tao toc do quay
   }
   else if((input(trg)==1)&&(input(trt)==0)&&(input(giua)==0)&&(input(pht)==0)&&(input(phg)==0))         //10000
   {
       PWM_DUTY=400;
       OUTPUT_low(MOTOR_ENA0);        // bat 2 dong  co
       OUTPUT_high(MOTOR_ENA1);
       DCMOTOR_TN=0;                   // = 1 quay thuan
       DC_MOTOR_KTAO_CCPX_KTAO();      // khoi tao quay 
       DC_MOTOR_PWW_SETUP_DUTY();      // khoi tao toc do quay
   }
   else if((input(trg)==0)&&(input(trt)==0)&&(input(giua)==0)&&(input(pht)==0)&&(input(phg)==1))         //00001
   {
       PWM_DUTY=400;
       OUTPUT_high(MOTOR_ENA0);        // bat 2 dong  co
       OUTPUT_low(MOTOR_ENA1);
       DCMOTOR_TN=0;                   // = 1 quay thuan
       DC_MOTOR_KTAO_CCPX_KTAO();      // khoi tao quay 
       DC_MOTOR_PWW_SETUP_DUTY();      // khoi tao toc do quay
   }
   else if((input(trg)==0)&&(input(trt)==0)&&(input(giua)==1)&&(input(pht)==1)&&(input(phg)==1))         //01111
   {
       PWM_DUTY=600;
       OUTPUT_high(MOTOR_ENA0);        // bat 2 dong  co
       OUTPUT_low(MOTOR_ENA1);
       DCMOTOR_TN=0;                   // = 1 quay thuan
       DC_MOTOR_KTAO_CCPX_KTAO();      // khoi tao quay 
       DC_MOTOR_PWW_SETUP_DUTY();      // khoi tao toc do quay
       delay_ms(100);
   }
   else if((input(trg)==1)&&(input(trt)==1)&&(input(giua)==1)&&(input(pht)==0)&&(input(phg)==0))         //11110
   {
       PWM_DUTY=600;
       OUTPUT_low(MOTOR_ENA0);        // bat 2 dong  co
       OUTPUT_high(MOTOR_ENA1);
       DCMOTOR_TN=0;                   // = 1 quay thuan
       DC_MOTOR_KTAO_CCPX_KTAO();      // khoi tao quay 
       DC_MOTOR_PWW_SETUP_DUTY();      // khoi tao toc do quay
       delay_ms(100);
   }
   else
   {
       PWM_DUTY=400;
       OUTPUT_high(MOTOR_ENA0);        // bat 2 dong  co
       OUTPUT_high(MOTOR_ENA1);
       DCMOTOR_TN=1;                   // = 1 quay thuan
       DC_MOTOR_KTAO_CCPX_KTAO();      // khoi tao quay 
       DC_MOTOR_PWW_SETUP_DUTY();      // khoi tao toc do quay
   }
}
VOID MAIN()
{  
    SET_TRIS_D(0X00);      // khoi tao cac port ra nen cho bang 0
    SET_TRIS_C(0X00);
    SET_TRIS_A(0Xff);     // vi chan AN0 vao nen cho len 1 con lai ve 0
    SET_TRIS_E(0Xff);
    SET_TRIS_B(0X00);

    SETUP_TIMER_1(T1_DISABLED);       //tat timer1
    ENABLE_INTERRUPTS(GLOBAL);        // cho ph�p ngat
    ENABLE_INTERRUPTS(INT_TIMER1);           // cho phep ngat timer 1
                   // khoi tao LCD
//!    
    SETUP_TIMER_2(T2_DIV_BY_16,249,1);       // 
    
//!    OUTPUT_HIGH(MOTOR_ENA0);
//!    OUTPUT_HIGH(MOTOR_ENA1);
//!    PWM_DUTY=1000;
//!    SETUP_CCP1(CCP_OFF);      
//!    SETUP_CCP2(CCP_PWM);    
//!    SET_PWM2_DUTY(PWM_DUTY);
    WHILE(TRUE)
    {
         DOC_KHOANG_CACH();
         if(kc>10)         
         {
            chay_line();
            output_low(pin_b0);
         }
         else        
         {
             OUTPUT_low(MOTOR_ENA0);        // bat 2 dong  co
             OUTPUT_low(MOTOR_ENA1);  
             output_high(pin_b0);
         }
    }
}


