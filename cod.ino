
int S0=5,S1=4,S2=2,S3=4;
int R,G,B;
int counter;
/* intitializeaza pwm-ul pe timerul 0 si 2 */
void init_pwm()
{
    TCCR0A|=(1<<WGM01)|(1<<WGM00);
    TCCR0A |= (1 <<COM0A1)|(1 <<COM0B1) ;
    TCCR0B |= (1 <<CS01) ;
    TCCR2A|=(1<<WGM21)|(1<<WGM20);
    TCCR2A |= (1 <<COM2A1)|(1 <<COM2B1) ;
    TCCR2B |= (1 <<CS21) ;

    OCR0A=0;
    OCR0B=0;
    OCR2A=0;
    OCR2B=0;

}
/*initializarea timerului 1*/
void init_timer1()
{ 
    
    TCCR1A=0;
    TCCR1B |=(1<<CS11);//prescaler pe 8 

}
/*initializare senzor de culoar*/
/* senzorul de culoare functioneaza in felul urmator:
in functie de ce matrice de diode fotovoltaice e pornita acesta va returna un semnal dreptungilor pe pinul 2 din portul D pe care avem setat o intrrupere externa
astefel in cat de fiecare data cand apare un rising endge counter va creste cu o unitate*/
void init_senzorCuloare()
{
    DDRD|=(1<<S1);
    DDRB|=(1<<S2)|(1<<S2)|(1<<S0);
    //prescaler de 100% senzor de culoare
    PORTD|=(1<<S1);
    PORTB|=(1<<S0);
}
void setup() {

     DDRD|=(1<<3)|(1<<5)|(1<<6);
     DDRB|=(1<<3);
     DDRC|=(1<<5);
    init_timer1();
    init_pwm();
    init_senzorCuloare();
 
}

/*verifica daca este pe o suprafat alba sau neagra*/

int d(int i)
{
    if(PINB&(1<<i))
    return 1;
    else
    return 0;
}

int culoare()
{
    EICRA|=(1<<ISC01);
    EIMSK|=(1<<INT0);
    PORTB&=~(1<<S2);
    PORTB&=~(1<<S3);
    TCNT1=0;
    while(TCNT1<2500);
    R=counter;

    counter=0;
    EICRA|=(1<<ISC01);
    EIMSK|=(1<<INT0);
    PORTB&=~(1<<S2);
    PORTB|=(1<<S3);
    TCNT1=0;
    while(TCNT1<2500);
    B=counter;

    counter=0;
    EICRA|=(1<<ISC01);
    EIMSK|=(1<<INT0);
 
    PORTB|=(1<<S2);
    PORTB|=(1<<S3);
    TCNT1=0;
    while(TCNT1<2500);
    G=counter;
    counter=0;




    EICRA|=0;
    EIMSK|=0;
    if(B>100)
    return 3;
    else
        if(R<G)
        return 1;
        else
            if(R>G&&B>25)
            return 2;
            else
                return 0;
}
int deley_ms(int n)
{
  int i;
/* provoaca un delay de n*10 milisecunde */
    for(i=0;i<n;i++)
    {
        TCNT1=0;
        while(TCNT1<2500);
    }
}

void loop() 
{


int a=culoare();


if(a==1)// daca culoare este rosu asteqapta 3 secunde dupa care traverseaza intersectia*/
{

    OCR0B=0;
    OCR2B=0; 
    OCR0A=0;
    OCR2A=0;
    deley_ms(300);

    OCR0B=0;
    OCR2B=0; 
    OCR0A=38;
    OCR2A=38;
    deley_ms(70);

}
if(a==2)/*daca culoarea este albastru traverseaza intersectia fara a te opri*/
{

    OCR0B=0;
    OCR2B=0; 
    OCR0A=38;
    OCR2A=38;
    deley_ms(70);


}
if(a==3)/*daca culoarea este galbena vireaza dreapta*/
{
    OCR0B=0;
    OCR2B=0; 
    OCR2A=0;
    OCR0A=0;
    deley_ms(60);
    OCR0B=0;
    OCR2B=0; 
    OCR2A=0;
    OCR0A=38;
    deley_ms(90);

}

if(d(0) == 1 && d(1) == 1 )/*daca ambi senzori detecteaza alb mergi in fata*/
{
    OCR0B=0;
    OCR2B=0; 
    OCR0A=38;
    OCR2A=38;
}
 if(d(0) == 1 && d(1) == 0 )/*daca senzorul stang detecteaza negru porneste doar motorul drept*/
{
    OCR0B=0;
    OCR0A=0;
    OCR2B=0; 
    OCR2A=38;
}
 if(d(0) == 0 && d(1) == 1 )/*daca senzorul drept detecteaza negru porneste doar motorul stang*/
{
    OCR2B=0; 
    OCR2A=0;
    OCR0B=0;
    OCR0A=38;
}


}

 ISR(INT0_vect)
 {
 counter++;
 }




