/*
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdlib.h>

#include "reader.h"
#include "scanner.h"
#include "parser.h"
#include "error.h"

Token *currentToken;
Token *lookAhead;

void scan(void) {
	Token* tmp = currentToken;
	currentToken = lookAhead;
	lookAhead = getValidToken();
	free(tmp);
}

void eat(TokenType tokenType) {
	if (lookAhead->tokenType == tokenType) {
		printToken(lookAhead);
		scan();
	}
	else missingToken(tokenType, lookAhead->lineNo, lookAhead->colNo);
}

void compileProgram(void) {
	assert("Parsing a Program ....");
	eat(KW_PROGRAM);
	eat(TK_IDENT);
	eat(SB_SEMICOLON);
	compileBlock();
	eat(SB_PERIOD);
	assert("Program parsed!");
}

void compileBlock(void) {
	assert("Parsing a Block ....");
	if (lookAhead->tokenType == KW_CONST) {
		eat(KW_CONST);
		compileConstDecl();
		compileConstDecls();
		compileBlock2();
	}
	else compileBlock2();
	assert("Block parsed!");
}

void compileBlock2(void) {
	if (lookAhead->tokenType == KW_TYPE) {
		eat(KW_TYPE);
		compileTypeDecl();
		compileTypeDecls();
		compileBlock3();
	}
	else compileBlock3();
}

void compileBlock3(void) {
	if (lookAhead->tokenType == KW_VAR) {
		eat(KW_VAR);
		compileVarDecl();
		compileVarDecls();
		compileBlock4();
	}
	else compileBlock4();
}

void compileBlock4(void) {
	compileSubDecls();
	compileBlock5();
}

void compileBlock5(void) {
	eat(KW_BEGIN);
	compileStatements();
	eat(KW_END);
}

void compileConstDecls(void) {
	// TODO done
	switch (lookAhead->tokenType) {
	case KW_TYPE:
	case KW_VAR:
	case KW_FUNCTION:
	case KW_PROCEDURE:
	case KW_BEGIN:
		break;
	default:
		compileConstDecl();
		compileConstDecls();
		break;
	}
}

void compileConstDecl(void) {
	// TODO done
	eat(TK_IDENT);
	eat(SB_EQ);
	compileConstant();
	eat(SB_SEMICOLON);
}

void compileTypeDecls(void) {
	// TODO done
	switch (lookAhead->tokenType) {
	case KW_VAR:
	case KW_FUNCTION:
	case KW_PROCEDURE:
	case KW_BEGIN:
		break;
	default:
		compileType();
		compileTypeDecls();
		break;
	}
}

void compileTypeDecl(void) {
	// TODO done
	eat(TK_IDENT);
	eat(SB_EQ);
	compileType();
	eat(SB_SEMICOLON);
}

void compileVarDecls(void) {
	// TODO done
	switch (lookAhead->tokenType) {
	case KW_FUNCTION:
	case KW_PROCEDURE:
	case KW_BEGIN:
		break;
	default:
		compileVarDecl();
		compileVarDecls();
		break;
	}
}

void compileVarDecl(void) {
	// TODO done
	eat(TK_IDENT);
	eat(SB_COLON);
	compileType();
	eat(SB_SEMICOLON);
}

void compileSubDecls(void) {
	assert("Parsing subtoutines ....");
	// TODO done
	switch (lookAhead->tokenType) {
	case KW_FUNCTION:
		compileFuncDecl();
		compileSubDecls();
		break;
	case KW_PROCEDURE:
		compileProcDecl();
		compileSubDecls();
		break;
	case KW_BEGIN:
		break;
	default:
		break;
	}
	assert("Subtoutines parsed ....");
}

void compileFuncDecl(void) {
	assert("Parsing a function ....");
	// TODO done
	eat(KW_FUNCTION);
	eat(TK_IDENT);
	compileParams();
	eat(SB_COLON);
	compileBasicType();
	eat(SB_SEMICOLON);
	compileBlock();
	eat(SB_SEMICOLON);
	assert("Function parsed ....");
}

void compileProcDecl(void) {
	assert("Parsing a procedure ....");
	// TODO done
	eat(KW_PROCEDURE);
	eat(TK_IDENT);
	compileParams();
	eat(SB_SEMICOLON);
	compileBlock();
	eat(SB_SEMICOLON);
	assert("Procedure parsed ....");
}

void compileUnsignedConstant(void) {
	// TODO done
	switch (lookAhead->tokenType) {
	case TK_NUMBER:
		eat(TK_NUMBER);
		break;
	case TK_IDENT:
		eat(TK_IDENT);
		break;
	case TK_CHAR:
		eat(TK_CHAR);
		break;
	default:
		break;
	}
}

void compileConstant(void) {
	// TODO done
	switch (lookAhead->tokenType) {
	case SB_PLUS:
		eat(SB_PLUS);
		compileConstant2();
		break;
	case SB_MINUS:
		eat(SB_MINUS);
		compileConstant2();
		break;
	case TK_CHAR:
		eat(TK_CHAR);
		break;
	default:
		compileConstant2();
		break;
	}
}

void compileConstant2(void) {
	// TODO done
	switch (lookAhead->tokenType) {
	case TK_IDENT:
		eat(TK_IDENT);
		break;
	case TK_NUMBER:
		eat(TK_NUMBER);
		break;
	default:
		break;
	}
}

void compileType(void) {
	// TODO done
	switch (lookAhead->tokenType) {
	case KW_INTEGER:
		eat(KW_INTEGER);
		break;
	case KW_CHAR:
		eat(KW_CHAR);
		break;
	case TK_IDENT:
		eat(TK_IDENT);
		break;
	case KW_ARRAY:
		eat(KW_ARRAY);
		eat(SB_LSEL);
		eat(TK_NUMBER);
		eat(SB_RSEL);
		eat(KW_OF);
		compileType();
		break;
	default:
		break;
	}
}

void compileBasicType(void) {
	// TODO done
	switch (lookAhead->tokenType)
	{
	case KW_INTEGER:
		eat(KW_INTEGER);
		break;
	case KW_CHAR:
		eat(KW_CHAR);
		break;
	default: 
		error(ERR_INVALIDBASICTYPE, lookAhead->lineNo, lookAhead->colNo);
		break;

	}
}

void compileParams(void) {
	// TODO done
	switch (lookAhead->tokenType) {
	case SB_LPAR:
		eat(SB_LPAR);
		compileParam();
		compileParams2();
		eat(SB_RPAR);
		break;
	case SB_COLON:
	case SB_SEMICOLON:
		break;
	default:
		break;
	}
}

void compileParams2(void) {
	// TODO done
	switch (lookAhead->tokenType) {
	case SB_SEMICOLON:
		eat(SB_SEMICOLON);
		compileParam();
		compileParams2();
		break;
	case SB_RPAR:
		break;
	default:
		break;
	}
}

void compileParam(void) {
	// TODO done
	switch (lookAhead->tokenType) {
	case TK_IDENT:
		eat(TK_IDENT);
		eat(SB_COLON);
		compileBasicType();
		break;
	case KW_VAR:
		eat(KW_VAR);
		eat(TK_IDENT);
		eat(SB_COLON);
		compileBasicType();
		break;
	default:
		break;
	}
}

void compileStatements(void) {
	// TODO done
	compileStatement();
	compileStatements2();
}

void compileStatements2(void) {
	// TODO done
	switch (lookAhead->tokenType) {
	case SB_SEMICOLON:
		eat(SB_SEMICOLON);
		compileStatement();
		compileStatements2();
		break;
	case KW_END:
		break;
	default:
		break;
	}
}

void compileStatement(void) {
	switch (lookAhead->tokenType) {
	case TK_IDENT:
		compileAssignSt();
		break;
	case KW_CALL:
		compileCallSt();
		break;
	case KW_BEGIN:
		compileGroupSt();
		break;
	case KW_IF:
		compileIfSt();
		break;
	case KW_WHILE:
		compileWhileSt();
		break;
	case KW_FOR:
		compileForSt();
		break;
	case KW_END:
	case SB_SEMICOLON:
	case KW_ELSE:
		break;
	default:
		error(ERR_INVALIDSTATEMENT, lookAhead->lineNo, lookAhead->colNo);
		break;
	}
}

void compileAssignSt(void) {
	assert("Parsing an assign statement ....");
	// TODO done
	switch (lookAhead->tokenType) {
	case TK_IDENT:
		eat(TK_IDENT);
		switch (lookAhead->tokenType) {
		case SB_LSEL:
			compileIndexes();
			break;
			// check the FOLLOW2 set
		/*case :
			break;*/
		default:
			break;
		}
		eat(SB_ASSIGN);
		compileExpression();
		break;
		// check the FOLLOW1 set
	case KW_END:
	case SB_SEMICOLON:
	case KW_ELSE:
		break;
	default:
		break;
	}
	assert("Assign statement parsed ....");
}

void compileCallSt(void) {
	assert("Parsing a call statement ....");
	// TODO done
	eat(KW_CALL);
	eat(TK_IDENT);
	compileArguments();
	assert("Call statement parsed ....");
}

void compileGroupSt(void) {
	assert("Parsing a group statement ....");
	// TODO done
	eat(KW_BEGIN);
	compileStatements();
	eat(KW_END);
	assert("Group statement parsed ....");
}

void compileIfSt(void) {
	assert("Parsing an if statement ....");
	eat(KW_IF);
	compileCondition();
	eat(KW_THEN);
	compileStatement();
	if (lookAhead->tokenType == KW_ELSE)
		compileElseSt();
	assert("If statement parsed ....");
}

void compileElseSt(void) {
	eat(KW_ELSE);
	compileStatement();
	/*switch (lookAhead->tokenType) {
	case KW_END:
	case SB_SEMICOLON:
	case KW_ELSE:
		break;
	default:
		break;
	}*/
}

void compileWhileSt(void) {
	assert("Parsing a while statement ....");
	// TODO done
	eat(KW_WHILE);
	compileCondition();
	eat(KW_DO);
	compileStatement();
	assert("While statement parsed ....");
}

void compileForSt(void) {
	assert("Parsing a for statement ....");
	// TODO done
	eat(KW_FOR);
	eat(TK_IDENT);
	eat(SB_ASSIGN);
	compileExpression();
	eat(KW_TO);
	compileExpression();
	eat(KW_DO);
	compileStatement();
	assert("For statement parsed ....");
}

void compileArguments(void) {
	// TODO done
	switch (lookAhead->tokenType) {
	case SB_LPAR:
		eat(SB_LPAR);
		compileExpression();
		compileArguments2();
		eat(SB_RPAR);
		break;
	case SB_SEMICOLON:
	case KW_END:
	case KW_ELSE:
		break;
	default:
		break;
	}
}

void compileArguments2(void) {
	// TODO done
	switch (lookAhead->tokenType) {
	case SB_COMMA:
		eat(SB_COMMA);
		compileExpression();
		compileArguments2();
		break;
	case SB_RPAR:
		break;
	default:
		break;
	}
}

void compileCondition(void) {
	// TODO done
	compileExpression();
	compileCondition2();
}

void compileCondition2(void) {
	// TODO done
	switch (lookAhead->tokenType) {
	case SB_EQ:
		eat(SB_EQ);
		compileExpression();
		break;
	case SB_NEQ:
		eat(SB_NEQ);
		compileExpression();
		break;
	case SB_LE:
		eat(SB_LE);
		compileExpression();
		break;
	case SB_LT:
		eat(SB_LT);
		compileExpression();
		break;
	case SB_GE:
		eat(SB_GE);
		compileExpression();
		break;
	case SB_GT:
		eat(SB_GT);
		compileExpression();
		break;
	default:
		break;
	}
}

void compileExpression(void) {
	assert("Parsing an expression");
	// TODO done
	switch (lookAhead->tokenType) {
	case SB_PLUS:
		eat(SB_PLUS);
		compileExpression2();
		break;
	case SB_MINUS:
		eat(SB_MINUS);
		compileExpression2();
		break;
	default:
		compileExpression2();
		break;
	}
	assert("Expression parsed");
}

void compileExpression2(void) {
	// TODO done
	compileTerm();
	compileExpression3();
}


void compileExpression3(void) {
	// TODO
	switch (lookAhead->tokenType) {
	case SB_PLUS:
		eat(SB_PLUS);
		compileTerm();
		compileExpression3();
		break;
	case SB_MINUS:
		eat(SB_MINUS);
		compileTerm();
		compileExpression3();
		break;
	default:
		break;
	}
}

void compileTerm(void) {
	compileFactor();
	compileTerm2();
}

void compileTerm2(void) {
	switch (lookAhead->tokenType) {
	case SB_TIMES:
		eat(SB_TIMES);
		compileFactor();
		compileTerm2();
		break;
	case SB_SLASH:
		eat(SB_SLASH);
		compileFactor();
		compileTerm2();
		break;
		// check the FOLLOW set
	case SB_PLUS:
	case SB_MINUS:
	case KW_TO:
	case KW_DO:
	case SB_RPAR:
	case SB_COMMA:
	case SB_EQ:
	case SB_NEQ:
	case SB_LE:
	case SB_LT:
	case SB_GE:
	case SB_GT:
	case SB_RSEL:
	case SB_SEMICOLON:
	case KW_END:
	case KW_ELSE:
	case KW_THEN:
		break;
	default:
		error(ERR_INVALIDTERM, lookAhead->lineNo, lookAhead->colNo);
	}
}

void compileFactor(void) {
	// TODO done
	switch (lookAhead->tokenType) {
	case TK_NUMBER:
	case TK_CHAR:
		compileUnsignedConstant();
		break;
	case SB_LPAR:
		eat(SB_LPAR);
		compileExpression();
		eat(SB_RPAR);
		break;
	case TK_IDENT:
		eat(TK_IDENT);
		switch (lookAhead->tokenType) {
		case SB_LSEL:
			compileIndexes();
			break;
		case SB_LPAR:
			compileArguments();
			break;
		default:
			break;
		}
		break;
		//case:
		//	break;
	default:
		break;
	}
}

void compileIndexes(void) {
	// TODO done
	switch (lookAhead->tokenType) {
	case SB_LSEL:
		eat(SB_LSEL);
		compileExpression();
		eat(SB_RSEL);
		compileIndexes();
		break;
	case SB_ASSIGN:
	case SB_TIMES:
	case SB_SLASH:
		break;
	default:
		break;
	}
}

int compile(char *fileName) {
	if (openInputStream(fileName) == IO_ERROR)
		return IO_ERROR;

	currentToken = NULL;
	lookAhead = getValidToken();

	compileProgram();

	free(currentToken);
	free(lookAhead);
	closeInputStream();
	return IO_SUCCESS;

}
