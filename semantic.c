//Cássio de Abreu Ramos, Felipe Barbosa Tormes

#include <stdio.h>
#include <stdlib.h>

#include "semantic.h"

struct symbolStruct globalScope;

struct symbolStruct* currentScope;

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
            variable->scope = &globalScope;

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
            variable->scope = &globalScope;

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

              while(ptr->child[0] != NULL)
              {
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

          break;
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
            function->node->symbol.scope = &globalScope;

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

          astree* parameters = ast->child[0]->child[2];
          astree* parameter_variable = parameters;

          while(parameter_variable != NULL)
          {

          //fprintf(stderr, "%s\n", parameter_variable->child[2]->node->symbol.text);

          switch(parameters->child[1]->node_type)
          {
            case TYPEBYTE:
              {
                parameter_variable->child[2]->node->symbol.data_type = INTEGER;
                break;
              }
              case TYPESHORT:
              {
                parameter_variable->child[2]->node->symbol.data_type = INTEGER;
                break;
              }
              case TYPELONG:
              {
                parameter_variable->child[2]->node->symbol.data_type = INTEGER;
                break;
              }
              case TYPEFLOAT:
              {
                parameter_variable->child[2]->node->symbol.data_type = REAL;
                break;
              }
              case TYPEDOUBLE:
              {
                parameter_variable->child[2]->node->symbol.data_type = REAL;
                break;
              }
          }

          parameter_variable = parameter_variable->child[0];

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
    if ((t0 == INTEGER || t0 == REAL) && (t1 == INTEGER || t1 == REAL))
        return 1;
    else
    {
      return 0;
    }
}

int same_types(astree* parameter, astree* argument)
{

    astree* identifier;
    astree* expr;
        identifier = parameter->child[2];

        expr = argument->child[0];

    dataType par = identifier->node->symbol.data_type;
    dataType arg = typeCheck(expr);

    //fprintf(stderr, "%s\n", identifier->node->symbol.text);
    //fprintf(stderr, "%s\n", expr->node->symbol.text);
    //fprintf(stderr, "%d\n", par);
    //fprintf(stderr, "%d\n", arg);
    return compatible(par,arg);
}

int checkParameters(astree* parameters, astree* arguments, int* expected, int* given)
{
  astree* parameter = parameters->child[2];
	astree* argument = arguments;
	*expected = 0;
	*given = 0;
	int types_are_correct = 1;

  while(1)
	{

    //fprintf(stderr, "%s\n", parameter->child[2]->node->symbol.text);
    //fprintf(stderr, "%s\n", argument->child[0]->node->symbol.text);
		if(parameter->child[0] == NULL || argument->child[1] == NULL)
    {
			break;
    }

		if(!same_types(parameter, argument))
		{

			types_are_correct = 0;
			break;
		}


		(*expected)++; (*given)++;

		parameter = parameter->child[0]; argument = argument->child[1];
	}

  (*expected)++; (*given)++;

	if(parameter->child[0] != NULL)
	{
    while(parameter->child[0] != NULL)
    {
      (*expected)++; parameter = parameter->child[0];
    }
	}

	if(argument->child[1] != NULL)
	{
		while(argument->child[1] != NULL)
    {
      (*given)++; argument = argument->child[1];
    }
	}

	return types_are_correct;
}

int typeCheck(astree* ast)
{
  if(ast == NULL)
	{
		return NO_TYPE;
	}

  else
	{
		switch(ast->node_type)
		{
      case IDENTIFIER:
			{
				if(ast->node->symbol.marked != TRUE)
				{
					fprintf(stderr,"SEMANTIC ERROR: Variable %s has not been defined yet on line %d\n", ast->node->symbol.text, ast->lineNumber);
          errorCount++;

					return NO_TYPE;
				}
				else if(ast->node->symbol.nature != SCALAR)
				{

					fprintf(stderr,"SEMANTIC ERROR: Value %s is not a scalar variable on line %d\n", ast->node->symbol.text, ast->lineNumber);
          errorCount++;

					return NO_TYPE;
				}
				else
				{
					return ast->node->symbol.data_type;
				}

				break;
			}

      case LITERAL:
			{
				return ast->node->symbol.type;

				break;
			}

      case ADDITION:
      {
        int t0 = typeCheck(ast->child[0]);
        int t1 = typeCheck(ast->child[1]);

        if((t0 == INTEGER && t1 == REAL) || (t0 == REAL && t1 == INTEGER))
        {
          return REAL;
        }

        else if(t0 == INTEGER && t1 == INTEGER)
        {
          return INTEGER;
        }

        else if(t0 == REAL && t1 == REAL)
        {
          return REAL;
        }

        else
        {
          fprintf(stderr, "SEMANTIC ERROR: Incompatible types for aritmetic operation on line %d\n", ast->lineNumber);
          return NO_TYPE;
        }

        break;
      }

      case SUBTRACTION:
      {
        int t0 = typeCheck(ast->child[0]);
        int t1 = typeCheck(ast->child[1]);

        if(t0 == INTEGER && t1 == REAL)
        {
          return REAL;
        }

        else if(t0 == INTEGER && t1 == INTEGER)
        {
          return INTEGER;
        }

        else if(t0 == REAL && t1 == REAL)
        {
          return REAL;
        }

        else
        {
          fprintf(stderr, "SEMANTIC ERROR: Incompatible types for aritmetic operation on line %d\n", ast->lineNumber);
          return NO_TYPE;
        }

        break;
      }

      case MULTIPLICATION:
      {
        int t0 = typeCheck(ast->child[0]);
        int t1 = typeCheck(ast->child[1]);

        if(t0 == INTEGER && t1 == REAL)
        {
          return REAL;
        }

        else if(t0 == INTEGER && t1 == INTEGER)
        {
          return INTEGER;
        }

        else if(t0 == REAL && t1 == REAL)
        {
          return REAL;
        }

        else
        {
          fprintf(stderr, "SEMANTIC ERROR: Incompatible types for aritmetic operation on line %d\n", ast->lineNumber);
          return NO_TYPE;
        }

        break;
      }

      case DIVISION:
      {
        int t0 = typeCheck(ast->child[0]);
        int t1 = typeCheck(ast->child[1]);

        if(t0 == INTEGER && t1 == REAL)
        {
          return REAL;
        }

        else if(t0 == INTEGER && t1 == INTEGER)
        {
          return INTEGER;
        }

        else if(t0 == REAL && t1 == REAL)
        {
          return REAL;
        }

        else
        {
          fprintf(stderr, "SEMANTIC ERROR: Incompatible types for aritmetic operation on line %d\n", ast->lineNumber);
          return NO_TYPE;
        }

        break;
      }

      case LESSERTHAN:
      {
        int t0 = typeCheck(ast->child[0]);
				int t1 = typeCheck(ast->child[1]);

        if(t0 == BOOL || t1 == BOOL)
        {
          fprintf(stderr, "SEMANTIC ERROR: Incompatible types for relational operation on line %d\n", ast->lineNumber);
          return NO_TYPE;
        }

        else
        {
          return BOOL;
        }

        break;
      }

      case GREATERTHAN:
      {
        int t0 = typeCheck(ast->child[0]);
				int t1 = typeCheck(ast->child[1]);

        if(t0 == BOOL || t1 == BOOL)
        {
          fprintf(stderr, "SEMANTIC ERROR: Incompatible types for relational operation on line %d\n", ast->lineNumber);
          return NO_TYPE;
        }

        else
        {
          return BOOL;
        }

        break;
      }

      case LESSEREQUAL:
      {
        int t0 = typeCheck(ast->child[0]);
				int t1 = typeCheck(ast->child[1]);

        if(t0 == BOOL || t1 == BOOL)
        {
          fprintf(stderr, "SEMANTIC ERROR: Incompatible types for relational operation on line %d\n", ast->lineNumber);
          return NO_TYPE;
        }

        else
        {
          return BOOL;
        }

        break;
      }

      case GREATEREQUAL:
      {
        int t0 = typeCheck(ast->child[0]);
				int t1 = typeCheck(ast->child[1]);

        if(t0 == BOOL || t1 == BOOL)
        {
          fprintf(stderr, "SEMANTIC ERROR: Incompatible types for relational operation on line %d\n", ast->lineNumber);
          return NO_TYPE;
        }

        else
        {
          return BOOL;
        }

        break;
      }

      case EQUAL:
      {
        int t0 = typeCheck(ast->child[0]);
				int t1 = typeCheck(ast->child[1]);

        if(t0 == BOOL || t1 == BOOL)
        {
          fprintf(stderr, "SEMANTIC ERROR: Incompatible types for relational operation on line %d\n", ast->lineNumber);
          return NO_TYPE;
        }

        else
        {
          return BOOL;
        }

        break;
      }

      case NOTEQUAL:
      {
        int t0 = typeCheck(ast->child[0]);
				int t1 = typeCheck(ast->child[1]);

        if(t0 == BOOL || t1 == BOOL)
        {
          fprintf(stderr, "SEMANTIC ERROR: Incompatible types for relational operation on line %d\n", ast->lineNumber);
          return NO_TYPE;
        }

        else
        {
          return BOOL;
        }

        break;
      }

      case AND:
      {
        int t0 = typeCheck(ast->child[0]);
				int t1 = typeCheck(ast->child[1]);

        if(t0 == BOOL || t1 == BOOL)
        {
          fprintf(stderr, "SEMANTIC ERROR: Incompatible types for relational operation on line %d\n", ast->lineNumber);
          return NO_TYPE;
        }

        else
        {
          return BOOL;
        }

        break;
      }

      case OR:
      {
        int t0 = typeCheck(ast->child[0]);
				int t1 = typeCheck(ast->child[1]);

        if(t0 == BOOL || t1 == BOOL)
        {
          fprintf(stderr, "SEMANTIC ERROR: Incompatible types for relational operation on line %d\n", ast->lineNumber);
          return NO_TYPE;
        }

        else
        {
          return BOOL;
        }

        break;
      }

      case FUNCTIONCALL:
      {

        
        symbolType* function = &(ast->child[0]->node->symbol);

        if(function->nature != FUNCTION)
				{
					fprintf(stderr,"SEMANTIC ERROR: Value %s is not a function on line %d\n", function->text, ast->lineNumber);
          errorCount++;
					return NO_TYPE;
				}

        else
				{
					int expected;
          int given;

					int types_are_correct = checkParameters(function->declaration->child[0], ast->child[1], &expected, &given);

					if(expected != given)
					{
						fprintf(stderr,"SEMANTIC ERROR: Function %s expected %d parameters, but given %d on line %d\n", function->text, expected, given, ast->lineNumber);
            errorCount++;
					}
					else if(!types_are_correct)
					{
						fprintf(stderr,"SEMANTIC ERROR: Incorrect types for parameters of function %s on line %d\n", function->text, ast->lineNumber);
            errorCount++;
					}

					return function->returnType;
				}

				break;
      }

      case ARRAYACCESS:
      {
        symbolType* vector_entry = &(ast->child[0]->node->symbol);

        if(vector_entry->nature != VECTOR)
        {
          errorCount++; fprintf(stderr,"SEMANTIC ERROR: Value %s is not an array on line %d\n", vector_entry->text, ast->lineNumber);
          return NO_TYPE;
        }

        int t1 = typeCheck(ast->child[1]);

        if(t1 != INTEGER)
        {
          errorCount++; fprintf(stderr,"SEMANTIC ERROR: Array indices must be integer types on line %d\n", ast->lineNumber);
        }
        
        return vector_entry->data_type;

        break;
      }

      case ARRAYEXPRESION:
      {
        symbolType* vector = &(ast->child[0]->node->symbol);

        if(vector->nature != VECTOR)
        {
          errorCount++; fprintf(stderr,"SEMANTIC ERROR: Value %s is not an array on line %d\n", vector->text, ast->lineNumber);
          return NO_TYPE;
        }

        int index_type = typeCheck(ast->child[1]);

        if(index_type != INTEGER)
        {
          errorCount++; fprintf(stderr,"SEMANTIC ERROR: Array index is not a integer value on line %d\n", ast->lineNumber);
        }
      }
    }
  }
}

int verify(astree* ast)
{
  if(ast == NULL)
	{
		return FALSE;
	}
	else
	{

		switch(ast->node_type)
    {
			case IDENTIFIER:
			case LITERAL:
			case ADDITION:
			case SUBTRACTION:
			case MULTIPLICATION:
			case DIVISION:
			case LESSERTHAN:
			case GREATERTHAN:
			case LESSEREQUAL:
			case GREATEREQUAL:
			case EQUAL:
			case NOTEQUAL:
			case AND:
			case OR:
			case FUNCTIONCALL:
			{
				return typeCheck(ast) != NO_TYPE;

				break;
			}

      case RETURN:
      {
        int return_type = typeCheck(ast->child[0]);

        if(return_type != currentScope->returnType)
        {
          char t0str[80];
          char t1str[80];

          typeToString(return_type,t0str);
          typeToString(currentScope->returnType,t1str);

          errorCount++; fprintf(stderr,"SEMANTIC ERROR: Incompatible return type %s on function %s on line %d\n", t1str, currentScope->text, ast->lineNumber);
        }

        currentScope = &globalScope;

        break;
      }

      case PRINTLIST:
      {
        if(ast->child[0] == NULL)
          return TRUE;
        else if(ast->child[1] == NULL)
          return typeCheck(ast->child[0]) != NO_TYPE;
        else
        {
          dataType t = typeCheck(ast->child[1]);
          int restIsCorrect = verify(ast->child[0]);

          return t != NO_TYPE && restIsCorrect;
        }
        break;
      }

      case PRINT:
      {
        return verify(ast->child[0]);

        break;
      }

      case READ:
      {
        dataType t = typeCheck(ast->child[0]);

        if(ast->child[0]->node->symbol.nature != SCALAR)
        {
          errorCount++; fprintf(stderr,"SEMANTIC ERROR: Input must use a scalar variable on line %d\n", ast->lineNumber);
          return FALSE;
        }

        return t;
        break;
      }

      case WHENTHEN:
      {
        dataType t = typeCheck(ast->child[0]);
        
        if(t != BOOL)
        {
          char tstr[80];
          typeToString(t, tstr);

          errorCount++; fprintf(stderr,"SEMANTIC ERROR: Expected boolean expression in condition, got %s instead on line %d\n", tstr, ast->lineNumber);
          return FALSE;
        }
        
        if(verify(ast->child[1]))
        {
          return TRUE;
        }
        else
        {
          return FALSE;
        }

        break;
      }

      case WHENTHENELSE:
      {
        dataType t = typeCheck(ast->child[0]);
        
        if(t != BOOL)
        {
          char tstr[80];
          typeToString(t, tstr);

          errorCount++; fprintf(stderr,"SEMANTIC ERROR: Expected boolean expression in condition, got %s instead on line %d\n", tstr, ast->lineNumber);
          return FALSE;
        }
        
        if(verify(ast->child[1]) && verify(ast->child[2]))
        {
          return TRUE;
        }
        else
        {
          return FALSE;
        }

        break;
      }

      case WHILE:
      {
        dataType t = typeCheck(ast->child[0]);
        
        if(t != BOOL)
        {
          char tstr[80];
          typeToString(t, tstr);

          errorCount++; fprintf(stderr,"SEMANTIC ERROR: Expected boolean expression in condition, got %s instead on line %d\n", tstr, ast->lineNumber);
          return FALSE;
        }
        
        if(verify(ast->child[1]))
        {
          return TRUE;
        }
        else
        {
          return FALSE;
        }

        break;
      }

      case FOR:
      {

        if(verify(ast->child[0]) && verify(ast->child[2]))
        {
          return TRUE;
        }
        else
        {
          return FALSE;
        }
      }

      case ASSIGNMENT:
			{
				dataType varType = typeCheck(ast->child[0]);
				dataType valType = typeCheck(ast->child[1]);

				if(varType != NO_TYPE && valType != NO_TYPE && !compatible(varType, valType))
				{
					char t0str[80];
					char t1str[80];
					typeToString(varType,t0str);
					typeToString(valType,t1str);

					errorCount++; fprintf(stderr,"SEMANTIC ERROR: Incompatible type in assignment: %s = %s on line %d\n", t0str, t1str, ast->lineNumber);
					return FALSE;
				}

				return TRUE;

				break;
			}

      case COMMANDLIST:
			{
				if(ast->child[0] == NULL)
					return TRUE;
				else if(ast->child[1] == NULL)
					return verify(ast->child[0]);
				else
				{
					int firstAreCorrect = verify(ast->child[0]);
					int lastIsCorrect = verify(ast->child[1]);

					return firstAreCorrect && lastIsCorrect;
				}
				break;
			}

      case BLOCK:
			{
				return verify(ast->child[0]);
				break;
			}

      case FUNCTIONDEFINITION:
      {

        currentScope = &(ast->child[0]->child[1]->node->symbol);

        return verify(ast->child[1]);

				break;
      }

      case PROGRAM:
      {
        if(ast->child[0] == NULL)
        {
          return TRUE;
        }
        else
        {
          int firstIsCorrect;
          int lastIsCorrect;

          firstIsCorrect = verify(ast->child[0]);

          if(ast->child[1]->node_type == FUNCTIONDEFINITION)
          {
            lastIsCorrect = verify(ast->child[1]);
          }
          else
          {
            lastIsCorrect = TRUE;
          }

          return firstIsCorrect && lastIsCorrect;
        }

        break;
      }
    }
  }
}

void initSemanticAnalyzer()
{
  globalScope.text = (char*)calloc(80,sizeof(char));
  sprintf(globalScope.text, "@global");
  //addToTable(globalScope,symbolTable,TABLE_SIZE);

  currentScope = &globalScope;

  errorCount = 0;
}
