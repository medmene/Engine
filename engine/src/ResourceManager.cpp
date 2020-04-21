#include "include/ResourceManager.h"

using namespace std::filesystem;


ResourceManager * ResourceManager::sm_instance = new ResourceManager();

Resource* Resource::FindResource(const string& resource, ResourceManager::Type type)
{
	if (!resource.empty())
	{
		auto path = current_path().generic_string() + "/../resources/";
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
}

ResourceManager::ResourceManager()
{
	RegisterTypes();
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

const string& ResourceManager::GetType(Type type)
{
	auto it = m_types.find(type);
	
	if (it != m_types.end())
	{
		return it->second;
	}
	
	return "";
}

void ResourceManager::RegisterTypes()
{
	m_types.emplace(std::pair<int, string>(PNG, ".png"));
	m_types.emplace(std::pair<int, string>(JPG, ".jpg"));
}
