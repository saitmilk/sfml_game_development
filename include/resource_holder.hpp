#ifndef RESOURCE_HOLDER_HPP
#define RESOURCE_HOLDER_HPP

#include <cassert>
#include <map>
#include <memory>
#include <string>

namespace Textures {
enum class ID {
    Landscape,
    Airplane,
    Missile
};
}

template <typename Resource, typename Identifier>
class TextureHolder {
public:
    void load(Identifier id, const std::string& filename) {
        std::unique_ptr<Resource> resource(new Resource());
        if (!resource->loadFromFile(filename)) {
            throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
        }
        // If loading successful, insert resource to map
        insertResource(id, std::move(resource));
    };

    template <typename Parameter>
    void load(Identifier id, const std::string& filename, const Parameter& secondParam) {
        // Create and load resource
        std::unique_ptr<Resource> resource(new Resource());
        if (!resource->loadFromFile(filename, secondParam)) {
            throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
        }
        // If loading successful, insert resource to map
        insertResource(id, std::move(resource));
    }

    Resource& get(Identifier id) {
        return const_cast<Resource&>(as_const(*this).get(id));
    };

    const Resource& get(Identifier id) const {
        auto found = mResourceMap.find(id);
        return *found->second;
    };

private:
    template <typename Resource, typename Identifier>
    void insertResource(Identifier id, std::unique_ptr<Resource> resource) {
        // Insert and check success
        auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
        assert(inserted.second);
    }

private:
    std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};

#endif // !RESOURCE_HPP
