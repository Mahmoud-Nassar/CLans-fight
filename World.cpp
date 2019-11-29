//
// Created by mahmood on 1/22/2018.
//

#include "World.h"
#include "Plain.h"
#include "Mountain.h"
#include "River.h"
#include <stdexcept>

namespace mtm {

    AreaPtr World::intiatAreaPtr(const string& area_name,AreaType type) {
        AreaPtr areaPtr;
        if (type == PLAIN) {
             areaPtr=AreaPtr(new Plain(area_name));
        } else if (type == RIVER) {
             areaPtr=AreaPtr(new River(area_name));
        }
        else {
            areaPtr=AreaPtr(new Mountain(area_name));
        }
        return areaPtr;
    }

    GroupPointer World::getGroup(const string& group_name) const {
        for (map<string, Clan>::const_iterator iterator1 = clan_map.begin();
             iterator1 != clan_map.end(); iterator1++) {
            if (iterator1->second.doesContain(group_name)) {
                return iterator1->second.getGroup(group_name);
            }
        }
        return nullptr;
    }

    string World::getGroupArea(const string& group_name) const {
        for (map<string, AreaPtr>::const_iterator iterator1 = area_map.begin();
             iterator1 != area_map.end(); iterator1++) {
            AreaPtr area_ptr = iterator1->second;
            if (area_ptr->getGroupsNames().contains(group_name)) {
                return iterator1->first;
            }
        }
        return "";
    }

    void World::addClan(const string& new_clan) {
        try {
            Clan clan_to_insert(new_clan);
            if (all_clan_names.contains(new_clan)) {
                throw WorldClanNameIsTaken();
            }
            clan_map.insert(
                    std::pair<std::string, Clan>(new_clan, clan_to_insert));
            all_clan_names.insert(new_clan);
        }
        catch (ClanEmptyName& clanEmptyName){
            throw WorldInvalidArgument();
        }
    }

    void World::addArea(const string& area_name, AreaType type) {
        try {
            AreaPtr areaPtr=intiatAreaPtr(area_name,type);
            if (area_map.find(area_name)!=area_map.end()) {
                throw WorldAreaNameIsTaken();
            }
            area_map.insert(std::pair<std::string, AreaPtr>(area_name,areaPtr));
        }
        catch (AreaInvalidArguments& areaInvalidArguments) {
            throw WorldInvalidArgument();
        }
    }

    void World::addGroup(const string& group_name, const string& clan_name, int
    num_children, int num_adults, const string& area_name)  {
        try {
            Group arriving_group(group_name,num_children,num_adults);
            if (getGroup(group_name)){
                throw WorldGroupNameIsTaken();
            }
            map<string, Clan>::iterator clan_it=clan_map.find(clan_name);
            if (clan_it==clan_map.end()) {
                throw WorldClanNotFound();
            }
            map<string, AreaPtr>::iterator area_it=area_map.find(area_name);
            if (area_it==area_map.end()) {
                throw WorldAreaNotFound();
            }
            clan_it->second.addGroup(arriving_group);
            area_it->second->groupArrive(group_name,clan_name,clan_map);
        }
        catch (GroupInvalidArgs& groupInvalidArgs) {
            throw WorldInvalidArgument();
        }
    }

    void World::makeReachable(const string& from, const string& to) {
        try {
           if (area_map.find(to)==area_map.end()||
                   area_map.find(from)==area_map.end()) {
               throw WorldAreaNotFound();
           }
           AreaPtr from_ptr= area_map.find(from)->second;
           from_ptr->addReachableArea(to);
        }
        catch (std::out_of_range& outOfRange) {
            throw  WorldAreaNotFound();
        }
    }

    void World::moveGroup(const string& group_name, const string& destination) {
        try {
            if (!getGroup(group_name)) {
                throw WorldGroupNotFound();
            }
            AreaPtr destination_ptr = area_map.at(destination);
            if (destination_ptr->getGroupsNames().contains(group_name)) {
                throw WorldGroupAlreadyInArea();
            }
            AreaPtr from_ptr = area_map.at(getGroupArea(group_name));
            if (from_ptr->getGroupsNames().contains(group_name)) {
                if (!from_ptr->isReachable(destination)) {
                    throw WorldAreaNotReachable();
                }
                from_ptr->groupLeave(group_name);
                destination_ptr->groupArrive(group_name,
                                             getGroup(group_name)->getClan(),
                                             clan_map);
            }
        }
        catch (std::out_of_range &outOfRange) {
            throw WorldAreaNotFound();
        }
    }

    void World::makeFriends(const string& clan1, const string& clan2) {
        try {
            clan_map.at(clan1).makeFriend(clan_map.at(clan2));
        }
        catch (std::out_of_range& outOfRange) {
            throw WorldClanNotFound();
        }
    }

    void World::uniteClans(const string& clan1, const string& clan2, const
    string& new_name) {
        try {
            if (new_name.empty()) {
                throw WorldInvalidArgument();
            }
            if (all_clan_names.contains(new_name)) {
                throw WorldClanNameIsTaken();
            }
            clan_map.insert(std::pair<std::string, Clan>(new_name,clan_map
                    .at(clan1).unite(clan_map.at(clan2),new_name)));
            clan_map.erase(clan2);
            clan_map.erase(clan1);
            all_clan_names.insert(new_name);
        }
        catch (std::out_of_range& outOfRange) {
            throw WorldClanNotFound();
        }
    }

    void World::printGroup(std::ostream& os, const string& group_name) const {
        GroupPointer group_to_print=getGroup(group_name);
        if (!group_to_print) {
            throw WorldGroupNotFound();
        }
        os<<*group_to_print<<"Group's current area: "<< getGroupArea
                (group_name)
          <<std::endl;
    }

    void World::printClan(std::ostream& os, const string& clan_name) const {
        try {
            os<<clan_map.at(clan_name);
        }
        catch (std::out_of_range& outOfRange) {
            throw WorldClanNotFound();
        }
    }
}
