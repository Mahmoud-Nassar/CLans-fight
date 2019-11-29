//
// Created by mahmood on 1/21/2018.
//

#ifndef EX4_PLAIN_H
#define EX4_PLAIN_H

#include "Area.h"

namespace mtm {
    class Plain : public Area {

        /** insert a gorup into (this) area , but first
         * the group unites with the strongest group in the area that belongs
         * to the same clan , if after the union the new group`s size will be
         * bigger than third the size of there clan , the union will not happen
         * @param groupPointer- pointer to the group that should be inserted
         * @param clan-the clan of the group mentioned above
         * @param clan_name- clan name of the group mentioned above
         */
        void uniteAndInsert(GroupPointer &groupPointer, Clan &clan,const
        string& clan_name);
        /** insert a gorup into (this) area , but first
         * the group will be divided into 2 groups , the new group`s name
         * will be "old_group`s_name_x"
         * where old_group`s_name- name of the group before the seperation
         * and x is the lowest number (that is bigger than 2) who`s ,if other
         * gorup has the same name .we add one to the number x .
         * @param groupPointer- pointer to the group that should be inserted
         * @param clan-the clan of the group mentioned above
         */
        void separateAndInsert
          (GroupPointer& groupPointer,Clan& clan,map<string, Clan> &clan_map);
    public:

        /**
           * Constructor
           * @param name The name of the Plain
           * @throws AreaInvalidArguments If the name is empty
           */
        explicit Plain(const std::string &name);

        /**
         * get Group into the plain
         * if size of the group was > third the size of its clan
         * and size of the group was >= 10
         * the group will be divided into 2 groups , the new group`s name
         * will be "old_group`s_name_x"
         * where old_group`s_name- name of the group before the seperation
         * and x is the lowest number (that is bigger than 2) who`s ,if other
         * gorup has the same name .we add one to the number x .
         * if size of the group was < third the size of its clan
         * the group unites with the strongest group in the area that balongs
         * to the same clan , if after the union the new group`s size will be
         * bigger than third the size of there clan , the union will not happen
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
        ~Plain() = default;
    };
}//namespace mtm


#endif //EX4_PLAIN_H
