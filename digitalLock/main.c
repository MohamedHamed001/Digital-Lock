#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

// LCD pin definitions
#define LCD_RS PB0
#define LCD_E PB1
#define LCD_D4 PB2
#define LCD_D5 PB3
#define LCD_D6 PB4
#define LCD_D7 PB5

// Servo and buzzer definitions
#define SERVO_PORT PB6
#define BUZZER_PORT PB7

// Keypad pin definitions
#define ROW0 PD0
#define ROW1 PD1
#define ROW2 PD2
#define ROW3 PD3
#define COL0 PD4
#define COL1 PD5
#define COL2 PD6

// Function prototypes
void initLCD();
void lcdCommand(uint8_t cmd);
void lcdData(uint8_t data);
void lcdPrint(const char* str);
int readKeypad();
void servoMove(int angle);
void buzzerAlert();

// Global variables
const char passcode[] = "1234"; // Define your passcode here
char input[5];
int inputIndex = 0;

int main() {
	// Initialize ports
	DDRB = 0xFF;  // Set PORTB as output
	DDRD = 0x0F;  // Set PD0 to PD3 as output (rows), PD4 to PD6 as input (columns)
	PORTD = 0xF0; // Enable pull-up resistors for PD4 to PD6

	// Initialize the LCD
	initLCD();

	// Set the initial lock status (locked)
	lcdPrint("LOCKED");

	// Initialize the servo (setting to default position)
	servoMove(0);

	while (1) {
		// Read input from the keypad
		int key = readKeypad();

		if (key != 0) { // If a key is pressed
			if (key == 11) { // '*' key for reset
				inputIndex = 0;
				memset(input, 0, sizeof(input));
				lcdPrint("RESET");
				_delay_ms(500);
				lcdPrint("LOCKED");
				} else if (key == 12) { // '#' key for enter
				input[inputIndex] = '\0'; // Null-terminate the input string
				if (strcmp(input, passcode) == 0) {
					lcdPrint("UNLOCKED");
					servoMove(90);
					} else {
					lcdPrint("WRONG");
					buzzerAlert();
					_delay_ms(500);
					lcdPrint("LOCKED");
				}
				inputIndex = 0;
				memset(input, 0, sizeof(input));
				} else {
				if (inputIndex < 4) { // Only accept up to 4 digits
					input[inputIndex++] = '0' + key;
					lcdData('*'); // Display '*' for each digit entered
				}
			}
		}

		_delay_ms(200); // Debounce delay
	}
}

void initLCD() {
	// Set LCD to 4-bit mode
	_delay_ms(20);
	lcdCommand(0x02); // Initialize in 4-bit mode
	lcdCommand(0x28); // 2 lines, 5x7 matrix
	lcdCommand(0x0C); // Display on, cursor off
	lcdCommand(0x06); // Increment cursor
	lcdCommand(0x01); // Clear display
	_delay_ms(2);
}

void lcdCommand(uint8_t cmd) {
	PORTB = (cmd & 0xF0) | (1 << LCD_E);
	PORTB &= ~(1 << LCD_RS);
	PORTB &= ~(1 << LCD_E);
	_delay_ms(2);
	
	PORTB = ((cmd << 4) & 0xF0) | (1 << LCD_E);
	PORTB &= ~(1 << LCD_RS);
	PORTB &= ~(1 << LCD_E);
	_delay_ms(2);
}

void lcdData(uint8_t data) {
	PORTB = (data & 0xF0) | (1 << LCD_E) | (1 << LCD_RS);
	PORTB &= ~(1 << LCD_E);
	_delay_ms(2);
	
	PORTB = ((data << 4) & 0xF0) | (1 << LCD_E) | (1 << LCD_RS);
	PORTB &= ~(1 << LCD_E);
	_delay_ms(2);
}

void lcdPrint(const char* str) {
	lcdCommand(0x01); // Clear display
	while (*str) {
		lcdData(*str++);
	}
}

int readKeypad() {
	for (int row = 0; row < 4; row++) {
		PORTD = ~(1 << row); // Set row low
		_delay_us(5); // Wait for signal stabilization

		for (int col = 0; col < 3; col++) {
			if (!(PIND & (1 << (col + 4)))) {
				// Return the key number based on row and column
				if (row == 3) {
					if (col == 0) return 11; // '*' key
					if (col == 2) return 12; // '#' key
				}
				return row * 3 + col + 1;
			}
		}
	}
	return 0; // No key pressed
}

void servoMove(int angle) {
	// Generate PWM signal for the servo
	// Assumes a servo that operates with 1ms to 2ms pulse width for 0 to 180 degrees
	// You will need to adjust based on your specific servo specifications
	int pulseWidth = 1000 + (angle * 1000 / 180); // Calculate pulse width
	for (int i = 0; i < 50; i++) {
		PORTB |= (1 << SERVO_PORT);
		for (int j = 0; j < pulseWidth; j++) _delay_us(1); // Busy wait
		PORTB &= ~(1 << SERVO_PORT);
		for (int j = 0; j < (20000 - pulseWidth); j++) _delay_us(1); // Busy wait
	}
}

void buzzerAlert() {
	for (int i = 0; i < 3; i++) {
		PORTB |= (1 << BUZZER_PORT);
		_delay_ms(100);
		PORTB &= ~(1 << BUZZER_PORT);
		_delay_ms(100);
	}
}
