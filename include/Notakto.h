#ifndef NOTAKTO_H_INCLUDED
#define NOTAKTO_H_INCLUDED

#include <map>

#include "Game.h"

struct NotaktoCompare;

//X's only Tic-Tac-Toe. Not allowed to make N in a row
class Notakto : public Game {
public:
    Notakto();
    Notakto(unsigned int board_size);
    ~Notakto();

    std::vector<unsigned int> get_valid_moves(bool player) const override;
    std::unique_ptr<Game> make_move(int m, bool player) const override;
    void render() const override;
protected:
    Surreal get_memo_value() const override;
    virtual bool is_memoizable() const override;
private:
    bool check_row(unsigned int row) const;
    bool check_col(unsigned int col) const;
    bool check_diag(bool diag) const;

    std::vector<bool> board;
    unsigned int board_size;

    static std::map<Notakto, Surreal, NotaktoCompare> value_table;
    friend NotaktoCompare;
};

#endif // NOTAKTO_H_INCLUDED
