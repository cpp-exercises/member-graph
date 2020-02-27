#pragma once

#include <set>
#include <string>
using namespace std;

class Member {
	set<Member*> following;  // members that I follow
	set<Member*> followers;  // members that follow me
	static int totalCountOfMembersInNetwork;

public:
	Member();
	~Member();

	void follow   (Member& other);
	void unfollow (Member& other);

	int numFollowing() const { return following.size();	}
	int numFollowers() const { return followers.size();	}

	static int count() { return totalCountOfMembersInNetwork; }
};
