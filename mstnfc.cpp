#include "mstnfc.h"

bool MSTNFC::init()
{
	nfc_connstring devices[1];
	nfc_context *context;

    nfc_init (&context);

	if(nfc_list_devices (context, devices, 1) == 0)
	{
		std::cout << "Error no NFC devices found..." << std::endl;
		return false;
	}

	m_nfc_device = nfc_open (context, devices[0]);

	if(m_nfc_device == NULL)
	{
		std::cout << "Error unable to open NFC device" << std::endl;
		return false;
	}
}

bool MSTNFC::createApplication(uint32_t aid)
{
	if(!isCardPresent() || (m_nfc_tag == NULL))
	{
		return false;
	}

	MifareDESFireAID temp_aid = mifare_desfire_aid_new(aid);

	if(mifare_desfire_create_application_aes(m_nfc_tag, temp_aid, 0x0F, 3) != OPERATION_OK)
	{
		std::cout << "Unable to create application" << std::endl;
		return false;
	}

	return true;
}

std::vector<uint32_t>* MSTNFC::listApplications() const
{
	//Not implemented
	return NULL;
}

bool MSTNFC::containsApplication(uint32_t aid) const
{
	MifareDESFireAID temp_aid = mifare_desfire_aid_new(aid);

	if(mifare_desfire_select_application(temp_id) == OPERATION_OK)
	{
		return true;
	}
	return false;
}

std::string MSTNFC::getUID() const
{
	char* temp_uid = freefare_get_tag_uid(m_nfc_tag);
	std::string uid = std::string(temp_uid);

	return uid;
}

bool MSTNFC::isCardPresent() const
{
	if(m_nfc_tag != NULL)
	{
		//Not a good way to do this, only checks if any card is present not one pointed
		//to by m_nfc_tag
		if(nfc_initiator_target_is_present(m_nfc_device, NULL) == OPERATION_OK)
		{
			return true;
		}
	}
	return false;
}

bool MSTNFC::scanForCards() const
{
	FreefareTag *tags = NULL;
	tags = freefare_get_tags(m_nfc_device);

	if(tags == NULL)
	{
		cout << "Error getting tags..." << endl;
		return;
	}

	for(int i = 0;tags[i];i++)
	{
		if (MIFARE_DESFIRE != freefare_get_tag_type (tags[i]))
		{
			continue;
		}

		//Attempt to copy tag before libfreefare destroys it
		FreefareTag* temp;
		*temp = *tags[i];

		m_nfc_tag = temp;
		break;
	}

	freefare_free_tags(tags);
}

bool MSTNFC::authenticate(AES128Key* key, uint32_t aid) const
{
	MifareDESFireAID temp_aid = mifare_desfire_aid_new(aid);

	MifareDESFireKey temp_key = mifare_desfire_aes_key_new(key->toArray());

	mifare_desfire_select_application(m_nfc_tag, temp_aid);
	int auth = mifare_desfire_authenticate(m_nfc_tag, 0, temp_key);
	return (auth>=0);
}

std::vector<AES128Key>* MSTNFC::generateKeys(AES128Key* old_key_data, uint32_t aid)
{
	std::cout << "Function not yet implemented..." << std::endl;

	return NULL;
}