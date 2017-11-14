//
// Created by thecharlesblake on 10/28/17.
//

#ifndef SOLVITAIRE_SOL_RULES_H
#define SOLVITAIRE_SOL_RULES_H

#include <vector>
#include <string>

#include <boost/optional.hpp>
#include <rapidjson/document.h>

class sol_rules {
public:
    enum class valid_sol {
        BLACK_HOLE,
        SIMPLE_BLACK_HOLE,
        SPANISH_PATIENCE,
        SIMPLE_SPANISH_PATIENCE,
        FREE_CELL,
        SIMPLE_FREE_CELL,
        CANFIELD,
        SIMPLE_CANFIELD
    };
    enum class build_order {
        NO_BUILD,
        DESCENDING,
        ASCENDING,
        BOTH,
        SINGLE_CARD
    };
    enum class build_policy {
        CLUBS,
        DIAMONDS,
        HEARTS,
        SPADES,
        ANY_SUIT,
        SAME_SUIT,
        RED_BLACK
    };

    static const sol_rules from_preset(const std::string);
    static const sol_rules from_file(const std::string);

    static bool is_suit(build_policy);
    static int suit_val(build_policy);

    unsigned int tableau_pile_count;
    build_order build_ord;
    build_policy build_pol;
    unsigned int max_rank;
    bool hole;
    bool foundations;
    unsigned int cells;
    unsigned int reserve_size;
    unsigned int stock_size;

private:
    static sol_rules get_default();
    static void modify_sol_rules(sol_rules&, rapidjson::Document&);
    static void parse_err(const std::string&);

    static valid_sol valid_sol_enum(const std::string&);
};

#endif //SOLVITAIRE_SOL_RULES_H
