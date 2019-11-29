//
// Created by mahmood on 1/21/2018.
//

#include "Mountain.h"
#include <stdexcept>


namespace mtm {

    void Mountain::setRuler(const GroupPointer& leaving_group,const string&
    current_ruler) {
        if (leaving_group->getName() == ruler->getName()) {
            vector<GroupPointer> clan_groups = getOrderedGroups();
            if (!clan_groups.empty()) {
                for (int i = 0; i < (int) clan_groups.size(); i++) {
                    if (clan_groups[i]->getClan()==leaving_group->getClan() &&
                            clan_groups[i]->getName() != current_ruler) {
                        ruler = clan_groups[i];
                        break;
                    }
                }
            } else if (groups.empty()) {
                ruler = std::shared_ptr<Group>(nullptr);
            } else {
                ruler = getStrongestGroup();
            }
        }
    }

    Mountain::Mountain(const std::string &name) : Area(name) {
        ruler=std::shared_ptr<Group>(nullptr);
    }

    void Mountain::groupArrive(const string &group_name, const string &clan,
                               map<string, Clan> &clan_map) {
        try {
            GroupPointer groupPointer = clan_map.at(clan).getGroup(group_name);
            checkGroupName(group_name);
            if (!ruler) {
                ruler=groupPointer;
            }
            else if (ruler->getClan()==groupPointer->getClan()) {
                if (*ruler<*groupPointer) {
                    ruler=groupPointer;
                }
            }
            else if (groupPointer->fight(*ruler)==WON) {
                ruler=groupPointer;
            }
            groups.push_back(groupPointer);
        }
        catch (std::out_of_range& outOfRange) {
            throw AreaClanNotFoundInMap();
        }
        catch (ClanGroupNotFound& clanGroupNotFound) {
            throw AreaGroupNotInClan();
        }
    }

    void Mountain::groupLeave(const std::string &group_name) {
        GroupPointer leaving_group=std::shared_ptr<Group>(nullptr);
        int i=0;
        for (;i<(int)groups.size();i++) {
            if (groups[i]->getName()==group_name) {
                leaving_group=groups[i];
                break;
            }
        }
        if (!leaving_group) {
            throw AreaGroupNotFound();
        }
        removeGroupe(i);
        setRuler(leaving_group,group_name);
    }
}