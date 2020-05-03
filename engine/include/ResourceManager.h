#pragma once
#include "include/Core.h"

class Resource;

class ResourceManager
{
	ResourceManager();
public:
	enum Type
	{
		PNG = 10,
		JPG,
		GOBJECT,
		PMAP,
		MP3,
		UNDEFINED = 1337
	};

	~ResourceManager();

	Resource * GetResource(const string & name, Type type);
	Resource * GetResource(const string & src);
	string GetType(Type type);

	Resource * CreateResourceFile(const string & dir, const string & name, Type tp);
	
	static ResourceManager * instance();
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
	const string GetDir() { return m_dir; }
	const string GetName() { return m_resName; }
	ResourceManager::Type GetType() { return m_type; }
private:
	string						m_path;
	string						m_dir;
	string						m_resName;
	ResourceManager::Type		m_type;
};