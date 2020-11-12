class DBWrapper {
public:
	DBWrapper() = default;
	virtual ~DBWrapper() {}

	DBWrapper( const DBWrapper& ) = delete;
	DBWrapper& operator=( const DBWrapper& ) = delete;

protected:
	// для добавления расположения файла в Storage в таблицу files в БД
	virtual add_file_record( 
		const std::string& file_id, 
		const std::string& filename, 
		const std::string& file_storage_ref, 
		const std::string& post_id ) = 0;

public:
	// TODO: решить, где будет генерация id для user и room (мб в DataManager)
	virtual Status& add_user( const std::string& user_id, const User& user_info ) = 0;
	virtual Status& add_room( const std::string& room_id, const Room& room_info ) = 0;
	virtual Status& add_post( const std::string& post_id, const Post& post_info ) = 0; // room_id and user_id inside Post
	virtual Status& add_user_to_room( const std::string& room_id, const std::string& user_id ) = 0;
	virtual Status& add_session( const std::string& session_id, const Session& session_info ) = 0;

	virtual Status& remove_user( const std::string& user_id ) = 0;
	virtual Status& remove_room( const std::string& room_id ) = 0;
	virtual Status& remove_post( const std::string& post_id ) = 0;
	virtual Status& remove_user_from_room( const std::string& room_id, const std::string& user_id ) = 0;
	virtual Status& remove_session( const std::string& session_id ) = 0;

	virtual Status& edit_user( const User& user_info ) = 0;
	virtual Status& edit_room( const Room& room_info ) = 0;
	virtual Status& edit_post( const Post& post_info ) = 0;

	virtual User& get_user_info( const std::string& user_id ) = 0;
	virtual Room& get_room_info( const std::string& room_id ) = 0;
	virtual Post& get_post_info( const std::string& post_id ) = 0;
	virtual Session& get_session_info( const std::string& session_id ) = 0;
}