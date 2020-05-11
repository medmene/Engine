#include "include/ResourceManager.h"
#include <fstream>


using namespace std::filesystem;


ResourceManager * ResourceManager::sm_instance = nullptr;

// ----------------------------------------------------------------------------------------- //

Resource* Resource::FindResource(const string& resource, ResourceManager::Type type)
{
	if (!resource.empty())
	{
		// At first find resource dir
		auto path = current_path().generic_string() + "/../../";
		bool finded = false;
		for (auto && p : recursive_directory_iterator(path.c_str()))
		{
			auto resPath = p.path().generic_string();

			if (resPath.find("resources") != string::npos)
			{
				path = resPath;
				finded = true;
				break;
			}
		}
		
		if (finded)
		{
			string typeName = ResourceManager::instance()->GetType(type);
			string resName = resource + typeName;

			for (auto && p : recursive_directory_iterator(path.c_str()))
			{
				auto resPath = p.path().generic_string();

				if (resPath.find(resName) != string::npos)
				{
					Resource * res = new Resource(resPath, resource, type);
					return res;
				}
			}
		}
	}
	return nullptr;
}

Resource::Resource()
	: m_resName("")
	, m_type(ResourceManager::UNDEFINED)
	, m_path("")
{
}

Resource::Resource(const string & path, const string & name, ResourceManager::Type type)
	: m_type(type)
	, m_path(path)
	, m_resName(name)
{
	m_dir = m_path.substr(0, m_path.find(m_resName));
}

// ----------------------------------------------------------------------------------------- //

ResourceManager::ResourceManager()
{
	RegisterTypes();
}

ResourceManager::~ResourceManager()
{
	for (auto && res : m_resources)
	{
		delete res;
	}
	
	m_resources.clear();
}

Resource* ResourceManager::GetResource(const string& name, Type type)
{
	auto it = m_resources.begin();
	
	for (; it != m_resources.end(); ++it)
	{
		if ((*it)->GetType() == type && (*it)->GetName() == name)
		{
			return (*it);
		}
	}

	if (it == m_resources.end())
	{
		Resource * res = Resource::FindResource(name, type);
		if (res)
		{
			m_resources.emplace_back(res);
			return res;
		}
	}
	
	return nullptr;
}

Resource* ResourceManager::GetResource(const string& src)
{
	auto pos = src.find('.');

	if (pos != string::npos)
	{
		string type = src.substr(pos);
		string name = src.substr(0, pos);
		
		for (auto && typeName : m_types)
		{
			if (typeName.second == type)
			{
				return GetResource(name, (Type)typeName.first);
			}
		}
	}
	return nullptr;
}

string ResourceManager::GetType(Type type)
{
	auto it = m_types.find(type);
	
	if (it != m_types.end())
	{
		return it->second;
	}
	
	return "";
}

Resource* ResourceManager::CreateResourceFile(const string& dir, const string& name, Type tp)
{
	std::ofstream out;
	out.open(dir + name + m_types[tp]);
	if (out.is_open())
	{
		out << "<?xml version=\"1.0\"?>\n";
		out << "<object>\n";
		out << "</object>\n";
		out.close();
		Resource * res = new Resource(dir + name + m_types[tp], name, tp);
		m_resources.emplace_back(res);
		return res;
	}
	return nullptr;
}

ResourceManager* ResourceManager::instance()
{
	if (!sm_instance)
	{
		sm_instance = new ResourceManager();
	}
	return sm_instance;
}

void ResourceManager::RegisterTypes()
{
	m_types.emplace(std::pair<int, string>(PNG, ".png"));
	m_types.emplace(std::pair<int, string>(JPG, ".jpg"));
	m_types.emplace(std::pair<int, string>(GOBJECT, ".gobj"));
	m_types.emplace(std::pair<int, string>(PMAP, ".pmap"));
	m_types.emplace(std::pair<int, string>(MP3, ".mp3"));
	m_types.emplace(std::pair<int, string>(TTF, ".ttf"));
}
