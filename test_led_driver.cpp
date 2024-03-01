#include "gtest/gtest.h"

extern "C" {
#include "led_driver.h"
#include <avr/io.h>
}

class LedDriverTest : public ::testing::Test {
protected:

	void SetUp() override {
		init_leds();
	}

	void TearDown() override {

	}
};

// Init test 
TEST_F(LedDriverTest, TestInitLEDS_DDR_Set_To_Output) {
	EXPECT_EQ(DDRA, 0xff);
}

TEST_F(LedDriverTest, TestInit_leds_off_after_int) {
	EXPECT_EQ(PORTA, 0xff);
}

TEST_F(LedDriverTest, IsValidRange_ValidRangeReturnsTrue) {
	EXPECT_TRUE(isvalidRange(1)); // Check lower bound
	EXPECT_TRUE(isvalidRange(8)); // Check upper bound
	EXPECT_FALSE(isvalidRange(0)); // Below valid range
	EXPECT_FALSE(isvalidRange(9)); // Above valid range
}

TEST_F(LedDriverTest, SetLed_ValidLedTurnsOn) {
	// Turn on LED 1
	set_led(1, true); 
	// Expect LED 1 to be turned on (PORTA = 1111 1110)
	EXPECT_EQ(PORTA, 0xfe); 
	// Checks if PA0 bit in PORTA is cleared
	EXPECT_EQ(PORTA & _BV(PA0), 0); 
}

TEST_F(LedDriverTest, SetLed_ValidLedTurnsOff) {
	// Setting all led to ON to test if led will be off 
	PORTA = 0x00; 
	// Turn of led 1 
	set_led(1, false);
	// Now LED one will be only turned off -- PORTA = 0000 0001
	EXPECT_EQ(PORTA, 0x01); 
	EXPECT_EQ(1, _BV(PORTA0));
}

TEST_F(LedDriverTest, SetLed4_LedTurnsOnn) {
	// Setting all led to ON to test if led will be off 
	PORTA = 0xff;
	// Turn of led 1 
	set_led(4, true);
	// Now LED one will be only turned on -- PORTA = 1111 0111
	EXPECT_EQ(PORTA, 0xF7);
	EXPECT_EQ(PORTA & _BV(PA3), 0);
}
