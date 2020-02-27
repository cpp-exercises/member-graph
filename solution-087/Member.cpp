#include "Member.h"

int Member::totalCountOfMembersInNetwork = 0;

Member::Member() {
	++totalCountOfMembersInNetwork;
}

Member::~Member() {
	for (Member* m: following) {
		this->unfollow(*m);
	}
	for (Member* m: followers) {
		m->unfollow(*this);
	}
	--totalCountOfMembersInNetwork;
}

void Member::follow(Member& other) {
	following.insert(&other);
	other.followers.insert(this);
}

void Member::unfollow(Member& other) {
	following.erase(&other);
	other.followers.erase(this);
}

