#pragma region Copyright (c) 2014-2018 OpenRCT2 Developers
/*****************************************************************************
 * OpenRCT2, an open source clone of Roller Coaster Tycoon 2.
 *
 * OpenRCT2 is the work of many authors, a full list can be found in contributors.md
 * For more information, visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * A full copy of the GNU General Public License can be found in licence.txt
 *****************************************************************************/
#pragma endregion

#pragma once

#include <stdexcept>
#include <string>
#include <jansson.h>

#include "../common.h"

namespace Json
{
    // Don't try to load JSON files that exceed 64 MiB
    constexpr uint64 MAX_JSON_SIZE = 64 * 1024 * 1024;

    json_t * ReadFromFile(const utf8 * path, size_t maxSize = MAX_JSON_SIZE);
    void     WriteToFile(const utf8 * path, const json_t * json, size_t flags = 0);

    json_t * FromString(const std::string & raw);
}

class JsonException final : public std::runtime_error
{
private:
    json_error_t _jsonError = {};

public:
    explicit JsonException(const std::string &message) : std::runtime_error(message) { }

    explicit JsonException(const json_error_t * jsonError) : JsonException(std::string(jsonError->text))
    {
        _jsonError = *jsonError;
    }
};
