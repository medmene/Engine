#pragma once
#include "include/Core.h"

class Resource;

class ResourceManager
{
public:
	enum Type
	{
		PNG = 10,
		JPG,
		GOBJECT,
		UNDEFINED = 1337
	};

	ResourceManager();
	~ResourceManager();

	Resource * GetResource(const string & name, Type type);
	Resource * GetResource(const string & src);
	const string & GetType(Type type);

	static ResourceManager * instance() { return sm_instance; }
private:
	vector<Resource *>					m_resources;
	map<int, string>					m_types;
	static ResourceManager			  * sm_instance;

	void RegisterTypes();
};


class Resource
{
public:
	static Resource * FindResource(const string & resource, ResourceManager::Type type);
	
	Resource();
	Resource(const string & path, const string & name, ResourceManager::Type type);
	const string GetPath() { return m_path; }
	const string GetName() { return m_resName; }
	ResourceManager::Type GetType() { return m_type; }
private:
	string						m_path;
	string						m_resName;
	ResourceManager::Type		m_type;
};