//
// Created by mahmood on 1/16/2018.
//

#include "testMacros.h"
#include "../Group.h"
#include "../exceptions.h"

using namespace mtm;

bool testConstructors(){
    ASSERT_EXCEPTION(Group("","Oghuz",1,1,1,1,1),GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("Kayi","Oghuz",-84,1,1,1,1),GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("Kayi","Oghuz",84,-1,1,1,1),GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("Kayi","Oghuz",84,1,-91,1,1),GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("Kayi","Oghuz",84,1,91,-61,1),GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("Kayi","Oghuz",84,1,91,61,-110),GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("Kayi","Oghuz",-84,-1,-91,-61,-1),GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("Kayi","Oghuz",-84,-1,91,-1,-1),GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("Kayi","Oghuz",-84,1,91,-1,1),GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("Kayi","Oghuz",0,0,91,1,1),GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("Kayi","Oghuz",0,1,91,1,101),GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("Kayi","Oghuz",0,1,91,1,10000),GroupInvalidArgs);

    Group kayi("Kayi", "Oghuz", 10, 10, 40, 50, 0);
    Group dodorga("dodorga", "Oghuz", 20, 30, 40, 50, 100);

    std::ostringstream os;

    os<< kayi;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Kayi\n"
                        "Group's clan: Oghuz\n"
                        "Group's children: 10\n"
                        "Group's adults: 10\n"
                        "Group's tools: 40\n"
                        "Group's food: 50\n"
                        "Group's morale: 0\n"));

    os<< dodorga;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: dodorga\n"
            "Group's clan: Oghuz\n"
            "Group's children: 20\n"
            "Group's adults: 30\n"
            "Group's tools: 40\n"
            "Group's food: 50\n"
            "Group's morale: 100\n"));

    os<< kayi << dodorga;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Kayi\n"
            "Group's clan: Oghuz\n"
            "Group's children: 10\n"
            "Group's adults: 10\n"
            "Group's tools: 40\n"
            "Group's food: 50\n"
            "Group's morale: 0\n"
            "Group's name: dodorga\n"
            "Group's clan: Oghuz\n"
            "Group's children: 20\n"
            "Group's adults: 30\n"
            "Group's tools: 40\n"
            "Group's food: 50\n"
            "Group's morale: 100\n"));

    ASSERT_EXCEPTION(Group("Kayi",-84,1),GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("Kayi",84,-1),GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("Kayi",0,0),GroupInvalidArgs);
    ASSERT_EXCEPTION(Group("",1,1),GroupInvalidArgs);

    Group kayi2("Kayi2", 2, 0);
    Group dodorga2("dodorga2", 12, 10);
    os<< kayi2 << dodorga2;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Kayi2\n"
            "Group's clan: \n"
            "Group's children: 2\n"
            "Group's adults: 0\n"
            "Group's tools: 0\n"
            "Group's food: 4\n"
            "Group's morale: 70\n"
            "Group's name: dodorga2\n"
            "Group's clan: \n" //notice the space!!!!!
            "Group's children: 12\n"
            "Group's adults: 10\n"
            "Group's tools: 40\n"
            "Group's food: 54\n"
            "Group's morale: 70\n"));


    return true;
}

bool testCopyConstructor(){
    Group kayi("Kayi", "Oghuz", 10, 10, 40, 50, 0);
    Group kayi_copy(kayi);

    std::ostringstream os;

    os<< kayi << kayi_copy;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Kayi\n"
            "Group's clan: Oghuz\n"
            "Group's children: 10\n"
            "Group's adults: 10\n"
            "Group's tools: 40\n"
            "Group's food: 50\n"
            "Group's morale: 0\n"
            "Group's name: Kayi\n"
            "Group's clan: Oghuz\n"
            "Group's children: 10\n"
            "Group's adults: 10\n"
            "Group's tools: 40\n"
            "Group's food: 50\n"
            "Group's morale: 0\n"));
    ASSERT_TRUE(kayi==kayi_copy);

    kayi.changeClan("magol");

    os<< kayi << kayi_copy;

    ASSERT_TRUE(VerifyOutput(os, "Group's name: Kayi\n"
            "Group's clan: magol\n"
            "Group's children: 10\n"
            "Group's adults: 10\n"
            "Group's tools: 40\n"
            "Group's food: 50\n"
            "Group's morale: 0\n"
            "Group's name: Kayi\n"
            "Group's clan: Oghuz\n"
            "Group's children: 10\n"
            "Group's adults: 10\n"
            "Group's tools: 40\n"
            "Group's food: 50\n"
            "Group's morale: 0\n"));

    return true;
}

bool testGetName(){
    Group kayi("Kayi", "Oghuz", 10, 10, 40, 50, 0);
    ASSERT_TRUE(kayi.getName()=="Kayi");

    Group kayi1("very_long_name*******", "Oghuz", 10, 10, 40, 50, 0);
    ASSERT_TRUE(kayi1.getName()=="very_long_name*******");

    Group kayi2("name_with_numbers_1515184", 10, 10);
    ASSERT_TRUE(kayi2.getName()=="name_with_numbers_1515184");

    return true;
}

bool testGetSize(){
    Group kayi("Kayi", "Oghuz", 10, 10, 40, 50, 0);
    ASSERT_TRUE(kayi.getSize()==20);

    Group kayi1("Kayi", "Oghuz", 100000, 100530, 40, 50, 0);
    ASSERT_TRUE(kayi1.getSize()==200530);

    Group kayi2("Kayi", "Oghuz", 100000000, 0, 40, 50, 0);
    ASSERT_TRUE(kayi2.getSize()==100000000);

    Group kayi3("Kayi", "Oghuz", 1, 0, 40, 50, 0);
    ASSERT_TRUE(kayi3.getSize()==1);

    return true;
}

bool testChangeClan(){
    Group kayi("Kayi", "Oghuz", 10, 10, 40, 50, 20);
    kayi.changeClan("Oghuz");
    std::ostringstream os;

    os<< kayi;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Kayi\n"
            "Group's clan: Oghuz\n"
            "Group's children: 10\n"
            "Group's adults: 10\n"
            "Group's tools: 40\n"
            "Group's food: 50\n"
            "Group's morale: 20\n"));

    Group kayi1("Kayi", "", 10, 10, 40, 50, 10);
    kayi1.changeClan("");

    os<< kayi1;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Kayi\n"
            "Group's clan: \n"
            "Group's children: 10\n"
            "Group's adults: 10\n"
            "Group's tools: 40\n"
            "Group's food: 50\n"
            "Group's morale: 10\n"));

    kayi1.changeClan("Oghuz");

    os<< kayi1;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Kayi\n"
            "Group's clan: Oghuz\n"
            "Group's children: 10\n"
            "Group's adults: 10\n"
            "Group's tools: 40\n"
            "Group's food: 50\n"
            "Group's morale: 11\n"));

    Group kayi2("Kayi", "", 10, 10, 40, 50, 5);

    kayi2.changeClan("Oghuz");

    os<< kayi2;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Kayi\n"
            "Group's clan: Oghuz\n"
            "Group's children: 10\n"
            "Group's adults: 10\n"
            "Group's tools: 40\n"
            "Group's food: 50\n"
            "Group's morale: 5\n"));

    Group kayi3("Kayi", "", 10, 10, 40, 50, 99);

    kayi3.changeClan("Oghuz");

    os<< kayi3;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Kayi\n"
            "Group's clan: Oghuz\n"
            "Group's children: 10\n"
            "Group's adults: 10\n"
            "Group's tools: 40\n"
            "Group's food: 50\n"
            "Group's morale: 100\n"));

    kayi3.changeClan("Dodorga");

    os<< kayi3;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Kayi\n"
            "Group's clan: Dodorga\n"
            "Group's children: 10\n"
            "Group's adults: 10\n"
            "Group's tools: 40\n"
            "Group's food: 50\n"
            "Group's morale: 90\n"));

    kayi3.changeClan("");

    os<< kayi3;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Kayi\n"
            "Group's clan: \n"
            "Group's children: 10\n"
            "Group's adults: 10\n"
            "Group's tools: 40\n"
            "Group's food: 50\n"
            "Group's morale: 81\n"));

    Group kayi4("Kayi", "Oghuz", 10, 10, 40, 50, 66);

    kayi4.changeClan("");

    os<< kayi4;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Kayi\n"
            "Group's clan: \n"
            "Group's children: 10\n"
            "Group's adults: 10\n"
            "Group's tools: 40\n"
            "Group's food: 50\n"
            "Group's morale: 60\n"));

    return true;
}

bool testCompareOperators(){
    Group kayi("Kayi", "Oghuz", 3, 3, 3, 3, 20);
    Group kayi_copy(kayi);

    ASSERT_TRUE(kayi==kayi_copy);
    ASSERT_TRUE(kayi>=kayi_copy);
    ASSERT_TRUE(kayi<=kayi_copy);

    Group kayi2("Kayz", "Oghuz", 3, 3, 3, 3, 20);

    ASSERT_FALSE(kayi2!=kayi2);
    ASSERT_TRUE(kayi!=kayi2);
    ASSERT_TRUE(kayi2>kayi);
    ASSERT_TRUE(kayi2>=kayi);


    Group dodorga("dodorga", "Oghuz", 3, 3, 3, 4, 20);
    ASSERT_TRUE(dodorga>kayi);
    ASSERT_TRUE(dodorga>kayi2);
    ASSERT_TRUE(dodorga!=kayi);

    return true;
}

bool testGroupUnite(){
    Group kayi("Kayi", "Oghuz", 10, 10, 40, 50, 70);
    Group dodorga("dodorga", "", 20, 30, 40, 50, 100);

    ASSERT_FALSE(kayi.unite(dodorga,100));
    ASSERT_FALSE(dodorga.unite(kayi,100));
    std::ostringstream os;

    os<< kayi;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Kayi\n"
            "Group's clan: Oghuz\n"
            "Group's children: 10\n"
            "Group's adults: 10\n"
            "Group's tools: 40\n"
            "Group's food: 50\n"
            "Group's morale: 70\n"));

    os<< dodorga;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: dodorga\n"
            "Group's clan: \n" //notice the space!!!!!
            "Group's children: 20\n"
            "Group's adults: 30\n"
            "Group's tools: 40\n"
            "Group's food: 50\n"
            "Group's morale: 100\n"));

    Group kayi2("Kayi", "Oghuz", 10, 10, 40, 50, 20);
    Group dodorga2("dodorga", "Oghuz", 20, 30, 40, 50, 100);

    ASSERT_FALSE(kayi2.unite(dodorga2,100));
    ASSERT_FALSE(dodorga2.unite(kayi2,100));

    os<< kayi2;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Kayi\n"
            "Group's clan: Oghuz\n"
            "Group's children: 10\n"
            "Group's adults: 10\n"
            "Group's tools: 40\n"
            "Group's food: 50\n"
            "Group's morale: 20\n"));

    os<< dodorga2;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: dodorga\n"
            "Group's clan: Oghuz\n"

            "Group's children: 20\n"
            "Group's adults: 30\n"
            "Group's tools: 40\n"
            "Group's food: 50\n"
            "Group's morale: 100\n"));

    Group kayi3("Kayi", "Oghuz", 10, 10, 40, 50, 80);
    Group dodorga3("dodorga", "Oghuz", 20, 30, 40, 50, 100);

    ASSERT_FALSE(kayi3.unite(dodorga3,69));
    ASSERT_FALSE(dodorga3.unite(kayi3,69));

    os<< kayi3;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Kayi\n"
            "Group's clan: Oghuz\n"
            "Group's children: 10\n"
            "Group's adults: 10\n"
            "Group's tools: 40\n"
            "Group's food: 50\n"
            "Group's morale: 80\n"));

    os<< dodorga2;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: dodorga\n"
            "Group's clan: Oghuz\n"
            "Group's children: 20\n"
            "Group's adults: 30\n"
            "Group's tools: 40\n"
            "Group's food: 50\n"
            "Group's morale: 100\n"));

    Group kayi4("Kayi", "Oghuz", 3, 3, 3, 3, 81);
    Group dodorga4("dodorga", "Oghuz", 3, 3, 3, 3, 80);

    ASSERT_TRUE(kayi4.unite(dodorga4,12));

    os<<kayi4<<dodorga4;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Kayi\n"
            "Group's clan: Oghuz\n"
            "Group's children: 6\n"
            "Group's adults: 6\n"
            "Group's tools: 6\n"
            "Group's food: 6\n"
            "Group's morale: 80\n"
            "Group's name: \n" // notice the space!!!!!
            "Group's clan: \n" //notice the space!!!!!
            "Group's children: 0\n"
            "Group's adults: 0\n"
            "Group's tools: 0\n"
            "Group's food: 0\n"
            "Group's morale: 0\n"));

    return true;
}

bool testGroupDivide(){
    Group kayi("Kayi", "Oghuz", 7, 7, 7, 7, 70);
    ASSERT_EXCEPTION(kayi.divide(""),GroupInvalidArgs);

    Group kayi1("Kayi", "Oghuz", 1, 1, 40, 50, 70);
    ASSERT_EXCEPTION(kayi1.divide("Dodorga"),GroupCantDivide);

    Group kayi2("Kayi", "Oghuz", 0,1 ,40, 50, 70);
    ASSERT_EXCEPTION(kayi2.divide("Dodorga"),GroupCantDivide);

    Group hayn=kayi.divide("hayn");

    std::ostringstream os;

    os<< kayi << hayn;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Kayi\n"
            "Group's clan: Oghuz\n"
            "Group's children: 4\n"
            "Group's adults: 4\n"
            "Group's tools: 4\n"
            "Group's food: 4\n"
            "Group's morale: 70\n"
            "Group's name: hayn\n"
            "Group's clan: Oghuz\n"
            "Group's children: 3\n"
            "Group's adults: 3\n"
            "Group's tools: 3\n"
            "Group's food: 3\n"
            "Group's morale: 70\n"));



    return true;
}

bool testGroupFight(){
    Group kayi("Kayi", "Oghuz", 7, 7, 7, 7, 70);
    Group dodorga("dodorga", "Oghuz", 1, 0, 40, 50, 100);

    Group temp(dodorga);
    temp.unite(dodorga,100);

    /** dodorga id now empty */

    ASSERT_EXCEPTION(kayi.fight(dodorga),GroupCantFightEmptyGroup);
    ASSERT_EXCEPTION(kayi.fight(kayi),GroupCantFightWithItself);

    Group kayi_copy(kayi);
    ASSERT_NO_EXCEPTION(kayi.fight(kayi_copy));
    ASSERT_TRUE(kayi.fight(kayi_copy)==DRAW);

    std::ostringstream os;
    os<< kayi << kayi_copy;

    ASSERT_TRUE(VerifyOutput(os, "Group's name: Kayi\n"
            "Group's clan: Oghuz\n"
            "Group's children: 7\n"
            "Group's adults: 7\n"
            "Group's tools: 7\n"
            "Group's food: 7\n"
            "Group's morale: 70\n"
            "Group's name: Kayi\n"
            "Group's clan: Oghuz\n"
            "Group's children: 7\n"
            "Group's adults: 7\n"
            "Group's tools: 7\n"
            "Group's food: 7\n"
            "Group's morale: 70\n"));

    Group kayi2("Kayi", "Oghuz", 4, 4, 4, 1, 7);
    Group dodorga2("dodorga", "Oghuz", 5, 5, 5, 5, 7);

    ASSERT_TRUE(kayi2.fight(dodorga2)==LOST);

    os<< kayi2 << dodorga2;
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Kayi\n"
            "Group's clan: Oghuz\n"
            "Group's children: 2\n"
            "Group's adults: 2\n"
            "Group's tools: 2\n"
            "Group's food: 0\n"
            "Group's morale: 5\n"
            "Group's name: dodorga\n"
            "Group's clan: Oghuz\n"
            "Group's children: 5\n"
            "Group's adults: 4\n"
            "Group's tools: 4\n"
            "Group's food: 5\n"
            "Group's morale: 9\n"));

    Group kayi3("Kayi", "Oghuz", 9, 9, 9, 9, 100);
    Group dodorga3("dodorga", "Oghuz", 5, 5, 5, 5, 9);

    ASSERT_TRUE(kayi3.fight(dodorga3)==WON);

    os<< kayi3 << dodorga3;

    ASSERT_TRUE(VerifyOutput(os, "Group's name: Kayi\n"
            "Group's clan: Oghuz\n"
            "Group's children: 9\n"
            "Group's adults: 7\n"
            "Group's tools: 7\n"
            "Group's food: 10\n"
            "Group's morale: 100\n"
            "Group's name: dodorga\n"
            "Group's clan: Oghuz\n"
            "Group's children: 3\n"
            "Group's adults: 3\n"
            "Group's tools: 2\n"
            "Group's food: 2\n"
            "Group's morale: 7\n"));

    Group kayi4("Kayi", "Oghuz", 1, 1, 1, 1, 100);
    Group dodorga4("dodorga", "Oghuz", 1, 1, 1, 1, 10);

    ASSERT_TRUE(kayi4.fight(dodorga4)==WON);

    os<< kayi4 << dodorga4;

    ASSERT_TRUE(VerifyOutput(os, "Group's name: Kayi\n"
            "Group's clan: Oghuz\n"
            "Group's children: 1\n"
            "Group's adults: 1\n"
            "Group's tools: 1\n"
            "Group's food: 1\n"
            "Group's morale: 100\n"
            "Group's name: \n"
            "Group's clan: \n"
            "Group's children: 0\n"
            "Group's adults: 0\n"
            "Group's tools: 0\n"
            "Group's food: 0\n"
            "Group's morale: 0\n"));

    return true;
}

bool testGroupTrade(){
    Group kayi("Kayi", "Oghuz", 7, 7, 7, 7, 70);
    Group kayi_copy(kayi);

    ASSERT_EXCEPTION(kayi.trade(kayi),GroupCantTradeWithItself);
    ASSERT_NO_EXCEPTION(kayi.trade(kayi_copy));

    Group t_equal_f("Kayi", "Oghuz", 7, 7, 2, 2, 70);
    Group kayi2("Kayi", "Oghuz", 7, 7, 9, 7, 70);
    ASSERT_FALSE(t_equal_f.trade(kayi2));
    ASSERT_FALSE(kayi2.trade(t_equal_f));

    std::ostringstream os;

    os << t_equal_f << kayi2;

    ASSERT_TRUE(VerifyOutput(os, "Group's name: Kayi\n"
            "Group's clan: Oghuz\n"
            "Group's children: 7\n"
            "Group's adults: 7\n"
            "Group's tools: 2\n"
            "Group's food: 2\n"
            "Group's morale: 70\n"
            "Group's name: Kayi\n"
            "Group's clan: Oghuz\n"
            "Group's children: 7\n"
            "Group's adults: 7\n"
            "Group's tools: 9\n"
            "Group's food: 7\n"
            "Group's morale: 70\n"));

    Group kayia3("Kayi", "Oghuz", 7, 7, 9, 7, 70);
    Group dodrga3("dodrga", "Oghuz", 7, 7, 9, 7, 70);

    ASSERT_FALSE(dodrga3.trade(kayia3));
    ASSERT_FALSE(kayia3.trade(dodrga3));

    os<< kayia3 << dodrga3;

    ASSERT_TRUE(VerifyOutput(os, "Group's name: Kayi\n"
            "Group's clan: Oghuz\n"
            "Group's children: 7\n"
            "Group's adults: 7\n"
            "Group's tools: 9\n"
            "Group's food: 7\n"
            "Group's morale: 70\n"
            "Group's name: dodrga\n"
            "Group's clan: Oghuz\n"
            "Group's children: 7\n"
            "Group's adults: 7\n"
            "Group's tools: 9\n"
            "Group's food: 7\n"
            "Group's morale: 70\n"));

    Group kayia4("Kayi", "Oghuz", 7, 7, 7, 9, 70);
    Group dodrga4("dodrga", "Oghuz", 7, 7, 7, 9, 70);

    ASSERT_FALSE(dodrga4.trade(kayia4));
    ASSERT_FALSE(kayia4.trade(dodrga4));

    os<< kayia4 << dodrga4;

    ASSERT_TRUE(VerifyOutput(os, "Group's name: Kayi\n"
            "Group's clan: Oghuz\n"
            "Group's children: 7\n"
            "Group's adults: 7\n"
            "Group's tools: 7\n"
            "Group's food: 9\n"
            "Group's morale: 70\n"
            "Group's name: dodrga\n"
            "Group's clan: Oghuz\n"
            "Group's children: 7\n"
            "Group's adults: 7\n"
            "Group's tools: 7\n"
            "Group's food: 9\n"
            "Group's morale: 70\n"));


    Group kayia5("Kayi", "Oghuz", 7, 7, 2, 701, 70);
    Group dodrga5("dodrga", "Oghuz", 7, 7, 2, 1, 70);

    ASSERT_TRUE(dodrga5.trade(kayia5));

    os<< kayia5 << dodrga5;

    ASSERT_TRUE(VerifyOutput(os, "Group's name: Kayi\n"
            "Group's clan: Oghuz\n"
            "Group's children: 7\n"
            "Group's adults: 7\n"
            "Group's tools: 4\n"
            "Group's food: 699\n"
            "Group's morale: 70\n"
            "Group's name: dodrga\n"
            "Group's clan: Oghuz\n"
            "Group's children: 7\n"
            "Group's adults: 7\n"
            "Group's tools: 0\n"
            "Group's food: 3\n"
            "Group's morale: 70\n"));

    Group kayia6("Kayi", "Oghuz", 7, 7, 9, 7, 70);
    Group dodrga6("dodrga", "", 7, 7, 6, 17, 70);

    ASSERT_TRUE(dodrga6.trade(kayia6));

    os<< kayia6 << dodrga6;

    ASSERT_TRUE(VerifyOutput(os, "Group's name: Kayi\n"
            "Group's clan: Oghuz\n"
            "Group's children: 7\n"
            "Group's adults: 7\n"
            "Group's tools: 5\n"
            "Group's food: 11\n"
            "Group's morale: 70\n"
            "Group's name: dodrga\n"
            "Group's clan: \n"
            "Group's children: 7\n"
            "Group's adults: 7\n"
            "Group's tools: 10\n"
            "Group's food: 13\n"
            "Group's morale: 70\n"));

    return true;
}

bool testOutputOperator() {
    //already tested
    return true;
}

int main() {
    RUN_TEST(testConstructors);
    RUN_TEST(testCopyConstructor);
    RUN_TEST(testGetName);
    RUN_TEST(testGetSize);
    RUN_TEST(testChangeClan);
    RUN_TEST(testCompareOperators);
    RUN_TEST(testGroupUnite);
    RUN_TEST(testGroupDivide);
    RUN_TEST(testGroupFight);
    RUN_TEST(testGroupTrade);
    RUN_TEST(testOutputOperator);

    return 0;
}

