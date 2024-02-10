//
//  main.cpp
//  Mini Projeect 3
//
//  Created by 顏浩昀 on 2020/6/26.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <cassert>
#include <set>
#include <queue>


//For alpha-beta
const int MAX = 999990;
const int MIN = -999990;



struct Point {
    int x, y;
    Point() : Point(0, 0) {}
    Point(float x, float y) : x(x), y(y) {}
    bool operator==(const Point& rhs) const {
        return x == rhs.x && y == rhs.y;
    }
    bool operator!=(const Point& rhs) const {
        return !operator==(rhs);
    }
    Point operator+(const Point& rhs) const {
        return Point(x + rhs.x, y + rhs.y);
    }
    Point operator-(const Point& rhs) const {
        return Point(x - rhs.x, y - rhs.y);
    }
};


int player;
const int SIZE = 8;
std::array<std::array<int, SIZE>, SIZE> playerboard;
std::vector<Point> next_valid_spots;



class OthelloBoard {
public:
    enum SPOT_STATE {
        EMPTY = 0,
        BLACK = 1,
        WHITE = 2
    };
    static const int SIZE = 8;
    const std::array<Point, 8> directions{{
        Point(-1, -1), Point(-1, 0), Point(-1, 1),
        Point(0, -1), /*{0, 0}, */Point(0, 1),
        Point(1, -1), Point(1, 0), Point(1, 1)
    }};
    std::array<std::array<int, SIZE>, SIZE> board;
    std::vector<Point> valid_spots;
    std::array<int, 3> disc_count;
    bool done;
    int winner;
    
    int cur_player, corner, stable_disc, valid_move, oponent_corner, oponent_stable_disc, oponent_valid_move, x_pos;
    int state_value;
    
private:
    int get_next_player(int player) const {
        return 3 - player;
    }
    bool is_spot_on_board(Point p) const {
        return 0 <= p.x && p.x < SIZE && 0 <= p.y && p.y < SIZE;
    }
    int get_disc(Point p) const {
        return board[p.x][p.y];
    }
    void set_disc(Point p, int disc) {
        board[p.x][p.y] = disc;
    }
    bool is_disc_at(Point p, int disc) const {
        if (!is_spot_on_board(p))
            return false;
        if (get_disc(p) != disc)
            return false;
        return true;
    }
    bool is_spot_valid(Point center) const {
        if (get_disc(center) != EMPTY)
            return false;
        for (Point dir: directions) {
            // Move along the direction while testing.
            Point p = center + dir;
            if (!is_disc_at(p, get_next_player(cur_player)))
                continue;
            p = p + dir;
            while (is_spot_on_board(p) && get_disc(p) != EMPTY) {
                if (is_disc_at(p, cur_player))
                    return true;
                p = p + dir;
            }
        }
        return false;
    }
    void flip_discs(Point center) {
        for (Point dir: directions) {
            // Move along the direction while testing.
            Point p = center + dir;
            if (!is_disc_at(p, get_next_player(cur_player)))
                continue;
            std::vector<Point> discs({p});
            p = p + dir;
            while (is_spot_on_board(p) && get_disc(p) != EMPTY) {
                if (is_disc_at(p, cur_player)) {
                    for (Point s: discs) {
                        set_disc(s, cur_player);
                    }
                    disc_count[cur_player] += discs.size();
                    disc_count[get_next_player(cur_player)] -= discs.size();
                    break;
                }
                discs.push_back(p);
                p = p + dir;
            }
        }
    }
public:
    OthelloBoard() {
        reset();
    }
    void reset() {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                board[i][j] = EMPTY;
            }
        }
        board[3][4] = board[4][3] = BLACK;
        board[3][3] = board[4][4] = WHITE;
        cur_player = BLACK;
        disc_count[EMPTY] = 8*8-4;
        disc_count[BLACK] = 2;
        disc_count[WHITE] = 2;
        valid_spots = get_valid_spots();
        done = false;
        winner = -1;
    }
    std::vector<Point> get_valid_spots() const {
        std::vector<Point> valid_spots;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                Point p = Point(i, j);
                if (board[i][j] != EMPTY)
                    continue;
                if (is_spot_valid(p))
                    valid_spots.push_back(p);
            }
        }
        return valid_spots;
    }
    bool put_disc(Point p) {
        if(!is_spot_valid(p)) {
            winner = get_next_player(cur_player);
            done = true;
            return false;
        }
        set_disc(p, cur_player);
        disc_count[cur_player]++;
        disc_count[EMPTY]--;
        flip_discs(p);
        // Give control to the other player.
        cur_player = get_next_player(cur_player);
        valid_spots = get_valid_spots();
        // Check Win
        if (valid_spots.size() == 0) {
            cur_player = get_next_player(cur_player);
            valid_spots = get_valid_spots();
            if (valid_spots.size() == 0) {
                // Game ends
                done = true;
                int white_discs = disc_count[WHITE];
                int black_discs = disc_count[BLACK];
                if (white_discs == black_discs) winner = EMPTY;
                else if (black_discs > white_discs) winner = BLACK;
                else winner = WHITE;
            }
        }
        return true;
    }
    void set_value(){
        
        this->corner = get_corner(player);
        this->oponent_corner = get_corner(3-player);
        this->stable_disc = get_stable_disc(player);
        this->oponent_stable_disc = get_stable_disc(3-player);
        this->oponent_valid_move = valid_spots.size();
        this->x_pos = get_x();
        
        int h = 0;
        h += corner*2000;
        h += stable_disc*300;
        h += -oponent_corner*2000;
        h += -oponent_stable_disc*300;
        h += -oponent_valid_move*10;
        if(oponent_valid_move == 0) h += 150;
        h += -x_pos*50;
        this->state_value = h;
    }
    

    int get_corner(int splayer){
        int corner = 0;
        if(board[0][0] == splayer)  corner++;
        if(board[7][0] == splayer)  corner++;
        if(board[0][7] == splayer)  corner++;
        if(board[7][7] == splayer)  corner++;
        return corner;
    }
    
    int get_x(){
        
        int x = 0;
        if(board[1][1] == player && board[0][0] == EMPTY)   x++;
        if(board[0][1] == player && board[0][0] == EMPTY)   x++;
        if(board[1][0] == player && board[0][0] == EMPTY)   x++;
    
        if(board[6][1] == player && board[7][0] == EMPTY)   x++;
        if(board[6][0] == player && board[7][0] == EMPTY)   x++;
        if(board[7][1] == player && board[7][0] == EMPTY)   x++;
           
        if(board[1][6] == player && board[0][7] == EMPTY)   x++;
        if(board[0][6] == player && board[0][7] == EMPTY)   x++;
        if(board[1][7] == player && board[0][7] == EMPTY)   x++;
           
        if(board[6][6] == player && board[7][7] == EMPTY)   x++;
        if(board[6][7] == player && board[7][7] == EMPTY)   x++;
        if(board[7][6] == player && board[7][7] == EMPTY)   x++;

        return x;
    }

    int get_stable_disc(int splayer){
        int stable = 0;
        if(get_corner(splayer) == 0) return 0;
        else{
            if(board[0][0] == splayer){
                for(int i = 1; i < 7; i++){
                    if(get_disc(Point(i,0)) == splayer)  stable++;
                    else    break;
                }
                for(int i = 1; i < 7; i++){
                    if(get_disc(Point(0,i)) == splayer)  stable++;
                    else    break;
                }
            }
            if(board[0][7] == splayer){
                for(int i = 1; i < 7; i++){
                    if(get_disc(Point(i,7)) == splayer)  stable++;
                    else    break;
                }
                for(int i = 6; i > 0; i++){
                    if(get_disc(Point(0,i)) == splayer)  stable++;
                    else    break;
                }
            }
            if(board[7][0] == splayer){
                for(int i = 6; i > 1; i++){
                    if(get_disc(Point(i,0)) == splayer)  stable++;
                    else    break;
                }
                for(int i = 1; i < 7; i++){
                    if(get_disc(Point(7,i)) == splayer)  stable++;
                    else    break;
                }
            }
            if(board[7][7] == splayer){
                for(int i = 6; i > 0; i++){
                    if(get_disc(Point(i,7)) == splayer)  stable++;
                    else    break;
                }
                for(int i = 6; i > 0; i++){
                    if(get_disc(Point(7,i)) == splayer)  stable++;
                    else    break;
                }
            }
            return stable;
        }
    }
    
};

//alpha-beta
int minimax(int depth, OthelloBoard b, int board_num, int maximizingPlayer, int alpha, int beta){
    int valid = b.valid_spots.size();
    if (depth == 5){
        b.set_value();
        return b.state_value;
    }
    if (maximizingPlayer == player){
        int ret = 0;
        int best = MIN;
        for (int i = 0; i < valid; i++){
            OthelloBoard next_board;
            next_board.board = b.board;
            next_board.cur_player = b.cur_player;
            next_board.valid_spots = b.valid_spots;
            next_board.put_disc(b.valid_spots[i]);
            int val = minimax(depth+1, next_board, i, 3-player, alpha, beta);
            if(val > best){
                ret = i;
                best = val;
            }
            alpha = std::max(alpha, best);
            if (beta <= alpha)      break;
        }
        if(depth == 0)  return ret;
        return best;
    }
    
    else{
        int best = MAX;
        for (int i = 0; i < valid; i++){
            OthelloBoard next_board;
            next_board.board = b.board;
            next_board.cur_player = b.cur_player;
            next_board.valid_spots = b.valid_spots;
            next_board.put_disc(b.valid_spots[i]);
            int val = minimax(depth+1, next_board, i, player, alpha, beta);
            best = std::min(best, val);
            beta = std::min(beta, best);
            if (beta <= alpha)      break;
        }
        return best;
    }
}







void read_board(std::ifstream& fin) {
    fin >> player;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            fin >> playerboard[i][j];
        }
    }
}

void read_valid_spots(std::ifstream& fin) {
    int n_valid_spots;
    fin >> n_valid_spots;
    float x, y;
    for (int i = 0; i < n_valid_spots; i++) {
        fin >> x >> y;
        next_valid_spots.push_back({x, y});
    }
}




void write_valid_spot(std::ofstream& fout) {
    OthelloBoard play;
    play.board = playerboard;
    play.cur_player = player;
    Point p;
    int index = minimax(0, play, 0, player, MIN, MAX);
    p = next_valid_spots[index];
    fout << p.x << " " << p.y << std::endl;
    fout.flush();
    
    //int index = (rand() % n_valid_spots);
              
    // Remember to flush the output to ensure the last action is written to file.
}




int main(int, char** argv) {
    std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2]);
    read_board(fin);
    read_valid_spots(fin);
    write_valid_spot(fout);
    fin.close();
    fout.close();
    return 0;
}
