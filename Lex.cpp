#include "Lex.h"

#include "Input.h"
#include "TokenType.h"
#include "Utils.h"

using namespace std;

Lex::Lex() {
	input = new Input();
    generateTokens(input);
}

Lex::Lex(const char* filename) {
    input = new Input(filename);
    generateTokens(input);
}

Lex::Lex(istream& istream) {
    input = new Input(istream);
    generateTokens(input);
}

Lex::Lex(const Lex& lex) {
    input = new Input(*lex.input);
    tokens = new vector<Token*>();

    vector<Token*>::iterator iter;
    for(iter=lex.tokens->begin(); iter != lex.tokens->end(); iter++) {
        Token* newToken = new Token(**iter);
        tokens->push_back(newToken);
    }

    index = lex.index;
    state = lex.state;
}

Lex::~Lex(){
    for (int i = 0; i < tokens->size(); i++) {
        delete (*tokens)[i];
    }
    delete tokens;
    delete input;
}

bool Lex::operator==(const Lex& lex) {
    bool result = (tokens->size() == lex.tokens->size()) && (index == lex.index);
    if(result) {
        vector<Token*>::iterator iter1;
        vector<Token*>::iterator iter2;
        iter1 = tokens->begin();
        iter2 = lex.tokens->begin();
        while(result && iter1 != tokens->end() && iter2 != lex.tokens->end()) {
            result = **iter1 == **iter2;
            iter1++;
            iter2++;
        }
        result = result && iter1 == tokens->end() && iter2 == lex.tokens->end();
    }
    return result;
}

string Lex::toString() const {
    int count = 0;
    string result;
    while(count < tokens->size()) {
        Token* token = (*tokens)[count];
        result += token->toString();
        count++;
    }
    result += "Total Tokens = ";
    string countToString;
    result += itoa(countToString, count);
    result += "\n";
    return result;
}

void Lex::generateTokens(Input* input) {
    tokens = new vector<Token*>();
    index = 0;
    
    state = Start;
    while(state != End) {
        state = nextState();
    }
}

Token* Lex::getCurrentToken() {
    return (*tokens)[index];
}

void Lex::advance() {
    index++;
}

bool Lex::hasNext() {
    return index < tokens->size();
}

State Lex::nextState() {
    State result;
    char character;
    switch(state) {
        case Start:               result = getNextState(); break;
        case Comma:               emit(COMMA); result = getNextState(); break;
        case Period:              emit(PERIOD); result = getNextState(); break;
		case Q_Mark:			  emit(Q_MARK); result = getNextState(); break;
		case Left_Paren:		  emit(LEFT_PAREN); result = getNextState(); break;
		case Right_Paren:		  emit(RIGHT_PAREN); result = getNextState(); break;
        case SawColon:
            character = input->getCurrentCharacter();
            if(character == '-') {
                result = Colon_Dash;
                input->advance();
            } else { //Every other character
                //throw "ERROR:: in case SawColon:, Expecting  '-' but found " + character + '.';
				result = Colon;
            }
            break;
		case Colon:				  emit(COLON); result = getNextState(); break;
        case Colon_Dash:          emit(COLON_DASH); result = getNextState(); break;
		case Multiply:			  emit(MULTIPLY); result = getNextState(); break;
		case Add:				  emit(ADD); result = getNextState(); break;
		case Identifier:
			character = input->getCurrentCharacter();
			if (!isAlphaNum(character)) {
				emit(ID);
				result = getNextState();
			}
			else {
				result = Identifier;
				input->advance();
			}
			break;
        case SawAQuote:  
            character = input->getCurrentCharacter();
            if(character == '\'') {
                result = PossibleEndOfString;
            } else if(character == -1) {
                //throw "ERROR:: in Saw_A_Quote::nextState, reached EOF before end of string.";
				result = Undefined;
            } else { //Every other character
                result = ProcessingString;
            }
            input->advance();
            break;
        case ProcessingString:  
            character = input->getCurrentCharacter();
            if(character == '\'') {
                result = PossibleEndOfString;
            } else if(character == -1) {
                //throw "ERROR:: in ProcessingString::nextState, reached EOF before end of string.";
				result = Undefined;
            } else { //Every other character
                result = ProcessingString;
            }
            input->advance();
            break;
        case PossibleEndOfString:
            if(input->getCurrentCharacter() == '\'') {
                input->advance();
                result = ProcessingString;
            } else { //Every other character
                emit(STRING);
                result = getNextState();
            }
            break;
		case SawAHash:
			character = input->getCurrentCharacter();
			if (character == '|') {
				result = BlockComment;
			}
			else {
				result = Comment;
			}
			input->advance();
			break;
		case Comment:
			character = input->getCurrentCharacter();
			if (character == '\n') {
				emit(COMMENT);
				result = getNextState();
			}
			else {
				input->advance();
				result = Comment;
			}
			break;
		case BlockComment:
			character = input->getCurrentCharacter();
			if (character == '|') {
				result = PossibleEndOfComment;
			}
			else if (character == -1) {
				result = Undefined;
			}
			else {
				result = BlockComment;
			}
			input->advance();
			break;
		case PossibleEndOfComment:
			character = input->getCurrentCharacter();
			if (character == '#') {
				input->advance();
				emit(COMMENT);
				result = getNextState();
			}
			else if (character == '|') {
				input->advance();
				result = PossibleEndOfComment;
			}
			else {
				input->advance();
				result = BlockComment;
			}
			break;
		case WhiteSpace:		  emit(WHITESPACE); result = getNextState(); break;
		case Undefined:			  emit(UNDEFINED); result = getNextState(); break;
        case End:
            result = Undefined;
            //throw "ERROR:: in End state:, the Input should be empty once you reach the End state.";
            break;
    };
    return result;
}

State Lex::getNextState() {
    State result;
    char currentCharacter = input->getCurrentCharacter();
    //The handling of checking for whitespace and setting the result to Whilespace and
    //checking for letters and setting the result to Id will probably best be handled by
    //if statements rather then the switch statement.
	if (currentCharacter == ',') {
		result = Comma;
	}
	else if (currentCharacter == '.') {
		result = Period;
	}
	else if (currentCharacter == '?') {
		result = Q_Mark;
	}
	else if (currentCharacter == '(') {
		result = Left_Paren;
	}
	else if (currentCharacter == ')') {
		result = Right_Paren;
	}
	else if (currentCharacter == ':') {
		result = SawColon;
	}
	else if (currentCharacter == '*') {
		result = Multiply;
	}
	else if (currentCharacter == '+') {
		result = Add;
	}
	else if (isAlpha(currentCharacter)) {
		result = Identifier;
	}
	else if (currentCharacter == '\'') {
		result = ProcessingString;
	}
	else if (currentCharacter == '#') {
		result = SawAHash;
	}
	else if (isspace(currentCharacter)) {
		result = WhiteSpace;
	}
	else if (currentCharacter == -1 || currentCharacter == END_OF_FILE) {
		result = End;
        input->advance();
		emit(END_OF_FILE);
	}
	else {
		result = Undefined;
	}
    input->advance();
    return result;
}

void Lex::emit(TokenType tokenType) {
	Token* token;
    token = new Token(tokenType, input->getTokensValue(), input->getCurrentTokensLineNumber());
	storeToken(token);
    input->mark();
}

void Lex::storeToken(Token* token) {
    //This section shoud ignore whitespace and comments and change the token type to the appropriate value
    //if the value of the token is "Schemes", "Facts", "Rules", or "Queries".

	//Handle EOF
	if (token->getTokenType() == END_OF_FILE) {
		tokens->push_back(token);
		return;
	}

    //Weird case
    if (token->getTokensValue().length() == 0) {
        delete token;
        return;
    }
    
	//Ignore whitespace
	char first = token->getTokensValue().at(0);
	if (isspace(first)) {
		delete token;
		return;
	}
	
	//Check for keywords
	std::string value = token->getTokensValue();
	if (value.compare("Schemes") == 0) {
		token->setTokenType(SCHEMES);
	}
	else if (value.compare("Facts") == 0) {
		token->setTokenType(FACTS);
	}
	else if (value.compare("Rules") == 0) {
		token->setTokenType(RULES);
	}
	else if (value.compare("Queries") == 0) {
		token->setTokenType(QUERIES);
	}
	
    tokens->push_back(token);
}
