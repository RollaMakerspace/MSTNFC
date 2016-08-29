#ifndef AES128KEY
#define AES128KEY

#include <vector>
#include <string>
#include <unistd.h>

class AES128Key {
public:
	/**
		Constructs the object with existing key data.

		@param[key_data] A 32 byte long vector<uint8_t> containing key data.
	*/
	AES128Key(vector<uint8_t>* key_data);

	/**
		Constructs the object with existing key data in hex string form.

		@param[key_data_as_hex] A hex string of 32 characters containing key data.
	*/
	AES128Key(std::string key_data_as_hex);

	/**
		An overload of the [] operator allow convenient access to key data.

		@return Returns the byte of key data at the requested reference.
	*/
	uint8_t& operator[](int x) const;

	/**
		Converts the key data to a hex string

		@return A hex string of the key data 32 characters in length.
	*/
	std::string toHexString() const;
protected:
	/**
		This function converts a single hex character into decimal form.

		@param[in] input A single hexadecimal character
		@return The 0-15 integer the hex input represents
	*/
	uint8_t char2int(char input) const;

	vector<uint8_t> *m_key_data;
};

#endif