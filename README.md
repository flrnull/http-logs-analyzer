Http Logs Analyzer
==================

Usage
-----

```shell
# Default usage with Patterns.h
./http-logs-analyzer -f ./example/access_log
# Specify own IP pattern
./http-logs-analyzer -f ./example/access_log -i "^([0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+)"
# List of all possible params
./http-logs-analyzer -h
```

Output
------

```shell
{
  views: 16,
  visitors: 5,
  urls: 5,
  traffic: 187990,
  lines: 24,
  fails: 8,
  crawlers: {
      Google: 2,
      Bing: 0,
      Baidu: 0,
      Yandex: 0
  },
  topUrls: {
      '/app/engine/api.php' : 4,
      '/app/modules/randomgallery.php' : 4,
      '/chat.php?id=a65' : 4,
      '/chat.php' : 2,
      '/mod.php' : 2
  },
  topRefs: {
      'http://lag.ru/index.php' : 12,
      'http://bim-bom.ru/' : 2,
      'http://wiki.org/index.php#lang=en' : 2
  }
}
```

Install
-------

```shell
git clone git://github.com/flrnull/http-logs-analyzer.git
cd http-logs-analyzer
make
cp dist/Release/http-logs-analyzer /usr/local/bin
```

License
-------

MIT
