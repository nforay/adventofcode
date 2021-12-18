#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

long long read_packet_data(std::vector<bool>::iterator &it, int &len, int subpacket);

long					hex_to_dec(const char &c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	else
		return (0);
}

int						get_n_bits(std::vector<bool>::iterator &it, int n, int &len)
{
	int	ret = 0;

	while (n-- && len) {
		std::cerr << *it;
		ret += (*it++ << n);
		len--;
	}
	return (ret);
}

std::vector<long long>	read_sub_packet(std::vector<bool>::iterator &it, int &len, int subpacket, int &id)
{
	std::vector<long long> values;
	if (id) {
		std::cerr << std::string(subpacket, '\t') << "Number of subpackets (";
		int subpackets = get_n_bits(it, 11, len);
		std::cerr << ") = " << subpackets << std::endl;
		while (subpackets--)
			values.push_back(read_packet_data(it, len, subpacket + 1));
	} else {
		std::cerr << std::string(subpacket, '\t') << "Subpackets length (";
		int length = get_n_bits(it, 15, len);
		std::cerr << ") = " << length << std::endl;
		len -= length;
		while (length > 0) {
			values.push_back(read_packet_data(it, length, subpacket + 1));
			std::cerr << std::string(subpacket, '\t') << "Length remaining: " << length << std::endl;
		}
	}
	return (values);
}

long long			 	read_packet_data(std::vector<bool>::iterator &it, int &len, int subpacket)
{
	std::cerr << std::string(subpacket, '\t') << "Version (";
	int version = get_n_bits(it, 3, len);
	std::cerr << ") = " << version << std::endl;
	std::cerr << std::string(subpacket, '\t') << "Type (";
	int type = get_n_bits(it, 3, len);
	std::cerr << ") = " << type << std::endl;
	long long value = 0;
	int id = 0;
	int groups = 0;
	std::vector<long long> values;
	if (type != 4) {
		std::cerr << std::string(subpacket, '\t') << "Type ID (";
		id = get_n_bits(it, 1, len);
		std::cerr << ") = " << id << std::endl;
	}
	switch (type) {
		case 0:						// Sum packets
			values = read_sub_packet(it, len, subpacket, id);
			for (auto &v : values)
				value += v;
			break;
		case 1:						// product packets
			value = 1;
			values = read_sub_packet(it, len, subpacket, id);
			for (auto &v : values)
				value *= v;
			break;
		case 2:						// minimum packets
			value = std::numeric_limits<long long>::max();
			values = read_sub_packet(it, len, subpacket, id);
			for (auto &v : values)
				value = std::min(value, v);
			break;
		case 3:						// maximum packets
			value = std::numeric_limits<long long>::min();
			values = read_sub_packet(it, len, subpacket, id);
			for (auto &v : values)
				value = std::max(value, v);
			break;
		case 4:						// Literal value
			while (42) {
				std::cerr << std::string(subpacket, '\t') << "Next 5 bits start with ";
				int next = get_n_bits(it, 1, len);
				std::cerr << (next ? " not last group (" : " last group (");
				if (!subpacket)
					groups++;
				value = (value << 4) ^ get_n_bits(it, 4, len);
				std::cerr << ") = " << value << std::endl;
				if (!next)
					goto exit_loop;
			}
			exit_loop: ;
			if (groups) {
				std::cerr << "ignore padding... (";
				get_n_bits(it, groups, len);
				std::cerr << ")" << std::endl;
			}
			std::cerr << std::string(subpacket, '\t') << "Value: " << value << std::endl;
			break;
		case 5:						// Greater than packets
			values = read_sub_packet(it, len, subpacket, id);
			value = values[0] > values[1];
			break;
		case 6:						// Less than packets
			values = read_sub_packet(it, len, subpacket, id);
			value = values[0] < values[1];
			break;
		default:					// Equal to packets
			values = read_sub_packet(it, len, subpacket, id);
			value = values[0] == values[1];
			break;
	}
	return (value);
}

int						main()
{
	std::string	str;
	int			len;
	long long	value = 0;

	while (std::getline(std::cin, str)) {
		std::vector<bool>	packet;
		std::cerr << "\nInput:\t\t" << str << "\nBitfield:\t";
		len = str.size() * 4;
		packet.reserve(len);
		for (auto &c : str)
			for (int i = 3; i >= 0; i--)
				packet.push_back((hex_to_dec(c) >> i) & 1);
		for (const auto &bit : packet)
			std::cerr << bit;
		std::cerr << std::endl;
		std::vector<bool>::iterator	it = packet.begin();
		value = read_packet_data(it, len, 0);
		std::cout << "Answer: " << value << std::endl;
	}
	return (0);
}