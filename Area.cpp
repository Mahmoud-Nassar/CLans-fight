//
// Created by mahmood on 1/20/2018.
//
#include "Area.h"
#include <stdexcept>

namespace mtm {

    void Area::checkGroupName(const string& name) const {
        for (int i = 0; i < (int)groups.size(); i++) {
            if (groups[i]->getName() == name) {
                throw AreaGroupAlreadyIn();
            }
        }
    }

    GroupPointer Area::getStrongestGroup() const {
        GroupPointer max = groups[0];
        for (int i = 0; i < (int) groups.size(); i++) {
            if (*groups[i] > *max) {
                max = groups[i];
            }
        }
        return max;
    }

    void Area::areaUpdate() {
        for (int i=0;i<(int)groups.size();i++) {
            if (groups[i]->getSize()==0) {
                removeGroupe(i);
            }
        }
    }

    void Area::removeGroupe(int place) {
        vector<GroupPointer> new_groups;
        for (int i=0;i<(int)groups.size();i++) {
            if (i==place) {
                continue;
            }
            new_groups.push_back(groups[i]);
        }
        groups=new_groups;
    }

    vector<GroupPointer> Area::getOrderedGroups() const {
        MtmSet<string> groups_in_area = this->getGroupsNames();
        vector<GroupPointer> groups_to_return;
        for (int i=0;i<(int)groups.size();i++) {
            groups_to_return.push_back(groups[i]);
        }
        for (int i = 0; i <(int)groups_to_return.size(); i++) {
            GroupPointer max = groups_to_return[i];
            int max_j = i;
            for (int j = i; j <(int)groups_to_return.size(); j++) {
                if (*groups_to_return[j] > *max) {
                    max = groups_to_return[j];
                    max_j = j;
                }
            }
            if (*max > *groups_to_return[i]) {
                groups_to_return[max_j] = groups_to_return[i];
                groups_to_return[i] = max;
            }
        }
        return groups_to_return;
    }

    Area::Area(const std::string &name) : reachable_areas() {
        if (name.empty()) {
            throw AreaInvalidArguments();
        }
        this->name=name;
        groups=vector<GroupPointer> ();
    }

    void Area::addReachableArea(const std::string& area_name) {
        reachable_areas.insert(area_name);
    }

    bool Area::isReachable(const std::string& area_name) const {
        if (area_name==name) return true;
        return reachable_areas.contains(area_name);
    }

    void Area::groupArrive(const string& group_name, const string& clan,
                             map<string, Clan>& clan_map) {}

    void Area::groupLeave(const std::string& group_name) {
        for (int i=0;i<(int)groups.size();i++) {
            string temp=groups[i]->getName();
            if (groups[i]->getName()==group_name) {
                removeGroupe(i);
                return;
            }
        }
        throw AreaGroupNotFound();
    }

    MtmSet<std::string> Area::getGroupsNames() const {
        MtmSet<std::string> namesSet;
        for (int i=0;i<(int)groups.size();i++) {
            namesSet.insert(groups[i]->getName());
        }
        return namesSet;
    }

}