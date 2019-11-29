//
// Created by mahmood on 1/19/2018.
//

#include "Clan.h"

using std::endl;

namespace mtm {

    const GroupPointer& Clan::getGroupPointer
            (const std::string& group_name) const {
        int i = 0;
        for (; i < (int) groups.size(); i++) {
            if (groups[i]->getName() == group_name) {
                break;
            }
        }
        return groups[i];
    }

    void Clan::insertGroupByOrder(const GroupPointer& group,int place) {
        vector<GroupPointer> new_groups;
        for (int i=0;i<(int)groups.size()+1;i++) {
            if (i<place) {
                new_groups.push_back(groups[i]);
            }
            else if (i==place) {
                new_groups.push_back(group);
            }
            else {
                new_groups.push_back(groups[i-1]);
            }
        }
        groups=new_groups;
    }

    Clan::Clan(const std::string& name) {
        if (name.empty()) {
            throw ClanEmptyName();
        }
        this->clan_name=name;
        this->groups=vector<GroupPointer>();
    }

    Clan::Clan(const Clan& other) : clan_name(other.clan_name) , clan_friends
            (other.clan_friends) {
        for (int i=0;i<(int)other.groups.size();i++) {
            groups.push_back(std::make_shared<Group>(*other.groups[i]));
        }
    }

    void Clan::addGroup(const Group& group) {
        if (group.getSize()==0) {
            throw ClanGroupIsEmpty();
        }
        GroupPointer groupPointer=std::make_shared<Group>(Group(group));
        groupPointer->changeClan(clan_name);
        int index=groups.size();
        for (int i=0;i<(int)groups.size();i++) {
            if (group.getName()==groups[i]->getName()) {
                throw ClanGroupNameAlreadyTaken();
            }
            if (*groups[i]<*groupPointer) {
                index=i;
                break;
            }
        }
        this->insertGroupByOrder(groupPointer,index);
    }

    const GroupPointer& Clan::getGroup(const std::string& group_name) const {
        if (!doesContain(group_name)) {
            throw ClanGroupNotFound();
        }
        return getGroupPointer(group_name);
    }

    bool Clan::doesContain(const std::string& group_name) const {
        int found=0;
        for (int i = 0; i < (int) groups.size(); i++) {
            if (groups[i]->getName() == group_name) {
                found=1;
            }
        }
        return found;
    }

    int Clan::getSize() const {
        int pepoles_number=0;
        for (int i=0;i<(int)groups.size();i++) {
            pepoles_number+=groups[i]->getSize();
        }
        return pepoles_number;
    }

    bool Clan::checkIfGroupsDiffrent(const Clan& other) const {
        for (int i=0;i<(int)groups.size();i++) {
            for (int j=0;j<(int)other.groups.size();j++) {
                if (groups[i]->getName() == other.groups[j]->getName()) {
                    return false;
                }
            }
        }
        return true;
    }

    Clan& Clan::unite(Clan& other, const std::string& new_name) {
        if (new_name.empty()) {
            throw ClanEmptyName();
        }
        if (clan_name==other.clan_name || !this->checkIfGroupsDiffrent(other)){
            throw ClanCantUnite();
        }
        this->clan_friends.unite(other.clan_friends);
        for (int i=0;i<(int)other.groups.size();i++) {
            if (!this->doesContain(other.groups[i]->getName())) {
                this->addGroup(*other.groups[i]);
            }
        }
        this->clan_name=new_name;
        for (int i=0;i<(int)groups.size();i++) {
            groups[i]->changeClan(new_name);
        }
        other.groups=vector<GroupPointer>();
        this->clan_friends=clan_friends.unite(other.clan_friends);
        return *this;
    }

    void Clan::makeFriend(Clan& other) {
        if (this->isFriend(other)) return;
        clan_friends.insert(other.clan_name);
        other.clan_friends.insert(clan_name);
    }

    bool Clan::isFriend(const Clan& other) const {
        if (clan_name==other.clan_name) return true;
        return clan_friends.contains(other.clan_name);
    }

    std::ostream& operator<<(std::ostream& os, const Clan& clan) {
        os << "Clan's name: " << clan.clan_name <<endl ;
        os << "Clan's groups:" <<endl ;
        for (int i=0;i<(int)clan.groups.size();i++) {
            os << clan.groups[i]->getName() <<endl;
        }
        return os;
    }
}