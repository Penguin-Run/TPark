struct User {
	User( std::string& _id, std::string& _nick_name, std::vector<std::pair<std::string, Rights>>& _rooms, std::string& _email = nullptr ) : 
		id(_id), 
		nick_name(_nick_name), 
		email(_email),
		rooms(_rooms) {}

	std::string id;
	std::string nick_name;
	std::string email;

	std::vector<std::pair<std::string, Rights>> rooms; // pair: room_id, rights

	// TODO: fill Users DB table and finish struct
}

struct Room {
	Room( std::string& _id, std::string& _room_name, std::vector<std::pair<std::string, Rights>>& _users ) : 
	id(_id),
	room_name(_room_name),
	users(_users) {}

	std::string id;
	std::string room_name;
	// std::string description;

	std::vector<std::pair<std::string, Rights>> users; // pair: user_id, rights

	// TODO: consider adding list of posts id in (?)

	// TODO: fill Rooms DB table and finish struct
}

enum Rights {
	CREATOR,
	ADMIN,
	MEMBER
}

struct Post {
	std::string id;
	std::string room_id; 
	std::string user_id; // post author

	std::string discipline;
	std::string category;

	std::string text;

	// TODO: Post on add and Post on get methods will propably have different vector values (on get - file ids in BD)
	// solve this problem (maybe template class, or separate classes, or move it from class or smth different..)
	std::vector<std::string> attachments; // list of files, that is attached to post
}

struct Session {
	Session( std::string& _id, std::string& _user_id ) : id(_id), user_id(_user_id) {}

	std::string id;
	std::string user_id;

	// TODO: fill Sessions DB table and finish struct
}