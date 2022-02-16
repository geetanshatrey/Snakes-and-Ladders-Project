#include<iostream>
#include<map>
#include<vector>

#define BOARD_SIZE 100

using namespace std;

class Player {

public:
    Player() 
    {
        current_position = 0;
    }

    Player(string _name) 
    {
        name = _name;
        current_position = 0;
    }

    string get_name() 
    {
        return name;
    }

    void set_name(string _name) 
    {
        name = _name;
    }

    int get_current_position() {
        return current_position;
    }

    void set_current_position(int _current_position)
    {
        current_position = _current_position;
    }

private:
    string name;
    int current_position;
};

class Board {

public:
    Board() 
    {
        snakes.clear();
        ladders.clear();
    }

    Board(int _size) 
    {
        board_size = _size;
        snakes.clear();
        ladders.clear();
    }

    int get_board_size() 
    {
        return board_size;
    }

    void add_snake(int _head, int _tail) 
    {
        // Assuming that there can only be one snake's head at a position.
        snakes.insert(make_pair(_head,_tail));
    }

    void add_ladder(int _start, int _end) 
    {
        // Assuming that there can only be one ladder's start at a position.
        ladders.insert(make_pair(_start,_end));
    }

    bool is_snake_present(int _position) 
    {
        if(snakes.find(_position) != snakes.end()) {
            return true;
        }
        else {
            return false;
        }
    }

    bool is_ladder_present(int _position) 
    {
        if(ladders.find(_position) != ladders.end()) {
            return true;
        }
        else {
            return false;
        }
    }

    bool is_valid_move(int _position)
    {
        if(_position <= board_size) {
            return true;
        }
        else {
            return false;
        }
    }

    int move(int _position) 
    {
        if(is_valid_move(_position)) {
            if(is_snake_present(_position)) {
                return snakes[_position];
            }
            else if(is_ladder_present(_position)) {
                return ladders[_position];
            }
            else {
                return _position;
            }
        }
        else {
            return _position;
        }
    }


private:
    int board_size;
    map<int,int> snakes;
    map<int,int> ladders;
};

class Game {

public:
    Game() 
    {
        winner = -1;
        is_winner_found = false;
    }

    Game(vector<string> _players, int _board_size, vector< pair<int,int> > _snakes, vector< pair<int,int> > _ladders) 
    {
        winner = -1;
        is_winner_found = false;

        for(int i = 0; i < _players.size(); i++) {
            Player new_player = Player(_players[i]);
            players.push_back(new_player);
        }

        board = Board(_board_size);
        for(int i = 0; i < _snakes.size(); i++) {
            board.add_snake(_snakes[i].first, _snakes[i].second);
        }
        for(int i = 0; i < _ladders.size(); i++) {
            board.add_ladder(_ladders[i].first, _ladders[i].second);
        }
    }

    int roll_dice() {
        return ((rand() % 6) + 1);
    }

    bool is_game_over() 
    {
        return is_winner_found;
    }

    string get_winner_name() 
    {
        return players[winner].get_name();
    }

    void play_game() 
    {
        int turn = 0;
        while(!is_game_over()) {
            int current_player = turn % players.size();
            int current_position = players[current_player].get_current_position();
            int dice_result = roll_dice();

            int new_position = board.move(current_position + dice_result);
            cout << players[current_player].get_name() << " rolled a " << dice_result << " and moved from " << current_position << " to " << new_position << endl; 
            
            players[current_player].set_current_position(new_position);
            if(new_position == board.get_board_size()) {
                winner = current_player;
                is_winner_found = true;
            }
            turn++;
        }
    }

private:
    vector<Player> players;
    Board board;
    bool is_winner_found;
    int winner;
};

void get_game_data(Game& _game) 
{
    int total_snakes, total_ladders, total_players;
    vector< pair<int,int> > snakes, ladders;
    vector<string> player_names;

    cin >> total_snakes;

    for(int i = 0; i < total_snakes; i++) {
        int head, tail;
        cin >> head >> tail;
        snakes.push_back(make_pair(head,tail));
    }
    
    cin >> total_ladders;

    for(int i = 0; i < total_ladders; i++) {
        int start, end;
        cin >> start >> end;
        ladders.push_back(make_pair(start,end));
    }

    cin >> total_players;

    for(int i = 0; i < total_players; i++) {
        string name;
        cin >> name;
        player_names.push_back(name);
    }

    _game = Game(player_names,100,snakes,ladders);
}

int main()
{
    srand(time(NULL));

    Game game;
    get_game_data(game);
    game.play_game();
    cout << game.get_winner_name() << " wins the game" << endl;
}
