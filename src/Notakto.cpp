#include <cassert>
#include <algorithm>
#include <iostream>

#include "Notakto.h"

struct NotaktoCompare {
    bool operator()(const Notakto& lhs, const Notakto& rhs) {
        return (lhs.board_size < rhs.board_size) ? true :
               (lhs.board_size > rhs.board_size) ? false : !std::equal(lhs.board.begin(), lhs.board.end(), rhs.board.begin());
    }
};

std::map<Notakto, Surreal, NotaktoCompare> Notakto::value_table;

Notakto::Notakto() : board_size(3), board(9, false) {
}

Notakto::Notakto(unsigned int board_size) : board_size(board_size), board(board_size*board_size, false) {
    assert(board_size%2 == 1);
}

Notakto::~Notakto() {
    board.clear();
}

bool Notakto::check_row(unsigned int row) const {
    int cnt = 0;
    for (size_t col = 0; col < board_size; ++col) {
        cnt += board[row*board_size + col];
    }
    return cnt + 1 < board_size;
}

bool Notakto::check_col(unsigned int col) const {
    int cnt = 0;
    for (size_t row = 0; row < board_size; ++row) {
        cnt += board[row*board_size + col];
    }
    return cnt + 1 < board_size;
}

bool Notakto::check_diag(bool diag) const {
    const int start = diag ? 0 : board_size-1;
    const int delta = diag ? board_size+1 : board_size-1;

    int cnt = 0;
    for (size_t d = 0; d < board_size; ++d) {
        cnt += board[start + delta*d];
    }
    return cnt + 1 < board_size;
}

std::vector<unsigned int> Notakto::get_valid_moves(bool) const {
    std::vector<unsigned int> ret;
    for (size_t row = 0; row < board_size; ++row) {
        for (size_t col = 0; col < board_size; ++col) {
            if (!board[row*board_size + col]) {
                bool value = check_row(row) && check_col(col);
                if (row == col) value = value && check_diag(true);
                if (row == board_size-col-1) value = value && check_diag(false);

                if (value) ret.push_back(row*board_size + col);
            }
        }
    }
    return ret;
}

std::unique_ptr<Game> Notakto::make_move(int m, bool player) const {
    auto ret = std::make_unique<Notakto>(board_size);
    ret->board = board;
    ret->board[m] = true;
    return ret;
}

void Notakto::render() const {
    std::cout<<std::endl<<std::string(4*board_size + 1, '-')<<std::endl;
    for (size_t row = 0; row < board_size; ++row) {
        std::cout<<"|";
        for (size_t col = 0; col < board_size; ++col) {
            std::cout<<" "<<(board[row*board_size + col] ? 'X' : ' ')<<" |";
        }
        std::cout<<std::endl<<std::string(4*board_size + 1, '-')<<std::endl;
    }
}

Surreal Notakto::get_memo_value() const {
    if (value_table.find(*this) == value_table.end()) {
        return value_table[*this] = calculate_value();
    }
    return value_table[*this];
}

bool Notakto::is_memoizable() const {
    return true;
}
