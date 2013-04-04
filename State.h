#ifndef STATE_H
#define STATE_H

#include <string>

/**
 * The states of the finite state machine defined in an enumerated type.
 */
enum State {Comma, Period, Q_Mark, Left_Paren, Right_Paren, SawColon, Colon, Colon_Dash, Multiply, Add, Identifier, SawAQuote, ProcessingString, PossibleEndOfString, SawAHash, Comment, BlockComment, PossibleEndOfComment, WhiteSpace, Undefined, Start, End};

    /**
     * Converts a state to a string.
     * 
     * Parameters: state -- the state to be converted to a string.
     * PreCondition: none
     * Postcondition: result = the string representation of the state which
     *                         looks exactly like its State name.
     */
    std::string StateToString(State state);
#endif
