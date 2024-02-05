#include <cstring>
#include <iostream>

float my_ceil(float f)
{
    unsigned input;
    memcpy(&input, &f, 4);
    int exponent = ((input >> 23) & 255) - 127;
    std::cout << "The exponent is " << exponent << std::endl;

    if (exponent < 0)
        return (f > 0);
    // small numbers get rounded to 0 or 1, depending on their sign

    int fractional_bits = 23 - exponent;
    std::cout << "The number of fractional bits is " << fractional_bits << std::endl;

    if (fractional_bits <= 0)
        return f;
    // numbers without fractional bits are mapped to themselves

    unsigned integral_mask = 0xffffffff << fractional_bits;
    unsigned output = input & integral_mask;
    // round the number down by masking out the fractional bits

    memcpy(&f, &output, 4);
    if (f > 0 && output != input)
        ++f;
    // positive numbers need to be rounded up, not down

    return f;
}

int main()
{
    float f = 0.5;
    float ceiling = my_ceil(f);
    std::cout << "The ceiling of " << f << " is " << ceiling << std::endl;
    return 0;
}