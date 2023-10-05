#include <iostream>
#include <vector>

namespace TicGame{
    constexpr int BOARD_WIDTH  = 3;
    using GameBoard = std::vector<std::vector<char>>;

    void print_game_board(GameBoard board){
        auto print_val = [&board](int x, int y) -> char{
            if(board[x][y] == 'T'){
                return '0' + (((BOARD_WIDTH * x) + y) );
            }else{
                return board[x][y];
            }
        };
        std::cout << "    |    |  \n";
        std::cout << " " << print_val(0,0) <<"  | " << print_val(0,1) <<"  | " << print_val(0,2) << " \n";
        std::cout << "____|____|____\n";
        std::cout << "    |    |  \n";
        std::cout << " " << print_val(1,0) <<"  | " << print_val(1,1) <<"  | " << print_val(1,2) << " \n";
        std::cout << "____|____|____\n";
        std::cout << "    |    |  \n";
        std::cout << " " << print_val(2,0) <<"  | " << print_val(2,1) <<"  | " << print_val(2,2) << " \n";
        std::cout << "    |    |  \n";
    }

    void process_user_input(std::string player_name, GameBoard& board, bool is_x){
        int user_choice;
        bool valid_move = false;

        std::cout << player_name << " please enter: ";
        std::cin >> user_choice;

        while(!((user_choice >= 0) && (user_choice <= 8))){
            std::cout << "Invalid Input!\n";
            std::cout << player_name << " please enter: ";
            std::cin >> user_choice;
        }

        int row = user_choice / BOARD_WIDTH;
        int column = user_choice % BOARD_WIDTH;

        while(!valid_move){
            if(board[row][column] != 'x' && board[row][column] != '0'){
                if(is_x){
                    board[row][column] = 'x';
                }
                else{
                    board[row][column] = '0';
                }
                valid_move = true;
            }
            else{
                std::cout << "There is no empty space! " << std::endl;
            }

            print_game_board(board);
        }
    }

    bool determine_winner(GameBoard board, const std::string& player, std::string& winner){

        for(int i = 0; i < 3 ; i++){

            if(board[i][0] == board[i][1]
            && board[i][0] == board[i][2]
            && board[i][0] != 'T'
            || board[0][i] == board[1][i]
            && board[0][i] == board[2][i]
            && board[0][i] != 'T')
            {
                winner = player;
                return true;
            }

            if(board[0][0] == board [1][1]
            && board[1][1] == board [2][2] && board[0][0] != 'T'
            || board[0][2] == board [1][1]
            && board[1][1] == board [2][0] && board[0][2] != 'T')
            {
                winner = player;
                return true;
            }
        }

        for (int i = 0; i < BOARD_WIDTH; ++i){
            for (int j = 0; j < BOARD_WIDTH; ++j){
                if (board[i][j] != 'x' && board [i][j] != '0'){
                    return false;
                }
            }
        }
        winner = "None";
        return false;
    }
}

int main (){
    using namespace TicGame;

    // declare local variables
    std::string player_one;
    std::string player_two;
    std::string winner;
    TicGame::GameBoard board(3, std::vector<char>(3, 'T'));
    bool turn = true;
    bool done = false;

    std::cout << "Enter the name of player 1: ";
    std::getline(std::cin, player_one);

    std::cout << "Enter the name of player 2: ";
    std::getline(std::cin, player_two);

    std::cout << player_one << " is player1 so they will play first\n";
    std::cout << player_two << " is player2 so they will play second\n";

    while(!done){
        TicGame::print_game_board(board);
        TicGame::process_user_input((turn) ? player_one : player_two,
                                    board, turn);
        done = determine_winner(board,
                                (turn) ? player_one : player_two,
                                winner);
        turn = !turn;
    }

    if(winner == "None"){
        std::cout << "It's a draw!\n";
    }else{
        std::cout << winner << " WINS !!!" << std::endl;
    }
}

