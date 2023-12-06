/* Author : Yoganand Kanhed
more here : http://www.catb.org/esr/structure-packing/

Q. What is structural padding & packking in C++?

In C++, structural padding and packing are techniques used to control the memory layout and alignment of data structures, especially when working with structures and classes. These techniques are primarily used to ensure that data structures are stored efficiently in memory, both in terms of space and access speed. Let's explore both concepts:

1. **Structural Padding**:
   - Structural padding refers to the unused bytes that may be inserted by the compiler between members of a struct or class to ensure that each member is properly aligned in memory.
   - Alignment is crucial for performance reasons because some hardware architectures require that certain data types (e.g., doubles or 4-byte integers) be stored at addresses that are multiples of their size. Failing to align data properly can lead to performance penalties or even program crashes on certain architectures.
   - The size and placement of padding bytes are determined by the compiler and the target architecture. It can vary between different compilers and platforms.
   - You can reduce structural padding by reordering the members within a struct or class, although this may make your code less readable.

Example of structural padding:


struct ExampleStruct {
    char a;      // 1 byte
    int b;       // 4 bytes (assuming 4-byte int)
    double c;    // 8 bytes (assuming 8-byte double)
};


In this example, there may be padding bytes inserted between `a`, `b`, and `c` to ensure proper alignment.

2. **Packing**:
   - Packing, or structure packing, is a technique used to control the alignment and padding of data structures manually. It involves specifying how data should be laid out in memory explicitly.
   - In C++, you can use compiler-specific pragmas or attributes to control packing. For example, in GCC, you can use `__attribute__((packed))` to indicate that a structure should have no padding between members.
   - Be cautious when using packing because it can lead to unaligned memory access, which can be slower and, on some architectures, result in crashes or undefined behavior.

Example of structure packing using GCC:


#pragma pack(push, 1)  // Set packing to 1 byte alignment
struct PackedStruct {
    char a;      // 1 byte
    int b;       // 4 bytes
    double c;    // 8 bytes
};
#pragma pack(pop)     // Restore the previous packing setting


In this example, `#pragma pack(push, 1)` specifies 1-byte packing, so there will be no padding bytes between the members.

Structural padding and packing are advanced topics that you should use with care. It's often best to rely on the default behavior of the compiler for most cases, as modern compilers are usually quite efficient in optimizing memory layout. However, in certain situations where memory layout is critical for performance or interoperability with external systems, these techniques can be valuable.

*/

#include <iostream>

#pragma pack(push, 1) // 1 byte packing enabled here(7 bytes)
class sampleClass
{
    char a;
    char b;
    int d; // 12 bytes  ( 4 byte word padded)
    char c;
    // int d; 8 bytes
};
#pragma pack(pop)

class sampleClass1
{
    char a; // a and b here takes 4 bytes
    char b;
    int d;  // 4 bytes
    char c; // 4 bytes
    // int d; 8 bytes
};

class sampleClass2
{
    int d;  // 4 bytes
    char a; // a and b  c here takes 4 bytes
    char b;
    char c;
    // int d; 8 bytes
};

// integer starts from the memory address divisible by 4, char can take anywhere.
// class is structured and padded based on largest data type

int main()
{
    std::cout << "Size of the sample class :" << sizeof(sampleClass) << std::endl;
    std::cout << "Size of the sample class1 :" << sizeof(sampleClass1) << std::endl;
    std::cout << "Size of the sample class1 :" << sizeof(sampleClass2) << std::endl;
    return 0;
}

// Read more here about How processor reads memory, segmentation and paging to optimise memory access.