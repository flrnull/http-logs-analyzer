Http Logs Analyzer
=====

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
  visitors: 3,
  urls: 5,
  traffic: 93995,
  lines: 12,
  fails: 4,
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