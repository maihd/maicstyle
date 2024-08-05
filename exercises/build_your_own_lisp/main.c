#include <stdio.h>
#include <stdlib.h>

#include <mpc.h>
#include <isocline.h>


mpc_parser_t* get_parser(void);


int main(int argc, const char* argv[])
{
    printf("Lisp v0.0.4\n");
    printf("Press Ctrl+C to exit!\n");
    
    while (1)
    {
        char* input = ic_readline("lisp");
        
        // When Ctrl+C, ic_readline return NULL
        // @todo(maihd): use nullptr to more maicstyle
        if (input == NULL)
        {
            break;
        }
        
        // Add history
        // @bug(maihd): can use up arrow to use history
        ic_history_add(input);
        
        // Simple print
        printf("No you're a %s\n", input);
        
        // `input` was malloc by ic_readline
        free(input);
    }
    
    return 0;
}


mpc_parser_t* get_parser(void)
{
    mpc_parser_t* Adjective = 
        mpc_or(4,
               mpc_sym("wow"), mpc_sym("many"),
               mpc_sym("so"), mpc_sym("such") 
               );
    
    mpc_parser_t* Noun =
        mpc_or(5,
               mpc_sym("lisp"), mpc_sym("language"),
               mpc_sym("book"), mpc_sym("build"),
               mpc_sym("c")
               );
    
    mpc_parser_t* Phrase =
        mpc_or(2, 
               mpcf_strfold,
               Adjective,
               Noun,
               free);
    
    mpc_parser_t* Doge = mpc_many(mpcf_strfold, Phrase);
    
    return Doge;
}


//! EOF


