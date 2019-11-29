//
// Created by mahmood on 1/18/2018.
//


#include "testMacros.h"
#include "../MtmSet.h"

using namespace mtm;

bool testConstructors(){
    /** default constructor testing */
    MtmSet<string> mtmSet1,mtmSet2;
    ASSERT_TRUE(mtmSet1.begin()==mtmSet1.end());
    ASSERT_TRUE(mtmSet1.size()==0);
    ASSERT_TRUE(mtmSet1.empty());
    ASSERT_TRUE(mtmSet1==mtmSet2);
    ASSERT_TRUE(mtmSet1.find("random_string")==mtmSet1.end());
    ASSERT_TRUE(mtmSet1.find("random_string")==mtmSet2.end());
    ASSERT_FALSE(mtmSet1.contains("random_string"));
    ASSERT_TRUE(mtmSet1.isSuperSetOf(mtmSet1));
    ASSERT_TRUE(mtmSet1.isSuperSetOf(mtmSet2));
    ASSERT_TRUE(mtmSet2.isSuperSetOf(mtmSet1));
    const MtmSet<string> const_set;
    ASSERT_TRUE(const_set.begin()==const_set.end());
    ASSERT_TRUE(const_set.size()==0);
    ASSERT_TRUE(const_set.empty());
    ASSERT_TRUE(const_set==mtmSet2);
    ASSERT_TRUE(mtmSet2==const_set);
    ASSERT_TRUE(const_set.find("random_string")==const_set.end());
    ASSERT_TRUE(const_set.find("random_string")==mtmSet2.end());
    ASSERT_FALSE(const_set.contains("random_string"));
    ASSERT_TRUE(const_set.isSuperSetOf(mtmSet1));
    ASSERT_TRUE(const_set.isSuperSetOf(mtmSet2));
    ASSERT_TRUE(const_set.isSuperSetOf(const_set));
    return true;
}

bool testCopyConstructor(){
    MtmSet<string> mtmSet1;
    ASSERT_NO_EXCEPTION(mtmSet1.insert("first_string"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("second_string"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("third_string"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("fourth_string"));
    MtmSet<string> mtmSet2(mtmSet1);
    ASSERT_TRUE(mtmSet1==mtmSet2);
    ASSERT_TRUE(mtmSet1.size()==4&&mtmSet2.size()==4);
    ASSERT_TRUE(mtmSet2.contains("first_string") &&
                mtmSet2.contains("second_string") &&
                mtmSet2.contains("third_string") &&
                mtmSet2.contains("fourth_string"));
    ASSERT_FALSE(mtmSet2.contains("fifth_string"));
    ASSERT_NO_EXCEPTION(mtmSet1.erase("first_string"));
    ASSERT_FALSE(mtmSet1==mtmSet2);

    MtmSet<double> mtmSet3;
    MtmSet<double> mtmSet4(mtmSet3);
    ASSERT_TRUE(mtmSet3==mtmSet4);
    ASSERT_TRUE(mtmSet4.empty());

    const MtmSet<float> mtmSet5;
    MtmSet<float> mtmSet6(mtmSet5);
    ASSERT_TRUE(mtmSet5==mtmSet6);
    ASSERT_TRUE(mtmSet6==mtmSet5);

    return true;
}

bool testSetInsert(){
    MtmSet<string> mtmSet1;
    ASSERT_NO_EXCEPTION(mtmSet1.insert("mahmoud"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("is"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("sick"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("of"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("matam"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert(":("));
    ASSERT_TRUE(mtmSet1.size()==6);
    ASSERT_TRUE(mtmSet1.contains("mahmoud"));
    ASSERT_TRUE(mtmSet1.contains("is"));
    ASSERT_TRUE(mtmSet1.contains("sick"));
    ASSERT_TRUE(mtmSet1.contains("of"));
    ASSERT_TRUE(mtmSet1.contains("matam"));
    ASSERT_TRUE(mtmSet1.contains(":("));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("mahmoud"));
    ASSERT_TRUE(mtmSet1.size()==6);
    ASSERT_TRUE(mtmSet1.contains("mahmoud"));
    mtm::MtmSet<string>::iterator mahmoud=mtmSet1.find("mahmoud");
    mtm::MtmSet<string>::iterator is=mtmSet1.find("is");
    mtm::MtmSet<string>::iterator sick=mtmSet1.find("sick");
    mtm::MtmSet<string>::iterator of=mtmSet1.find("of");
    mtm::MtmSet<string>::iterator matam=mtmSet1.find("matam");
    mtm::MtmSet<string>::iterator sad_face=mtmSet1.find(":(");
    mtm::MtmSet<string>::iterator temp=mtmSet1.begin();
    (++(++(++(++(++(++temp))))))==mtmSet1.end();
    ASSERT_TRUE(*(mtmSet1.insert(","))==",");
    mtm::MtmSet<string>::const_iterator period=mtmSet1.find(",");
    ASSERT_TRUE(*(mtmSet1.insert(","))==*period);
    ASSERT_TRUE(mtmSet1.size()==7);
    ASSERT_TRUE(*mahmoud=="mahmoud");
    ASSERT_TRUE(*is=="is");
    ASSERT_TRUE(*sick=="sick");
    ASSERT_TRUE(*of=="of");
    ASSERT_TRUE(*matam=="matam");
    ASSERT_TRUE(*sad_face==":(");

    return true;
}

bool testSetErase(){
    MtmSet<string> mtmSet1;
    ASSERT_NO_EXCEPTION(mtmSet1.insert("mahmoud"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("is"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("sick"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("of"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("matam"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert(":("));
    ASSERT_NO_EXCEPTION(mtmSet1.erase("nothing"));
    ASSERT_TRUE(mtmSet1.size()==6);
    ASSERT_TRUE(mtmSet1.contains("mahmoud"));
    ASSERT_TRUE(mtmSet1.contains("is"));
    ASSERT_TRUE(mtmSet1.contains("sick"));
    ASSERT_TRUE(mtmSet1.contains("of"));
    ASSERT_TRUE(mtmSet1.contains("matam"));
    ASSERT_TRUE(mtmSet1.contains(":("));
    ASSERT_NO_EXCEPTION(mtmSet1.erase(":("));
    ASSERT_TRUE(mtmSet1.size()==5);
    ASSERT_TRUE(mtmSet1.contains("mahmoud"));
    ASSERT_TRUE(mtmSet1.contains("is"));
    ASSERT_TRUE(mtmSet1.contains("sick"));
    ASSERT_TRUE(mtmSet1.contains("of"));
    ASSERT_TRUE(mtmSet1.contains("matam"));
    ASSERT_NO_EXCEPTION(mtmSet1.erase("sick"));
    ASSERT_TRUE(mtmSet1.size()==4);
    ASSERT_TRUE(mtmSet1.contains("mahmoud"));
    ASSERT_TRUE(mtmSet1.contains("is"));
    ASSERT_TRUE(mtmSet1.contains("of"));
    ASSERT_TRUE(mtmSet1.contains("matam"));
    ASSERT_NO_EXCEPTION(mtmSet1.erase("mahmoud"));
    ASSERT_TRUE(mtmSet1.size()==3);
    ASSERT_TRUE(mtmSet1.contains("is"));
    ASSERT_TRUE(mtmSet1.contains("of"));
    ASSERT_TRUE(mtmSet1.contains("matam"));
    MtmSet<string>::iterator is=mtmSet1.find("is");
    MtmSet<string>::iterator of=mtmSet1.find("of");
    ASSERT_NO_EXCEPTION(mtmSet1.erase(of));
    ASSERT_TRUE(mtmSet1.size()==2);
    ASSERT_TRUE(mtmSet1.contains("is"));
    ASSERT_TRUE(mtmSet1.contains("matam"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("HW4"));
    ASSERT_NO_EXCEPTION(mtmSet1.erase(is));
    ASSERT_TRUE(mtmSet1.size()==2);
    ASSERT_TRUE(mtmSet1.contains("matam"));
    ASSERT_TRUE(mtmSet1.contains("HW4"));
    MtmSet<string>::iterator virtual_element=mtmSet1.end();
    ASSERT_NO_EXCEPTION(mtmSet1.erase(virtual_element));
    ASSERT_TRUE(mtmSet1.size()==2);
    ASSERT_TRUE(mtmSet1.contains("matam"));
    ASSERT_TRUE(mtmSet1.contains("HW4"));

    return true;
}

bool testSetGetSize(){
    MtmSet<string> mtmSet1;
    ASSERT_TRUE(mtmSet1.size()==0);
    ASSERT_NO_EXCEPTION(mtmSet1.insert("mahmoud"));
    ASSERT_TRUE(mtmSet1.size()==1);
    ASSERT_NO_EXCEPTION(mtmSet1.erase("mahmoud"));
    ASSERT_TRUE(mtmSet1.size()==0);
    ASSERT_NO_EXCEPTION(mtmSet1.insert("mahmoud"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("is"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("sick"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("of"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("matam"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert(":("));
    ASSERT_TRUE(mtmSet1.size()==6);
    ASSERT_NO_EXCEPTION(mtmSet1.erase(":("));
    ASSERT_TRUE(mtmSet1.size()==5);
    ASSERT_NO_EXCEPTION(mtmSet1.insert(":("));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("."));
    ASSERT_NO_EXCEPTION(mtmSet1.erase("."));
    ASSERT_TRUE(mtmSet1.size()==6);
    const MtmSet<string> copy(mtmSet1);
    ASSERT_TRUE(copy.size()==6);

    return true;
}

bool testSetIsEmpty(){
    MtmSet<string> mtmSet1;
    ASSERT_TRUE(mtmSet1.empty());
    ASSERT_NO_EXCEPTION(mtmSet1.insert("mahmoud"));
    ASSERT_FALSE(mtmSet1.empty());
    ASSERT_NO_EXCEPTION(mtmSet1.insert("is"));
    ASSERT_FALSE(mtmSet1.empty());
    MtmSet<string> mtmSet2(mtmSet1);
    ASSERT_NO_EXCEPTION(mtmSet1.erase("mahmoud"));
    ASSERT_NO_EXCEPTION(mtmSet1.erase("is"));
    ASSERT_TRUE(mtmSet1.empty());
    ASSERT_NO_EXCEPTION(mtmSet2.clear());
    ASSERT_TRUE(mtmSet2.empty());

    return true;
}

bool testSetClear() {
    MtmSet<string> mtmSet1;
    ASSERT_NO_EXCEPTION(mtmSet1.insert("mahmoud"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("is"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("sick"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("of"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("matam"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert(":("));
    ASSERT_FALSE(mtmSet1.empty());
    ASSERT_NO_EXCEPTION(mtmSet1.clear());
    ASSERT_TRUE(mtmSet1.empty());
    ASSERT_TRUE(mtmSet1.begin()==mtmSet1.end());
    ASSERT_NO_EXCEPTION(mtmSet1.clear());
    ASSERT_NO_EXCEPTION(mtmSet1.insert("mahmoud"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("is"));

    return true;
}

bool testSetBeginAndEnd() {
    MtmSet<string> mtmSet1,mtmSet2;
    ASSERT_TRUE(mtmSet1.begin()==mtmSet1.end());
    ASSERT_NO_EXCEPTION(mtmSet1.insert("mahmoud"));
    MtmSet<string>::iterator first=mtmSet1.begin();
    ASSERT_TRUE(*first=="mahmoud");
    ASSERT_TRUE(++first==mtmSet1.end());
    ASSERT_TRUE(first==mtmSet2.end());
    ASSERT_NO_EXCEPTION(mtmSet1.insert("is"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("sick"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("of"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("matam"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert(":("));
    /** test simple intrsion on the set using set.begin and set.end() */
    int size=mtmSet1.size();
    ASSERT_TRUE(size==6);
    for (MtmSet<string>::const_iterator iterator1=mtmSet1.begin();
         iterator1!=mtmSet1.end();iterator1++) {
        size--;
    }
    ASSERT_FALSE(size);

    return true;
}

bool testSetFindAndContains() {
    MtmSet<string> mtmSet1;
    ASSERT_TRUE(mtmSet1.find("any_thing")==mtmSet1.end());
    ASSERT_FALSE(mtmSet1.contains("any_thing"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("mahmoud"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("is"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("sick"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("of"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("matam"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert(":("));
    ASSERT_TRUE(mtmSet1.contains("mahmoud"));
    ASSERT_TRUE(mtmSet1.contains("is"));
    ASSERT_TRUE(mtmSet1.contains("sick"));
    ASSERT_TRUE(mtmSet1.contains("of"));
    ASSERT_TRUE(mtmSet1.contains("matam"));
    ASSERT_TRUE(mtmSet1.contains(":("));

    mtm::MtmSet<string>::iterator mahmoud=mtmSet1.find("mahmoud");
    mtm::MtmSet<string>::iterator is=mtmSet1.find("is");

    ASSERT_TRUE(mtmSet1.contains(":("));
    ASSERT_TRUE(*mtmSet1.find((":("))==":(");

    ASSERT_TRUE(*mahmoud=="mahmoud");
    ASSERT_TRUE(*is=="is");

    ASSERT_NO_EXCEPTION(mtmSet1.erase("mahmoud"));
    ASSERT_NO_EXCEPTION(mtmSet1.erase("is"));
    ASSERT_NO_EXCEPTION(mtmSet1.erase("sick"));
    ASSERT_NO_EXCEPTION(mtmSet1.erase("of"));
    ASSERT_NO_EXCEPTION(mtmSet1.erase("matam"));
    ASSERT_NO_EXCEPTION(mtmSet1.erase(":("));

    mahmoud=mtmSet1.find("mahmoud");
     is=mtmSet1.find("is");

    ASSERT_TRUE(mahmoud==mtmSet1.end());
    ASSERT_TRUE(is==mtmSet1.end());

    return true;
}

bool testIsSuperSetOf() {
    MtmSet<string> mtmSet1;
    ASSERT_NO_EXCEPTION(mtmSet1.insert("mahmoud"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("is"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("sick"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("of"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("matam"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert(":("));
    MtmSet<string> mtmSet2(mtmSet1);
    ASSERT_TRUE(mtmSet1.isSuperSetOf(mtmSet2));
    ASSERT_TRUE(mtmSet1.isSuperSetOf(mtmSet1));
    ASSERT_TRUE(mtmSet2.isSuperSetOf(mtmSet1));
    ASSERT_TRUE(mtmSet2.isSuperSetOf(mtmSet2));
    MtmSet<string> mtmSet3;
    ASSERT_NO_EXCEPTION(mtmSet3.insert("mahmoud"));
    ASSERT_NO_EXCEPTION(mtmSet3.insert("is"));
    ASSERT_NO_EXCEPTION(mtmSet3.insert("sick"));
    ASSERT_TRUE(mtmSet1.isSuperSetOf(mtmSet3));
    ASSERT_NO_EXCEPTION(mtmSet3.insert("oh no ! this element does not exist"));
    ASSERT_FALSE(mtmSet1.isSuperSetOf(mtmSet3));

    /** test empty set handling */
    MtmSet<double> mtmSet4,mtmSet5;
    ASSERT_TRUE(mtmSet4.isSuperSetOf(mtmSet5));
    ASSERT_TRUE(mtmSet4.isSuperSetOf(mtmSet4));
    ASSERT_TRUE(mtmSet5.isSuperSetOf(mtmSet4));
    ASSERT_TRUE(mtmSet5.isSuperSetOf(mtmSet5));
    ASSERT_NO_EXCEPTION(mtmSet4.insert(-4.5));
    ASSERT_FALSE(mtmSet5.isSuperSetOf(mtmSet4));
    ASSERT_TRUE(mtmSet4.isSuperSetOf((mtmSet5)));
    /***************************/

    /** simple test on diffrent type */
    MtmSet<float> mtmSet6,mtmSet7;
    ASSERT_NO_EXCEPTION(mtmSet6.insert(4.5));
    ASSERT_NO_EXCEPTION(mtmSet6.insert(4.3));
    ASSERT_NO_EXCEPTION(mtmSet7.insert(4.3));
    ASSERT_TRUE(mtmSet6.isSuperSetOf(mtmSet7));
    /**********************************/

    return true;
}

bool testComparisonOperators() {
    MtmSet<string> mtmSet1,mtmSet2;
    ASSERT_TRUE(mtmSet1==mtmSet2);
    ASSERT_TRUE(mtmSet1==mtmSet1);
    ASSERT_FALSE(mtmSet1!=mtmSet2);
    ASSERT_NO_EXCEPTION(mtmSet1.insert("mahmoud"));
    ASSERT_FALSE(mtmSet1==mtmSet2);
    ASSERT_TRUE(mtmSet2!=mtmSet1);
    ASSERT_NO_EXCEPTION(mtmSet1.insert("is"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("sick"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("of"));
    ASSERT_FALSE(mtmSet1==mtmSet2);
    ASSERT_TRUE(mtmSet2!=mtmSet1);
    ASSERT_NO_EXCEPTION(mtmSet1.insert("matam"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert(":("));
    ASSERT_FALSE(mtmSet1==mtmSet2);
    ASSERT_TRUE(mtmSet2!=mtmSet1);
    ASSERT_NO_EXCEPTION(mtmSet2.insert("mahmoud"));
    ASSERT_FALSE(mtmSet1==mtmSet2);
    ASSERT_TRUE(mtmSet2!=mtmSet1);
    ASSERT_NO_EXCEPTION(mtmSet2.insert("is"));
    ASSERT_NO_EXCEPTION(mtmSet2.insert("sick"));
    ASSERT_NO_EXCEPTION(mtmSet2.insert("of"));
    ASSERT_FALSE(mtmSet2==mtmSet1);
    ASSERT_TRUE(mtmSet2!=mtmSet1);
    ASSERT_NO_EXCEPTION(mtmSet2.insert("matam"));
    ASSERT_NO_EXCEPTION(mtmSet2.insert(":("));
    ASSERT_TRUE(mtmSet2==mtmSet1);
    ASSERT_FALSE(mtmSet2!=mtmSet1);

    /** test handilng with empty set */
    MtmSet<string> mtmSet3,mtmSet4;
    ASSERT_NO_EXCEPTION(mtmSet3.insert("mahmoud"));
    ASSERT_FALSE(mtmSet3==mtmSet4);
    ASSERT_TRUE(mtmSet3!=mtmSet4);
    /*********************************/

    return true;
}

bool testSetUnite() {
    MtmSet<string> mtmSet1,mtmSet2;
    ASSERT_NO_EXCEPTION(mtmSet1.unite(mtmSet2));
    ASSERT_TRUE(mtmSet1.empty());
    ASSERT_TRUE(mtmSet2.empty());
    ASSERT_NO_EXCEPTION(mtmSet1.insert("mahmoud"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("is"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("sick"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("of"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("matam"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert(":("));
    MtmSet<string> mtmSet1_copy(mtmSet1),mtmSet5;
    ASSERT_NO_EXCEPTION(mtmSet2.unite(mtmSet1));
    ASSERT_TRUE(mtmSet1==mtmSet1_copy);
    ASSERT_TRUE(mtmSet1==mtmSet2);
    ASSERT_NO_EXCEPTION(mtmSet5.insert(","));
    ASSERT_NO_EXCEPTION(mtmSet5.insert("and"));
    ASSERT_NO_EXCEPTION(mtmSet5.insert("hopes"));
    ASSERT_NO_EXCEPTION(mtmSet5.insert("it"));
    ASSERT_NO_EXCEPTION(mtmSet5.insert("ends"));
    ASSERT_NO_EXCEPTION(mtmSet5.insert("soon"));
    ASSERT_TRUE(mtmSet5!=mtmSet1);
    mtmSet1.unite(mtmSet5);
    ASSERT_TRUE(mtmSet1.size()==12);
    ASSERT_TRUE(mtmSet5.size()==6);
    mtmSet5.unite(mtmSet1);
    ASSERT_TRUE(mtmSet1==mtmSet5);

    ASSERT_TRUE(mtmSet1.contains("mahmoud"));
    ASSERT_TRUE(mtmSet1.contains("is"));
    ASSERT_TRUE(mtmSet1.contains("sick"));
    ASSERT_TRUE(mtmSet1.contains("of"));
    ASSERT_TRUE(mtmSet1.contains("matam"));
    ASSERT_TRUE(mtmSet1.contains(":("));
    ASSERT_TRUE(mtmSet1.contains(","));
    ASSERT_TRUE(mtmSet1.contains("and"));
    ASSERT_TRUE(mtmSet1.contains("hopes"));
    ASSERT_TRUE(mtmSet1.contains("it"));
    ASSERT_TRUE(mtmSet1.contains("ends"));
    ASSERT_TRUE(mtmSet1.contains("soon"));

    /**************************************/
    MtmSet<string> mtmSet6,mtmSet7;
    ASSERT_NO_EXCEPTION(mtmSet6.insert("mahmoud"));
    ASSERT_NO_EXCEPTION(mtmSet6.unite(mtmSet7));
    ASSERT_TRUE(mtmSet6.size()==1);
    ASSERT_TRUE(mtmSet6.contains("mahmoud"));
    ASSERT_FALSE(mtmSet7.contains("mahmoud"));
    /*************************************/

    /** chechking const version */
    MtmSet<string> mtmSet8,mtmSet9;
    ASSERT_NO_EXCEPTION(mtmSet9.insert("mahmoud"));
    ASSERT_NO_EXCEPTION(mtmSet9.insert("is"));
    ASSERT_NO_EXCEPTION(mtmSet9.insert("sick"));
    ASSERT_NO_EXCEPTION(mtmSet9.insert("of"));
    ASSERT_NO_EXCEPTION(mtmSet9.insert("matam"));
    ASSERT_NO_EXCEPTION(mtmSet8.insert(":("));
    const MtmSet<string> const_mtmSet8=mtmSet8;
    const MtmSet<string> const_mtmSet9=mtmSet9;
    ASSERT_TRUE(const_mtmSet8.unite(const_mtmSet9)==
                        const_mtmSet9.unite(const_mtmSet8));
    ASSERT_TRUE(const_mtmSet8.unite(const_mtmSet9).size()==6);
    ASSERT_TRUE(const_mtmSet8.size()==1);
    ASSERT_TRUE(const_mtmSet9.size()==5);
    /***********************************/

    return true;
}

bool testSetIntersect() {
    MtmSet<string> mtmSet1,mtmSet2;
    ASSERT_NO_EXCEPTION(mtmSet1.intersect(mtmSet2));
    ASSERT_TRUE(mtmSet1.empty());
    ASSERT_TRUE(mtmSet2.empty());

    ASSERT_NO_EXCEPTION(mtmSet1.insert("mahmoud"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("is"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("sick"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("of"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("matam"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert(":("));
    ASSERT_NO_EXCEPTION(mtmSet1.intersect(mtmSet2));
    ASSERT_TRUE(mtmSet1.empty());
    ASSERT_TRUE(mtmSet2.empty());

    ASSERT_NO_EXCEPTION(mtmSet1.insert("mahmoud"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("is"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("sick"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("of"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("matam"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert(":("));

    ASSERT_NO_EXCEPTION(mtmSet2.insert("mahmoud"));
    ASSERT_NO_EXCEPTION(mtmSet2.intersect(mtmSet1));
    ASSERT_TRUE(mtmSet2.size()==1);
    ASSERT_TRUE(mtmSet1.size()==6);
    ASSERT_TRUE(mtmSet1.contains("mahmoud"));
    ASSERT_TRUE(mtmSet2.contains("mahmoud"));
    ASSERT_NO_EXCEPTION(mtmSet2.erase("mahmoud"));
    ASSERT_TRUE(mtmSet1.intersect(mtmSet2).empty());

    MtmSet<string> mtmSet3,mtmSet4,mtmSet5;
    ASSERT_NO_EXCEPTION(mtmSet3.insert("mahmoud"));
    ASSERT_NO_EXCEPTION(mtmSet3.insert("is"));
    ASSERT_NO_EXCEPTION(mtmSet3.insert("sick"));

    ASSERT_NO_EXCEPTION(mtmSet4.insert("mahmoud"));
    ASSERT_NO_EXCEPTION(mtmSet4.insert("is"));
    ASSERT_NO_EXCEPTION(mtmSet4.insert(":("));

    ASSERT_NO_EXCEPTION(mtmSet5.insert("is"));

    ASSERT_NO_EXCEPTION(mtmSet3.intersect(mtmSet4));
    ASSERT_TRUE(mtmSet3.size()==2);
    ASSERT_TRUE(mtmSet3.contains("mahmoud"));
    ASSERT_TRUE(mtmSet3.contains("is"));

    ASSERT_TRUE(mtmSet4.size()==3);
    ASSERT_NO_EXCEPTION(mtmSet4.intersect(mtmSet3));
    ASSERT_TRUE(mtmSet4.size()==2);
    ASSERT_TRUE(mtmSet4.contains("mahmoud"));
    ASSERT_TRUE(mtmSet4.contains("is"));

    ASSERT_NO_EXCEPTION(mtmSet3.intersect(mtmSet4).intersect(mtmSet5));
    ASSERT_TRUE(mtmSet3.size()==1);
    ASSERT_TRUE(mtmSet4.size()==2);
    ASSERT_TRUE(mtmSet5.size()==1);

    /****** testing const version *****/
    MtmSet<string> mtmSet6,mtmSet7;
    ASSERT_NO_EXCEPTION(mtmSet7.insert("const"));
    ASSERT_NO_EXCEPTION(mtmSet7.insert("version"));
    ASSERT_NO_EXCEPTION(mtmSet7.insert("testing"));

    MtmSet<string> temp;
    const MtmSet<string> const_mtmSet7=mtmSet7;

    ASSERT_NO_EXCEPTION(temp.insert("this should be deleted"));
    temp=mtmSet7.intersect(mtmSet6);
    ASSERT_TRUE(const_mtmSet7.size()==3);
    ASSERT_TRUE(const_mtmSet7.contains("const"));
    ASSERT_TRUE(const_mtmSet7.contains("testing"));
    ASSERT_TRUE(const_mtmSet7.contains("version"));
    ASSERT_TRUE(mtmSet6.empty());
    ASSERT_TRUE(temp.empty());

    /************************/


    return true;
}

bool isLongerThan5(const string& strnig1) {
    return strnig1.length()>5;
}

bool isEqualTo2(const string& strnig1) {
    return strnig1.length()==2;
}

bool testGetSubSet() {
    MtmSet<string> mtmSet1;
    ASSERT_NO_EXCEPTION(mtmSet1.getSubSet(isLongerThan5));
    ASSERT_TRUE(mtmSet1.empty());

    ASSERT_NO_EXCEPTION(mtmSet1.insert("mahmoud"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("is"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("sick"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("of"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("matam"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert(":((((("));
    ASSERT_NO_EXCEPTION(mtmSet1.getSubSet(isLongerThan5));
    ASSERT_TRUE(mtmSet1.size()==2);
    ASSERT_TRUE(mtmSet1.contains("mahmoud"));
    ASSERT_TRUE(mtmSet1.contains(":((((("));

    ASSERT_NO_EXCEPTION(mtmSet1.insert("mahmoud"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("is"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("sick"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("of"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("matam"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert(":((((("));
    ASSERT_NO_EXCEPTION(mtmSet1.getSubSet(isEqualTo2));
    ASSERT_TRUE(mtmSet1.size()==2);
    ASSERT_TRUE(mtmSet1.contains("is"));
    ASSERT_TRUE(mtmSet1.contains("of"));

    ASSERT_NO_EXCEPTION(mtmSet1.insert("mahmoud"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("is"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("sick"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("of"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("matam"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert(":((((("));
    ASSERT_NO_EXCEPTION(mtmSet1.getSubSet(isLongerThan5).getSubSet(isEqualTo2));
    ASSERT_TRUE(mtmSet1.size()==0);
    ASSERT_FALSE(mtmSet1.contains("is"));
    ASSERT_FALSE(mtmSet1.contains("of"));

    ASSERT_NO_EXCEPTION(mtmSet1.insert("666666"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("7777777"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("88888888"));
    ASSERT_NO_EXCEPTION(mtmSet1.getSubSet(isLongerThan5));
    ASSERT_TRUE(mtmSet1.size()==3);
    ASSERT_NO_EXCEPTION(mtmSet1.contains("666666"));
    ASSERT_NO_EXCEPTION(mtmSet1.contains("7777777"));
    ASSERT_NO_EXCEPTION(mtmSet1.contains("88888888"));

    mtmSet1.clear();

    ASSERT_NO_EXCEPTION(mtmSet1.insert(""));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("1"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("333"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("4444"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("55555"));
    ASSERT_NO_EXCEPTION(mtmSet1.getSubSet(isEqualTo2));
    ASSERT_TRUE(mtmSet1.empty());

    /**** testing const version ***/
    ASSERT_NO_EXCEPTION(mtmSet1.insert("mahmoud"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("is"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("sick"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("of"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("matam"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert(":((((("));

    const MtmSet<string> const_mtmSet1=mtmSet1;
    MtmSet<string> temp=mtmSet1.getSubSet(isEqualTo2);

    ASSERT_TRUE(const_mtmSet1.size()==6);
    ASSERT_TRUE(const_mtmSet1.contains("mahmoud"));
    ASSERT_TRUE(const_mtmSet1.contains("is"));
    ASSERT_TRUE(const_mtmSet1.contains("sick"));
    ASSERT_TRUE(const_mtmSet1.contains("of"));
    ASSERT_TRUE(const_mtmSet1.contains("matam"));
    ASSERT_TRUE(const_mtmSet1.contains(":((((("));

    ASSERT_TRUE(temp.size()==2);
    ASSERT_TRUE(temp.contains("is"));
    ASSERT_TRUE(temp.contains("of"));
    /******************************/

    return true;
}

bool testIteratorUse() {
    MtmSet<string> mtmSet1;
    ASSERT_NO_EXCEPTION(mtmSet1.insert("mahmoud"));
    MtmSet<string>::iterator mahmoud = mtmSet1.find("mahmoud");
    ASSERT_TRUE(mahmoud->length() == 7);
    ASSERT_NO_EXCEPTION(mtmSet1.insert("is"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("sick"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("of"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert("matam"));
    ASSERT_NO_EXCEPTION(mtmSet1.insert(":((((("));
    int size = mtmSet1.size();
    for (MtmSet<string>::iterator iterator1 = mtmSet1.begin();
         iterator1 != mtmSet1.end(); iterator1++) {
        ASSERT_TRUE(*iterator1 == "mahmoud" ||
                    *iterator1 == "is" ||
                    *iterator1 == "sick" ||
                    *iterator1 == "of" ||
                    *iterator1 == "matam" ||
                    *iterator1 == ":(((((");
        size--;
    }
    ASSERT_FALSE(size);

    return true;
}

int main() {
    RUN_TEST(testConstructors);
    RUN_TEST(testCopyConstructor);
    RUN_TEST(testSetInsert);
    RUN_TEST(testSetErase);
    RUN_TEST(testSetGetSize);
    RUN_TEST(testSetIsEmpty);
    RUN_TEST(testSetClear);
    RUN_TEST(testSetBeginAndEnd);
    RUN_TEST(testSetFindAndContains);
    RUN_TEST(testIsSuperSetOf);
    RUN_TEST(testComparisonOperators);
    RUN_TEST(testSetUnite);
    RUN_TEST(testSetIntersect);
    RUN_TEST(testGetSubSet);
    RUN_TEST(testIteratorUse);

    return 0;
}

