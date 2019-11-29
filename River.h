//
// Created by mahmood on 1/21/2018.
//

#ifndef EX4_RIVER_H
#define EX4_RIVER_H

#include "Area.h"

namespace mtm {
    class River : public Area {
    public:
        /**
           * Constructor
           * @param name The name of the Plain
           * @throws AreaInvalidArguments If the name is empty
           */
        explicit River(const std::string &name) ;

        /**
         * get Group into the River
         * if there`s at least one group in the River from the same caln, the
         * arriving group does a trade with the strongest one that can be
         * traded with
         * if there`s no groups from the same clan in the river , the group
         * does a trade with the strongest group in the river that can be
         * traded with
         * if no groups was found to trade with the arriving group does not
         * trade with any group
         * @param group_name The name of the group that get into the area.
         * @param clan The name of the clan that the group belongs to.
         * @param clan_map The map of clans that contains the clan of the group
         * @throws AreaClanNotFoundInMap If there is no clan with the given
         * name in the map.
         * @throws AreaGroupNotInClan If there is no group with the given name
         * in the clan with the given name in the map.
         * @throws AreaGroupAlreadyIn If group with same name already in the
         *  area.
         */
        void groupArrive(const string &group_name, const string &clan,
                         map<string, Clan> &clan_map) override ;

        /**
        * Destructor
        */
        ~River() = default;
    };
}//namespace mtm


#endif //EX4_RIVER_H
