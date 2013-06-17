#ifndef PATTERNS_H
#define	PATTERNS_H

#define IP_PATTERN "^([0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+)"
#define AGENT_PATTERN "\" \"([^\"]+)\""
#define URL_PATTERN "\"[a-zA-Z]+T (/[^\"]+) HTTP"
#define TRAFFIC_PATTERN "HTTP/[0-9]\\.[0-9]\" [0-9][0-9][0-9]? ([0-9]+)[0-9 ]*\""
#define REF_PATTERN "\"[^\"]+\"([^\"]+)\" \""

#define GOOGLE_PATTERN "(Googlebot)"
#define BING_PATTERN "(msnbot)"
#define BAIDU_PATTERN "(Baiduspider)"
#define YANDEX_PATTERN "(YandexBot)"

#endif	/* PATTERNS_H */

