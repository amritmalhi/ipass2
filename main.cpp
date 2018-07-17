#include "hwlib.hpp"

int main( void ) {
	WDT->WDT_MR = WDT_MR_WDDIS;

	namespace target = hwlib::target;
}
