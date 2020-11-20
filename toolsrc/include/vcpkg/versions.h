#pragma once

#include <vcpkg/base/strings.h>

namespace vcpkg::Versions
{
    enum class Scheme
    {
        Relaxed,
        Semver,
        Date,
        String,
        Unknown
    };

    struct Version
    {
        std::string text;
        int port_version;

        Version() = default;
        Version(const std::string& text, int port_version);

        void to_string(std::string& out) const
        {
            Strings::append(out, text);
            if (port_version != 0) Strings::append(out, '#', port_version);
        }

        bool operator==(const Version& rhs) const { return text == rhs.text && port_version == rhs.port_version; }
        bool operator<(const Version& rhs) const
        {
            if (text != rhs.text) return text < rhs.text;
            if (port_version != rhs.port_version) return port_version < rhs.port_version;
            return false;
        }
        bool operator!=(const Version& rhs) const { return !(*this == rhs); }
    };

    struct VersionSpec
    {
        const std::string port_name;
        const Version version;
        const Scheme scheme;

        VersionSpec(const std::string& port_name, const Version& version, Scheme scheme);

        VersionSpec(const std::string& port_name, const std::string& version_string, int port_version, Scheme scheme);

        friend bool operator==(const VersionSpec& lhs, const VersionSpec& rhs);
        friend bool operator!=(const VersionSpec& lhs, const VersionSpec& rhs);
    };

    struct VersionSpecHasher
    {
        std::size_t operator()(const VersionSpec& key) const;
    };

    struct Constraint
    {
        enum class Type
        {
            None,
            Minimum,
            Exact
        };
    };
}
