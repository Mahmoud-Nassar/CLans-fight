//
// Created by mahmood on 1/22/2018.
//

#include "../World.h"
#include "testMacros.h"

using namespace mtm;

bool testAddClan() {
    World world;
    ASSERT_EXCEPTION(world.addClan(""),WorldInvalidArgument);
    ASSERT_NO_EXCEPTION(world.addClan("Bidar"));
    ASSERT_NO_EXCEPTION(world.addClan("Mhghal"));
    ASSERT_NO_EXCEPTION(world.addClan("Bahmani"));
    ASSERT_NO_EXCEPTION(world.addClan("Ohgoz"));

    std::ostringstream os;

    world.printClan(os,"Ohgoz");
    ASSERT_TRUE(VerifyOutput(os, "Clan's name: Ohgoz\n"
            "Clan's groups:\n"));
    world.printClan(os,"Mhghal");
    ASSERT_TRUE(VerifyOutput(os, "Clan's name: Mhghal\n"
            "Clan's groups:\n"));
    world.printClan(os,"Bahmani");
    ASSERT_TRUE(VerifyOutput(os, "Clan's name: Bahmani\n"
            "Clan's groups:\n"));
    world.printClan(os,"Bidar");
    ASSERT_TRUE(VerifyOutput(os, "Clan's name: Bidar\n"
            "Clan's groups:\n"));


    ASSERT_EXCEPTION(world.addClan("Bidar"), WorldClanNameIsTaken);
    ASSERT_EXCEPTION(world.addClan("Bahmani"),WorldClanNameIsTaken);
    ASSERT_EXCEPTION(world.addClan("Mhghal"),WorldClanNameIsTaken);
    ASSERT_EXCEPTION(world.addClan("Ohgoz"),WorldClanNameIsTaken);

    ASSERT_NO_EXCEPTION(world.uniteClans
            ("Bidar","Mhghal","Bidar_Mhghal_union"));


    ASSERT_EXCEPTION(world.printClan(os,"Bidar"),WorldClanNotFound);
    ASSERT_EXCEPTION(world.printClan(os,"Mhghal"),WorldClanNotFound);
    ASSERT_EXCEPTION(world.addClan("Mhghal"),WorldClanNameIsTaken);
    ASSERT_EXCEPTION(world.addClan("Bidar"),WorldClanNameIsTaken);


    ASSERT_EXCEPTION(world.addClan(""),WorldInvalidArgument);

    ASSERT_NO_EXCEPTION(world.uniteClans
            ("Ohgoz","Bahmani","Ohgoz_Bahmani_union"));
    ASSERT_EXCEPTION(world.printClan(os,"Ohgoz"),WorldClanNotFound);
    ASSERT_EXCEPTION(world.printClan(os,"Bahmani"),WorldClanNotFound);
    ASSERT_EXCEPTION(world.addClan("Ohgoz"),WorldClanNameIsTaken);
    ASSERT_EXCEPTION(world.addClan("Bahmani"),WorldClanNameIsTaken);

    return true;
}

bool testAddArea() {
    World world;
    ASSERT_EXCEPTION(world.addArea("",PLAIN),WorldInvalidArgument);
    ASSERT_EXCEPTION(world.addArea("",MOUNTAIN),WorldInvalidArgument);
    ASSERT_EXCEPTION(world.addArea("",RIVER),WorldInvalidArgument);
    ASSERT_NO_EXCEPTION(world.addArea("Anadol",PLAIN));
    ASSERT_NO_EXCEPTION(world.addArea("Erciyes",MOUNTAIN));
    ASSERT_NO_EXCEPTION(world.addArea("Filyos",RIVER));

    ASSERT_EXCEPTION(world.addArea("",PLAIN),WorldInvalidArgument);

    ASSERT_EXCEPTION(world.addArea("Anadol",PLAIN),WorldAreaNameIsTaken);
    ASSERT_EXCEPTION(world.addArea("Erciyes",MOUNTAIN),WorldAreaNameIsTaken);
    ASSERT_EXCEPTION(world.addArea("Filyos",RIVER),WorldAreaNameIsTaken);

    return true;
}

bool testAddGroup1() {
    World world;

    ASSERT_EXCEPTION(world.addGroup("Dodrga","Bahmani",1,11,"Anadol")
    ,WorldClanNotFound );

    ASSERT_NO_EXCEPTION(world.addArea("Anadol",PLAIN));
    ASSERT_NO_EXCEPTION(world.addArea("Erciyes",MOUNTAIN));
    ASSERT_NO_EXCEPTION(world.addArea("Filyos",RIVER));

    ASSERT_EXCEPTION(world.addGroup("Dodrga","Bahmani",1,11,"Anadol")
    ,WorldClanNotFound );

    ASSERT_NO_EXCEPTION(world.addClan("Bidar"));
    ASSERT_NO_EXCEPTION(world.addClan("Mhghal"));
    ASSERT_NO_EXCEPTION(world.addClan("Bahmani"));
    ASSERT_NO_EXCEPTION(world.addClan("Ohgoz"));


    ASSERT_EXCEPTION(world.addGroup("Dodrga","",1,11,"Anadol")
    ,WorldClanNotFound );

    ASSERT_EXCEPTION(world.addGroup
            ("","Ohgoz",3,3,"Anadol"),WorldInvalidArgument);
    ASSERT_EXCEPTION(world.addGroup
            ("Dodrga","Ohgoz",-3,9,"Anadol"),WorldInvalidArgument);
    ASSERT_EXCEPTION(world.addGroup
            ("Dodorga","Ohgoz",9,-3,"Anadol"),WorldInvalidArgument);
    ASSERT_EXCEPTION(world.addGroup
            ("Dodorga","Ohgoz",0,0,"Anadol"),WorldInvalidArgument);


    ASSERT_NO_EXCEPTION(world.addGroup("Dodrga","Ohgoz",0,3,"Anadol"));

    ASSERT_EXCEPTION(world.addGroup("Dodrga","Bahmani",1,11,"Anadol")
                         ,WorldGroupNameIsTaken );


    ASSERT_EXCEPTION(world.addGroup("Dodrga","Ohgoz",1,11,"Anadol")
    ,WorldGroupNameIsTaken );


    ASSERT_EXCEPTION(world.addGroup("Dodrga","Mhghal",1,11,"Anadol")
    ,WorldGroupNameIsTaken );


    ASSERT_EXCEPTION(world.addGroup("Dodrga","Bahmani",1,11,"Anadol")
    ,WorldGroupNameIsTaken );


    ASSERT_EXCEPTION(world.addGroup("Dodrga1","this clan does not exist",1,11,
                                    "Anadol"),WorldClanNotFound );

    ASSERT_EXCEPTION(world.addGroup("Dodrga1","t9856&&%%ist",1,11,
                                    ""),WorldClanNotFound );

    ASSERT_EXCEPTION(world.addGroup("Dodrga1","Ohgoz",1,10,
                        "this area does not exist"),WorldAreaNotFound );

    ASSERT_EXCEPTION(world.addGroup("Dodrga1","Ohgoz",1,10,
                                    "mereise"),WorldAreaNotFound );


    ASSERT_NO_EXCEPTION(world.addGroup("OhgozChan","Mhghal",4,0,
                                "Filyos"));

    ASSERT_NO_EXCEPTION(world.addGroup("theBahmanis","Bahmani",5,0,
                                "Erciyes"));

    std::ostringstream os;

    ASSERT_NO_EXCEPTION(world.printGroup(os,"Dodrga"));
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Dodrga\n"
                        "Group's clan: Ohgoz\n"
                        "Group's children: 0\n"
                        "Group's adults: 3\n"
                        "Group's tools: 12\n"
                        "Group's food: 9\n"
                        "Group's morale: 77\n"
                        "Group's current area: Anadol\n"));

    ASSERT_NO_EXCEPTION(world.printGroup(os,"OhgozChan"));
    ASSERT_TRUE(VerifyOutput(os, "Group's name: OhgozChan\n"
            "Group's clan: Mhghal\n"
            "Group's children: 4\n"
            "Group's adults: 0\n"
            "Group's tools: 0\n"
            "Group's food: 8\n"
            "Group's morale: 77\n"
            "Group's current area: Filyos\n"));


    ASSERT_NO_EXCEPTION(world.printGroup(os,"theBahmanis"));
    ASSERT_TRUE(VerifyOutput(os, "Group's name: theBahmanis\n"
            "Group's clan: Bahmani\n"
            "Group's children: 5\n"
            "Group's adults: 0\n"
            "Group's tools: 0\n"
            "Group's food: 10\n"
            "Group's morale: 77\n"
            "Group's current area: Erciyes\n"));


    return true;
}

bool testAddGroup2() {
    World world;

    ASSERT_NO_EXCEPTION(world.addArea("Anadol",PLAIN));
    ASSERT_NO_EXCEPTION(world.addArea("Erciyes",MOUNTAIN));
    ASSERT_NO_EXCEPTION(world.addArea("Filyos",RIVER));

    ASSERT_NO_EXCEPTION(world.addClan("Bidar"));
    ASSERT_NO_EXCEPTION(world.addClan("Mhghal"));
    ASSERT_NO_EXCEPTION(world.addClan("Bahmani"));
    ASSERT_NO_EXCEPTION(world.addClan("Ohgoz"));

    ASSERT_NO_EXCEPTION(world.addGroup("theBahmanis","Bahmani",12,0,
                                       "Anadol"));

    std::ostringstream os;

    ASSERT_NO_EXCEPTION(world.printGroup(os,"theBahmanis"));
    ASSERT_TRUE(VerifyOutput(os, "Group's name: theBahmanis\n"
            "Group's clan: Bahmani\n"
            "Group's children: 6\n"
            "Group's adults: 0\n"
            "Group's tools: 0\n"
            "Group's food: 12\n"
            "Group's morale: 77\n"
            "Group's current area: Anadol\n"));

    ASSERT_NO_EXCEPTION(world.printGroup(os,"theBahmanis_2"));
    ASSERT_TRUE(VerifyOutput(os, "Group's name: theBahmanis_2\n"
            "Group's clan: Bahmani\n"
            "Group's children: 6\n"
            "Group's adults: 0\n"
            "Group's tools: 0\n"
            "Group's food: 12\n"
            "Group's morale: 77\n"
            "Group's current area: Anadol\n"));

    ASSERT_NO_EXCEPTION(world.addGroup("weak_Bahmanis","Bahmani",1,0,
                                       "Anadol"));

    ASSERT_EXCEPTION(world.printGroup(os,"weak_Bahmanis"),WorldGroupNotFound);

    return true;
}

bool testMakeReachableAndMoveGroup() {
    World world;
    ASSERT_EXCEPTION(world.makeReachable("Erciyes","Anadol"),WorldAreaNotFound);
    ASSERT_NO_EXCEPTION(world.addArea("Anadol",PLAIN));
    ASSERT_EXCEPTION(world.makeReachable("Erciyes","Anadol"),WorldAreaNotFound);
    ASSERT_NO_EXCEPTION(world.addArea("Erciyes",MOUNTAIN));
    ASSERT_EXCEPTION(world.moveGroup("Kayi","Filyos"),WorldGroupNotFound);
    ASSERT_EXCEPTION(world.makeReachable("Filyos","Anadol"),WorldAreaNotFound);
    ASSERT_NO_EXCEPTION(world.addArea("Filyos",RIVER));
    ASSERT_NO_EXCEPTION(world.addArea("Marmaris",PLAIN));
    ASSERT_NO_EXCEPTION(world.addArea("Mardin",MOUNTAIN));
    ASSERT_NO_EXCEPTION(world.addArea("Konya",PLAIN));

    ASSERT_NO_EXCEPTION(world.addClan("Bidar"));
    ASSERT_NO_EXCEPTION(world.addClan("Mhghal"));
    ASSERT_NO_EXCEPTION(world.addClan("Bahmani"));
    ASSERT_NO_EXCEPTION(world.addClan("Ohgoz"));


    ASSERT_NO_EXCEPTION(world.makeReachable("Erciyes","Anadol"));
    ASSERT_NO_EXCEPTION(world.makeReachable("Anadol","Erciyes"));
    ASSERT_NO_EXCEPTION(world.makeReachable("Erciyes","Mardin"));
    ASSERT_NO_EXCEPTION(world.makeReachable("Mardin","Anadol"));
    ASSERT_NO_EXCEPTION(world.makeReachable("Marmaris","Mardin"));
    ASSERT_NO_EXCEPTION(world.makeReachable("Konya","Mardin"));
    ASSERT_NO_EXCEPTION(world.makeReachable("Anadol","Konya"));


    ASSERT_NO_EXCEPTION(world.addGroup("Dodrga","Bahmani",0,3,"Anadol"));
    ASSERT_NO_EXCEPTION(world.addGroup("Kayi","Ohgoz",3,3,"Mardin"));

    ASSERT_EXCEPTION(world.moveGroup("Dodrga","a**"),WorldAreaNotFound);
    ASSERT_EXCEPTION
                 (world.moveGroup("Dodrga","Anadol"),WorldGroupAlreadyInArea);
    ASSERT_EXCEPTION
    (world.moveGroup("Dodrga","Mardin"),WorldAreaNotReachable);
    ASSERT_NO_EXCEPTION(world.moveGroup("Dodrga","Erciyes"));
    ASSERT_NO_EXCEPTION(world.moveGroup("Dodrga","Mardin"));//fight

    std::ostringstream os;
    ASSERT_NO_EXCEPTION(world.printGroup(os,"Dodrga"));
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Dodrga\n"
            "Group's clan: Bahmani\n"
            "Group's children: 0\n"
            "Group's adults: 2\n"
            "Group's tools: 6\n"
            "Group's food: 4\n"
            "Group's morale: 61\n"
            "Group's current area: Mardin\n"));

    ASSERT_NO_EXCEPTION(world.printGroup(os,"Kayi"));
    ASSERT_TRUE(VerifyOutput(os, "Group's name: Kayi\n"
            "Group's clan: Ohgoz\n"
            "Group's children: 3\n"
            "Group's adults: 3\n"
            "Group's tools: 9\n"
            "Group's food: 17\n"
            "Group's morale: 93\n"
            "Group's current area: Mardin\n"));

    return true;
}

bool testUniteClansAndMakeFriends() {
    World world;
    ASSERT_EXCEPTION(world.makeFriends("Ohgoz","Bahmani"),WorldClanNotFound);

    ASSERT_NO_EXCEPTION(world.addArea("Anadol",PLAIN));
    ASSERT_NO_EXCEPTION(world.addArea("Erciyes",MOUNTAIN));
    ASSERT_NO_EXCEPTION(world.addArea("Filyos",RIVER));
    ASSERT_NO_EXCEPTION(world.addArea("marmares",PLAIN));

    ASSERT_EXCEPTION(world.makeFriends("Ohgoz","Bahmani"),WorldClanNotFound);

    ASSERT_NO_EXCEPTION(world.addClan("Bidar"));
    ASSERT_NO_EXCEPTION(world.addClan("Mhghal"));
    ASSERT_NO_EXCEPTION(world.addClan("Bahmani"));
    ASSERT_NO_EXCEPTION(world.addClan("Ohgoz"));

    ASSERT_NO_EXCEPTION(world.addGroup("Bahmani1","Bahmani",1,0,
                                       "marmares"));
    ASSERT_NO_EXCEPTION(world.addGroup("Ohgoz1","Ohgoz",1,0,
                                       "Anadol"));
    ASSERT_NO_EXCEPTION(world.addGroup("Bidar1","Bidar",1,0,
                                       "Filyos"));
    ASSERT_NO_EXCEPTION(world.addGroup("Mhghal1","Mhghal",1,0,
                                       "Erciyes"));

    ASSERT_EXCEPTION(world.makeFriends("Ohgozzz","Bahmani"),WorldClanNotFound);
    ASSERT_EXCEPTION(world.makeFriends("Ohgoz","Bahmaniii"),WorldClanNotFound);


    ASSERT_EXCEPTION(world.uniteClans
            ("Ohgoz","Bidar","Bidar"),WorldClanNameIsTaken);
    ASSERT_EXCEPTION(world.uniteClans
            ("Ohgoz","Bidar","Mhghal"),WorldClanNameIsTaken);
    ASSERT_EXCEPTION(world.uniteClans
            ("Ohgoz","Bidarrr","Ohgoz_Bidar_union"),WorldClanNotFound);
    ASSERT_EXCEPTION(world.uniteClans
            ("Ohgooooooz","Bidarrr","Ohgoz_Bidar_union"),WorldClanNotFound);
    ASSERT_EXCEPTION(world.makeFriends("Bidarrr","Bidar"),WorldClanNotFound);
    ASSERT_EXCEPTION(world.makeFriends
            ("Mhghal","Ohgooooooz"),WorldClanNotFound);

    ASSERT_NO_EXCEPTION(world.makeFriends("Bidar","Bahmani"));
    ASSERT_NO_EXCEPTION(world.makeFriends("Mhghal","Ohgoz"));

    ASSERT_NO_EXCEPTION(world.uniteClans
            ("Ohgoz","Bahmani","Ohgoz_Bahmani_union"));

    std::ostringstream os;
    ASSERT_NO_EXCEPTION(world.printClan(os,"Ohgoz_Bahmani_union"));
    ASSERT_TRUE(VerifyOutput(os, "Clan's name: Ohgoz_Bahmani_union\n"
            "Clan's groups:\n"
            "Ohgoz1\n"
            "Bahmani1\n"));

    return true;
}

bool testPrintsExcptions() {
    World world;

    std::ostringstream os;
    ASSERT_EXCEPTION(world.printGroup(os,"any_clan"),WorldGroupNotFound);
    ASSERT_EXCEPTION(world.printClan(os,"any_clan"),WorldClanNotFound);
    ASSERT_EXCEPTION(world.printGroup(os,""),WorldGroupNotFound);
    ASSERT_EXCEPTION(world.printClan(os,""),WorldClanNotFound);

    ASSERT_NO_EXCEPTION(world.addArea("Anadol",PLAIN));
    ASSERT_NO_EXCEPTION(world.addArea("Erciyes",MOUNTAIN));
    ASSERT_NO_EXCEPTION(world.addArea("Filyos",RIVER));
    ASSERT_NO_EXCEPTION(world.addArea("Marmaris",PLAIN));
    ASSERT_NO_EXCEPTION(world.addArea("Mardin",MOUNTAIN));
    ASSERT_NO_EXCEPTION(world.addArea("Konya",PLAIN));

    ASSERT_NO_EXCEPTION(world.addClan("Bidar"));
    ASSERT_NO_EXCEPTION(world.addClan("Mhghal"));
    ASSERT_NO_EXCEPTION(world.addClan("Bahmani"));
    ASSERT_NO_EXCEPTION(world.addClan("Ohgoz"));

    ASSERT_NO_EXCEPTION(world.addGroup("Bahmani1","Bahmani",1,0,
                                       "Anadol"));

    ASSERT_EXCEPTION(world.printGroup(os,"fer(&9&g"),WorldGroupNotFound);
    ASSERT_EXCEPTION(world.printClan(os,"ewrvert&(&"),WorldClanNotFound);
    ASSERT_EXCEPTION(world.printGroup(os,""),WorldGroupNotFound);
    ASSERT_EXCEPTION(world.printClan(os,""),WorldClanNotFound);

    return true;
}

int main(){
    RUN_TEST(testAddClan);
    RUN_TEST(testAddArea);
    RUN_TEST(testAddGroup1);
    RUN_TEST(testAddGroup2);
    RUN_TEST(testMakeReachableAndMoveGroup);
    RUN_TEST(testUniteClansAndMakeFriends);
    RUN_TEST(testPrintsExcptions);
    return 0;
}