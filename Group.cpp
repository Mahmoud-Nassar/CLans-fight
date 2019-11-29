//
// Created by mahmood on 1/15/2018.
//

#include "Group.h"
#include "exceptions.h"
#include <iostream>

namespace mtm {

    Group::Group(const std::string &name, const std::string &clan, int children,
                 int adults, int tools, int food, int morale) : clan_name(
            clan) {
        if (name.empty() || children < 0 || adults < 0 || tools < 0 ||
            food < 0 ||
            morale < 0 || morale > 100 || children + adults == 0) {
            throw GroupInvalidArgs();
        }
        this->group_name = name;
        this->children_number = children;
        this->adult_number = adults;
        this->tools = tools;
        this->food = food;
        this->morale = morale;
    }

    Group::Group(const std::string &name, int children, int adults) {
        *this = Group(name, "", children, adults, 4 * adults,
                      3 * adults + 2 * children, 70);
    }

    const std::string &Group::getName() const {
        return this->group_name;
    }

    int Group::getSize() const {
        return this->adult_number + this->children_number;
    }

    const std::string &Group::getClan() const {
        return this->clan_name;
    }

    void Group::changeClan(const std::string &clan) {
        if (clan == this->clan_name) return;
        if (!clan.empty() && this->clan_name.empty()) {
            this->morale +=int(this->morale * 0.1);
        }
        else if (!this->clan_name.empty() && this->clan_name!=clan) {
            this->morale -= int(this->morale * 0.1);
        }
        if (this->morale>100){
            this->morale=100;
        }
        this->clan_name = clan;
    }

    bool Group::operator<(const Group &rhs) const {
        int this_power = (10*this->adult_number+3*this->children_number)*
                         (10 * this->tools+this->food)*this->morale/100;
        int rhs_power = (10 * rhs.adult_number + 3 * rhs.children_number) *
                        (10 * rhs.tools+rhs.food)*rhs.morale/100;
        if (this_power != rhs_power) {
            return this_power < rhs_power;
        }
        return this->group_name < rhs.group_name;
    }

    bool Group::operator>(const Group &rhs) const {
        return rhs < *this;
    }

    bool Group::operator<=(const Group &rhs) const {
        return (!(*this > rhs));
    }

    bool Group::operator>=(const Group &rhs) const {
        return (!(*this < rhs));
    }

    bool Group::operator==(const Group &rhs) const {
        return (!(*this > rhs || rhs > *this));
    }

    bool Group::operator!=(const Group &rhs) const {
        return !(*this == rhs);
    }

    void Group::separateGroup() {
        this->group_name = "";
        this->clan_name = "";
        this->children_number = 0;
        this->adult_number = 0;
        this->food = 0;
        this->tools = 0;
        this->morale = 0;
    }

    bool Group::unite(Group &other, int max_amount) {
        if (this == &other || this->clan_name != other.clan_name ||
            this->morale < 70 || other.morale < 70 ||
            this->getSize() + other.getSize() > max_amount) {
            return false;
        }
        if (other > *this) {
            this->group_name = other.group_name;
        }
        this->morale =
                (this->getSize() * this->morale +
                 other.getSize() * other.morale)/(this->getSize() +
                                                  other.getSize());
        this->adult_number += other.adult_number;
        this->children_number += other.children_number;
        this->food += other.food;
        this->tools += other.tools;
        other.separateGroup();
        return true;
    }

    void Group::updateAfterFight(Group &loser) {
        int loser_food_loss = ((loser.food+2-1)/2);
        loser.food -= loser_food_loss;
        loser.children_number -=((loser.children_number+3-1)/3);
        loser.adult_number -= ((loser.adult_number+3-1)/3);
        loser.tools -= ((loser.tools+2-1)/2);
        loser.morale -= ((2*loser.morale+10-1)/10);
        if (loser.getSize()==0){
            loser.separateGroup();
        }
        this->adult_number -= this->adult_number / 4;
        this->tools -= this->tools / 4;
        this->food += loser_food_loss / 2;
        this->morale += ((2*this->morale+10-1)/10);
        if (this->morale>100){
            this->morale=100;
        }
    }

    Group Group::divide(const std::string &name) {
        if (name.empty()) {
            throw GroupInvalidArgs();
        }
        if (this->children_number < 2 && this->adult_number < 2) {
            throw GroupCantDivide();
        }
        int other_children_number = this->children_number / 2;
        int other_adults_number = this->adult_number / 2;
        int other_food_number = this->food/2;
        int other_tools_number = this->tools/2;
        this->children_number -= other_children_number;
        this->adult_number -= other_adults_number;
        this->food -= other_food_number;
        this->tools -= other_tools_number;
        return Group(name, this->clan_name, other_children_number,
                     other_adults_number, other_tools_number, other_food_number,
                     this->morale);
    }

    FIGHT_RESULT Group::fight(Group &opponent) {
        if (this == &opponent) {
            throw GroupCantFightWithItself();
        }
        if (this->getSize() == 0 || opponent.getSize() == 0) {
            throw GroupCantFightEmptyGroup();
        }
        if (*this==opponent) return DRAW;
        if (*this > opponent) {
            this->updateAfterFight(opponent);
            return WON;
        }
        opponent.updateAfterFight(*this);
        return LOST;
    }

    void Group::updateAfterTrade(Group &other) {
        int this_offer, other_offer, trade;
        this_offer = (((this->tools - this->food)+2-1)/2);
        other_offer = (((other.food - other.tools)+2-1)/2);
        trade =((this_offer + other_offer+2-1)/2);
        if (trade > this->tools) {
            trade = this->tools;
        }
        if (trade > other.food) {
            trade = other.food;
        }
        this->tools -= trade;
        other.tools += trade;
        this->food += trade;
        other.food -= trade;
    }

    bool Group::trade(Group &other) {
        if (&other == this) {
            throw GroupCantTradeWithItself();
        }
        if (this->tools == this->food) return false;
        if (other.tools == other.food) return false;
        if (this->tools > this->food) {
            if (other.tools > other.food) {
                return false;
            }
            this->updateAfterTrade(other);
        }
        else if (this->tools < this->food) {
            if (other.tools < other.food) {
                return false;
            }
            other.updateAfterTrade(*this);
        }
        return true;
    }

    std::ostream& operator<<(std::ostream& os, const Group& group){
        os<<"Group's name: "<< group.group_name<<std::endl;
        os<<"Group's clan: "<< group.clan_name<<std::endl;
        os<<"Group's children: "<< group.children_number<<std::endl;
        os<<"Group's adults: "<< group.adult_number<<std::endl;
        os<<"Group's tools: "<< group.tools<<std::endl;
        os<<"Group's food: "<< group.food<<std::endl;
        os<<"Group's morale: "<< group.morale<<std::endl;
        return os;
    }
}
