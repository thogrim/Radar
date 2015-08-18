#pragma once

#include <map>
#include <string>
#include <memory>
#include <cassert>

template<typename Resource>
class ResourceHolder
{
private:
	std::map<std::string, std::unique_ptr<Resource>> resourceHolder_;
public:
	ResourceHolder();
	~ResourceHolder();

	void load(const std::string& key, const std::string& filename);
	const Resource& get(const std::string& key) const;
	Resource& get(const std::string& key); //non-const version - not sure if needed
};

template<typename Resource>
ResourceHolder<Resource>::ResourceHolder()
	:resourceHolder_(){
}

template<typename Resource>
ResourceHolder<Resource>::~ResourceHolder(){
}

template<typename Resource>
void ResourceHolder<Resource>::load(const std::string& key, const std::string& filename){
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename)){
		throw std::runtime_error("ResourceHolder failed to load resource: " + key + " from file: " + filename);
	}
	auto inserted = resourceHolder_.insert(std::make_pair(key, std::move(resource)));
	assert(inserted.second);
}

template<typename Resource>
const Resource& ResourceHolder<Resource>::get(const std::string& key) const{
	auto found = resourceHolder_.find(key);
	assert(found != resourceHolder_.end());
	return *found->second;
}

template<typename Resource>
Resource& ResourceHolder<Resource>::get(const std::string& key){
	auto found = resourceHolder_.find(key);
	assert(found != resourceHolder_.end());
	return *found->second;
}