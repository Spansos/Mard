#pragma once

#include <array>
#include <cstdint>

#include "card.hpp"

template <typename T>
class ObjectId {
public:
    T & operator*() {
        return *object;
    }
private:
    std::uint8_t id;
    std::uint16_t counter;
    T * object;
};

class GameState {
public:
    std::array<ObjectId<CardType>, 256> p1_pile_cards;
    std::array<ObjectId<CardType>, 256> p1_open_cards;
    std::array<ObjectId<CardType>, 256> p1_closed_cards;
    std::array<ObjectId<ActiveCard>, 256> p1_active_cards;

    std::array<ObjectId<CardType>, 256> p2_pile_cards;
    std::array<ObjectId<CardType>, 256> p2_open_cards;
    std::array<ObjectId<CardType>, 256> p2_closed_cards;
    std::array<ObjectId<ActiveCard>, 256> p2_active_cards;
private:
};