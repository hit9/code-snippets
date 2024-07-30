Promisify.js
============

Promisify module for node.js/io.js.

Native Promise will be used by default, to use custom
Promise implementations, e.g.

```js
global.Promise = require('bluebird').Promise;
```

Install
-------

```
npm install promisify.js
```

Example
-------

See [example.js](example.js).

License
-------

MIT. (c) 2015 Chao Wang <hit9@icloud.com>.
