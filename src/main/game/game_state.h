//
// Created by thecharlesblake on 10/24/17.
//

#ifndef SOLVITAIRE_GAME_STATE_H
#define SOLVITAIRE_GAME_STATE_H

#include <vector>
#include <string>

#include <rapidjson/document.h>
#include <boost/functional/hash.hpp>

#include "card.h"
#include "pile.h"
#include "sol_rules.h"

class game_state {
    friend class deal_parser;
    friend class state_printer;
    friend class predicate;
    friend class hasher;
public:
    // Defines types
    typedef uint8_t pile_ref;
    struct move {
        move(pile_ref, pile_ref, pile::size_type = 1);
        pile_ref from; pile_ref to; pile::size_type count;
    };

    // Constructors
    // Creates a game state representation from a JSON doc
    game_state(const sol_rules&, const rapidjson::Document&);
    // Does the same from a 'rules' object
    game_state(const sol_rules&, int seed);

    // For testing
    game_state(std::initializer_list<pile>);

    // Alters state
    void make_move(move);
    void undo_move(move);

    std::vector<move> get_legal_moves() const;

    // Inspects state
    bool is_solved() const;
    const std::vector<pile>& get_data() const;

    friend std::ostream& operator<< (std::ostream&, const game_state&);

private:
    static std::vector<card> gen_shuffled_deck(int, card::rank_t, bool);

    // Private constructor
    explicit game_state(const sol_rules&);

    // Used in get_legal_moves()
    move get_stock_tableau_move() const;
    bool is_valid_tableau_move(pile_ref, pile_ref) const;
    bool is_valid_foundations_move(pile_ref, pile_ref) const;
    bool is_valid_hole_move(pile_ref) const;
    void get_built_group_moves(std::vector<move>&) const;
    pile::size_type get_built_group_height(pile_ref) const;
    bool valid_built_group_move(card, card, card) const;
    void add_built_group_move(std::vector<move>&, pile_ref, pile_ref) const;
    void add_empty_built_group_moves(std::vector<move>&, pile_ref, pile_ref,
                                     card) const;

    // References to piles
    const sol_rules rules;
    std::vector<pile_ref> tableau_piles;
    std::vector<pile_ref> cells;
    pile_ref stock;
    pile_ref waste;
    std::vector<pile_ref> reserve;
    std::vector<pile_ref> foundations;
    pile_ref hole;

    // Stores the original pile refs of the commutative piles so that they can
    // be printed in the order the user expects
    std::vector<pile_ref> original_tableau_piles;
    std::vector<pile_ref> original_cells;
    std::vector<pile_ref> original_reserve;

    // The core piles
    std::vector<pile> piles;
};

#endif //SOLVITAIRE_GAME_STATE_H
