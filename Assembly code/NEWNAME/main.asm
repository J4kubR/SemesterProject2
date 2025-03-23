.org 0
jmp main                ; jump to the main code
.org 0x38
jmp rxc					; jump to rxc on receive complete interrupt

main:
ldi r16, high(ramend)	; intializing the stack
out sph, r16			; intializing the stack
ldi r16, low(ramend)	; intializing the stack
out spl, r16			; intializing the stack
ldi r16,0b00010001		; setting light indicators up as output
out ddrc, r16			; setting light indicators up as output
cbi ddra, dda1			; setting ADC1 as input
cbi porta, porta1		; disabling pull-up resistor in ADC1
ldi r16, 0b01100001		; setting reference, left shifting, and MUX selecting ADC1
sts admux, r16			; setting reference, left shifting, and MUX selecting ADC1
ldi r16, 0b10000011		; enabling adc and setting division factor to 8
sts adcsra, r16			; enabling adc and setting division factor to 8
sbi ddrd, ddd4			; priming PWM2
cbi portd, portd4		; motor is off
sbi ddrc, ddc3			; priming DIR2
ldi r16, 0b00100010		; doubling transmission speed
sts ucsr1a, r16			; doubling transmission speed
ldi r16, 0b10011000		; enabling RX, its interrupt, and TX
sts ucsr1b, r16			; enabling RX, its interrupt, and TX
sei						; enabling global interrups
ldi r16, 0x0c			; setting baud rate
sts ubrr1l, r16			; setting baud rate

	standBy: 
	cbi portd, portd4	; turn motor off
	sbi portc, portc0	; set lights up in Standby mode
	sbi portc, portc4	; set lights up in Standby mode
	jmp standBy			; looping in Standby mode

	rxc:				; Receive complete - routine
	lds r19, udr1		; read data register
	cpi r19, 0xf0		; check if received value is the close command (0xf0)
	breq close			; close if the close command has been received
	cpi r19, 0x0f		; check if received value is the open command (0x0f)
	breq open			; open if the close command has been received
	jmp rxc				; looping in receive complete routine until valid command is received

	close:
		ldi r16, 0b00001000		; disabling RX and its interrupt, keeping TX
		sts ucsr1b, r16			; disabling RX and its interrupt, keeping TX
		cbi portc, portc0		; turn off right light
		sbi portd, portd4		; set PWM2 to turn motor on
		sbi portc, portc3		; set DIR2 to close gripper

		ldi r18, 0x10			; starting a waiting loop to let the motor get...
		closeLoop0:				; ...up to speed, so that the code does not...
			ldi r28, 0xff		; ... stop the motor prematurely
			closeLoop1:
				ldi r29, 0xff
				closeLoop2:
					dec r29
					brne closeLoop2
					dec r28
					brne closeLoop1
					dec r18
					brne closeLoop0

		newClose:
		ldi r16, 0b11000011		; starting adc conversion
		sts adcsra, r16			; starting adc conversion
		closeConversion:
			lds r16, adcsra			; looping until conversion is completed
			andi r16, 0b01000000	; looping until conversion is completed
			cpi r16, 0b01000000		; looping until conversion is completed
			brne closeContinue		; Continue if conversion is completed
			jmp closeConversion		; looping until conversion is completed
		closeContinue:
		lds r16, adch			; reading adc conversion value
		subi r16, 0x90			; checking if the closing voltage threshold has been reached
		brcs newClose			; if closing voltage thresold has not been reached, start new conversion
		ldi r17, 69				; if threshold has been reached, send "closing done" message (decimal 69)
		sts udr1, r17			; if threshold has been reached, send "closing done" message (decimal 69)
		ldi r16, 0b10011000		; re-enabling RX and its interrupt
		sts ucsr1b, r16			; re-enabling RX and its interrupt
		reti					; returning to standby

	open:
		ldi r16, 0b00001000		; disabling RX and its interrupt, keeping TX
		sts ucsr1b, r16			; disabling RX and its interrupt, keeping TX
		cbi portc, portc4		; turn off left light
		sbi portd, portd4		; set PWM2 to turn motor on
		cbi portc, portc3		; set DIR2 to open gripper

		ldi r18, 0x10			; starting a waiting loop to let the motor get...
		openLoop0:				; ...up to speed, so that the code does not...
			ldi r28, 0xff		; ... stop the motor prematurely
			openLoop1:
				ldi r29, 0xff
				openLoop2:
					dec r29
					brne openLoop2
					dec r28
					brne openLoop1
					dec r18
					brne openLoop0

		newOpen:
		ldi r16, 0b11000011		; starting adc conversion
		sts adcsra, r16			; starting adc conversion
		openConversion:
			lds r16, adcsra			; looping until conversion is completed
			andi r16, 0b01000000	; looping until conversion is completed
			cpi r16, 0b01000000		; looping until conversion is completed
			brne openContinue		; Continue if conversion is completed
			jmp openConversion		; looping until conversion is completed
		openContinue:
		lds r16, adch				; reading adc conversion value
		subi r16, 0x6f				; checking if the opening voltage threshold has been reached
		brcc newOpen				; if opening voltage thresold has not been reached, start new conversion
		ldi r17, 42					; if threshold has been reached, send "opening done" message (decimal 42)
		sts udr1, r17				; if threshold has been reached, send "opening done" message (decimal 42)
		ldi r16, 0b10011000			; re-enabling RX and its interrupt
		sts ucsr1b, r16				; re-enabling RX and its interrupt
		reti						; returning to standby