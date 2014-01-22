Http Logs Analyzer
==================

Parses ~ 2 000 000 lines per minute on Core i5. 

Usage
-----

```shell
http-logs-analyzer -f ./example/access_log
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
  },
  statusCodes: {
      '200' : 14,
      '301' : 2
  }
}
```

Advanced usage
-----

```shell
# You could specify you own format for RegExps, e.g. IP pattern
./http-logs-analyzer -f ./example/access_log -i "^([0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+)"
# List of all possible params
./http-logs-analyzer -h
```

Install
-------

```shell
git clone git://github.com/flrnull/http-logs-analyzer.git
cd http-logs-analyzer
make && make install
# Now you can use it
http-logs-analyzer -h
```

License
-------

MIT
