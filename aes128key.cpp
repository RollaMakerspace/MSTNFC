#include "aes128key.h"


AES128Key::AES128Key(std::vector<uint8_t>* key_data)
{
	m_key_data = key_data;
}

AES128Key::AES128Key(std::string key_data_as_hex)
{
	if(key_data_as_hex.length() != 32)
	{
		std::cout << "Key string length not 32" << std::endl;
		return;
	}

	for(int i = 0;i < 32;i++)
	{
		std::vector<uint8_t>* key_data = new std::vector<uint8_t>(32);
		key_data->push_back(char2int(key_data_as_hex[i]));
	}
}

uint8_t& AES128Key::operator[](int x) const
{
	uint8_t out = 0;
	if((x >= 0) && (x < 32))
	{
		out = m_key_data[x];
		return out;
		//return m_key_data[x];
	}
	return out;
}

std::string AES128Key::toHexString() const
{
	std::ostringstream ss;
	ss << std::hex << std::uppercase << std::setfill( '0' );

	std::for_each(m_key_data->cbegin(), m_key_data->cend(), [&]( int c ) { ss << std::setw( 2 ) << c; } );
	std::string result = ss.str();

	return result;
}

uint8_t AES128Key::char2int(char input) const
{
  if(input >= '0' && input <= '9')
    return input - '0';
  if(input >= 'A' && input <= 'F')
    return input - 'A' + 10;
  if(input >= 'a' && input <= 'f')
    return input - 'a' + 10;
  throw std::invalid_argument("Invalid input string");
}

uint8_t* AES128Key::toArray() const
{
	return &m_key_data[0];
}