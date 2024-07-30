Logging.js
----------

Stream based logging module for nodejs/iojs.

Installation
------------

```js
npm install logging.js
```

Example
-------

```js
var logging = require('logging.js'),
  log = logging.get('mylogger');

log.addRule({name: 'stdout', stream: process.stdout});
log.info('logging from %(from)s to %(to)s', {from: 'mylogger', to: 'stdout'})
// => 2015-04-25 14-28-58,548 info mylogger[8274]: logging from mylogger to stdout
```

Logging Levels
--------------

There are 5 levels available as:

```js
logging.DEBUG
logging.INFO
logging.WARN  // alias `logging.WARNING`
logging.ERROR
logging.CRITICAL
```

Global Registry
---------------

In a single node process, `logging.get('mylogger')` will always return the same logger object,
because all loggers are registered in a global registry after they are created.

```js
logging.get('name') === logging.get('name');  // true
```

Propagate
---------

When we create a new logger by `name`, if there is
a `fatherLogger` which enables propagate and its name is a long
enough prefix of `name`, the new logger will propagate rules
from `fatherLogger`:

```js
var fatherLogger = logging.get('app');
var childLogger = logging.get('app.module');
```

API Refs
--------

### logging.get(name)

Get a logger from global registry, if the logger dose not exist, create one and return it.

```js
var log = logging.get('mylogger');
```

### log.addRule(rule)

A logging rule is an object like:

```js
{
  name: 'stdout',            // a rule has a name, required
  stream: process.stdout,    // a writable stream, required
  level: logging.INFO,       // logging level, default: logging.INFO
  formatter: '...',          // formatter, string or function (optional)
  levelCmp: logging.LEVEL_GE // do logging only if current message level greater than rule's level
}
```

If no rules were added when logging, `process.stderr` will be used.

### log.removeRule(name)

Remove a rule from logger by name.

### log.getRule(name)

Get a rule from logger by name.

### log.setPropagate(bool)

Enable/Disable this logger to be a `father`in the future (the `Logger` constructor sets
`log.propagate = true`).

### log.debug/info..

```js
log.debug(fmt, ...)
log.info(fmt, ...)
log.warn(fmt, ...)  // alias log.warning(fmt, ...)
log.error(fmt, ...)
log.critical(fmt, ...)
```

Formatter
----------

A formatter can be a string or a function like `function(record) {..}`.

- For string case, an example:

   ```js
   '%(asctime)s %(levelname)s %(name)s[%(pid)s]: %(message)s'
   ```

   And all available named attributes for a `log record`:

   ```
   name       logger name
   level      record level (number)
   levelName  record level (string)
   levelname  record level (string, lowercase)
   fmt        record formatter string
   args       record arguments
   message    record message (fmt % args)
   pid        process id
   created    the datetime when this record created
   asctime    human readable time string, e.g. '2003-07-08 16:49:45,896'
   ```

- For function case, it should like `function(record) {return string}`

Message Formatting
-------------------

Logging enables 2 handy string formatting types:

```js
log.info('%s %d', 'val', 1) // 'val 1'
log.info('%(key1)s %(key2)d', {key1: 'abc', key2: 123}) // 'abc 123'
```

File Stream Example
--------------------

We can add multiple rules (or say streams) to a logger, here is
an example for file stream:

```js
var fs = require('fs');
var log = logging.get('myapp');

log.addRule({name: 'file', stream:
  fs.createWriteStream('myapp.log', {flags: 'a'})});

log.info('logging from the maginc world');
```

Logging to Different Files By Level
-----------------------------------

For example, we want to log messages to 3 files by level: `error.log`, `warning.log` and `all.log`:

```js
var fs = require('fs');
var log = logging.get('myapp');

log.addRule({name: 'all',
  stream: fs.createWriteStream('all.log', {flags: 'a'})});

log.addRule({name: 'error', level: logging.ERROR, levelCmp: logging.LEVEL_EQ,
  stream: fs.createWriteStream('error.log', {flags: 'a'})});

log.addRule({name: 'warning', level: logging.WARNING, levelCmp: logging.LEVEL_EQ,
  stream: fs.createWriteStream('warning.log', {flags: 'a'})});
```

License
-------

MIT. (c) Chao Wang <hit9@icloud.com>
