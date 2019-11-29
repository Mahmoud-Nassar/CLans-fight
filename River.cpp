//
// Created by mahmood on 1/21/2018.
//

#include "River.h"
#include <stdexcept>

namespace mtm {

    River::River(const std::string &name) : Area(name) {}

    void River::groupArrive(const string &group_name, const string &clan,
                     map<string, Clan> &clan_map) {
        try {
            GroupPointer groupPointer = clan_map.at(clan).getGroup(group_name);
            checkGroupName(group_name);
            vector<GroupPointer> clan_groups = getOrderedGroups();
            if (!clan_groups.empty()) {
                for (int i=0;i<(int)clan_groups.size();i++) {
                    if (clan==clan_groups[i]->getClan() && groupPointer->trade
                            (*clan_groups[i])) {
                        groups.push_back(groupPointer);
                        return;
                    }
                }
            }
            if (!groups.empty()){
                GroupPointer strongest=getStrongestGroup();
                for (int i=0;i<(int)clan_groups.size();i++) {
                    if (groupPointer->trade(*clan_groups[i])) {
                        break;
                    }
                }
            }
            groups.push_back(groupPointer);
        }
        catch (std::out_of_range& outOfRange) {
            throw AreaClanNotFoundInMap();
        }
        catch (ClanException& clanException) {
            throw AreaGroupNotInClan();
        }
    }
}