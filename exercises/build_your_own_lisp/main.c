#include <stdio.h>

int main()
{
    printf("Lisp v0.1\n");
    printf("Press Ctrl+C to exit!\n");

    while (1)
    {
        printf("lisp> ");

        char input[1024];
        fgets(input, sizeof(input), stdin);

        printf("No you're %s\n", input);
    }

    return 0;
}

//! EOF


