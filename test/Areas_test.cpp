//
// Created by mahmood on 1/21/2018.
//
#include "../Area.h"
#include "../Plain.h"
#include "../Mountain.h"
#include "../River.h"
#include "testMacros.h"


using namespace mtm;

typedef std::shared_ptr<Area> AreaPtr;

std::map<std::string, Clan> makeClanMap(){
    std::map<std::string, Clan> clan_map;
    clan_map.insert(std::pair<std::string, Clan>("Bidar", Clan("Bidar")));
    clan_map.insert(std::pair<std::string, Clan>("Mhghal", Clan("Mhghal")));
    clan_map.insert(std::pair<std::string, Clan>("Ohgoz", Clan("Ohgoz")));
    clan_map.insert(std::pair<std::string, Clan>("Bahmani", Clan("Bahmani")));
    return clan_map;
}

bool testExceptions(AreaPtr& areaPtr){
    std::map<std::string, Clan> clan_map = makeClanMap();
    /******* test error throw **************/
    ASSERT_EXCEPTION(areaPtr->groupArrive("any group name", "any clan name",
                                         clan_map),AreaClanNotFoundInMap);
    clan_map.at("Ohgoz").addGroup(Group("Kayi","", 9, 9, 40, 10, 70));
    ASSERT_EXCEPTION(areaPtr->groupArrive("Kayi", "not Ohgoz",
                                         clan_map),AreaClanNotFoundInMap);
    ASSERT_EXCEPTION(areaPtr->groupArrive("not Kayi", "Ohgoz",
                                         clan_map),AreaGroupNotInClan);
    ASSERT_EXCEPTION(areaPtr->groupArrive("", "Ohgoz",
                                         clan_map),AreaGroupNotInClan);
    clan_map.at("Ohgoz").addGroup(Group("weak_Kayi","", 1, 1, 1, 1, 1));
    ASSERT_NO_EXCEPTION(areaPtr->groupArrive("weak_Kayi", "Ohgoz",
                                            clan_map));
    ASSERT_EXCEPTION(areaPtr->groupArrive("weak_Kayi", "Ohgoz",clan_map),
                     AreaGroupAlreadyIn );
    return true;
}

bool plainGroupArrive(){
    AreaPtr anadolExc(new Plain("Anadol"));
    if (!testExceptions(anadolExc)) {
        return false;
    }
    AreaPtr anadol(new Plain("Anadol"));
    std::map<std::string, Clan> clan_map = makeClanMap();
    /***** size of the group > third the size of its clan and lower than 10*/
    clan_map.at("Ohgoz").addGroup(Group("weak_Kayi","", 1, 1, 1, 1, 1));
    ASSERT_NO_EXCEPTION(anadol->groupArrive("weak_Kayi", "Ohgoz",
                                            clan_map));
    clan_map.at("Ohgoz").addGroup(Group("strong_Kayi","", 9, 0, 9, 9,
                                        9));
    ASSERT_NO_EXCEPTION(anadol->groupArrive("strong_Kayi", "Ohgoz",
                                            clan_map));
    ASSERT_TRUE(anadol->getGroupsNames().contains("weak_Kayi"));
    ASSERT_TRUE(anadol->getGroupsNames().contains("strong_Kayi"));
    ASSERT_TRUE(anadol->getGroupsNames().size()==2);

    clan_map.at("Mhghal").addGroup(Group("strong_Mhghal1_2","", 4, 0, 40, 40,
                                         40));
    ASSERT_NO_EXCEPTION(anadol->groupArrive("strong_Mhghal1_2", "Mhghal",
                                            clan_map));
    ASSERT_TRUE(anadol->getGroupsNames().contains("strong_Mhghal1_2"));
    ASSERT_TRUE(anadol->getGroupsNames().contains("strong_Kayi"));
    ASSERT_TRUE(anadol->getGroupsNames().contains("weak_Kayi"));
    ASSERT_TRUE(anadol->getGroupsNames().size()==3);

    clan_map.at("Mhghal").addGroup(Group("strong_Mhghal1_3","", 7, 0, 40, 40,
                                         70));
    ASSERT_NO_EXCEPTION(anadol->groupArrive("strong_Mhghal1_3", "Mhghal",
                                            clan_map));
    ASSERT_TRUE(anadol->getGroupsNames().contains("strong_Mhghal1_2"));
    ASSERT_TRUE(anadol->getGroupsNames().contains("strong_Mhghal1_3"));
    ASSERT_TRUE(anadol->getGroupsNames().contains("strong_Kayi"));
    ASSERT_TRUE(anadol->getGroupsNames().contains("weak_Kayi"));
    ASSERT_TRUE(anadol->getGroupsNames().size()==4);


    clan_map.at("Mhghal").addGroup(Group("strong_Mhghal1","", 11, 0, 40, 40,
                                         40));
    ASSERT_NO_EXCEPTION(anadol->groupArrive("strong_Mhghal1", "Mhghal",
                                            clan_map));
    ASSERT_TRUE(anadol->getGroupsNames().contains("strong_Mhghal1"));

    ASSERT_TRUE(anadol->getGroupsNames().contains("strong_Mhghal1_2"));
    ASSERT_TRUE(anadol->getGroupsNames().contains("strong_Mhghal1"));
    ASSERT_TRUE(anadol->getGroupsNames().contains("strong_Mhghal1_4"));
    ASSERT_TRUE(anadol->getGroupsNames().contains("strong_Mhghal1_3"));
    ASSERT_TRUE(anadol->getGroupsNames().contains("strong_Kayi"));
    ASSERT_TRUE(anadol->getGroupsNames().contains("weak_Kayi"));
    ASSERT_TRUE(anadol->getGroupsNames().size()==6);

    clan_map.at("Mhghal").addGroup(Group("very_weak_Mhghal","", 1, 0, 0, 1,
                                         1));
    ASSERT_NO_EXCEPTION(anadol->groupArrive("very_weak_Mhghal", "Mhghal",
                                            clan_map));

    ASSERT_TRUE(anadol->getGroupsNames().contains("strong_Mhghal1_2"));
    ASSERT_TRUE(anadol->getGroupsNames().contains("very_weak_Mhghal"));
    ASSERT_TRUE(anadol->getGroupsNames().contains("strong_Mhghal1"));
    ASSERT_TRUE(anadol->getGroupsNames().contains("strong_Mhghal1_4"));
    ASSERT_TRUE(anadol->getGroupsNames().contains("strong_Mhghal1_3"));
    ASSERT_TRUE(anadol->getGroupsNames().contains("strong_Kayi"));
    ASSERT_TRUE(anadol->getGroupsNames().contains("weak_Kayi"));
    ASSERT_TRUE(anadol->getGroupsNames().size()==7);

    clan_map.at("Mhghal").addGroup(Group("very_strong_Mhghal","", 600, 0, 0, 1,
                                         1));

    int old_size=clan_map.at("Mhghal").getGroup("strong_Mhghal1_3")->getSize();
    clan_map.at("Mhghal").addGroup(Group("Mhghal_should_unite","", 3, 0, 0, 1,
                                         70));
    ASSERT_NO_EXCEPTION(anadol->groupArrive("Mhghal_should_unite", "Mhghal",
                                            clan_map));

    ASSERT_TRUE(anadol->getGroupsNames().contains("strong_Mhghal1_2"));
    ASSERT_TRUE(anadol->getGroupsNames().contains("very_weak_Mhghal"));
    ASSERT_TRUE(anadol->getGroupsNames().contains("strong_Mhghal1"));
    ASSERT_TRUE(anadol->getGroupsNames().contains("strong_Mhghal1_4"));
    ASSERT_TRUE(anadol->getGroupsNames().contains("strong_Mhghal1_3"));
    ASSERT_TRUE(anadol->getGroupsNames().contains("strong_Kayi"));
    ASSERT_TRUE(anadol->getGroupsNames().contains("weak_Kayi"));
    ASSERT_TRUE(anadol->getGroupsNames().size()==7);
    ASSERT_TRUE(clan_map.at("Mhghal").getGroup("strong_Mhghal1_3")->getSize()==
                   old_size+3);

    return true;
}

bool mountainGroupArrive(){
    AreaPtr erciyesExc(new Mountain("Erciyes"));
    if (!testExceptions(erciyesExc)) {
        return false;
    }
    AreaPtr erciyes(new Mountain("Erciyes"));
    std::map<std::string, Clan> clan_map = makeClanMap();

    clan_map.at("Ohgoz").addGroup(Group("Kayi","", 10, 5, 1, 1, 1));
    ASSERT_NO_EXCEPTION(erciyes->groupArrive("Kayi", "Ohgoz",
                                             clan_map));

   ASSERT_TRUE(clan_map.at("Ohgoz").getGroup("Kayi")->getSize()==15);

    clan_map.at("Mhghal").addGroup(Group("OhgozChan","",8 , 1, 1, 1, 1));
    ASSERT_NO_EXCEPTION(erciyes->groupArrive("OhgozChan", "Mhghal",
                                             clan_map));

    /** oh no !! there was a fight */
    ASSERT_TRUE(clan_map.at("Ohgoz").getGroup("Kayi")->getSize()!=15);
    ASSERT_TRUE(clan_map.at("Mhghal").getGroup("OhgozChan")->getSize()!=9);
    /**************************/

    clan_map.at("Ohgoz").addGroup(Group("dodorga","", 10, 500, 1, 1, 1));
    ASSERT_NO_EXCEPTION(erciyes->groupArrive("dodorga", "Ohgoz",
                                             clan_map));
    /** no fight */
    ASSERT_TRUE(clan_map.at("Ohgoz").getGroup("dodorga")->getSize()==510);
    /**************/
    clan_map.at("Bahmani").addGroup(Group("theBahmanis","", 10, 50, 1, 1, 1));
    ASSERT_NO_EXCEPTION(erciyes->groupArrive("theBahmanis", "Bahmani",
                                             clan_map));

    /** oh no !! there was a fight */
    ASSERT_TRUE(clan_map.at("Ohgoz").getGroup("Kayi")->getSize()!=510);
    ASSERT_TRUE(clan_map.at("Mhghal").getGroup("OhgozChan")->getSize()!=60);
    /**************************/

    clan_map.at("Ohgoz").addGroup(Group("strong_kayi","", 100, 500, 1, 1, 1));
    ASSERT_NO_EXCEPTION(erciyes->groupArrive("strong_kayi", "Ohgoz",
                                             clan_map));
    /** no fight */
    ASSERT_TRUE(clan_map.at("Ohgoz").getGroup("strong_kayi")->getSize()==600);
    /**************/

    clan_map.at("Ohgoz").addGroup(Group("weak_kayi","", 1, 3, 3, 1, 1));
    ASSERT_NO_EXCEPTION(erciyes->groupArrive("weak_kayi", "Ohgoz",
                                             clan_map));
    /** no fight */
    ASSERT_TRUE(clan_map.at("Ohgoz").getGroup("weak_kayi")->getSize()==4);
    /**************/

    return true;
}

bool mountainGroupLeave(){
    AreaPtr erciyes(new Mountain("Erciyes"));
    std::map<std::string, Clan> clan_map = makeClanMap();
    ASSERT_EXCEPTION(erciyes->groupLeave("any group name"),AreaGroupNotFound);
    clan_map.at("Ohgoz").addGroup(Group("Kayi","", 10, 5, 1, 1, 1));
    ASSERT_EXCEPTION(erciyes->groupLeave("not_kayi"),AreaGroupNotFound);
    /***********************************************/
    ASSERT_NO_EXCEPTION(erciyes->groupArrive("Kayi", "Ohgoz",
                                             clan_map));
    clan_map.at("Ohgoz").addGroup(Group("dodorga","", 5, 5, 1, 1, 1));
    ASSERT_NO_EXCEPTION(erciyes->groupArrive("dodorga", "Ohgoz",
                                             clan_map));
    clan_map.at("Ohgoz").addGroup(Group("weak_dodorga","", 2, 2, 1, 1, 1));
    ASSERT_NO_EXCEPTION(erciyes->groupArrive("weak_dodorga", "Ohgoz",
                                             clan_map));

    ASSERT_NO_EXCEPTION(erciyes->groupLeave("Kayi"));

    clan_map.at("Mhghal").addGroup(Group("OhgozChan","",8 , 1, 1, 1, 1));
    ASSERT_NO_EXCEPTION(erciyes->groupArrive("OhgozChan", "Mhghal",
                                             clan_map));

    /** oh no !! there was a fight */
    ASSERT_TRUE(clan_map.at("Ohgoz").getGroup("dodorga")->getSize()==9);
    ASSERT_TRUE(clan_map.at("Ohgoz").getGroup("weak_dodorga")->getSize()==4);
    ASSERT_TRUE(clan_map.at("Mhghal").getGroup("OhgozChan")->getSize()!=9);

    ASSERT_NO_EXCEPTION(erciyes->groupLeave("OhgozChan"));
    /** num of OhgozChan pepole is 5 */
    ASSERT_NO_EXCEPTION(erciyes->groupArrive("OhgozChan", "Mhghal",
                                             clan_map));

    /** oh no !! there was a fight */
    ASSERT_TRUE(clan_map.at("Ohgoz").getGroup("dodorga")->getSize()!=9);
    ASSERT_TRUE(clan_map.at("Ohgoz").getGroup("weak_dodorga")->getSize()==4);
    ASSERT_TRUE(clan_map.at("Mhghal").getGroup("OhgozChan")->getSize()!=5);
    /** num of OhgozChan pepole is 3 */
    ASSERT_NO_EXCEPTION(erciyes->groupLeave("OhgozChan"));
    ASSERT_NO_EXCEPTION(erciyes->groupLeave("dodorga"));

    ASSERT_NO_EXCEPTION(erciyes->groupArrive("OhgozChan", "Mhghal",
                                             clan_map));

    /** oh no !! there was a fight */
    ASSERT_TRUE(clan_map.at("Ohgoz").getGroup("weak_dodorga")->getSize()==4);
    ASSERT_TRUE(clan_map.at("Mhghal").getGroup("OhgozChan")->getSize()!=3);
    /** num of OhgozChan pepole is 2 */
    ASSERT_NO_EXCEPTION(erciyes->groupLeave("OhgozChan"));
    ASSERT_NO_EXCEPTION(erciyes->groupLeave("weak_dodorga"));

    ASSERT_NO_EXCEPTION(erciyes->groupArrive("OhgozChan", "Mhghal",
                                             clan_map));

    ASSERT_TRUE(clan_map.at("Mhghal").getGroup("OhgozChan")->getSize()==2);

    return true;
}

bool riverGroupArrive(){
    AreaPtr filyosExc(new River("Filyos"));
    if (!testExceptions(filyosExc)) {
        return false;
    }
    AreaPtr filyos(new River("Filyos"));

    std::map<std::string, Clan> clan_map = makeClanMap();
    clan_map.at("Ohgoz").addGroup(Group("weak_Kayi","", 1, 1, 1, 1, 1));
    ASSERT_NO_EXCEPTION(filyos->groupArrive("weak_Kayi", "Ohgoz",
                                             clan_map));
    /***** souhld not trade **/
    clan_map.at("Ohgoz").addGroup(Group("Kayi","", 1, 1, 2, 1, 1));
    ASSERT_NO_EXCEPTION(filyos->groupArrive("Kayi", "Ohgoz",
                                            clan_map));

    ASSERT_TRUE(*clan_map.at("Ohgoz").getGroup("Kayi")==
                        Group("Kayi","", 1, 1, 2, 1, 1));

    /***** souhld not trade **/
    clan_map.at("Ohgoz").addGroup(Group("Kayi2","", 1, 1, 10, 1, 1));
    ASSERT_NO_EXCEPTION(filyos->groupArrive("Kayi2", "Ohgoz",
                                            clan_map));

    ASSERT_TRUE(*clan_map.at("Ohgoz").getGroup("Kayi2")==
                        Group("Kayi2","", 1, 1, 10, 1, 1));

    /***** souhld not trade **/
    clan_map.at("Bahmani").addGroup(Group("theBahmanis","", 1, 1, 20, 10, 1));
    ASSERT_NO_EXCEPTION(filyos->groupArrive("theBahmanis", "Bahmani",
                                            clan_map));

    ASSERT_TRUE(*clan_map.at("Bahmani").getGroup("theBahmanis")==
                        Group("theBahmanis","", 1, 1, 20, 10, 1));

    /*******************************************************************/

    AreaPtr filyos2(new River("Filyos"));

    std::map<std::string, Clan> clan_map2 = makeClanMap();
    clan_map2.at("Ohgoz").addGroup(Group("weak_Kayi","", 1, 1, 5, 1, 1));
    ASSERT_NO_EXCEPTION(filyos2->groupArrive("weak_Kayi", "Ohgoz",
                                             clan_map2));

    /***** souhld not trade **/
    clan_map2.at("Ohgoz").addGroup(Group("Kayi","", 1, 1, 100, 1, 1));
    ASSERT_NO_EXCEPTION(filyos2->groupArrive("Kayi", "Ohgoz",
                                             clan_map2));

    ASSERT_TRUE(*clan_map2.at("Ohgoz").getGroup("weak_Kayi")==
                (Group("weak_Kayi","Ohgoz", 1, 1, 5, 1, 1)));

    ASSERT_TRUE(*clan_map2.at("Ohgoz").getGroup("Kayi")==
                        Group("Kayi","Ohgoz", 1, 1, 100, 1, 1));

    /****** should trade with Kayi **/
    clan_map2.at("Bahmani").addGroup(Group("theBahmanis","", 1, 1, 10, 20, 1));
    ASSERT_NO_EXCEPTION(filyos2->groupArrive("theBahmanis", "Bahmani",
                                            clan_map2));

    ASSERT_TRUE(*clan_map2.at("Ohgoz").getGroup("Kayi")!=
                        Group("Kayi","Ohgoz", 1, 1, 100, 1, 1));

    ASSERT_TRUE(*clan_map2.at("Bahmani").getGroup("theBahmanis")!=
                        Group("theBahmanis","Bahmani", 1, 1, 10, 20, 1));

    ASSERT_TRUE(*clan_map2.at("Ohgoz").getGroup("weak_Kayi")==
                (Group("weak_Kayi","Ohgoz", 1, 1, 5, 1, 1)));

    Group current_kayi=*clan_map2.at("Ohgoz").getGroup("Kayi");

    /**** should trade with Kayi **/
    clan_map2.at("Ohgoz").addGroup(Group("Dodorga","", 1, 1, 1, 5, 1));
    ASSERT_NO_EXCEPTION(filyos2->groupArrive("Dodorga", "Ohgoz",
                                             clan_map2));

    ASSERT_TRUE(*clan_map2.at("Ohgoz").getGroup("weak_Kayi")==
                (Group("weak_Kayi","Ohgoz", 1, 1, 5, 1, 1)));

    ASSERT_TRUE(*clan_map2.at("Ohgoz").getGroup("Dodorga")!=
                (Group("Dodorga","Ohgoz", 1, 1, 1, 5, 1)));

    ASSERT_TRUE(*clan_map2.at("Ohgoz").getGroup("Kayi")!=current_kayi);

    return true;
}

bool testSuperClassFunc() {
    AreaPtr anadol(new Plain("Anadol"));
    AreaPtr erciyes(new Mountain("Erciyes"));
    ASSERT_TRUE(anadol->isReachable("Anadol"));
    ASSERT_TRUE(erciyes->isReachable("Erciyes"));
    ASSERT_FALSE(anadol->isReachable("Erciyes"));
    ASSERT_FALSE(anadol->isReachable("Erciyes"));
    ASSERT_NO_EXCEPTION(anadol->addReachableArea("Erciyes"));
    ASSERT_NO_EXCEPTION(anadol->addReachableArea("Erciyes"));
    ASSERT_TRUE(anadol->isReachable("Erciyes"));
    ASSERT_FALSE(erciyes->isReachable("Anadol"));
    ASSERT_NO_EXCEPTION(erciyes->addReachableArea("Anadol"));
    ASSERT_TRUE(anadol->isReachable("Erciyes"));
    ASSERT_TRUE(erciyes->isReachable("Anadol"));
    AreaPtr mardin(new Plain("Mardin"));
    AreaPtr konya(new Plain("Konya"));
    AreaPtr marmaris(new River("Marmaris"));
    ASSERT_NO_EXCEPTION(mardin->addReachableArea("Erciyes"));
    ASSERT_NO_EXCEPTION(anadol->addReachableArea("Mardin"));
    ASSERT_NO_EXCEPTION(mardin->addReachableArea("Marmaris"));
    ASSERT_NO_EXCEPTION(mardin->addReachableArea("Konya"));
    ASSERT_NO_EXCEPTION(konya->addReachableArea("Anadol"));
    /******************************************************/
    ASSERT_TRUE(anadol->isReachable("Erciyes"));
    ASSERT_TRUE(erciyes->isReachable("Anadol"));

    ASSERT_TRUE(mardin->isReachable("Erciyes"));
    ASSERT_FALSE(erciyes->isReachable("Mardin"));

    ASSERT_TRUE(anadol->isReachable("Mardin"));
    ASSERT_FALSE(mardin->isReachable("Anadol"));

    ASSERT_TRUE(mardin->isReachable("Marmaris"));
    ASSERT_FALSE(marmaris->isReachable("Mardin"));

    ASSERT_TRUE(mardin->isReachable("Konya"));
    ASSERT_FALSE(konya->isReachable("Marmaris"));

    ASSERT_TRUE(konya->isReachable("Anadol"));
    ASSERT_FALSE(anadol->isReachable("Konya"));


    ASSERT_TRUE(konya->isReachable("Konya"));
    ASSERT_TRUE(marmaris->isReachable("Marmaris"));
    ASSERT_TRUE(mardin->isReachable("Mardin"));

    /******************************************/
    std::map<std::string, Clan> clan_map = makeClanMap();
    ASSERT_EXCEPTION(marmaris->groupLeave("this group does not exit !!"),
                     AreaGroupNotFound);
    clan_map.at("Ohgoz").addGroup(Group("weak_Kayi","", 1, 1, 1, 1, 1));
    ASSERT_NO_EXCEPTION(anadol->groupArrive("weak_Kayi", "Ohgoz",
                                            clan_map));
    clan_map.at("Ohgoz").addGroup(Group("Kayi","", 2, 2, 2, 2, 2));
    ASSERT_NO_EXCEPTION(anadol->groupArrive("Kayi", "Ohgoz",
                                            clan_map));
    clan_map.at("Ohgoz").addGroup(Group("Dodrga","", 2, 2, 2, 2, 2));
    ASSERT_NO_EXCEPTION(anadol->groupArrive("Dodrga", "Ohgoz",
                                            clan_map));
    clan_map.at("Bahmani").addGroup(Group("theBahmanis","", 1, 1, 10, 20, 1));
    ASSERT_NO_EXCEPTION(anadol->groupArrive("theBahmanis", "Bahmani",
                                            clan_map));
    ASSERT_TRUE(anadol->getGroupsNames().contains("theBahmanis"));
    ASSERT_TRUE(anadol->getGroupsNames().contains("weak_Kayi"));
    ASSERT_TRUE(anadol->getGroupsNames().contains("Kayi"));
    ASSERT_TRUE(anadol->getGroupsNames().contains("Dodrga"));

    ASSERT_EXCEPTION(anadol->groupLeave("this group does not exit !!"),
                     AreaGroupNotFound);

    ASSERT_NO_EXCEPTION(anadol->groupLeave("theBahmanis"));
    ASSERT_FALSE(anadol->getGroupsNames().contains("theBahmanis"));

    ASSERT_NO_EXCEPTION(anadol->groupLeave("weak_Kayi"));
    ASSERT_FALSE(anadol->getGroupsNames().contains("theBahmanis"));
    ASSERT_FALSE(anadol->getGroupsNames().contains("weak_Kayi"));

    ASSERT_NO_EXCEPTION(anadol->groupLeave("Dodrga"));
    ASSERT_FALSE(anadol->getGroupsNames().contains("theBahmanis"));
    ASSERT_FALSE(anadol->getGroupsNames().contains("weak_Kayi"));
    ASSERT_FALSE(anadol->getGroupsNames().contains("Dodrga"));

    ASSERT_NO_EXCEPTION(anadol->groupLeave("Kayi"));
    ASSERT_FALSE(anadol->getGroupsNames().contains("theBahmanis"));
    ASSERT_FALSE(anadol->getGroupsNames().contains("weak_Kayi"));
    ASSERT_FALSE(anadol->getGroupsNames().contains("Dodrga"));
    ASSERT_FALSE(anadol->getGroupsNames().contains("Kayi"));

    ASSERT_EXCEPTION(anadol->groupLeave("theBahmanis"),
                     AreaGroupNotFound);
    ASSERT_EXCEPTION(anadol->groupLeave("weak_Kayi"),
                     AreaGroupNotFound);
    ASSERT_EXCEPTION(anadol->groupLeave("Dodrga"),
                     AreaGroupNotFound);
    ASSERT_EXCEPTION(anadol->groupLeave("Kayi"),
                     AreaGroupNotFound);

    return true;
}

int main(){
    RUN_TEST(plainGroupArrive);
    RUN_TEST(mountainGroupArrive);
    RUN_TEST(mountainGroupLeave);
    RUN_TEST(riverGroupArrive);
    RUN_TEST(testSuperClassFunc);
    return 0;
}