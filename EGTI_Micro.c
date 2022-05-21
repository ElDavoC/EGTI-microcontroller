#include <16F877.h>
#device adc=10
#FUSES XT,NOWDT
#use delay(clock=20000000)
#include <HDM64GS12.c>
#include <graphics.c>
#use standard_io(a)


void main() {
   int16 q;
   int16 k;
   float p;
   float z1;
   float z2;
   float m1;
   float m2;
   int y1;
   int y2;
   int j1;
   int j2;

   setup_adc_ports(ALL_ANALOG);              //Todos los canales analógicos
   setup_adc(ADC_CLOCK_INTERNAL);          //Fuente de reloj RC
   
   CHAR A1[20];
   CHAR A2[ ]="EGT";
   CHAR A3[20];
   CHAR A4[20];
   CHAR A5[20];
   CHAR D1[ ]="0";
   CHAR D2[ ]="4";
   CHAR D3[ ]="8";
   CHAR S1[ ]="C";
   glcd_init(ON);
   glcd_text57(49,1,A2,2,1);     //Texto "EGT".
   glcd_text57(63,20,S1,1,1);    //Texto "°C".


   for (;;) {
      
      
      set_adc_channel(0);                 //Habilitación canal 0
      delay_ms(1);
      q = read_adc();                     //Lectura canal 0
      
      set_adc_channel(1);                 //Habilitación canal 1
      delay_ms(1);
      k = read_adc();                     //Lectura canal 1
      
      z1 = 0.8815249267 * q;              //Acondicionamiento señal canal 0 ((q - 1022)*(-1)) 0.87890625 (900/1024); 0.8815249267 = (901.8/1023); 0.8797653959 (900/1023)
      z2 = 0.8815249267 * k;              //Acondicionamiento señal canal 1.
      
      p = 5.0 * q / 1023.0;               //Conversión a tensión
      
      sprintf(A3,"%03.0f",z1);            //Temperatura canal 0.
      sprintf(A1,"%03.0f",z2);            //Temperatura canal 1.
      
      m1= z1/18;                          //Conversiòn de la temperatura a la escala de pixeles (motor 1).
      m1= (int)m1;                        //Variable "m1" se convierte en int.
      y1= 56-m1;                          //Ubicaciòn en "y" del indicicador (motor 1).
      
      m2= z2/18;                          //Conversiòn de la temperatura a la escala de pixeles (motor 2).
      m2= (int)m2;                        //Variable "m2" se convierte en int.       
      y2= 56-m2;                          //Ubicaciòn en "y" del indicicador (motor 2).
      
      
      //Motor 1.
      glcd_line(11,j1,19,j1,0);        //Línea 1 del indicador que "Borra".
      glcd_line(6,j1,9,j1,0);          //Línea 2 del indicador que "Borra".
      glcd_line(10,6,10,56,1);         //Línea principal.
      glcd_line(9,22,15,22,1);         //Límite ambar.
      glcd_line(9,20,15,20,1);         //Límite rojo.
      glcd_line(11,56,13,56,1);        //Indicador de 0.
      glcd_line(11,33,13,33,1);        //Indicador de 400.
      glcd_line(11,12,13,12,1);        //Indicador de 800.
      glcd_line(6,y1,19,y1,1);         //Línea del indicador.
      glcd_rect(32,35,52,45,0,ON);     //Rectángulo temperatura.
      glcd_text57(34,37,A4,1,0);       //Texto que "limpia".
      glcd_text57(34,37,A3,1,1);       //EGT.
      glcd_text57(18,53,D1,1,1);       //0°C
      glcd_text57(18,30,D2,1,1);       //400°C
      glcd_text57(18,8,D3,1,1);        //800°C
      
      
      //Motor 2.
      glcd_line(119,j2,122,j2,0);            //Línea 1 del indicador que "Borra".
      glcd_line(109,j2,117,j2,0);            //Línea 2 del indicador que "Borra".
      glcd_line(118,6,118,56,1);             //Línea principal.
      glcd_line(113,22,119,22,1);            //Límite ambar.
      glcd_line(113,20,119,20,1);            //Límite rojo.
      glcd_line(115,56,117,56,1);            //Indicador de 0.
      glcd_line(115,33,117,33,1);            //Indicador de 400.
      glcd_line(115,12,117,12,1);            //Indicador de 800.
      glcd_line(109,y2,122,y2,1);           //Línea del indicador.
      glcd_rect(77,35,97,45,0,ON);           //Rectángulo temperatura.
      glcd_text57(79,37,A5,1,0);             //Texto que "limpia".
      glcd_text57(79,37,A1,1,1);             //EGT.
      glcd_text57(105,53,D1,1,1);            //0°C
      glcd_text57(105,30,D2,1,1);            //400°C
      glcd_text57(105,8,D3,1,1);             //800°C
      
      
      
      sprintf(A4,"%03.0f",z1);
      sprintf(A5,"%03.0f",z2);
      j1 = y1;
      j2 = y2;
      delay_us(1);
      }
   
}
