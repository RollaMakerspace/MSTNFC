#ifndef MSTNFC_H
#define MSTNFC_H

extern "C" {
	#include "libnfc.h"
	#include "libfreefare.h"
}

#include <unistd.h>
#include <iostream>
#include <string>
#include "aes128key.h"

class MSTNFC {
public:
	MSTNFC();

	/**
		Initializes the NFC reader and prepares it to scan cards.
		@return Returns true if initialization occurred successfully otherwise false
	*/
	bool init();

	/**
		Attempts to create an application on the connected card.

		@param[aid] The Application ID stored in the last 3 bytes of the integer
			0x00XXXXXX as depicted by X's
		@return Returns true if success and false on an error.
	*/
	bool createApplication(uint32_t aid);

	/**
		Lists the applications currently on the card.

		@return A vector containing the application IDs on the card. Each value stores an
			AID in the last 3 bytes of an integer, 0x00XXXXXX demonstrated using X's. Returns
			null if failure.
	*/
	std::vector<uint32_t>* listApplications() const;

	/**
		Checks if the card contains a specific Application by ID.

		@param[aid] The application ID stored as the last 3 bytes of a integer, 0x00XXXXXX
			 demonstrated using X's.
		@return Returns true on sucess and false on failure.
	*/
	bool containsApplication(uint32_t aid) const;

	/**
		Attempt to get the UID of the connected card.

		@return A string of hex chars representing the UID. Returns null if failure.
	*/
	std::string getUID() const;

	/**
		Function returns status of connected card.

		@return Returns true if card is currently connected and false if not.
	*/
	bool isCardPresent() const;

	/**
		Initiates a scan for cards.

		@return Returns true if scan was finished successfully and false if there was an error.
	*/
	bool scanForCards() const;

	/**
		Attempts to authenticate to an application on connected card using an AES key.

		@param[key] An AES128Key object containing the key data for the master key for the AID.
		@param[aid] The application ID stored in the last 3 bytes of an integer 0x00XXXXXX like so.
		@return True on success and false on failure.
	*/
	bool authenticate(AES128Key* key, uint32_t aid) const;

	/**
		Generates three random keys and stores them in the specified applicaiton.

		@param[old_key_data] The key data for the old master key of the application.
		@param[aid] The application ID stored as the last 3 bytes of a integer, 0x00XXXXXX
			 demonstrated using X's.
		@return Returns the 3 keys as AES128Key objects stored in a vector<AES128Key>.
	*/
	std::vector<AES128Key>* generateKeys(AES128Key* old_key_data, uint32_t aid);
protected:
	nfc_device *m_nfc_device;
	FreefareTag* m_nfc_tag;
};

#endif