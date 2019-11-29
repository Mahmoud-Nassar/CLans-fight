//
// Created by mahmood on 1/19/2018.
//
#include "testMacros.h"
#include "../Clan.h"

using namespace mtm;

bool testConstructors() {
    ASSERT_EXCEPTION(Clan oghoz(""),ClanEmptyName);
    Clan turkish("Turkish");
    ASSERT_EXCEPTION(turkish.getGroup("any group name"),ClanGroupNotFound);
    ASSERT_TRUE(turkish.getSize()==0);
    ASSERT_FALSE(turkish.doesContain("any group name"));
    Clan arab("Arab");
    ostringstream os;
    ASSERT_FALSE(turkish.isFriend(arab));
    ASSERT_NO_EXCEPTION(os << turkish);
    ASSERT_TRUE(VerifyOutput(os, "Clan's name: Turkish\n"
            "Clan's groups:\n"));
    /** testing copy constructor */
    Clan christians("Christians");
    Group kayi("Kayi", "", 10, 10, 40, 50, 100);
    Group dodorga("Dodorga", "", 2, 3, 1, 1, 20);
    ASSERT_NO_EXCEPTION(turkish.addGroup(kayi));
    ASSERT_NO_EXCEPTION(turkish.addGroup(dodorga));
    ASSERT_NO_EXCEPTION(turkish.makeFriend(christians));
    ASSERT_NO_EXCEPTION(os << turkish);
    ASSERT_TRUE(VerifyOutput(os, "Clan's name: Turkish\n"
            "Clan's groups:\n"
            "Kayi\n"
            "Dodorga\n"));
    ASSERT_TRUE(turkish.getSize()==25);
    /** testing copy constructor */
    Clan turkish_Copy(turkish);
    ASSERT_TRUE(turkish_Copy.getSize()==25);
    ASSERT_TRUE(turkish_Copy.doesContain("Kayi"));
    ASSERT_TRUE(turkish_Copy.doesContain("Dodorga"));
    ASSERT_TRUE(turkish_Copy.isFriend(christians));
    ASSERT_NO_EXCEPTION(os << turkish_Copy);
    ASSERT_TRUE(VerifyOutput(os, "Clan's name: Turkish\n"
            "Clan's groups:\n"
            "Kayi\n"
            "Dodorga\n"));
    Clan christians_copy(christians);
    ASSERT_TRUE(christians_copy.getSize()==0);
    ASSERT_FALSE(turkish_Copy.doesContain("any tribe"));
    ASSERT_TRUE(christians_copy.isFriend(turkish_Copy));
    ASSERT_NO_EXCEPTION(os << christians_copy);
    ASSERT_TRUE(VerifyOutput(os, "Clan's name: Christians\n"
            "Clan's groups:\n"));
    /****************************/
    return true;
}

bool testAddGroup() {
    Group kayi("Kayi", "Oghuz", 7, 7, 7, 7, 70);
    Group dodorga("dodorga", "Oghuz", 1, 0, 40, 50, 100);

    Group temp(dodorga);
    temp.unite(dodorga,100);
    Clan turkish("Turkish");
    Clan christians("Christians");
    /** dodorga id now empty */
    ASSERT_EXCEPTION(turkish.addGroup(dodorga),ClanGroupIsEmpty);
    ASSERT_NO_EXCEPTION(turkish.addGroup(kayi));
    ASSERT_EXCEPTION(turkish.addGroup(kayi),ClanGroupNameAlreadyTaken);
    /**********************************************************/
    kayi.changeClan("not_Turkish");
    ASSERT_TRUE(turkish.getGroup("Kayi")->getClan()=="Turkish");
    /**********************************************************/

    ASSERT_NO_EXCEPTION(christians.addGroup(Group("1", "", 1,1,1,1,70)));
    ASSERT_NO_EXCEPTION(christians.addGroup(Group("7", "", 7,1,1,1,70)));
    ASSERT_NO_EXCEPTION(christians.addGroup(Group("3", "", 3,1,1,1,70)));
    ASSERT_NO_EXCEPTION(christians.addGroup(Group("6", "", 6,1,1,1,70)));
    ASSERT_NO_EXCEPTION(christians.addGroup(Group("2", "", 2,1,1,1,70)));
    ASSERT_NO_EXCEPTION(christians.addGroup(Group("9", "", 9,1,1,1,70)));
    ASSERT_NO_EXCEPTION(christians.addGroup(Group("10","", 10,1,1,1,70)));
    ASSERT_NO_EXCEPTION(christians.addGroup(Group("4", "", 4,1,1,1,70)));
    ASSERT_NO_EXCEPTION(christians.addGroup(Group("5", "", 5,1,1,1,70)));
    ASSERT_NO_EXCEPTION(christians.addGroup(Group("8", "", 8,1,1,1,70)));

    ostringstream os;
    ASSERT_NO_EXCEPTION(os<<christians);
    ASSERT_TRUE(VerifyOutput(os, "Clan's name: Christians\n"
            "Clan's groups:\n"
            "10\n"
            "9\n"
            "8\n"
            "7\n"
            "6\n"
            "5\n"
            "4\n"
            "3\n"
            "2\n"
            "1\n"));

    return true;
}

bool testGetGroup() {
    Clan turkish("Turkish");
    ASSERT_EXCEPTION(turkish.getGroup("any group name"),ClanGroupNotFound);
    Group kayi("Kayi", "Oghuz", 7, 7, 7, 7, 70);
    Group dodorga("Dodorga", "Oghuz", 1, 3, 40, 50, 100);
    ASSERT_NO_EXCEPTION(turkish.addGroup(kayi));
    ASSERT_NO_EXCEPTION(turkish.addGroup(dodorga));
    ASSERT_EXCEPTION(turkish.getGroup("Kayiiii"),ClanGroupNotFound);
    ASSERT_TRUE(turkish.getGroup("Kayi")->getName()=="Kayi");
    ASSERT_TRUE(turkish.getGroup("Kayi")->getClan()=="Turkish");
    ASSERT_TRUE(turkish.getGroup("Dodorga")->getName()=="Dodorga");
    ASSERT_TRUE(turkish.getGroup("Dodorga")->getClan()=="Turkish");
    ASSERT_EXCEPTION(turkish.getGroup("any group name"),ClanGroupNotFound);
    {
        Group turkish_kayi=*turkish.getGroup("Kayi");
        Group turkish_dodorga=*turkish.getGroup("Kayi");
    }
    ASSERT_TRUE(turkish.getGroup("Kayi")->getName()=="Kayi");
    ASSERT_TRUE(turkish.getGroup("Kayi")->getClan()=="Turkish");
    ASSERT_TRUE(turkish.getGroup("Dodorga")->getName()=="Dodorga");
    ASSERT_TRUE(turkish.getGroup("Dodorga")->getClan()=="Turkish");

    return true;
}

bool testDoesContain () {
    Clan turkish("Turkish");
    ASSERT_FALSE(turkish.doesContain("any group name"));
    Group kayi("Kayi", "Oghuz", 7, 7, 7, 7, 70);
    Group dodorga("Dodorga", "Oghuz", 1, 3, 40, 50, 100);
    ASSERT_NO_EXCEPTION(turkish.addGroup(kayi));
    ASSERT_NO_EXCEPTION(turkish.addGroup(dodorga));
    ASSERT_FALSE(turkish.doesContain("Kayiiii"));
    ASSERT_TRUE(turkish.doesContain("Dodorga"));
    ASSERT_TRUE(turkish.doesContain("Dodorga"));

    return true;
}

bool testGetSize() {
    Clan turkish("Turkish");
    ASSERT_TRUE(turkish.getSize()==0);
    Group kayi("Kayi", "Oghuz", 7, 7, 7, 7, 70);
    Group dodorga("Dodorga", "Oghuz", 1, 3, 40, 50, 100);
    ASSERT_NO_EXCEPTION(turkish.addGroup(kayi));
    ASSERT_TRUE(turkish.getSize()==14);
    ASSERT_NO_EXCEPTION(turkish.addGroup(dodorga));
    ASSERT_TRUE(turkish.getSize()==18);

    Group temp(kayi);
    /*************************/
    Group weakDodorga("weakDodorga", "Oghuz", 1, 0, 0, 0, 1);
    ASSERT_NO_EXCEPTION(turkish.addGroup(weakDodorga));
    ASSERT_TRUE(turkish.getSize()==19);
    ASSERT_NO_EXCEPTION(turkish.getGroup("weakDodorga"));
    ASSERT_NO_EXCEPTION(turkish.getGroup("weakDodorga")->fight(temp));
    ASSERT_TRUE(turkish.getSize()==18);

    return true;
}

bool testClanUnite() {
    Clan turkish("Turkish");
    Clan christians("Christians");
    /************************************/
    Group kayi("Kayi", "random", 30, 30, 1, 1, 1);
    Group dodorga("Dodorga", "random", 20, 20, 1, 1, 1);
    Group protestant("Protestant","random", 10, 10, 1, 1, 1);
    Group catholic("Catholic", "random", 5, 5, 1, 1, 1);
    ASSERT_NO_EXCEPTION(turkish.addGroup(kayi));
    ASSERT_NO_EXCEPTION(turkish.addGroup(dodorga));
    ASSERT_NO_EXCEPTION(christians.addGroup(catholic));
    ASSERT_NO_EXCEPTION(christians.addGroup(protestant));
    /****************************************/
    ASSERT_EXCEPTION(christians.unite(turkish,""),ClanEmptyName);
    ASSERT_TRUE(christians.getSize()==30);
    ASSERT_TRUE(turkish.getSize()==100);
    ASSERT_TRUE(turkish.doesContain("Kayi"));
    ASSERT_TRUE(turkish.doesContain("Dodorga"));
    ASSERT_TRUE(christians.doesContain("Protestant"));
    ASSERT_TRUE(christians.doesContain("Catholic"));
    /******************************************/
    ASSERT_EXCEPTION(christians.unite(christians,"Christians"),ClanCantUnite);
    ASSERT_TRUE(christians.getSize()==30);
    ASSERT_TRUE(turkish.getSize()==100);
    ASSERT_TRUE(turkish.doesContain("Kayi"));
    ASSERT_TRUE(turkish.doesContain("Dodorga"));
    ASSERT_TRUE(christians.doesContain("Protestant"));
    ASSERT_TRUE(christians.doesContain("Catholic"));
    /******************************************/
    Clan kayi_clan("Kayi");
    ASSERT_NO_EXCEPTION(kayi_clan.addGroup(kayi));
    ASSERT_EXCEPTION(kayi_clan.unite(turkish,"Christians"),ClanCantUnite);
    ASSERT_TRUE(kayi_clan.getSize()==60);
    ASSERT_TRUE(turkish.getSize()==100);
    ASSERT_TRUE(turkish.doesContain("Kayi"));
    ASSERT_TRUE(turkish.doesContain("Dodorga"));
    ASSERT_TRUE(christians.doesContain("Protestant"));
    ASSERT_TRUE(christians.doesContain("Catholic"));
    /*****************************************/
    Clan roman("Roman"),arab("Arab");
    ASSERT_NO_EXCEPTION(turkish.makeFriend(arab));
    ASSERT_NO_EXCEPTION(turkish.makeFriend(roman));
    ASSERT_NO_EXCEPTION(turkish.unite(christians,"Turkish_Cristian_UN"));
    ASSERT_TRUE(turkish.doesContain("Protestant"));
    ASSERT_TRUE(turkish.doesContain("Catholic"));
    ASSERT_TRUE(turkish.doesContain("Kayi"));
    ASSERT_TRUE(turkish.doesContain("Dodorga"));
    ASSERT_TRUE(turkish.getGroup("Protestant")->getClan()
                        =="Turkish_Cristian_UN");
    ASSERT_TRUE(turkish.getGroup("Catholic")->getClan()=="Turkish_Cristian_UN");
    ASSERT_TRUE(turkish.getGroup("Kayi")->getClan()=="Turkish_Cristian_UN");
    ASSERT_TRUE(turkish.getGroup("Dodorga")->getClan()=="Turkish_Cristian_UN");
    ASSERT_TRUE(turkish.getSize()==130);
    ASSERT_TRUE(turkish.isFriend(arab));
    ASSERT_TRUE(turkish.isFriend(roman));
    ASSERT_TRUE(christians.getSize()==0);
    ASSERT_FALSE(christians.doesContain("Protestant"));
    ASSERT_FALSE(christians.doesContain("Catholic"));
    ostringstream os;
    ASSERT_NO_EXCEPTION(os << turkish);
    ASSERT_TRUE(VerifyOutput(os, "Clan's name: Turkish_Cristian_UN\n"
            "Clan's groups:\n"
            "Kayi\n"
            "Dodorga\n"
            "Protestant\n"
            "Catholic\n"));
    /***************************************************/
    Group collina("Collina", "random", 1, 1, 1, 1, 1);
    Group banuTaym("BanuTaym", "random", 500, 60, 1, 1, 1);
    ASSERT_NO_EXCEPTION(arab.addGroup(banuTaym));
    ASSERT_NO_EXCEPTION(roman.addGroup(collina));
    ASSERT_NO_EXCEPTION(arab.unite(turkish.unite
            (roman,"Turkish_Cristian_UN"),"Greatest_UN"));
    ASSERT_NO_EXCEPTION(os << arab);
    ASSERT_TRUE(VerifyOutput(os, "Clan's name: Greatest_UN\n"
            "Clan's groups:\n"
            "BanuTaym\n"
            "Kayi\n"
            "Dodorga\n"
            "Protestant\n"
            "Catholic\n"
            "Collina\n"));
    ASSERT_TRUE(arab.getGroup("Protestant")->getClan() =="Greatest_UN");
    ASSERT_TRUE(arab.getGroup("Catholic")->getClan()=="Greatest_UN");
    ASSERT_TRUE(arab.getGroup("Kayi")->getClan()=="Greatest_UN");
    ASSERT_TRUE(arab.getGroup("Dodorga")->getClan()=="Greatest_UN");
    ASSERT_TRUE(arab.getGroup("Collina")->getClan()=="Greatest_UN");
    ASSERT_TRUE(arab.getGroup("BanuTaym")->getClan()=="Greatest_UN");

    return true;
}

bool testMakeFriendAndIsFriend() {
    Clan turkish("Turkish");
    Clan christians("Christians");
    ASSERT_FALSE(turkish.isFriend(christians));
    ASSERT_FALSE(christians.isFriend(turkish));
    ASSERT_NO_EXCEPTION(turkish.makeFriend(christians));
    ASSERT_TRUE(turkish.isFriend(christians));
    ASSERT_TRUE(christians.isFriend(turkish));
    ASSERT_NO_EXCEPTION(turkish.makeFriend(christians));
    ASSERT_TRUE(turkish.isFriend(christians));
    ASSERT_TRUE(christians.isFriend(turkish));
    return true;
}

bool testOutputOperator() {
    //already tested
    return true;
}

int main() {
    RUN_TEST(testConstructors);
    RUN_TEST(testAddGroup);
    RUN_TEST(testGetGroup);
    RUN_TEST(testDoesContain);
    RUN_TEST(testGetSize);
    RUN_TEST(testClanUnite);
    RUN_TEST(testMakeFriendAndIsFriend);
    RUN_TEST(testOutputOperator);
    return 0;
}