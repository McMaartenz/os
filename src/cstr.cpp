#include "cstr.h"

uint8_t str_length(const char* string)
{
	for (uint8_t i = 0; i < 256; i++)
	{
		if (string[i] == 0)
		{
			return i;
		}
	}
	return 255; // Overflow
}

char output[128];
const char* to_s(uint64_t value)
{
	uint8_t size = 0;
	uint64_t size_test = value;
	while (size_test / 10 > 0)
	{
		size_test /= 10;
		size++;
	}
	
	uint8_t i = 0;
	while (value / 10 > 0)
	{
		output[size - i] = (value % 10) + '0';
		value /= 10;
		i++;
	}
	
	output[size - i] = (value % 10) + '0';
	output[size + 1] = 0;
	return output;
}

const char* to_s(int64_t value)
{
	uint8_t is_negative = 0;

	if (value < 0)
	{
		is_negative = 1;
		value *= -1;
		output[0] = '-';
	}

	uint8_t size = 0;
	uint64_t size_test = value;
	while (size_test / 10 > 0)
	{
		size_test /= 10;
		size++;
	}
	
	uint8_t i = 0;
	while (value / 10 > 0)
	{
		output[is_negative + size - i] = (value % 10) + '0';
		value /= 10;
		i++;
	}
	
	output[is_negative + size - i] = (value % 10) + '0';
	output[is_negative + size + 1] = 0;
	return output;
}

const char* to_s(double value, int8_t decimals)
{
	char* int_ptr = (char*)to_s((int64_t)value);
	char* double_ptr = output;
	
	if (decimals > 20)
	{
		decimals = 20;
	}

	if (value < 0)
	{
		value *= -1;
	}

	while (*int_ptr != 0)
	{
		*double_ptr = *int_ptr;
		int_ptr++;
		double_ptr++;
	}

	*double_ptr = '.';
	double_ptr++;

	double new_value = value - (int)value;

	for (uint8_t i = 0; i < decimals; i++)
	{
		new_value *= 10;
		*double_ptr = (int)new_value + '0';
		new_value -= (int)new_value;
		double_ptr++;
	}

	*double_ptr = 0;
	return output;
}

const char* to_s(float value, int8_t decimals)
{
	char* int_ptr = (char*)to_s((int64_t)value);
	char* double_ptr = output;
	
	if (decimals > 20)
	{
		decimals = 20;
	}

	if (value < 0)
	{
		value *= -1;
	}

	while (*int_ptr != 0)
	{
		*double_ptr = *int_ptr;
		int_ptr++;
		double_ptr++;
	}

	*double_ptr = '.';
	double_ptr++;

	float new_value = value - (int)value;

	for (uint8_t i = 0; i < decimals; i++)
	{
		new_value *= 10;
		*double_ptr = (int)new_value + '0';
		new_value -= (int)new_value;
		double_ptr++;
	}

	*double_ptr = 0;
	return output;
}


const char* to_hs(uint64_t value)
{
	uint64_t* value_ptr = &value;
	uint8_t* ptr;
	uint8_t tmp;
	uint8_t size = 15; // 8 * 2 - 1

	for (uint8_t i = 0; i < size; i++)
	{
		ptr = ((uint8_t*)value_ptr + i);
		tmp = ((*ptr & 0xF0) >> 4);
		output[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 55 : '0');
		tmp = ((*ptr & 0x0F));
		output[size - (i * 2)] = tmp + (tmp > 9 ? 55 : '0');
	}

	output[size + 1] = 0;
	return output;
}


const char* to_hs(uint32_t value)
{
	uint32_t* value_ptr = &value;
	uint8_t* ptr;
	uint8_t tmp;
	uint8_t size = 7;

	for (uint8_t i = 0; i < size; i++)
	{
		ptr = ((uint8_t*)value_ptr + i);
		tmp = ((*ptr & 0xF0) >> 4);
		output[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 55 : '0');
		tmp = ((*ptr & 0x0F));
		output[size - (i * 2)] = tmp + (tmp > 9 ? 55 : '0');
	}

	output[size + 1] = 0;
	return output;
}


const char* to_hs(uint16_t value)
{
	uint16_t* value_ptr = &value;
	uint8_t* ptr;
	uint8_t tmp;
	uint8_t size = 3;

	for (uint8_t i = 0; i < size; i++)
	{
		ptr = ((uint8_t*)value_ptr + i);
		tmp = ((*ptr & 0xF0) >> 4);
		output[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 55 : '0');
		tmp = ((*ptr & 0x0F));
		output[size - (i * 2)] = tmp + (tmp > 9 ? 55 : '0');
	}

	output[size + 1] = 0;
	return output;
}


const char* to_hs(uint8_t value)
{
	uint8_t* value_ptr = &value;
	uint8_t* ptr;
	uint8_t tmp;
	uint8_t size = 1;

	for (uint8_t i = 0; i < size; i++)
	{
		ptr = ((uint8_t*)value_ptr + i);
		tmp = ((*ptr & 0xF0) >> 4);
		output[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 55 : '0');
		tmp = ((*ptr & 0x0F));
		output[size - (i * 2)] = tmp + (tmp > 9 ? 55 : '0');
	}

	output[size + 1] = 0;
	return output;
}
