class PostgreDBWrapper : public DBWrapper {
private:
	PostgreDBWrapper() = default;
	virtual ~PostgreDBWrapper() {}

	PostgreDBWrapper( const PostgreDBWrapper& ) = delete;
	PostgreDBWrapper& operator=( const PostgreDBWrapper& ) = delete;

protected:
	add_file_record( 
		const std::string& file_id, 
		const std::string& filename, 
		const std::string& file_storage_ref, 
		const std::string& post_id ) override;
public:
	Status& add_user( const User& user_info ) override;
	Status& add_room( const Room& room_info ) override;
	Status& add_post( const Post& post_info ) override;
	Status& add_user_to_room( const std::string& room_id, const std::string& user_id; ) override;
	Status& add_session( const Session& session_info ) override;

	Status& remove_user( const std::string& user_id ) override;
	Status& remove_room( const std::string& room_id ) override;
	Status& remove_post( const std::string& post_id ) override;
	Status& remove_user_from_room( const std::string& room_id, const std::string& user_id ) override;
	Status& remove_session( const std::string& session_id ) override;

	Status& edit_user( const User& user_info ) override;
	Status& edit_room( const Room& room_info ) override;
	Status& edit_post( const Post& post_info ) override;

	User& get_user_info( const std::string& user_id ) override;
	Room& get_room_info( const std::string& room_id ) override;
	Post& get_post_info( const std::string& post_id ) override;
	Session& get_session_info( const std::string& session_id ) override;
}