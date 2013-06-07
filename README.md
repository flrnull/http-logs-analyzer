Http Logs Analyzer
=====

Usage
-----

```shell
./http-logs-analyzer -f ./example/access_log
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