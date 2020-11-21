#include <vcpkg/versions.h>

namespace vcpkg::Versions
{
    std::size_t VersionSpecHasher::operator()(const VersionSpec& key) const
    {
        using std::hash;
        using std::size_t;
        using std::string;

        return (hash<string>()(key.name) ^ (hash<string>()(key.version.value)) ^ hash<int>()(key.version.port_version));
    }
}