//
// Created by mahmood on 1/21/2018.
//

#include "Plain.h"
#include <stdexcept>

namespace mtm {

    Plain::Plain(const std::string &name) : Area(name) {}

    void Plain::uniteAndInsert
            (GroupPointer &groupPointer, Clan &clan,const string& clan_name){
        vector<GroupPointer> order_groups=getOrderedGroups();
        for (int i = 0; i <(int)order_groups.size(); i++) {
            if (order_groups[i]->unite(*groupPointer, 3 * clan.getSize())){
                return;
            }
        }
    }

    void Plain::separateAndInsert
          (GroupPointer& groupPointer,Clan& clan,map<string, Clan> &clan_map){
        MtmSet<string> names=getGroupsNames();
        int group_number=2;
        string group_name=groupPointer->getName();
        for (MtmSet<string>::iterator iterator1=names.begin();iterator1!=names
                .end(); iterator1++) {
            if (group_name.size()<iterator1->size()) {
                string current_name=*iterator1;
                current_name.resize(group_name.size());
                if (current_name==group_name) {
                    group_number++;
                }
            }
        }
        string new_name=group_name+="_";
        new_name+=(char)(group_number+48);
        clan.addGroup(groupPointer->divide(new_name));
        groups.push_back(clan_map.at
                (groupPointer->getClan()).getGroup(new_name));
    }

    void Plain::groupArrive(const string &group_name, const string &clan,
                            map<string, Clan> &clan_map) {
         try {
           GroupPointer groupPointer = clan_map.at(clan).getGroup(group_name);
           int clan_size= clan_map.at(clan).getSize();
           checkGroupName(group_name);
           if (groupPointer->getSize()*3<clan_size) {
               uniteAndInsert(groupPointer,clan_map.at(clan),clan);
           }
             else if (groupPointer->getSize()>=10) {
               separateAndInsert(groupPointer,clan_map.at(clan),clan_map);

           }
           groups.push_back(groupPointer);
           areaUpdate();
       }
       catch (std::out_of_range &outOfRange) {
           throw AreaClanNotFoundInMap();
       }
       catch (ClanGroupNotFound &clanGroupNotFound) {
           throw AreaGroupNotInClan();
       }
    }
}