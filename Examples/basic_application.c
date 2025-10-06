#include <stdio.h>
#include <stdlib.h>

#include "ludix.h"

int main()
{
    window_init("Basic Application", 800, 600);

    while (!window_is_closing())
    {
        begin_main_loop();

        end_main_loop();
    }

    return EXIT_SUCCESS;
}
