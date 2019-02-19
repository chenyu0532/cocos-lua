#ifndef __XDEF_H__
#define __XDEF_H__

#include <string.h>
#include <stdio.h>

#include <stdint.h>

#define NS_XGAME_BEGIN  namespace xgame {
#define NS_XGAME_END    }
#define USING_NS_XGAME using namespace xgame
#define USING_NS_CC_EXP using namespace cocos2d::experimental

#define strequal(str1, str2)           (strcmp(str1, str2) == 0)
#define strnequal(str1, str2, len)     (strncmp(str1, str2, len) == 0)

#ifdef _WIN32
#define strcaseequal(str1, str2) (_stricmp(str1, str2) == 0)
#define strncaseequal(str1, str2, len) (_strnicmp(str1, str2) == 0)
#else
#define strcaseequal(str1, str2)       (strcasecmp(str1, str2) == 0)
#define strncaseequal(str1, str2, len) (strncasecmp(str1, str2) == 0)
#endif

#define CONF_ANTIALIAS_ENABLED "conf.antialias.enabled"
#define CONF_ANTIALIAS_SAMPLES "conf.antialias.samples"

inline uint64_t strtov(const char *version)
{
    uint64_t v1, v2, v3;
    if (sscanf(version, "%lld.%lld.%lld", &v1, &v2, &v3) == 3)
    {
        return v1 * 1000000 + v2 * 1000 + v3;
    }
    else
    {
        return 0;
    }
}

inline int versioncmp(const char *vstr1, const char *vstr2)
{
    uint64_t v1 = strtov(vstr1);
    uint64_t v2 = strtov(vstr2);
    return v1 == v2 ? 0 : (v1 < v2 ? -1 : 1);
}

inline bool strstartwith(const char *src, const char *prefix)
{
    const char *pos = strstr(src, prefix);
    return pos == src;
}

inline bool strendwith(const char *src, const char *suffix)
{
    const char *pos = strstr(src, suffix);
    return !pos ? false : (src + strlen(src) == pos + strlen(suffix));
}

#endif