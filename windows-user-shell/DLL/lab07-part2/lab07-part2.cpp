// lab07-part2.cpp : Defines the exported functions for the DLL.
//

#include "framework.h"
#include "lab07-part2.h"


// This is an example of an exported variable
LAB07PART2_API int nlab07part2=0;

// This is an example of an exported function.
LAB07PART2_API int fnlab07part2(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
Clab07part2::Clab07part2()
{
    return;
}
