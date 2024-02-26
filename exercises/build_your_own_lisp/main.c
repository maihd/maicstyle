#include <stdio.h>
#include <stdlib.h>
#include <isocline.h>

int main()
{
    printf("Lisp v0.0.3\n");
    printf("Press Ctrl+C to exit!\n");

    while (1)
    {
        char* input = ic_readline("lisp");
        ic_history_add(input);

        printf("No you're a %s\n", input);

        free(input);
    }

    return 0;
}

//! EOF


