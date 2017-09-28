#pragma once
#include <stdexcept>
#include <unordered_map>

#define FILE_NAME "fileName"
#define MTX_BUILD_TYPE "mtx_build_type"

class Parameters
{
  private:
	std::unordered_map<std::string, std::string> parameters;

  public:
	template <typename T>
	void add(std::string key, T value);

	template <typename T>
	T get(std::string key)
	{
		if (parameters.find(key) == parameters.end())
			throw runtime_error(key + " is unset");
		istringstream read(parameters[key]);
		T value;
		read >> value;
		return value;
	}

	template <typename T>
	T get(std::string key, T defaultValue)
	{
		if (parameters.find(key) == parameters.end())
			return defaultValue;
		istringstream read(parameters[key]);
		T value;
		read >> value;
		return value;
	}
};

template <>
inline void Parameters::add<const char *>(std::string key, const char *value)
{
	parameters[key] = std::string(value);
}

template <>
inline void Parameters::add<std::string>(std::string key, std::string value)
{
	parameters[key] = value;
}

template <typename T>
inline void Parameters::add(std::string key, T value)
{
	parameters[key] = std::to_string(value);
}