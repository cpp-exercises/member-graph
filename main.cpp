#include <iostream>
#include "Member.h"

using std::cout, std::endl;

bool EXPECT_EQ(int num1 , int num2 )
{
    return num1 == num2 ;
}

bool adding_followers()
{
    cout << "adding_followers" << endl;
    bool pass = true ;
    Member dana ,chana, avi ;
    chana.follow(dana);
    dana.follow(avi);
    pass = pass && EXPECT_EQ(chana.numFollowers(),0);
    pass = pass && EXPECT_EQ(chana.numFollowing(),1);
    pass = pass && EXPECT_EQ(avi.numFollowers(),1);
    pass = pass && EXPECT_EQ(avi.numFollowing(),0);
    pass = pass && EXPECT_EQ(Member::count(),3);
    return pass;
}
bool unfollow()
{
    cout << "unfollow" << endl;
    bool pass = true ;

    Member dana ,chana, avi ;
    chana.follow(dana);
    dana.follow(avi);
    pass = pass && EXPECT_EQ(avi.numFollowers(),1);
    dana.unfollow(avi);
    pass = pass && EXPECT_EQ(avi.numFollowers(),0);
    pass = pass && EXPECT_EQ(Member::count(),3);
    return pass;
}
bool unfollow_wont_delete_oun_followers()
{
    cout << "unfollow_wont_delete_own_Followers" << endl;
    bool pass = true ;
    Member avi,dana ;
    pass = pass && EXPECT_EQ(dana.numFollowers(),0);
    avi.follow(dana);
    pass = pass && EXPECT_EQ(dana.numFollowers(),1);
    dana.unfollow(avi);
    pass = pass && EXPECT_EQ(dana.numFollowers(),1);
    return pass;
}

bool destructing_followers1 ()
{
    cout << "destructing followers" << endl;
    bool pass = true ;
    // are followers deleted properly ,
    Member* dana = new Member;
    Member* avi = new Member;
    Member* chana = new Member;
    pass = pass && EXPECT_EQ(Member::count(),3);
    delete avi;
    pass = pass && EXPECT_EQ(Member::count(),2);
    delete chana;
    pass = pass && EXPECT_EQ(Member::count(),1);
    delete dana;
    pass = pass && EXPECT_EQ(Member::count(),0);
    return pass;
}
bool duplicateUnfollow()
{
    cout << "duplicate unfollow" << endl;
    bool pass = true ;
    Member avi,dana ;
    pass = pass && EXPECT_EQ(avi.numFollowers(),0);
    pass = pass && EXPECT_EQ(avi.numFollowing(),0);
    avi.unfollow(dana);
    pass = pass && EXPECT_EQ(avi.numFollowers(),0);
    pass = pass && EXPECT_EQ(avi.numFollowing(),0);
    return pass;
}
bool duplicateFollow ()
{
    cout << "duplicate follow" << endl;
    bool pass = true ;
    // are followers deleted properly
    Member* chana = new Member;
    Member* avi = new Member;
    pass = pass && EXPECT_EQ(Member::count(),2);
    chana->follow(*avi);
    chana->follow(*avi);
    pass = pass && EXPECT_EQ(avi->numFollowers(),1);
    delete chana ;
    delete avi ;
    return pass;
}
bool destructing_followers2()
{
    cout << "destructing followers 2" << endl;
    bool pass = true ;
    // are followers deleted properly ,
    Member* chana = new Member;
    Member* avi = new Member;
    pass = pass && EXPECT_EQ(Member::count(),2);
    chana->follow(*avi);
    avi->follow(*chana);
    pass = pass && EXPECT_EQ(avi->numFollowers(),1);
    pass = pass && EXPECT_EQ(avi->numFollowing(),1);
    delete chana ;
    pass = pass && EXPECT_EQ(avi->numFollowers(),0);
    pass = pass && EXPECT_EQ(avi->numFollowing(),0);
    delete avi ;
    return pass;
}
bool followMyself()
{
    cout << "follow myself" << endl;
    bool pass = true ;
    Member you;
    pass = pass && EXPECT_EQ(you.numFollowing(),0);
    pass = pass && EXPECT_EQ(you.numFollowers(),0);
    you.follow(you);
    pass = pass && EXPECT_EQ(you.numFollowing(),0);
    pass = pass && EXPECT_EQ(you.numFollowers(),0);
    you.unfollow(you);
    pass = pass && EXPECT_EQ(you.numFollowing(),0);
    pass = pass && EXPECT_EQ(you.numFollowers(),0);
    return pass;

}

int main()
{
    int passingTests = 0 ;
    int failingTests = 0 ;
    cout << "main.cpp start" << endl;
    adding_followers()? ++passingTests : ++failingTests;
    unfollow()? ++passingTests : ++failingTests;
    unfollow_wont_delete_oun_followers()? ++passingTests : ++failingTests;
    destructing_followers1()? ++passingTests : ++failingTests;
    duplicateUnfollow()? ++passingTests : ++failingTests;
    duplicateFollow()? ++passingTests : ++failingTests;
    destructing_followers2()? ++passingTests : ++failingTests;
    followMyself()? ++passingTests : ++failingTests;
    double calculated_grade = passingTests * 100.0 /(passingTests+failingTests);
    std::cout << "\n*** Right: " << passingTests << ". Wrong: " << failingTests << ". Grade: " << calculated_grade << " ***\n";
}
