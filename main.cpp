/**
 * use base -1 for ascii 
 * 
 */
#include <iostream>
#include <string>
#include <cstring>
#include <math.h>
#include <stdbool.h>


std::string dec_to_any(unsigned int number, int base, bool debug = false) {
    if(base < 2) {
        return std::string("invalid base: ") += std::to_string(base);
    }

    if(debug) std::cout << "converting " << number << " to base " << base << std::endl;    
    int num_of_digits;
    for(int i=0;; i++) {
        if(pow(base, i) > number) {
            num_of_digits = i;
            break;
        }
    }
    if(debug) std::cout << num_of_digits << " digits required" << std::endl;

    std::string result;

    unsigned int num = 0;
    for(int i=num_of_digits-1; i>=0; i--) {
        if(debug) std::cout << "i: " << i << std::endl;
        if(debug) std::cout << "num: " << num << std::endl;

        if(debug) std::cout << "pow(base, i) = " << pow(base, i) << std::endl;

        int j = 0;
        while(num + pow(base, i) <= number) {
            j++;
            num += pow(base, i);
        }

        result += j<10 ? std::to_string(j) : std::string(1, (char)('A'+j-10));
    }

    if(debug) std::cout << "final num: " << num << std::endl;
    if(debug) std::cout << "base " << base << ": " << result << std::endl;

    return result;
}

unsigned int any_to_dec(std::string number, int base, bool debug);
unsigned int any_to_dec(std::string number, bool debug = false) {
    std::string get_base = number.substr(0,2);
    if(debug) std::cout << "base: " << get_base << std::endl;

    if(get_base == "0b") {
        return any_to_dec(number.substr(2, number.size()), 2, debug);
    }
    if(get_base == "0x") {
        return any_to_dec(number.substr(2, number.size()), 16, debug);
    }

    std::cout << "unknown prefix: " << get_base << std::endl;
    return -1;
}

unsigned int any_to_dec(std::string number, int base, bool debug = false) {
    if(base < 2) {
        return -1;
    }    
    if(debug) std::cout << "converting " << number << " from base: " << base << std::endl;

    unsigned int result = 0;

    for(int i=0; i<number.length(); i++) {
        int num;
        if(number[i] >= '0' && number[i] <= '9') {
            num = number[i]-'0';
        } else if(number[i] >= 'A' && number[i] <= 'F') {
            num = number[i]-'A'+10;
        } else {
            std::cout << "invalid char: " << number[i] << " max range is hex/0x (0-F)" << std::endl;
            return -1;
        }
        for(int j=0; j<num; j++) {
            result += pow(base, number.length()-i-1);
        }
    }

    if(debug) std::cout << "result: " << result << std::endl;
    return result;
}


std::string any_to_any(std::string number_in, int base_in, int base_out, bool debug = false) {
    unsigned int num_dec = any_to_dec(number_in, base_in);
    std::string result = dec_to_any(num_dec, base_out, debug);
    return result;
}

int get_base_from_string(std::string base) {
    if(base == "ascii" || base == "ASCII")
        return 10;
    return atoi(base.c_str());
}

int main(int argc, char* argv[]) {

    #if 0
    std::cout << "328, 4: " << dec_to_any(328, 4) << std::endl;
    std::cout << "328, 2: " << dec_to_any(328, 2) << std::endl;
    std::cout << "12, 16: " << dec_to_any(12, 16) << std::endl;
    std::cout << "654654, 16: " << dec_to_any(654654, 16) << std::endl;
    #endif

    #if 0
    std::cout << "11020, 4: " << any_to_dec("11020", 4) << std::endl;
    std::cout << "101001000, 2: " << any_to_dec("101001000", 2) << std::endl;
    std::cout << "9FD3E, 16: " << any_to_dec("9FD3E", 16) << std::endl;
    std::cout << "0xFFFFFF: " << any_to_dec("0xFFFFFF") << std::endl;
    std::cout << "0xFFFFFFF: " << any_to_dec("0xFFFFFFF") << std::endl;
    std::cout << "0xFFFFFFFF: " << any_to_dec("0xFFFFFFFF") << std::endl;
    #endif

    #if 0
    std::cout << "164523, 7 -> 14: " << any_to_any("164523", 7, 14) << std::endl;
    std::cout << "BD83, 14 -> 3: " << any_to_any("BD83", 14, 3) << std::endl;
    std::cout << "1200001120, 3 -> 2: " << any_to_any("1200001120", 3, 2) << std::endl;
    std::cout << "1000000001001111, 2 -> 7: " << any_to_any("1000000001001111", 2, 7) << std::endl;
    #endif
    
    std::string input_number;
    int input_base;
    int target_base;

    std::cout << "argc: " << argc << std::endl;
    std::cout << "make sure your number does not exceed 0d2^32 / 0xFFFFFFFF" << std::endl;


    bool get_input = false;
    if(argc == 1) get_input = true;
    while(get_input) {
        std::cout << "enter number: ";
        std::cin >> input_number;

        std::cout << "enter base: ";
        std::cin >> input_base;
        
        std::cout << "enter target base: ";
        std::cin >> target_base;

        std::cout << any_to_any(input_number, input_base, target_base) << std::endl;

    }
    
    if(argc != 4) {
        std::cout << "invalid arg-length: ./main \"your number\" base_of_number target_base" << std::endl;
        return 0;
    }



    return 0;
}