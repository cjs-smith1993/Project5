#include "State.h"

using namespace std;

string StateToString(State tokenType){
    string result = "";
    switch(tokenType){
        case Comma:                      result = "Comma"; break;
        case Period:                     result = "Period"; break;
		case Q_Mark:					 result = "Q_Mark"; break;
		case Left_Paren:				 result = "Left_Paren"; break;
		case Right_Paren:				 result = "Right_Paren"; break;
        case SawColon:                   result = "SawColon"; break;
		case Colon:						 result = "Colon"; break;
        case Colon_Dash:                 result = "Colon_Dash"; break;
		case Multiply:					 result = "Multiply"; break;
		case Add:						 result = "Add"; break;
		case Identifier:				 result = "Identifier"; break;
        case SawAQuote:                  result = "SawAQuote"; break;
        case ProcessingString:           result = "ProcessingString"; break;
        case PossibleEndOfString:        result = "PossibleEndOfString"; break;
		case SawAHash:					 result = "SawAHash"; break;
		case Comment:					 result = "Comment"; break;
		case BlockComment:				 result = "BlockComment";
		case PossibleEndOfComment:		 result = "PossibleEndOfComment";
		case WhiteSpace:				 result = "WhiteSpace"; break;
		case Undefined:					 result = "Undefined"; break;
        case Start:                      result = "Start"; break;
        case End:                        result = "End"; break;
    }
    return result;
};
