#ifndef NIM_H_INCLUDED
#define NIM_H_INCLUDED

#include <map>

#include "Game.h"

struct NimCompare;

class Nim : public Game {
public:
    Nim(unsigned int heap);
    Nim(unsigned int heap, std::vector<unsigned int> poss);
    ~Nim();

    std::vector<unsigned int> get_valid_moves(bool player) const override;
    std::unique_ptr<Game> make_move(int m, bool player) const override;
    void render() const override;
protected:
    Surreal get_memo_value() const override;
    virtual bool is_memoizable() const override;
private:
    std::vector<unsigned int> possible_moves;
    unsigned int heap_size;

    static std::map<Nim, Surreal, NimCompare> value_table;
    friend NimCompare;
};

#endif // NIM_H_INCLUDED
