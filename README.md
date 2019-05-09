# key-value store

* key-vaue store that you can telnet into
* supports text-based network protocol for getting and setting keys
* plaintext protocol

## run it

in `/src` run `make`

`./server` to run server

`telnet localhost 8888`

## features

* [ ] LRU
* [ ] namespaces
* [ ] key being data structure (list, set)
* [ ] persistence to disk
* [ ] client library in python that talks to it over the network
* [ ] webserver

design protocol

* [x] get key
* [x] set key
* [x] delete key
* [x] list keys
* [x] get key in namespace
* [x] set key in namespace
* [x] delete key in namespace
* [x] list keys in namespace
* [ ] set namespace
* [ ] clear namespace
* [ ] delete namespace
* [ ] list namespaces
