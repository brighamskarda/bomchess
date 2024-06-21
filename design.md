# BOMChess Design

This file serves as a single place to see the overall design of the project. While not necessary for the average developer who uses the library, it can be useful reference for developers of the library to see why things were done the way they were.

## Game

This will be a full representation of a chess game as defined in the pgn standard. https://ia802908.us.archive.org/26/items/pgn-standard-1994-03-12/PGN_standard_1994-03-12.txt. The game must always be in a valid state. Invalid constructions, and moves are not allowed.

### Data Members
 * Board - Represents the current state of the game.
 * Move History - Contains a full history of all the moves in the game.
 * PGN Tags - Map of two strings containing all tags. If tag doesn't exist return ""

### Member Functions
 * Game() - Starts a game from the starting position. No Tags are included. Defaults things
 * Game(istream& pgn) - reads a pgn and constructs a game from it. Only accepts export formatted PGNs with a single game.
 * Game(Board& board) - starts a game from a board position.
 * Getters for everything - should be const so that moves can't be applied to board, must go through game
 * const Board GetBoard(uint16) - Gets the board at the given half move number.
 * stringview GetTag(stringview) - Gets the tag, or returns empty string if it doesn't exist.
 * SetTag(stringview) - Sets/overwrites a game tag. No validation, or cleansing of tags is done. Cannot set result tag, use set result function.
 * Set Result, sets the result. If the result is invalid (i.e. undetermined if the position is checkmate) throw.
 * Move(Move) - Makes a move (defined in Board), throws if move is invalid. Updates Move History and tags and board. If Result is set, it is unset. If halfmove is greater than 175, automatically draws.
 * UndoneMove UndoMove() - Updates Tags, and undoes last move from the board and history. (Note game must be resimulated)
 * Result Result - Returns the result of the Game, either the color of the winner, draw, or no result. Based off the result tag, if the tag is invalid, no result.
 * ToString(withSymbols)

### External Functions
 * MultipleGamesFromPGN(istream& pgn) - Returns an array of games from a pgn containing multiple games.
 * CombinePGNs(ostream&, vector of Games) - writes to an ostream of many games.
 * GeneratePGN(ostream&) - outputs the pgn.
 * ostream* operator<< - Returns a representation of the current board, move history, and pgn tags.
 * CanClaimDraw - by 50 move rule, or threefold repeition, three fold is done by simulating the entire game.
 * CanClaimefiftyMove
 * CanClaimthreefold

### Constants
 * List of standard tags
 * Enum Result - White, Black, Draw, None

## Board

A representation of a chess board as defined by the FEN standard. The board, must always be in a valid state. This means the following
 * The enPassant square must be valid
 * The castling rights must be valid
 * There must be one of each king on the board
 * There can be no pawns on the final rank.

### Data Members

 * Position
 * Color side_to_move
 * 4 castling bools
 * Square enPassant
 * half move
 * full move

### Member Functions

Board() - Makes board in default position - Defaults things
Board(fen)
readFen
Getters for each data member. Combined getter for castling rights.
Move(Move) - only applied if valid, use custom move validation (faster than using move gen). Throws if not valid.

### External Functions

generateFen
ostream << includes all debug information
ToString(withSymbols)

### Constants
 * Default FEN string

## BoardBuilder Struct

As opposed to board, board builder does not always need to be in a valid state.

### Data Members

Public
* Position
* Color side_to_move
* 4 castling bools
* Square enPassant
* half move
* full move

### Member Functions

BoardBuilder() = default
BoardBuilder(Fen)
Setter for castling rights with string.

### External Functions

ostream<< debug info
ToString(With Symbols)
Board MakeBoard() - Generates and fen and sends it to board. Either throws or give back a valid board. Anything not set is defaulted.

## MoveGen

Generates Moves and determines checks/checmates.

### Functions

 * IsCheck()
 * IsCheckMate()
 * IsStaleMate()
 * GenerateLegalMoves()
 * GeneratePsuedoLegalMoves()
 * GenerateLegalMoves(Board, Square)

## Position

Represents a chess position with no information related to moves. Does not need to be valid, but boards can't be build with invalid positions.

### Data Members

std::array of pieces

### Member Functions

at
iterator

### External Functions

ostream<<
ToString(print with symbols)
get piecemap
FromFEN

## Piece

Represents a Piece

### Data Members
    
 * PieceType
 * PieceColor

### Member Functions

 * Piece(string) - Takes letters or symbols
 * getters, not setters

### Functions

 * Hash specialization
 * ToString(bool use symbols)
 * ostream<<

### Constants

 * PieceType
 * PieceColor
 * One for each piece.

## Color Enum

A simple enum to represent colors. All printing of colors should be handled outside of this.

### ExternalFunctions

 * ostream
 * ToString

## Move Struct

Represents a UCI chess move. Needs board info to do things like SAN, and LAN.

### Member Variables

 * From Square
 * To Square
 * Promotion

### Functions

 * From UCI
 * ToString
 * ostream<<
 * FromSAN(Board, string)
 * FromLan(Board, string)


## Square Enum

### Functions

operator<<
FromString
ToString
From(File, Rank)

### Constants

AllSquares