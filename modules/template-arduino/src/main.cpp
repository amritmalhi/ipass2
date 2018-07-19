#include "wrap-hwlib.hpp"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;

    hwlib::wait_ms(1000);
    hwlib::cout << "Hello world!" << hwlib::endl;

    // hwlib::target::pin_out a = hwlib::target::pin_out(hwlib::target::pins::d10);

    return 0;
}
