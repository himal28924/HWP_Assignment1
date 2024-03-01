#include "gtest/gtest.h"

extern "C" {
#include "key_input_driver.h"
#include <avr/io.h>
}

class KeyDriverTest : public ::testing::Test {
protected:

	void SetUp() override {
		init_keys();
	}

	void TearDown() override {

	}
};


// init test 

TEST_F(KeyDriverTest, Test_InitKeys_DDR_Set_To_Input) {

	EXPECT_EQ(DDRC, 0x00);
}

TEST_F(KeyDriverTest, Test_InitKeys_Port_Enabled) {
	EXPECT_EQ(PORTC, 0xff);
}

// when no key is pressed 
TEST_F(KeyDriverTest, TEST_Zero_Keys_Pressed) {
	// Mock PinC
	PINC = 0;

	// Hardcode No Pin Pressed 
	PINC = 0xff;

    // for each pin looking if it is false 
    for (uint8_t i = 1; i <= 6; i++) {
        ASSERT_FALSE(get_key(i));
    }
}

// When only one key is pressed 
TEST_F(KeyDriverTest, TEST_One_Key_Pressed) {
	
	// Mock PinC
	PINC = 0;

	// HardcodeKey 3 is pressed
	PINC = ~(1 << 2);
	

	// Checking if 3 is pressed and any other than 3 is pressed or not 
	for (uint8_t i = 1; i <= 6; i++) {
		if (i != 3) {
			ASSERT_FALSE(get_key(i));
		}
		else {
			ASSERT_TRUE(get_key(3));
		}
	}
}

// Many keys are presed 
TEST_F(KeyDriverTest, TEST_Multiple_Keys_Pressed) {

	// Mock PinC
	PINC = 0;

	// Hardcode Key  2 and 4 as pressed
	PINC = ~((1 << (2 - 1)) | (1 << (4 - 1)));

	// Testing 
	ASSERT_TRUE(get_key(2));
	ASSERT_TRUE(get_key(4));
	// Keys 1, 5, 6 are not pressed
	ASSERT_FALSE(get_key(1));
	ASSERT_FALSE(get_key(5));
	ASSERT_FALSE(get_key(6));
}


// Testing for Boundry 
TEST_F(KeyDriverTest, TEST_Boundary_Check) {
	// Mock PinC
	PINC = 0;

	// Hard core  1 and 6 (Pin0 and 5) to check boundry 

	PINC = ~((1 << PIN0) | (1 << PIN5));
	
	ASSERT_TRUE(get_key(1));
	ASSERT_TRUE(get_key(6));

	
	// Out of range
	ASSERT_FALSE(get_key(0)); // Below valid range
	ASSERT_FALSE(get_key(7)); // Above valid range


}




