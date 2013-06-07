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
  views: 8,
  visitors: 4,
  urls: 5,
  traffic: 93995,
  lines: 12,
  fails: 4,
  crawlers: {
      Google: 1,
      Bing: 0,
      Baidu: 0,
      Yandex: 0
  },
  topUrls: {
      '/app/engine/api.php' : 2,
      '/app/modules/randomgallery.php' : 2,
      '/mod.php' : 1
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
