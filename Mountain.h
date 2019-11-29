//
// Created by mahmood on 1/21/2018.
//

#ifndef EX4_MOUNTAIN_H
#define EX4_MOUNTAIN_H

#include "Area.h"

namespace mtm {
    class Mountain : public Area {
        GroupPointer ruler;
        void setRuler(const GroupPointer& leaving_group,const string&
        current_ruler);
    public:

        /**
           * Constructor
           * @param name The name of the Plain
           * @throws AreaInvalidArguments If the name is empty
           */
        explicit Mountain(const std::string &name) ;

        /**
         * get Group into the Mountain
         * if there is no ruler group in the area then the group who is arriving
         * becoumes the ruler
         * if the arriving group and the ruler group bleongs to the same clan
         * then the stronger group becoumes the new ruler of the area
         * if clan of the arriving group is diffrent from clan of the rurler
         * the two groups fight and winner becoumes/stayes the ruler
         * @param group_name The name of the group that get into the Mountain.
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
            * Get a group out of the Mountain.
            * if its not the ruler group then it doesn`t affect any thing
            * if its the ruler group in the mountain , and there is at least
            * one group in the area which belongs to the same clan , then the
            * new ruler group is the strongest group who belongs to the same
            * clan (other than this clan)
            * if its the ruler group in the mountain ,and there`s no other
            * group that belongs to the same clan then the strongest group
            * from any clan becoumes the new ruler , if there`s no group
            * except the levaing group then the mountain becoumes empty with
            * no ruler
            * @param group_name The name of the leaving group.
            * @throws AreaGroupNotFound If there is no group in the area with the
            *  same name;
           */
        void groupLeave(const std::string &group_name) override ;

        /**
  * Destructor
  */
        ~Mountain() = default;
    };
}


#endif //EX4_MOUNTAIN_H
