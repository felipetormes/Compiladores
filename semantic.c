//Cássio de Abreu Ramos, Felipe Barbosa Tormes

#include <stdio.h>
#include <stdlib.h>

#include "semantic.h"

void first_pass(astree* ast)
{
  if(ast == NULL)
  	{
  		return;
  	}
    else
  	{
  		switch(ast->node_type)
  		{
  			case DECLARATION:
        {
          symbolType* variable = &(ast->child[0]->node->symbol);

          if(variable->marked == TRUE)
  				{
  					fprintf(stderr,"(SEMANTIC) Variable > %s < is already defined on line %d\n", variable->text, ast->lineNumber);
  				}
          else
          {
            variable->marked = TRUE;
          }
          break;
        }
        default:
  			{
  				first_pass(ast->child[0]);
  				first_pass(ast->child[1]);
  				first_pass(ast->child[2]);
  				first_pass(ast->child[3]);

  				break;
  			}
      }
    }
}
