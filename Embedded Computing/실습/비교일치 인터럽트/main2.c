/*
 *  아트멜 스튜디오와 아두이노로 배우는 ATmega328 프로그래밍
 *
 * 		Gyeongyong Heo (hgycap@deu.ac.kr)
 *			Department of Electronic Engineering
 *			Dong-eui University
 *  	2015. 07. 14
 */ 
#define F_CPU 16000000L		//16Mhz
#include <avr/io.h>
#include <avr/interrupt.h>
volatile int count = 0; // 비교일치가 발생한 횟수
int state = 0; // LED 점멸 상태
ISR(TIMER0_COMPA_vect)
{
	count++;
	TCNT0 = 0; // 자동으로 0으로 변하지 않는다.
}
int main(void)
{
	DDRB = 0x20; // PB5 핀을 출력으로 설정
	PORTB = 0x00; // LED는 끈 상태에서 시작
	TCCR0B |= (1 << CS02) | (1 << CS00); // 분주비를 1024로 설정
	OCR0A = 128; // 비교일치 기준값
	TIMSK0 |= (1 << OCIE0A); // 비교일치 인터럽트 허용
	sei(); // 전역적으로 인터럽트 허용
	while(1){
		if(count == 64){ // 비교일치 64회 발생 = 0.5초 경과
			count = 0; // 카운터 초기화
			state = !state; // LED 상태 반전
			if(state) PORTB = 0xFF; // LED 켜기
			else PORTB = 0x00; // LED 끄기
		}
	}
}