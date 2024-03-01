#include "gtest/gtest.h"

extern "C" {
#include <LogicOperation.h>
#include <avr/io.h>
}

class LogicOperationTest : public ::testing::Test {
protected:

	void SetUp() override {
		init_Application();
	}

	void TearDown() override {

	}
};

// Testing if init is ok 
TEST_F(LogicOperationTest, TEST_PORT_DDR_Init) {
	
	EXPECT_EQ(PORTC, 0xff);
	EXPECT_EQ(DDRC, 0x00);

	EXPECT_EQ(PORTA, 0xff);
	EXPECT_EQ(DDRA, 0xff);
}

// Both pin is 0 so NAND, NOR , XNOR is on 
TEST_F(LogicOperationTest, TEST_Both_PIN_OFF) {
	// Mock 
	// HardCode NO pin Pressed 
	PINC = 0xff;

	// Comand 

	run_Operators();

	// Assert 
	// Want to see if led  is turned on 
	// Led 4,5,6
	// 1100 0111 = C7 
	EXPECT_EQ(PORTA , 0xC7);
}

TEST_F(LogicOperationTest, TEST_KEY1_Pressed) {
	// HardCode all pin to not pressed 
	PINC = 0xff;

	// Mock 
	// set pin0 / KEY1  to be pressed 
	PINC = 0xfe;

	run_Operators();
	
	// Assert 
	// LED 2 ,3 , 4 should be on 
	// 1111 0001
	EXPECT_EQ(PORTA, 0xF1);
}

TEST_F(LogicOperationTest, TEST_BOTH_KEY_Pressed) {
	// HardCode all pin to not pressed 
	PINC = 0xff;
	PORTA = 0xff;
	// Mock 
	// set KEY 1 and Key 2  to be pressed  -- 1111 1100
	PINC = 0xfc;

	run_Operators();

	// Assert 
	// LED 1,2,6  should be on 
	// 1101 1100
	EXPECT_EQ(PORTA, 0xdc);

}

