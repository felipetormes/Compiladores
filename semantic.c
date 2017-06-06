//Cássio de Abreu Ramos, Felipe Barbosa Tormes

#include <stdio.h>
#include <stdlib.h>

#include "semantic.h"

int errorCount;

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
  					fprintf(stderr,"SEMANTIC ERROR: Variable %s is already defined on line %d\n", variable->text, ast->lineNumber);
            errorCount++;
  				}
          else
          {
            variable->marked = TRUE;
            variable->declaration = ast;
            variable->nature = SCALAR;

            switch(ast->child[1]->node_type)
            {
              case TYPEBYTE:
              {
                variable->data_type = INTEGER;
                break;
              }
              case TYPESHORT:
              {
                variable->data_type = INTEGER;
                break;
              }
              case TYPELONG:
              {
                variable->data_type = INTEGER;
                break;
              }
              case TYPEFLOAT:
              {
                variable->data_type = REAL;
                break;
              }
              case TYPEDOUBLE:
              {
                variable->data_type = REAL;
                break;
              }
            }

            symbolType* literal = &(ast->child[2]->node->symbol);

            if(literal->type != variable->data_type)
            {
              char string_type[80];
              typeToString(variable->data_type,string_type);

              //fprintf(stderr,"%d\n\n", ast->child[2]->node->symbol.type);
              //fprintf(stderr,"%d\n\n", variable->data_type);

              fprintf(stderr, "SEMANTIC ERROR: Incompatible types in declaration: variable %s needs to receive a/an %s type value on line %d\n", variable->text, string_type, ast->lineNumber);
              errorCount++;
            }
          }
          break;
        }

        case ARRAYDECLARATION:
        {
          symbolType* variable = &(ast->child[0]->node->symbol);

          if(variable->marked == TRUE)
          {
            fprintf(stderr,"SEMANTIC ERROR: Variable %s is already defined on line %d\n", variable->text, ast->lineNumber);
            errorCount++;
          }
          else
          {
            variable->marked = TRUE;
            variable->declaration = ast;
            variable->nature = VECTOR;

            switch(ast->child[1]->node_type)
            {
              case TYPEBYTE:
              {
                variable->data_type = INTEGER;
                break;
              }
              case TYPESHORT:
              {
                variable->data_type = INTEGER;
                break;
              }
              case TYPELONG:
              {
                variable->data_type = INTEGER;
                break;
              }
              case TYPEFLOAT:
              {
                variable->data_type = REAL;
                break;
              }
              case TYPEDOUBLE:
              {
                variable->data_type = REAL;
                break;
              }
            }

            //astree* hues = ast->child[3]->child[0]->child[1];
            //astree* hues2 = hues->child[0];
            //astree* hues3 = hues2->child[1];

            astree* ptr = ast->child[3]->child[0];

            //fprintf(stderr, "%s\n", ptr->child[0]->child[1]->node->symbol.text);

            if(ptr != NULL)
            {
              if(ptr->child[1] == NULL)
              {
                ptr = ptr->child[0];
              }

              int expected_literal_count = ast->child[2]->node->symbol.value.intLit;
              int literal_count = 0;

              while(ptr != NULL)
              {

                if(ptr->child[0] == NULL)
                {
                  break;
                }

                astree* literals;

                literals = ptr->child[1];

                symbolType* literal_vector = &(literals->node->symbol);

                if(literal_vector->type != variable->data_type)
                {
                  char string_type1[80];
                  char string_type2[80];
                  typeToString(variable->data_type,string_type1);
                  typeToString(literal_vector->type,string_type2);

                  fprintf(stderr,"SEMANTIC ERROR: Expected only %s values on array %s, but found %s instead on line %d\n", string_type1, variable->text, string_type2, ast->lineNumber);
                  errorCount++;
                }

                literal_count++;
                ptr = ptr->child[0];
              }

              if(expected_literal_count != literal_count)
              {
                fprintf(stderr,"SEMANTIC ERROR: Expected %d literals on array %s, but found %d instead on line %d\n", expected_literal_count, variable->text, literal_count, ast->lineNumber);
                errorCount++;
              }
            }
          }
        }

        case FUNCTIONDEFINITION:
        {
          astree* function = ast->child[0]->child[1];

          if(function->node->symbol.marked == TRUE)
          {
            fprintf(stderr,"SEMANTIC ERROR: Function %s is already defined on line %d\n", function->node->symbol.text, ast->lineNumber);
          }

          else
          {
            function->node->symbol.marked = TRUE;
            function->node->symbol.data_type = FUNCTION_TYPE;
            function->node->symbol.declaration = ast;
            function->node->symbol.nature = FUNCTION;

            astree* returnType = ast->child[0]->child[0];

            switch(returnType->node_type)
            {
              case TYPEBYTE:
              {
                function->node->symbol.returnType = INTEGER;
                break;
              }
              case TYPESHORT:
              {
                function->node->symbol.returnType = INTEGER;
                break;
              }
              case TYPELONG:
              {
                function->node->symbol.returnType = INTEGER;
                break;
              }
              case TYPEFLOAT:
              {
                function->node->symbol.returnType = REAL;
                break;
              }
              case TYPEDOUBLE:
              {
                function->node->symbol.returnType = REAL;
                break;
              }
            }
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

void typeToString(int type, char* str)
{
  switch(type)
  {
    case INTEGER:
    {
      sprintf(str,"INTEGER");
      break;
    }
    case REAL:
    {
      sprintf(str,"REAL");
      break;
    }
    case NO_TYPE:
    {
      sprintf(str,"NO TYPE");
      break;
    }
    case FUNCTION_TYPE:
    {
      sprintf(str,"FUNCTION TYPE");
      break;
    }
  }
}

int compatible(dataType t0, dataType t1)
{
    if (t0 == INTEGER && t1 == INTEGER)
        return 1;
    if (t0 == REAL && t1 == REAL)
        return 1;
    return 0;
}

int same_types(astree* parameter, astree* argument)
{
    astree* identifier;
    astree* expr;
    if (parameter->child[2] == NULL)
        identifier = parameter->child[1];
    else
        identifier = parameter->child[2];
    if (argument->child[1] == NULL)
        expr = argument->child[0];
    else
        expr = argument->child[1];
    dataType par = identifier->node->symbol.data_type;
    dataType arg = typeCheck(expr);
    return compatible(par,arg);
}

int typeCheck(astree* ast)
{

}
