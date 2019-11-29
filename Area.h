#ifndef MTM4_AREA_H
#define MTM4_AREA_H

#include <string>
#include <map>
#include "Clan.h"
#include "Group.h"
#include <vector>
#include <memory>
#include "exceptions.h"

using std::string;
using std::shared_ptr;
using std::map;

namespace mtm{
    
    /**
     * An abstract call of an area in the world.
     * Assume every name is unique.
     * Groups that become empty, should be removed from the area.
     */
    class Area {
        MtmSet<string> reachable_areas;

    protected:
        std::vector<GroupPointer> groups;
        string name;
        /**
        * removes all the empty groups(groups with no peepole) from the area
        * (this)
        */
        void areaUpdate();
        /** assumes that is 0 < place < groups.size()
         * removes the group (from this groups vector) which it`s place in the
         * groups vector = paramter place
         * @param place - index to the group that should be removed
         */
        void removeGroupe(int place) ;
        /**
         * @return a poiner for the strongest group in the river
         * assumes that there`s at least one grouop in the river
         */
        GroupPointer getStrongestGroup() const;
        /**
         * checks if there`s a group with the same name in the area
         * @param name- name to check
         * @throws AreaGroupAlreadyIn if a group found with name equal to
         * (parameter) name
         */
        void checkGroupName(const string& name) const;
        /**
         * get the groups in area
         * @return ordered vector of GroupPointers , where the
         * pointer=vector[0] points to the strongest group in the area, the
         * pointer=vector[1] points to the second strongest group in the
         * area...
         */
        vector<GroupPointer> getOrderedGroups() const;

    public:
        /**
         * Constructor
         * @param name The name of the area
         * @throws AreaInvalidArguments If the name is empty
         */
        explicit Area(const std::string &name);

        /**
         * Disable copy constructor
         */
        Area(const Area &) = delete;

        /**
         * Disable assignment operator
         */
        Area &operator=(const Area &) = delete;

        /**
         * Destructor
         */
        virtual ~Area() = default;

        /**
         * Add an area, that can be reachable from this area.
         * Doesn't mean that this area is reachable from the area with the
         * given name.
         * @param area_name The name of the area that can be reachable from
         *  this are.
         */
        void addReachableArea(const std::string &area_name);

        /**
         * Check if an area is reachable from this area.
         * An area is always reachable from itself.
         * @param area_name The name of the area to check if it's reachable.
         * @return True if the area with the given name is reachable from
         * this area, and false otherwise.
         */
        bool isReachable(const std::string &area_name) const;

        /**
         * Get a group into the area.
         * @param group_name The name of the group that get into the area.
         * @param clan The name of the clan that the group belongs to.
         * @param clan_map The map of clans that contains the clan of the group
         * @throws AreaClanNotFoundInMap If there is no clan with the given
         * name in the map.
         * @throws AreaGroupNotInClan If there is no group with the given name
         * in the clan with the given name in the map.
         * @throws AreaGroupAlreadyIn If group with same name already in the
         *  area.
         *
         */
        virtual void groupArrive(const string &group_name, const string &clan,
                                 map<string, Clan> &clan_map);

        /**
             * Get a group out of the area.
             * @param group_name The name of the leaving group.
             * @throws AreaGroupNotFound If there is no group in the area with the
             *  same name;
            */
        virtual void groupLeave(const std::string &group_name);

        /**
         * Get a set of the names of all the groups in the area.
         * @return A set that contains the names of all the groups in the area.
         */
        MtmSet<std::string> getGroupsNames() const;
    };
} //namespace mtm

#endif //MTM4_AREA_H
